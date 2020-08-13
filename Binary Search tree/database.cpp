//--------------------------------------------------------------------
//
//  Laboratory 11, In-lab Exercise 1                     database.cs
//	Name: Shivang Trivedi
//	Date: April 1, 2019
//  (Shell) Indexed accounts database program
//--------------------------------------------------------------------

// Builds a binary search tree index for the account records in the
// text file accounts.dat.

#include <iostream>
#include <fstream>
#include "BSTree.cpp"
#include <string>
using namespace std;

//--------------------------------------------------------------------
//
// Declarations specifying the accounts database
//

const int nameLength      = 11;   // Maximum number of characters in
                                  //   a name
const long bytesPerRecord = 38;   // Number of bytes used to store
                                  //   each record in the accounts
                                  //   database file

struct AccountRecord
{
    int acctID;                   // Account identifier
    char firstName[nameLength],   // Name of account holder
         lastName[nameLength];
    double balance;               // Account balance
};

//--------------------------------------------------------------------
//
// Declaration specifying the database index
//

struct IndexEntry
{
    int acctID;              // (Key) Account identifier
    long recNum;             // Record number

    int getKey () const
        { return acctID; }   // Return key field
};

//--------------------------------------------------------------------

void main ()
{
    ifstream acctFile ("accounts.dat");   // Accounts database file
    AccountRecord acctRec;                // Account record
    BSTree<IndexEntry,int> index;         // Database index
    IndexEntry entry;                     // Index entry
    int searchID = -1;                         // User input account ID
    long recNum = 0;                          // Record number

    // Iterate through the database records. For each record, read the
    // account ID and add the (account ID, record number) pair to the
    // index.
	string skip;
	while (acctFile.good()) {
		acctFile >> entry.acctID;
		acctFile >> skip >> skip >> skip;
		entry.recNum = recNum;
		recNum++;
		index.insert(entry);
	}
	
    // Output the account IDs in ascending order.
	cout << "\nAccount IDs in ascending order: " << endl;
	index.writeKeys();
	cout << endl;
    // Clear the status flags for the database file.

    acctFile.clear();
	acctFile.close();
    // Read an account ID from the keyboard and output the
    // corresponding record.
	acctFile.open("accounts.dat");
	cout << "\nPlease enter an account ID to search (Enter 0 to exit): ";
	cin >> searchID;

	while (searchID != 0) {
		if (index.retrieve(searchID, entry)) {
			for (int x = 0; x <= entry.recNum; x++) {
				acctFile >> acctRec.acctID;
				acctFile >> acctRec.firstName;
				acctFile >> acctRec.lastName;
				acctFile >> acctRec.balance;
			}

			cout << "Record Number: " << entry.recNum << endl;
			cout << "Account Number: " << acctRec.acctID << endl;
			cout << "Name: " << acctRec.firstName << " " << acctRec.lastName << endl;
			cout << "Balance: " << acctRec.balance;
		}
		else {
			cout << "No accout found under that Account ID." << endl;
		}
		acctFile.clear();
		acctFile.close();

		acctFile.open("accounts.dat");
		cout << "\n\nPlease enter an account ID to search (Enter 0 to exit): ";
		cin >> searchID;
	}
}
