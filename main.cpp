include<iostream>
#include "library.h"

using namespace std;
int menu()
{
int option;
cout << "1)View all items\n2)Borrow Items\n3)View Borrowed Items\n4)Return Borrowed Item\n5)Quit\nEnter Option : " ;
cin >> option;
return option;
}
int login(Library lib)
{
//  here we are passing by value so the copy constructor is called
string id, pass;
cout << endl;
cout << "Enter ID: ";
cin >> id;
cout << "Enter password: ";
cin >> pass;
return lib.validate(id, pass);
}
int main()
{
//initializing a library instance
string libraryId = "123";
Library lib(libraryId);

//is account validated?
lib.readAccount();
    lib.readBookItems();
lib.readVideoItems();
// read then we validate 
int accountIndex = login(lib);
cout << lib.getAccountList().size();
//if validated, show the menu

if (accountIndex != -1)
{
//retreived the account object
Account account = lib.getAccountList()[accountIndex];
//holds the option, input for the menu option
int option;
do {
option = menu();
//Option 1 displays all items in the library both books and videos
if (option == 1)
{
for (int i = 0; i < lib.getItemList().size(); i++)
{
lib.getItemList()[i]->print(); 
}
//if option borrow item
if (option == 2)
{
Transaction trans;
int numItems;
string itemId;
cout << "\nHow many items to borrow: ";
cin >> numItems;
for (int i = 0; i < numItems; i++)
{
cout << "\nEnter the ID of the item to borrow: ";
cin >> itemId;
//check if the itemId is borrowed by the user
int foundInd = lib.SearchItem(itemId);
if (foundInd != -1)
{
  trans.borrowItems(lib.getItemList()[foundInd]);
  // remove from library 
  lib.removeItem(lib.getItemList()[foundInd]);



}
else
{
cout << "Item not found in the library..." << endl;
i--;
}

}

account.addTransaction(trans);

//add the transaction to the account

}
//if option is to view borrowed items
if (option == 3)
{

cout << "============== Borrowed Items =============" << endl;
//View the borrowed items. Borrowed items can be of type book or video
for (int i = 0; i < account.getTransaction().size(); i++)
{
for (int j = 0; j < account.getTransaction()[i].getItemVector().size(); j++)
{
account.getTransaction()[i].getItemVector()[j]->print();
}
}
cout << "========== End of Borrowed Items ==========" << endl;

/*
for (int i = 0; account.getTransaction().size(); i++)
{
vector<Item*> tempvec;
tempvec = account.getTransaction()[i].getItemVector();
for (int i = 0; i < tempvec.size(); i++)
{
cout << tempvec[i];
}
}
*/
//View the borrowed items. Borrowed items can be of type book or video
}
//option to return an item back to the library
if (option == 4)
{
string id; 
cout << " Enter the id  of the item you would like to give back " << endl; 
cin >> id; 

for (int i = 0 ; i< account.getTransaction().size() ; i++)
{
for (int j = 0; j < account.getTransaction()[i].getItemVector().size(); j++)
{
if (account.getTransaction()[i].getItemVector()[j]->getID() == id)
{
lib.addItem((account.getTransaction()[i].getItemVector()[j]));

account.getTransaction()[i].getItemVector().erase(account.getTransaction()[i].getItemVector().begin() + j);
}
   }
}


//return the item back to the library
}
} while (option != 5); //end of do while
}
system("pause");
return 0;
}
