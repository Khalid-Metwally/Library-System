#pragma once
#include <string>
#include <iostream>

using namespace std;
class Item
{
public:
//constructors
Item()
{
theID = "none"; 
theTitle = "none"; 
}
Item(string iid, string ititle)
{
theID = iid; 
theTitle = ititle; 
}
Item(string iid)
{
theID = iid;
}
//getters and setters
//_____________________
string getID()
{
return theID;
}

void setID(string someid)
{
theID = someid; 
}

string getTitle()
{
return theTitle; 
}

void setTitle(string sometitle)
{
theTitle = sometitle; 
}
//Include virtual function print
//_____________________

virtual void print() {}
~Item()
{
}
virtual Item* duplicate()
{
return nullptr;
}


protected:
//common attributes for video and book items

string theID;
string theTitle;
};

class Video : public Item
{

private:
// Format (Video Id, Title, Genre, director, producer)
//string vidId;
//string Title;
string Genre;
string director;
string producer;

public:

Video() :Item("none")
    {
Genre = "none", director = "none", producer = "none";
// vidId = "none", Title = "none", mistake

}

Video(string vidId, string Title, string Genre, string director, string producer) : Item(vidId, Title) 
{
//this->vidId = vidId;
// mistake this->Title = Title;
this->Genre = Genre;
this->director = director;
this->producer = producer;


}
Video(string theID , string Genre , string director , string producer): Item(theID)
{
this->Genre = Genre;
this->director = director;
this->producer = producer; 
}
     //    Item::print();

//Item::print(); you cannot call functions in the class , only prototypes




void print() override
{

cout << "-------------- - Video Item----------------" << endl;
cout << "Video Information :" << endl;
cout << "Video Id : " << getID() << endl;
cout << "Video Title : " << getTitle() << endl;
cout << "Video Director : " << director << endl;
cout << "Video Genre : " << Genre << endl;
cout << "video Producer : " << producer << endl;
cout << "----------------------------------------" << endl;


}

Video* duplicate()
{
Video* avideo = new Video(theID,  Genre , director , producer );
return avideo;
}


};

class Book : public Item
// Format (Book Id, Title, Author)
{
private:

string Author;

public:

Book() : Item("none")
{

Author= "none";
}
Book(string theId, string author):Item(theId)
{
this->Author = author; 

}

Book(string bookId, string Title, string Author) : Item(bookId, Title)
{
//this->bookId = bookId; 
//this->Title = Title; 
this->Author = Author; 

}
void print() override
{

cout << "---------------Book Item----------------" << endl;
cout << "Book Id : " << theID << endl;
cout << "Book title : " << theTitle << endl;
cout << "Book Author : " << Author << endl;
cout << "----------------------------------------" << endl;


}

Book* duplicate()
{
Book* abook = new Book(theID, Author);
return abook;
}


};
