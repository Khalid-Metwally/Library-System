#pragma once
#include "itemfile.h" 
#include <fstream>
#include <vector>

class Transaction
{
public:
Transaction()
{

}
//this function adds an item to the itemVector
void borrowItems(Item* item)
{
itemVector.push_back(item);
}
//this function returns the itemVector
vector<Item*>& getItemVector()
{
//& is v important 
return itemVector;
}
//this function is a setter to the itemVector attribute
void setItemVector(vector<Item*> iVector)
{
itemVector.clear();
itemVector = iVector;
}
//this function returns the index location of the found item in the a transaction.
//the function return -1 if the item is not found
int findBorrowedItem(Item* item)
{
for (int i = 0; itemVector.size(); i++)
{
if (item->getID() == itemVector[i]->getID())
{
return i;
}

}
return -1;
}

~Transaction();
Transaction(const Transaction& trans)
{
itemVector.resize(trans.itemVector.size());
for (int i = 0; i < trans.itemVector.size(); i++)
{

itemVector[i] = trans.itemVector[i]->duplicate();
}



}

void operator=(const Transaction& trans)
{
itemVector.resize(trans.itemVector.size());
for (int i = 0; i < itemVector.size(); i++)
{
delete itemVector[i];
}

itemVector.clear();
for (int i = 0; i < trans.itemVector.size(); i++)
{

itemVector[i] = trans.itemVector[i]->duplicate();
}
}
private:
//holds the items borrowed in the vector
vector<Item*> itemVector;
// apply rule of 3 


};

Transaction::~Transaction()
{
for (int i = 0; i < itemVector.size(); i++)
{
delete itemVector[i];
}

itemVector.clear();
}

class Account
{
public:
//Todo: default constructor and a non-default constructor that takes in the ID and password
Account()
{
id = "none", pass = "none";

}
Account(string id, string pass)
{
this->id = id;
this->pass = pass;

}
//Todo: getTransaction that function returns the vector of all transactions for the account
vector<Transaction>& getTransaction()
{
return translist;
// by reference because i want the actual vector in the account not the copy 
}
//Todo: addTransaction function that adds a transaction to the transaction list
void addTransaction(const Transaction atransaction)
{
translist.push_back(atransaction);
}

//Todo: setTransaction function set the transaction vector in the account
void setTransaction(vector<Transaction> translist)
{
//this->translist.clear();
this->translist = translist;

}

string getID()
{
return id;
}
string getPass()
{
return pass;
}


//Todo: Any required operators that is to be overloaded
private:
//id holds the id of the account, pass holds the password
string id, pass;
//vector holds all the transactions associated to the account
vector<Transaction> translist;
};


class Library
{
public:


//Todo: constructor that takes a library ID (string)

Library(string Libid)
{
this->libId = Libid;
}
Library()
{
libId = "none"; 
}
// Todo: readBookItems function reads from the book.txt, creates the book object and
//stores them in the ItemList vector. Note the name of the file is “book” //followed by the library ID.

void readBookItems()
{
string bookid, bookname, author; 

ifstream ifile; 
// cin.getline is not overloaded to accept strings
// istream cannot open files
// whwen to use cin and getline ??
if (ifile.fail())
{
cout << "cant open file " << endl; 
}
else
{
ifile.open("books" + libId + ".txt");
}

while (!ifile.eof())
{
//Item* theitem = new Item();

getline(ifile,bookid);
if (ifile.eof())
break;
   getline(ifile , bookname);

getline(ifile, author);


            Book* abook = new Book(bookid, bookname, author);

itemList.push_back(abook); 


// IF U HAVE A VECTOR of a certain type (iTem*) , you can also push elements from its child classes
}
}

// Todo: readVideoItems function that reads from the video.txt, creates the video
//object and stores them in the ItemList vector. Note the name of the file is “video”
//followed by the library ID.

void readVideoItems()
{
// Format (Video Id, Title, Genre, director, producer)
string videoid, Title, Genre, director, producer; 
ifstream ifile;


if (ifile.fail())
{
cout << " cant open file " << endl; 
exit(2);
}

else
{
ifile.open("vide" + libId + ".txt"); 
}

while (!ifile.eof())
{
getline(ifile, videoid);
if (ifile.eof())
break;
getline(ifile, Title);
getline(ifile, Genre);
getline(ifile, director);
getline(ifile, producer);

//ifile >> videoid >> Title >> Genre >> director >> producer;
Video* vid = new Video(videoid, Title, Genre, director, producer); 
itemList.push_back(vid); 


}
}
// Todo: readAccount function reads from the account.txt, creates the account object
//and stores them in the accountList vector. Note the name of the file is “account”
//followed by the library ID.

// string accountid, accountp;
// check for fail 
void readAccount()
{
ifstream ifile;
ifile.open("account" + libId + ".txt");
string apass, aid;

while (!ifile.eof())
{
ifile >> aid >> apass;
if (ifile.eof())
break;
Account acc (aid, apass);
accountList.push_back(acc);
}
}



// Todo: validate function validates the passed id and password.
//the function returns -1 if invalid, and the index of the account if valid
int validate(string aid, string apass)
{

for (int i = 0; i < accountList.size(); i++)
{
if (accountList[i].getID() == aid && accountList[i].getPass() == apass)
{
return i; 
}


}

return -1; 

}



// Todo: getItemList function returns the vector of Items addresses
vector<Item*> getItemList()
{
return itemList;
    }
// Todo: addItem function adds an Item into the itemList
void addItem(Item* item)
{
itemList.push_back(item); 
           
}
// Todo: getAccountList function returns the accountList
vector<Account>&getAccountList()
{
return accountList;
}
// Todo: removeItem function removes an item from the itemList and returns true if
//item is found and removed successfully
bool removeItem(Item* item)
{
for (int i = 0; i < itemList.size(); i++)
{
if (itemList[i]->getID() == item->getID())
{
itemList.erase(itemList.begin() +  i);
cout << " item removed successfully " << endl; 
return true; 
}
}

return false; 
// for double tab

}
//SearchItem function searches for an item.
//the function returns the index of the found item. If no item is found,
//the function returns -1
int SearchItem(string id)
{
for (int i = 0; i < itemList.size(); i++)
{
if (itemList[i]->getID() == id)
{
return i;
}

}
return -1; 
}

~Library();

Library(const Library& lib2);
void operator= (const Library& lib)
{
libId = lib.libId;
accountList = lib.accountList;
for (int i = 0; i < itemList.size(); i++)
{
delete itemList[i];
}
itemList.clear();
itemList.resize(itemList.size());
for (int i = 0; i < itemList.size(); i++)
{
itemList.push_back(lib.itemList[i]->duplicate());
}

/*
accountList.clear();

for (int i = 0; i < itemList.size(); i++)
{
delete itemList[i];
}
itemList.clear();

libId = lib.libId;



for (int i = 0; i < lib.accountList.size(); i++)
{
//accountList[i] = 
// [i] does not exist yet 
accountList.push_back(lib.accountList[i]);
}
Item* item2;
for (int i = 0; i < lib.itemList.size(); i++)
{
item2 = new Item(lib.itemList[i]->getID());

itemList.push_back(item2);


}
*/
}

//cfriend ostream& operator<< (ostream& out, vector<Item*> itemList); 

private:


string libId;


//itemList hold the items objects in the library
vector<Item*> itemList;

// apply rule of 3 

//accountList hold the account objects
vector<Account> accountList;







};
/*
ostream& operator<< (ostream& out, Item* item)
{

Video* vid = dynamic_cast<Video*>(item); 
// when ur dynamically casting  an object to an invalid type , the dynamic cast returns a nullptr

if (vid != nullptr)
{
item->print();
}



Book* book = dynamic_cast<Book*>(item); 

if (book != nullptr)
{
item->print();
}

return out; 
}
*/

Library::Library(const Library& lib)
{



libId = lib.libId;
accountList = lib.accountList;
itemList.resize(lib.itemList.size());
for (int i = 0; i < itemList.size(); i++)
{
itemList[i]= (lib.itemList[i]->duplicate()); 
/*
if (dynamic_cast<Book*>(lib.itemList[i]) != nullptr)
{
itemList[i] = new Book(*dynamic_cast<Book*>(lib.itemList[i]));
}
else
{
itemList[i] = new Video(*dynamic_cast<Video*>(lib.itemList[i]));
}
*/
}








/*
libId = lib.libId; 



for (int i = 0; i < lib.accountList.size(); i++)
{
//accountList[i] = 
// [i] does not exist yet 
accountList.push_back(lib.accountList[i]); 
}
Item* item2;
for (int i = 0; i <lib.itemList.size(); i++)
{
item2 = new Item(lib.itemList[i]->getID()); 

itemList.push_back(item2);


}
*/
}

Library::~Library()
{

for (int i = 0; i < itemList.size(); i++)
{
delete itemList[i];
}

itemList.clear();
}
