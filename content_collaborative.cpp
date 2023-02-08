#include<bits/stdc++.h>
using namespace std;

class User{
	public:
	int id;
	string genre1;
	string genre2;
	int number;
	User(int i,string g,string t,int n):id(i),genre1(g),genre2(t),number(n){
	}
	User(){
		id=0;
		number=0;
	}
	void display(){
		cout<<"User id: "<<id<<"\nMost watched Genre:  "<<genre1<<"\nSecond Most watched Genre: "<<genre2<<"\nNumber of movies watched/rated: "<<number<<endl;
	}
	void change(int i,string g,string t,int n){
		id=i;
		genre1=g;
		genre2=t;
		number=n;
	}
};
void make_user_file(){
	//this function was used to create a file of users containing just their id movies_watched and favourite genres
	ifstream fin("new_main_file.txt");
	//map data structure was used so that we can directly increment like this obj[genre]++
	map<string,int> obj;
	obj["comedy"]=0;
	obj["crime"]=0;
	obj["drama"]=0;
	obj["thriller"]=0;
	obj["romance"]=0;
	obj["musical"]=0;
	obj["war"]=0;
	obj["adventure"]=0;
	obj["film-noir"]=0;
	obj["sci-fi"]=0;
	obj["mystery"]=0;
	obj["children"]=0;
	obj["fantasy"]=0;
	obj["action"]=0;
	obj["documentry"]=0;
	obj["animation"]=0;
	obj["horror"]=0;
	obj["imax"]=0;
	obj["western"]=0;
	char buffer[256],ch;
	int number_of_movies=0,id,i=1000,compare,USER;
	priority_queue<pair<int,string> > pq;    //this was used so that we can get most watched genre and second most genre without looping
												//priority is based on int
	string temp,name,rating,string_id,genre,genre1,genre2;
	
	fin.getline(buffer,256,'\n');      //ignore the first line
	fin.getline(buffer,256,'\n');      //user1 data starts from here
	temp=buffer;
	number_of_movies++;
	temp=temp.substr(temp.find('~')+1,temp.length());
	string_id=temp.substr(0,temp.find('~'));
	USER=atoi(string_id.c_str());      
	compare=USER;
	genre=temp.substr(temp.rfind('~')+1,temp.length());   
	map<string, int>::iterator itr;// was created to loop thorugh in the map
    for (itr = obj.begin(); itr != obj.end(); ++itr) {
        if(genre.find(itr->first)!=string::npos){   //adding 1 to index "action'/"thriller" or whichever genre is in the movie
        												//genre string will be like this action|drama|thriller thats why find function is used
        	itr->second=itr->second+1;
		}
    }
    ofstream write_file("users_data.txt");
	i=259;
	pair<int,string> p1,p2;
	while(!fin.eof()){
		fin.getline(buffer,256,'\n');
		cout<<buffer<<endl;
		temp=buffer;
		temp=temp.substr(temp.find('~')+1,temp.length());
		string_id=temp.substr(0,temp.find('~'));
		USER=atoi(string_id.c_str());
		if(USER!=compare){    //if while reading the file movies watched by user1 or user1 data ends then prepare it to write in the file
			for (itr = obj.begin(); itr != obj.end(); ++itr) {
				pq.push(make_pair(itr->second,itr->first));//pushing the maps value in priority queue to get max and second max
    		}
    		p1=pq.top();
    		pq.pop();
    		p2=pq.top();     //now p1 and p2 contain max and second max genre
    		write_file<<compare<<"~"<<number_of_movies<<"~"<<p1.second<<"~"<<p2.second<<endl;
    		compare=USER;//update compare
    		number_of_movies=0;
    		pq=priority_queue<pair<int,string> > ();   //clearing the pq
    		for (itr = obj.begin(); itr != obj.end(); ++itr) {  //clearing the map
    		 	cout << '\t' << itr->first<< '\t' << itr->second << '\n';
				itr->second=0;
    		}
		}
		number_of_movies++;
		genre=temp.substr(temp.rfind('~')+1,temp.length());
    	for (itr = obj.begin(); itr != obj.end(); ++itr) {
        	if(genre.find(itr->first)!=string::npos){
        		itr->second=itr->second+1;
			}
    	}
	}
}

void users_bin(){
	//function to create a binary file of users because it is easier to jump data in binary files
	ifstream fin("users_data.txt");
	ofstream fout("users_data_bin.bin", ios::binary|ios::out);
	string str;
	while(!fin.eof()){
		getline(fin,str,'\n');
		fout<<str;
		fout<<"\n";
	}
}
void movies_bin(){
	ifstream fin("new_main_file.txt");
	ofstream fout("new_main_file_bin.bin", ios::binary|ios::out);
	string str;
	while(!fin.eof()){
		getline(fin,str,'\n');
		fout<<str;
		fout<<"\n";
	}
}


void make_file_binary(){
	//this function was used to create a utility file to search for users in the main 1.6gb file so
	//that we dont have to search the file sequentially for a particular user
	ofstream fout("search_utility_users.txt");
	ifstream fin("users_data_bin.bin",ios::binary);
	ifstream fin1("new_main_file_bin.bin",ios::binary);
	
	char buffer[300],buffer1[300],ch,ch1;
	long long i=100,for_small,for_long,ptr,ptr1;

	string str;
	fin>>for_small;
	fin.getline(buffer,256,'\n');
	fin1.getline(buffer1,256,'\n');
	fout<<1<<" "<<0<<" "<<0<<endl;  
	//after intervals of 100 we will write in the utility file because minimum we only have to search for 100 users sequentially          
	while(!fin.eof()){
		ptr=fin.tellg();
		fin>>for_small;
		getline(fin,str,'\n');
		if(for_small==i){    //time to write in the utility file 
			ptr1=fin1.tellg();
			while(for_long!=i&& (!fin1.eof())){     //now finding which exact position the particular users data is starting in the 1.6gb file
				ptr1=fin1.tellg();
				fin1.getline(buffer1,256,'\n');
				str=buffer1;
				str=str.substr(str.find('~')+1,str.length());
				str=str.substr(0,str.find('~'));
				for_long=atoi(str.c_str());
			}
			fout<<i<<" "<<ptr<<" "<<ptr1<<"\n";
			i=i+100;    
		}
	}
	
}

void content_based(int i){
	//function used to search movies on the basis of content based filtering
	ifstream fin("users_data_bin.bin",ios::binary);
	ifstream fin1("new_main_file_bin.bin",ios::binary);
	ifstream fin2("search_utility_users.txt");
	long long next,prev,next1,prev1,ptr,ptr1,user,user1;
	string temp,id,display,genre,genre1,number;
	char buffer[300];
	User u1;
	if(i<=162541){
		while(!fin2.eof()){
			prev=next;   //if while searching in the utility if next crosses the required id so for that we have a prev value stored
			fin2>>next;
			if(next>i||next==162500){    //if next crosses the user id or if user value>162500 an next crosses 162500 this means we have our 100 users interval in which we can search in the interval for our user 
				fin.seekg(ptr,ios::beg);    //move pointer to the file in users_data file to find its fav genre
				while(i!=user){          //while we didnt find users_data fin it in the file
					fin>>user;
					fin.getline(buffer,200,'\n');		
				}
				
				temp=buffer;   //if found then our users data will be in buffer like this   ~movies_watche~genre1~genre2
				temp[0]='@';    //ignoring the first char as it is always ~
				number=temp.substr(1,temp.find('~')-1);
				genre=temp.substr(temp.find('~')+1,temp.length());
				genre=genre.substr(0,genre.find('~'));
				genre1=temp.substr(temp.rfind('~')+1,temp.length());     //  breaking the string
				u1.change(user,genre,genre1,atoi(number.c_str()));
				u1.display();
				//now find the userid in the 1.6gb file so that we can suggest movies other than that user have watched
				fin1.seekg(ptr1,ios::beg);  //jump to the 100 interval mark directly instead of searching the whole file
				while(user!=user1){    //while user is not found read the line and break it
					fin1.getline(buffer,300,'\n');
					temp=buffer;
					display=buffer;
					temp=temp.substr(temp.find('~')+1,temp.length());
					id=temp.substr(0,temp.find('~'));
					user1=atoi(id.c_str());
				}
				
				
				vector<string> v1,v2;   //movies name will be stored in these vectors v1 will contain most favourite genres movie 
				for(int j=0;j<atoi(number.c_str());j++){    //loop till the users data i.e the number of movies watched =number of lines in big data
					if(display.find(genre)!=string::npos){     //if movie with favourite genre is read from the file store it in the vector
						temp=display.substr(0,display.rfind('~'));
						temp=temp.substr(0,temp.rfind('~'));
						temp=temp.substr(temp.rfind('~')+1,temp.length());
						v1.push_back(temp);
					}
					if(display.find(genre1)!=string::npos){  //if movie with 2nd best genre is read from file store it in v2
						temp=display.substr(0,display.rfind('~'));
						temp=temp.substr(0,temp.rfind('~'));
						temp=temp.substr(temp.rfind('~')+1,temp.length());
						v2.push_back(temp);
					}
					fin1.getline(buffer,300,'\n');
					display=buffer;
				}
				fin.close();
				fin2.close();
				//now opening the file of the top fav genres
				genre+=".txt";
				genre1+=".txt";
				fin.open(genre.c_str());
				fin2.open(genre1.c_str());
				int count=0;
				int j=0;
				cout<<"\n\t\tMovies recommended on the basis of your most watched genre\n\n";
				//display 5 movies from the genre list which are not watched by the user
				while(count<5){
					fin.getline(buffer,300,'\n');
					display=buffer;
					display=display.substr(0,display.find('~'));
					for(j=0;j<v1.size();j++){     //if movie read from the file is in the vector then break the loop and continue reading
						if(v1[j]==display){     
							break;
						}
					}
					if(j!=v1.size()){ //if the upper loop is not completed this means user have watched the movie so just continue
						continue;
					}
					count++;    //program will move here iff user have not watched the movie
					string buffer_temp,name_temp,rating_temp,genre_temp;
					buffer_temp=buffer;
					name_temp=buffer_temp.substr(0,buffer_temp.find('~'));
					rating_temp=buffer_temp.substr(buffer_temp.find('~')+1,buffer_temp.rfind('~'));
					rating_temp=rating_temp.substr(0,rating_temp.find('~'));
					genre_temp=buffer_temp.substr(buffer_temp.rfind('~')+1,buffer_temp.length());
					cout<<"Movie Name: "<<name_temp<<"\nRating: "<<rating_temp<<"\nGenre: "<<genre_temp<<endl;
					cout<<"--------------------------------------------------\n";
					v2.push_back(display);    //also push it in vector 2 so in below loop no duplicate movies are suggested
				}
				count=0;
				cout<<"\t\tMovies recommended on the basis of your Second most watched genre\n\n";
				while(count<5){
					fin2.getline(buffer,300,'\n');
					display=buffer;
					display=display.substr(0,display.find('~'));
					for(j=0;j<v2.size();j++){
						if(v2[j]==display){
							break;
						}
					}
					if(j!=v2.size()){
						continue;
					}
					count++;
					string buffer_temp,name_temp,rating_temp,genre_temp;
					buffer_temp=buffer;
					name_temp=buffer_temp.substr(0,buffer_temp.find('~'));
					rating_temp=buffer_temp.substr(buffer_temp.find('~')+1,buffer_temp.rfind('~'));
					rating_temp=rating_temp.substr(0,rating_temp.find('~'));
					genre_temp=buffer_temp.substr(buffer_temp.rfind('~')+1,buffer_temp.length());
					cout<<"Movie Name: "<<name_temp<<"\nRating: "<<rating_temp<<"\nGenre: "<<genre_temp<<endl;
					cout<<"--------------------------------------------------\n";
				}
				return;
			}
			
			fin2>>ptr>>ptr1; //reading from the utility file of users
		}
	}
	else{
		cout<<"\nInvalid user id";
	}
}

void collaborative(int i){
	ifstream fin("users_data_bin.bin",ios::binary);
	ifstream fin1("new_main_file_bin.bin",ios::binary);
	ifstream fin2("search_utility_users.txt");
	long long next,prev,next1,prev1,ptr,ptr1,user,user1;
	priority_queue<	pair<float,pair<string,string> > >pq;
	string temp,id,display,genre,genre1,number,tempgenre,name,rating;
	char str[300];
	User u1;
	if(i<=162541){
		while(!fin2.eof()){
			prev=next;
			fin2>>next;
			if(next>i||next==162500){
				fin.seekg(ptr,ios::beg);
				while(i!=user){
					fin>>user;
					fin.getline(str,200,'\n');		
				}
				temp=str;
				temp[0]='@';
				number=temp.substr(1,temp.find('~')-1);
				genre=temp.substr(temp.find('~')+1,temp.length());
				genre=genre.substr(0,genre.find('~'));
				genre1=temp.substr(temp.rfind('~')+1,temp.length());
				u1.change(user,genre,genre1,atoi(number.c_str()));
				u1.display();
				fin1.seekg(ptr1,ios::beg);
				while(user!=user1){
					fin1.getline(str,300,'\n');
					temp=str;
					display=str;
					temp=temp.substr(temp.find('~')+1,temp.length());
					id=temp.substr(0,temp.find('~'));
					user1=atoi(id.c_str());
				}
				vector<string> v1,v2;
				for(int j=0;j<atoi(number.c_str());j++){
					if(display.find(genre)!=string::npos||display.find(genre1)!=string::npos){
						temp=display.substr(0,display.rfind('~'));
						temp=temp.substr(0,temp.rfind('~'));
						temp=temp.substr(temp.rfind('~')+1,temp.length());
						v1.push_back(temp);
					}
					fin1.getline(str,300,'\n');
					display=str;
				}
				fin.close();
				fin1.close();
				fin2.close();// line 304 till here is same as above content_based function
				
				//now opening the users file to fin a user which have the same genre as our previous genre
				fin2.open("users_data.txt");
				fin1.open("new_main_file_bin.bin",ios::binary);
				int l,k;
				string sndid;			
				while(!fin2.eof()){
					fin2.getline(str,300,'\n');	//read from the users_data file
					display=str;
					if((display.find(genre)!=string::npos)&&(display.find(genre1)!=string::npos)){   //if our required users genre matches any other user genre
						temp=display.substr(0,display.find('~'));
						id=temp;
						temp=display.substr(display.find('~')+1,display.length());
						temp=temp.substr(0,temp.find('~'));
						user1=atoi(temp.c_str());     //breaking the id of other matched user
						if(i!=atoi(id.c_str())&&(user1>150)){    //if other matched users i is not same as previous and matched users movies are greater than 150 yhen move forward
							while(!fin1.eof()){   //searching for the user sequentially in the main 1.6gb file because it may be between 1-100
								fin1.getline(str,300,'\n');	
								display=str;
								display=display.substr(display.find('~')+1,display.length());
								sndid=display.substr(0,display.find('~'));
								if(id==sndid){   //if we have reached till our matched users data then move forward 
									for(int i=0;i<user1;i++){    //loop till we have all his movies in the priority queue
										fin1.getline(str,300,'\n');	
										display=str;
										tempgenre=display.substr(display.rfind('~')+1,display.length());
										rating=display.substr(display.find('~')+1,display.length());
										name=rating.substr(rating.find('~')+1,rating.length());
										rating=name.substr(name.find('~')+1,name.rfind('~'));
										rating=rating.substr(0,rating.find('~'));							
										name=name.substr(0,name.find('~'));    //just take out the rating ,name an genre of the movie and push into pq
										pq.push(make_pair(atof(rating.c_str()),make_pair(name,tempgenre)));
									}
									pair<float,pair<string,string> > pq_movie;
									cout<<"\n\t\tMovies Recommended on the basis of other user\n\n";
									for(int i=0;i<10&&pq.size()>1;){
										pq_movie=pq.top();
										pq.pop();    
										int loop=0;
										for(loop=0;loop<v1.size();loop++){   //to check if the user has watche the movie or not
											if(v1[loop]==pq_movie.second.first){
												break;
											}
											
										}
										if(loop==v1.size()){
											cout<<"\nMovie name:"<<pq_movie.second.first<<endl;
											cout<<"Rating by user: "<<pq_movie.first<<endl;
											cout<<"Genre: "<<pq_movie.second.second<<endl;
											i=i+2;
										}
										if(!pq.empty())
										pq.pop();
									}
									return;
								}
							}
						}
					}
				}
				return ;
			}
			fin2>>ptr>>ptr1;
		}
	}
	else{
		cout<<"\nInvalid id";
	}
}

void me(){
//	make_user_file();
//	users_bin();
//	movies_bin();
//	make_file_binary();
//	content_based(100);
//collaborative(33333);
}



