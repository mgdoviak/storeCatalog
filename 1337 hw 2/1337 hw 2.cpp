// 1337 hw 2.cpp : Defines the entry point for the console application.
//
/*
Author: Mary Grace Doviak
Compiler: GNU GCC
Date: 2/1/2018

Purpose of program: Read in product records from a file and then store the info in parallel arrays.
Show the user a menu, if they choose option 1, go to checkout and search for a PLU and calculate the 
total cost. If they choose option 2, show them the current inventory, updated from previous purchases. 
If they choose option 3, show the updated inventory and quit the program. 
*/


#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// prototypes
int determineNumRecords(string fname);
bool readInventory(string fname, string * pluPtr, string * namePtr,
	int * typePtr, double * pricePtr, int * inventoryPtr, int numRecords);
double checkout(string * pluPtr, double * pricePtr, int * inventoryPtr, int numRecords);
int searchProduct(string plu, string *pluPtr, int numRecords);

// beginning of main function
int main()
{
	int choice;
	int siz = 7;
	string fname;
	ifstream inputFile;
	cout << "Enter the file name: ";
	cin >> fname; // get file name

	int numRecords = determineNumRecords(fname); // call determineNumRecords
	cout << "There are " << numRecords << " records in the file" << endl;

	// dynamically allocate parallel arrays
	string *pluPtr = nullptr;
	pluPtr = new string[siz];

	string *namePtr = nullptr;
	namePtr = new string[siz];

	int *typePtr = nullptr;
	typePtr = new int[siz];

	double *pricePtr = nullptr;
	pricePtr = new double[siz];

	int *inventoryPtr = nullptr;
	inventoryPtr = new int[siz];



	// call readInventory 
	readInventory(fname, pluPtr, namePtr, typePtr, pricePtr, inventoryPtr, numRecords);

	// display file 
	inputFile.open(fname); // open file
	cout << endl << "Inventory read from file" << endl;
	cout << "------------------------" << endl;
	for (int i = 0; i < numRecords; i++) // output arrays
	{
		cout << "PLU: " << pluPtr[i];
		cout << ", " << namePtr[i];
		cout << ", type: " << typePtr[i];
		cout << ", unit price: " << pricePtr[i];
		cout << ", inventory: " << inventoryPtr[i] << endl;
	} // end of for loop
	inputFile.close(); // close program


	do
	{
		// output menu
		cout << endl << "1 - Checkout" << endl;
		cout << "2 - Print current inventory" << endl;
		cout << "3 - Quit" << endl;
		cin >> choice; // read in user choice

		while(choice < 1 || choice > 3)
		{
			cout << "Invalid choice, reenter: " << endl;
			cin >> choice;
		} // end of while loop
		if (choice == 1 || choice == 2 || choice == 3)
		{
			switch (choice)
			{
			case 1: // if the user chooses option 1
			{
				checkout(pluPtr, pricePtr, inventoryPtr, siz); // call checkout function
				break;
			}
			case 2: // if the user chooses option 2
			{
				inputFile.open(fname); // open file
				cout << "Current Inventory" << endl;
				cout << "-----------------" << endl;
				for (int i = 0; i < numRecords; i++) // output current inventory 
				{
					cout << "PLU: " << pluPtr[i];
					cout << ", " << namePtr[i];
					cout << ", type: " << typePtr[i];
					cout << ", unit price: " << pricePtr[i];
					cout << ", inventory: " << inventoryPtr[i] << endl;
				} // end of for loop
				inputFile.close(); // close file
				break;
			}
			case 3: // if the user chooses option 3
			{
				inputFile.open(fname); // open file
				cout << "Updated Inventory" << endl;
				cout << "-----------------" << endl;
				for (int i = 0; i < numRecords; i++) // output updated inventory 
				{
					cout << "PLU: " << pluPtr[i];
					cout << ", " << namePtr[i];
					cout << ", type: " << typePtr[i];
					cout << ", unit price: " << pricePtr[i];
					cout << ", inventory: " << inventoryPtr[i] << endl;
				} // end of for loop
				inputFile.close(); // close file
				break;
			}
			} // end of switch statement
		} // end of if statement
		
	} while (choice != 3); // while the user does not choose to quit & end of do while loop
    return 0;
} // end of main function

/*
 This function reads from a file to determine the number of records
(or equivalently, the number of products)
It returns -1 if file open is unsuccessful, else it returns the number
of records. It should close the
file when done
*/
// beginning of determineNumRecords
int determineNumRecords(string fname) 
{
	ifstream inputFile;
	string line;
	int numberOfRecords = 0;
	inputFile.open(fname); // open the file
	if (inputFile)
	{
		while (getline(inputFile, line)) // while you can read a line in the file
		{
			numberOfRecords++;
		} // end of while statement
		inputFile.close();
		return numberOfRecords;
	} // end of if statement
	else
		return -1;
} // end of determineNumRecords
/* This function reads from a file and populates parallel arrays. It
takes as arguments the file name,
and the pointers to the parallel arrays, as well as the number of
records.
It returns true if file open is successful, false otherwise. It should
close the file when done
*/
// beginning of readInventory function
bool readInventory(string fname, string * pluPtr, string * namePtr,
int * typePtr, double * pricePtr, int * inventoryPtr, int numRecords)
{
	ifstream inputFile;
	inputFile.open(fname); // open the file
	numRecords = determineNumRecords(fname); // call determineNumRecords
	if (inputFile) // check to make sure the file opens
	{
		for (int i = 0; i < numRecords; i++) // populate the arrays
		{
			inputFile >> skipws >> pluPtr[i];
			inputFile >> namePtr[i];
			inputFile >> typePtr[i];
			inputFile >> pricePtr[i];
			inputFile >> inventoryPtr[i];
		} // end of for loop
		inputFile.close(); // close file
		return true;
	} // end of if statement
	else
		return false;
	
} // end of readInventory function
/* This function does the checkout. It takes as argument the pointers
to the parallel arrays, and the number of records in the
inventory. It reads the PLU and quantity from the user, updates the
data in the arrays to reflect the user's purchase,
does input validation on the purchased quantity (> 0), asks the user
to reenter as long as the quantity is < 0.
It prompts the user for more purchases.
The user types a PLU of zero when done. The function returns the total
purchase price.
*/
// beginning of checkout function
double checkout(string * pluPtr, double * pricePtr, int * inventoryPtr, int numRecords)
{
	int quantity;
	string plu;
	int pluInt, inventInt;
	double price1;
	double totalPrice = 0;
	do
	{
		cout << endl << "Enter PLU, 0 if done: ";
		cin >> plu; // get plu code
		cout << "Enter quantity: ";
		cin >> quantity; // get quantity
		while (quantity <= 0) // if quantity is negative
		{
			cout << "Quantity must be positive, reenter: ";
			cin >> quantity; 
		} // end of while loop
		pluInt = searchProduct(plu, pluPtr, numRecords); // call searchProduct function
		if (pluInt == -1) // if plu was not found
			cout << "PLU not found" << endl;
		else
		{
			inventInt = inventoryPtr[pluInt];
			if (quantity > inventInt)
			{
				quantity = inventInt;
			} // end of if statement
			
			price1 = pricePtr[pluInt];
			totalPrice += price1 * quantity; // calculate total price
			inventoryPtr[pluInt] = inventInt - quantity; // update inventory
		} // end of else statement
	} while (strcmp(plu.c_str(), "0\0")); // compare plu to 0 & end of do while 
	// output total
	cout << "Total is: $" << totalPrice; // output total price
	return totalPrice;
	
	
} // end of checkout function
/* This function searches for a product in the inventory using the PLU
as the search key
It returns the array index if the product is found, -1 otherwise
*/
// beginning of searchProduct function
int searchProduct(string plu, string *pluPtr, int numRecords)
{
	int index = 0;
	int position = -1;
	bool found = false; 

	while (index < numRecords && !found) // while index is less than number of records and it's not found
	{
		if (pluPtr[index] == plu)
		{
			found = true; // say plu code is found
			position = index;
		} // end of if statement
		index++;
	} // end of while loop
	return position; 
} // end of searchproduct function
