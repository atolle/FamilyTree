//****************************************************************************
//       CLASS:  CSCE-2100.021
//  ASSIGNMENT:  Program 4
//     STUDENT:  Andrew Tolle
// DESCRIPTION:  This program creates an address book. It loads data from a 
//				 .csv file.
//
//				 This file contains main.                                   
//			                                                   
//
//
// REQUIRED SOURCE FILES:   D_00_P4_class.h
//							D_00_P4_func.cpp			
//							D_00_P4_func.h						
//
//
//****************************************************************************
#include "D_00_P4_func.h"		// include func.h function

int main(void)		// defines main
{
	Address_Book Book;	// creates new Address Book 
	// welcome message
	cout << endl << "Welcome to the Address Book!" << endl << endl << "Press ENTER to go to a list of commands and the command prompt" << endl << ">";
	cin.ignore();

	printcmds();		// calls print commands function
	menu(&Book);		// calls menu function

	cout << endl << "Have a good day and a pleasant tomorrow! Goodbye.";		// after user quits
	cin.ignore();

	return 0;	// ends program normally
}
