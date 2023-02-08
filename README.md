# Movie-recommendation-system-in-C++
This is a Data structures & algorithms project made on C++ to get a beginners experience on how sorting algorithms, searching algorithms and data structures are implemented.

## Idea
A recommender system is a simple algorithm whose aim is to provide the most relevant information to a user by discovering patterns in a dataset. The algorithm rates the items and shows the user the items that they would rate highly. An example of recommendation in action is when you visit Amazon and you notice that some items are being recommended to you or when Netflix recommends certain movies to you. They are also used by Music streaming applications such as Spotify and Deezer to recommend music that you might like.

## Trimming data
My first task was to divide the 1.5GB of [data-set](https://www.kaggle.com/datasets/rounakbanik/the-movies-dataset) that I picked from the Internet. The data contained hundreds and thousands of IDs and each ID had movies that were watched by the ID and the rating they gave to the movies and the genre they consumed the most. This data had to be divided and arranged in a way that most watched genres were in one file, highest rated movies were in another file, and names of the movies were in another file; similarly there had to be separate files for content-based recommendation and for Collaborative recommendation. I divided all this data using functions. [Priority queue](https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/) was used to sort out the most viewed genres by giving them priorities, when a genre was consumed its priority changes, similarly highest rated movies were also arranged using priority queue.

Here is a code snippet from `content_collaborative.cpp`

```bash
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
```
Insertion sort was used to sort the movies by name and rating, I tried to use quick sort but it was using too much resources due to recursion, and insertion sort was more stable.

Snippet from `cleaning_making_files`

```bash
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
  ```
 After the files were divided it was time to start coding for the searching algorithms and the data structures. [BST](https://www.programiz.com/dsa/binary-search-tree) was used to search by genre or name or rating. I used the built-in structures [MAP and vectors](https://www.geeksforgeeks.org/map-of-vectors-in-c-stl-with-examples/) to create a BST to search via the genres or the names or ratings.
 
 snippet from `content_collaborative.cpp`
 
 ```bash
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
```

## Data structures and algorithms used

⦁	[Priority Queue](https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/)
⦁	[Queue](https://www.geeksforgeeks.org/queue-cpp-stl/)
⦁	[Linked List](https://www.geeksforgeeks.org/data-structures/linked-list/)
⦁	[Vector](https://www.geeksforgeeks.org/map-of-vectors-in-c-stl-with-examples/)
⦁	[Array](https://www.geeksforgeeks.org/arrays-in-c-cpp/)  
⦁	[Insertion sort](https://www.geeksforgeeks.org/insertion-sort/)
⦁	[Binary search](https://www.programiz.com/dsa/binary-search-tree)


 
