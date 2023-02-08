#include<bits/stdc++.h>
using namespace std;
class movies
{
	public:
    	string name;
    	double rating;
    	int no;
    	string genre;
    	movies()
    	{
        	rating = 0;
        	no = 0;
    	}
    	movies(string n, double r, string g, int num = 1) : name(n), rating(r), genre(g)
    	{
        	no = num;
    	}
    	bool operator==(const movies &rhs)
    	{
        	return (name == rhs.name);    //if only name of two movies are same then they are same
    	}
//    	bool operator>(const movies &rhs)
//    	{ 
//       	return (name >rhs.name);      //this was used while sorting data on the basis of alphabetical order
//    	}
//    	bool operator>(const movies &rhs)
//    	{
//      	return (no >rhs.no);         //this was used while sorting data on the basis of number of people watched
//    	}
    	bool operator>(const movies &rhs)
    	{
        	return (rating >rhs.rating);     //this was used while sorting data on the basis of rating
    	}
    	void display()
    	{
        	cout << "Name: " << name;
        	cout << "\nRating: " << rating << "\nGenre: " << genre << "\nPeople watched: " << no << endl;
    	}
    	void change(string n, double r, string g)   //function to change values
		{
    		name=n;rating=r;genre=g;no=1;
		}  
};
void clean_main_file()
{
	//this function is created to convert csv to new.txt and replacing commas with tildes 
	//as some data had commas in between them such as 1,2,"dark ,the",4,drama|comedy  this was converted to 
	//												  1~2~dark ,the~4~drama|comedy
    char buffer[300];
    ifstream obj_to_read("movies_dataset.csv");
    ofstream obj_to_write("new_main_file.txt");
    string string1, string2;
    if (!obj_to_read)
    {
        cout << "\nerror";
    }
    else
    {
        while (!obj_to_read.eof())
        {
            obj_to_read.getline(buffer, 300, '\n');
            string1 = buffer;
            if (string1.length() > 0)
            {
                replace(string1.begin(), string1.begin() + string1.find(',') + 1, ',', '~');  //replacing , with ~ it cannot be done in one
                replace(string1.begin(), string1.begin() + string1.find(',') + 1, ',', '~');   //go because then movie name would become
                replace(string1.begin() + string1.rfind(','), string1.end(), ',', '~');   // dark knight~ the
                replace(string1.begin() + string1.rfind(','), string1.end(), ',', '~');   //but we want it to maintain its prev version dark knight, the
                string1.erase(remove(string1.begin(), string1.end(), '"'), string1.end());  // remove all double quotations same data had it
                transform(string1.begin(), string1.end(), string1.begin(), ::tolower);
            }
            cout << string1 << endl;
            obj_to_write << string1 << endl;
        }
    }
    cout << "\nended";
}

void all_movies(){
	//This function was made to reduce movies data from 25 million to around 60,000 
	//As there were almost 160,000 users and they may have watched the same movies but rated different so a file was made
	//which contained movie_name~average_rating~no. of people watched~genre
	//this function ran only once because we only need to find avg rating of movies once and use it in further tasks
    char buffer[300];
    ifstream obj_to_read("new_main_file.txt");
    string string1, name,genre,rating;
    deque<movies> l1;
    ofstream obj_to_write("avg_movies.txt");
    if (!obj_to_read)
    {
        cout << "\nerror";
    }
    else
    {
        obj_to_read.getline(buffer, 256, '\n');
        int i;
        long z=1;
        movies m1;
        while (!obj_to_read.eof())
        {
            obj_to_read.getline(buffer, 256, '\n');
            cout<<buffer<<endl;
            string1 = buffer;
            string1 = string1.substr(string1.find('~') + 1, string1.length());//breaking the data from row_no~id~movie~rating~genre
            string1 = string1.substr(string1.find('~') + 1, string1.length());  // to only movie   rating  and genre
            rating = string1.substr(string1.find('~') + 1, string1.length());   //string1=movies_name      rating=movie_rating
            genre = rating.substr(rating.find('~') + 1, rating.length());     //genre=movie_genre
            rating = rating.substr(0, rating.find('~'));
            string1 = string1.substr(0, string1.find('~'));
            if(l1.size()==0){
                l1.push_back(movies(string1,atof(rating.c_str()),genre));   //push the movie in deque
            }
            else{
                m1.change(string1,atof(rating.c_str()),genre);
                for( i=0;i<l1.size();i++){     //this loops work if a movies is already in the deque then only its rating is added
                    if(l1[i]==m1){             //and number of people watched is increased
                        l1[i].rating+=atof(rating.c_str());
                        l1[i].no++;
                        l1[i].display();
                        break;
                    }
                }
                if(i==l1.size()){    //if the loop has worked completely that is the movie was not present in the deque
                    l1.push_back(m1);    //then it is pushed
                }
            }
        }
        if(obj_to_write)   
        for(int i=0;i<l1.size();i++){   //writing the deque in the file
            l1[i].rating=l1[i].rating/(l1[i].no);
            obj_to_write<<l1[i].name<<"~"<<l1[i].rating<<"~"<<l1[i].no<<"~"<<l1[i].genre<<endl;
        }
    }
}//after this function was executed we only had around 60,000 movies with avg rating and most watched and genre

void sort(){
	ifstream obj_to_read("avg_movies.txt");      //this file contains data in the following format-> movie_name~avg_rating~people_watched~genre   
	//this function is made to sort the avg calculated movies on the basis 
	movies array[58956];                  //of alphabetical order and most watched only
	char buffer[256];
	string name,rating,genre,watched;
	for(int i=0;i<58956;i++){
		obj_to_read.getline(buffer, 256, '\n');
		name = buffer;
        rating = name.substr(name.find('~') + 1, name.length());
        watched = rating.substr(rating.find('~') + 1, rating.length());
    	genre=watched.substr(watched.find('~')+1,watched.length());
        watched=watched.substr(0, watched.find('~'));
        rating = rating.substr(0, rating.find('~'));
        name = name.substr(0, name.find('~'));
        array[i]=movies(name,atof(rating.c_str()),genre,atoi(watched.c_str()));
        cout<<name<<"   "<<rating<<"  "<<watched<<"  "<<genre<<endl;
	}	
	movies temp;
	int n=58956;     //insertion sort was used because quick sort was eating up resources due to recursion 
	for(int i=1,j;i<n;i++){    //insertion is also stable
		temp= array[i];
		j=i-1;
		while(j>=0 && array[j]>temp){
			array[j+1]=array[j];
			j--;
		}
		array[j+1]=temp;
	}
//	ofstream fout("alphabetical.txt");
//	for(int i=0;i<n;i++){    //storing sorted in alphaberical order
//		fout<<array[i].name<<"~"<<array[i].rating<<"~"<<array[i].no<<"~"<<array[i].genre<<endl;
//	}   //only 1 was executed once because we cant sort movies both on alphabetical order and most watched simultaneously
	ofstream fout("most_watched.txt");     //only top 1000 most watched movies were stored
	for(int i=n-1;i>n-1001;i--){    //storing sorted in most watched order.
		fout<<array[i].name<<"~"<<array[i].rating<<"~"<<array[i].no<<"~"<<array[i].genre<<endl;
	}
	
}




void most_rated(){
	//function to find movies based on top 1000 rated movies from 60,000 movies file
	//as we can not directly sort movies on the basis of rating from 60,000 movies file so data was taken from most_watched movies file
	//because it wont be fair if only 1 user has watched a movies and has rated it 5 star and no user has watched it so placing it on
	//the top would be ineffeceint so top rated movies were calculated from most_watched i.e atleast 6,000 people have watched the movie
	//to be placed in the top_rated list
	ifstream obj_to_read("most_watched.txt");
	movies array[1000];
	char buffer[256];
	string name,rating,genre,watched;
	for(int i=0;i<1000;i++){
		obj_to_read.getline(buffer, 256, '\n');
		name = buffer;        
        rating = name.substr(name.find('~') + 1, name.length());   //breaking the string as it is in this format
        watched = rating.substr(rating.find('~') + 1, rating.length());  //movie_name~rating~people_watched~genre
    	genre=watched.substr(watched.find('~')+1,watched.length());
        watched=watched.substr(0, watched.find('~'));
        rating = rating.substr(0, rating.find('~'));
        name = name.substr(0, name.find('~'));
        array[i]=movies(name,atof(rating.c_str()),genre,atoi(watched.c_str()));
        cout<<name<<"   "<<rating<<"  "<<watched<<"  "<<genre<<endl;
	}
	for(int i=0;i<1000;i++){
		//this formula was used to calculate the rating for the movie this was taken from the imdb official website
		//to calculate top 1000 rated movies  the validty of this formula can be confirmed i.e after calculating avg rating
		//shawshank redemption is on the top an it is also rated the best movie in the world
		array[i].rating=(array[i].no/(array[i].no+6000.0))*array[i].rating+(6000.0/(array[i].no+6000.0))*3.5;
	}
	movies temp;
	int n=1000;
	//now sorting the movies on rating after using the formula
	for(int i=1,j;i<n;i++){
		temp= array[i];
		j=i-1;
		while(j>=0 && array[j]>temp){
			array[j+1]=array[j];
			j--;
		}
		array[j+1]=temp;
	}
	ofstream fout("most_rated.txt");
	for(int i=n-1;i>n-1001;i--){
		fout<<array[i].name<<"~"<<array[i].rating<<"~"<<array[i].no<<"~"<<array[i].genre<<endl;
	}
	
}

void binary_search_file(){
	//converting the alphabetically created 60,000 movies file to binary because it is easier to jump record in binary files
//	ifstream fin("alphabetical.txt");
//	ofstream fout("alphabeticalbin.bin", ios::binary|ios::out);
//	string str;
//	while(!fin.eof()){
//		getline(fin,str,'\n');
//		fout<<str;
//		fout<<"\n";
//	}


	ofstream fout1("utility.txt");   //now a utility file was created to aid searching for movies on the basis of name
	//i.e if the movie to search starts from s instead of searching all the movies from start directly jump to offset of s in the alpahbetical.tx
	//and thats why utility was created it contained starting offset of all the char alphabetically
	//this enabled to search in less than 0.5 sec
	ifstream fin1("alphabeticalbin.bin",ios::binary);
	char ch,ch1;
	string str;
	long long i=fin1.tellg();
	getline(fin1,str,'\n');
	ch=str[0];	
	while(!fin1.eof()){
		i=fin1.tellg();
		getline(fin1,str,'\n');
		if(ch!=str[0]){
			cout<<str<<endl;
			fout1<<str[0]<<" "<<i<<endl;
			ch=str[0];	
		}
	}
	
}

void split_on_genre(string genre){
	//files were created on the basis of genre so that if anyone want best thriller movies directly open that file and display
	string genree=genre+".txt";
	ofstream fout(genree.c_str());
	ifstream fin("most_rated.txt");
	char str[256];
	string temp;
	while(!fin.eof()){
		fin.getline(str,256,'\n');
		temp=str;
		cout<<str<<endl;
		if((temp.find(genre,0))!=string::npos){
			fout<<str<<endl;
		}
	}
}
void call_genre(){
//	split_on_genre("comedy");
//	split_on_genre("crime");
//	split_on_genre("drama");
//	split_on_genre("thriller");
//	split_on_genre("romance");
//	split_on_genre("musical");
//	split_on_genre("war");
//	split_on_genre("adventure");
//	split_on_genre("film-noir");
//	split_on_genre("sci-fi");
//	split_on_genre("mystery");
//	split_on_genre("children");
//	split_on_genre("fantasy");
//	split_on_genre("action");
//	split_on_genre("documentary");
//	split_on_genre("animation");
//	split_on_genre("horror");
//	split_on_genre("imax");
//	split_on_genre("western");
}

bool search_string(string mov){
	
	//in this function first we will find the offset of the starting first character of the movie from utility
	//for example if the movie is pulp fiction so directly jump to "pa" instead of starting from start in alphabetical.txt
	//starting offset(i.e from where the movies that start with p are starting in alphabetical.txt)
	//of p can be determined from "utility.txt"
	ifstream fin("alphabeticalbin.bin",ios::binary);
	char buffer[256];
	ifstream fin1("utility.txt");
	int i,j;
	char ch,temp=mov[0];
	string stri,name,rating,most;
	movies temp1;
	while(!fin1.eof()){
		fin1>>ch>>j;    //reading the char and the starting offset of it(in alphabeticalbin.bin) from utility.txt
		if(ch==temp){    //if we have reached till the starting char of our movie name
		fin.seekg(j,ios::beg);  //then directly jump to it 
		while((stri.find(mov,0))==string::npos&&!fin.eof()){    //now start to find the movie from alphabeticalbin.bin 
		//if movie is not found stri.find() returns string::npos()
			fin.getline(buffer,256,'\n');
			stri=buffer;
			if(temp!=stri[0]){   //condition for if movie is not there that while searching movie starting with p we are now passed
				return 0;   //		movies which were starting from p this means it is not there
			}
		}
			name=stri.substr(0,stri.find('~'));    //now our required movie is found so breaking the string 
			rating=stri.substr(stri.find('~')+1,stri.length());   //and displaying the movie in the required format
			most=rating.substr(rating.find('~')+1,rating.length());
			rating=rating.substr(0,rating.find('~'));
			most=most.substr(0,most.find('~'));
			temp1=movies(name,atof(rating.c_str()),stri.substr(stri.rfind('~')+1,stri.length()),atoi(most.c_str()));
			temp1.display();
			return 1;
		}
	}
	return 0;
}
void function_calling()
{
	//calling the functions
//	clean_main_file();
////	all_movies();
//	sort();
//	most_rated();
//	binary_search_file();
//	call_genre();
}




