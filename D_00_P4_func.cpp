//****************************************************************************
//       CLASS:  CSCE-2100.021
//  ASSIGNMENT:  Program 4
//     STUDENT:  Andrew Tolle
// DESCRIPTION:  This program creates an address book. It loads data from a 
//				 .csv file.
//
//				 This file contains the menu function of the program.        
//				                                                  
//
//
// REQUIRED SOURCE FILES:   D_00_P4_main.cpp   
//							D_00_P4_class.h			
//							D_00_P4_func.h						
//
//
//****************************************************************************
#include "D_00_P4_func.h"	// includes func.h file

void menu(Address_Book *Book)		// menu function definition
{
	string cmd1, cmd2, cmd, fname, lname, ID, homeID;					// command to be given by user, first and last name, IDs, address
	bool quit = false;			// used to determine when user quits

	while (!quit)				// while the user hasn't quit
	{	// prints commands prompt
		cout << endl << "cmd>";
		cin >> cmd1;
		if (cmd1 == "quit" || cmd1 == "QUIT")		// if commands is quit
		{
			cin.ignore();			// clears newline in buffer
			quit = true;			// ends while loop and exits program
		}
		else if (cmd1 == "search" || cmd1 == "SEARCH")	// if command is to search
		{	
			cin.ignore();			// clears newline in buffer
			Book->search();			// calls search function
		}
		else if (cmd1 == "print" || cmd1 == "PRINT")		// if command is to print
		{
			cin >> cmd2;		// gets either all commands or ID
			cin.ignore();		// clears buffer

			if (cmd2 == "all" || cmd2 == "ALL")				// if command is to print all
				Book->printall();		// calls print all function
			else
				Book->print(cmd2);	// calls print function 
		}
		else if (cmd1 == "file" || cmd1 == "FILE")			// if command is file
		{
			cin.ignore();	// clears buffer
			Book->file();	// calls file function
		}

		else if (cmd1 == "commands" || cmd1 == "COMMANDS")	// if command is to access list of commands
		{
			cin.ignore();		// clears buffer
			printcmds();	// calls function to print all commands
		}
		else if (cmd1 == "ftree" || cmd1 == "FTREE")
		{
			cin >> cmd2;
			cin.ignore();

			Book->print_tree(cmd2);
		}
		else if (cmd1 == "add" || cmd1 == "ADD")			// if command is to add
		{
			cin >> cmd2;	// gets second command

			if (cmd2 == "name" || cmd2 == "NAME")			// if second command is name
			{
				cin.ignore();								// clears buffer
				Book->add_name();				// calls add name function
			}
			else if (cmd2 == "spouse" || cmd2 == "SPOUSE")	// if second command is spouse
			{
				cin >> homeID;								
				cin.ignore();					// clears buffer
				Book->add_spouse(homeID);		// add spouse function
			}
			else if (cmd2 == "child" || cmd2 == "CHILD")
			{
				cin >> homeID;
				cin.ignore();					// clears buffer
				Book->add_child(homeID);		// add child function	
			}
			else if (cmd2 == "address1" || cmd2 == "ADDRESS1")
			{
				cin >> ID;
				cin.ignore();					// clears buffer
				Book->add_address(ID);			// add address function
			}
			else if (cmd2 == "city" || cmd2 == "CITY")
			{
				cin >> ID;
				cin.ignore();					// clears buffer
				Book->add_city(ID);				// add city function
			}
			else if (cmd2 == "state" || cmd2 == "STATE")
			{
				cin >> ID;
				cin.ignore();					// clears buffer
				Book->add_state(ID);			// add state function
			}		
			else if (cmd2 == "zip" || cmd2 == "ZIP")
			{
				cin >> ID;
				cin.ignore();					// clears buffer
				Book->add_zip(ID);				// add zip function
			}
			else if (cmd2 == "date_birth" || cmd2 == "DATE_BIRTH")
			{
				cin >> ID;
				cin.ignore();					// clears buffer
				Book->add_birthday(ID);			// add birthday function
			}
			else if (cmd2 == "date_wedding" || cmd2 == "DATE_WEDDING")
			{
				cin >> ID;
				cin.ignore();					// clears buffer
				Book->add_weddingdate(ID);		// add weddingdate function
			}
			else if (cmd2 == "date_death" || cmd2 == "DATE_DEATH")
			{
				cin >> ID;
				cin.ignore();					// clears buffer
				Book->add_deathdate(ID);		// add deathdate function
			}
			else			// if no valid command 2
			{
				string input;
				getline(cin, input, '\n');					// clears rest of input
				cout << endl << "Invalid input!" << endl;	// prints error
			}
		}
		else	// if no valid command 1
		{
			string input;
			getline(cin, input, '\n');					// clears rest of input
			cout << endl << "Invalid input!" << endl;	// prints error
		}
	}
}

void printcmds(void)
{
	system("clear");			// clears screen
	cout << endl << "******************************************************************";		// list of commands
	cout << endl << "** NOTE: Type you can enter all commands and fields on one line **";
	cout << endl << "**       i.e. add name John Smith (ENTER)                       **";
	cout << endl << "**       Commands can be all uppercase or all lower case        **";
	cout << endl << "******************************************************************";
	cout << endl << endl;
	cout << endl << "COMMAND          COMMAND FIELD	   DESCRIPTION";
	cout << endl << "add name         <name>           Add a new name (First Last) to the Address Book";
	cout << endl << "add spouse       <uid> <name>     Add spouse of <uid> (First Last) to the Address Book";
	cout << endl << "add child        <uid> <name>     Add a child of <uid> (First Last) to the Address Book";
	cout << endl << "add address1     <uid> <address>  Add/change address for <uid>";
	cout << endl << "add city         <uid> <city>	   Add/change city for <uid>";
	cout << endl << "add state        <uid> <state>    Add/change state for <uid>";
	cout << endl << "add zip          <uid> <zipcode>  Add/change zipcode for <uid>";
	cout << endl << "add date         <uid> <ddmmyyyy> Add/change birthday for <uid>";
	cout << endl << "add date_wedding <uid> <ddmmyyyy> Add/change wedding day for <uid>";
	cout << endl << "add date_death   <uid> <ddmmyyyy> Add/change date of death for <uid>";
	cout << endl << "search           <name>           Searches for name (First Last) and returns the <uid>, if found";
	cout << endl << "print all                         Prints list of all name in Address Book with their <uid>";
	cout << endl << "print            <uid>            Print all information for <uid>";
	cout << endl << "file                              Loads file from directory given by user (.csv files only)";
	cout << endl << "ftree            <uid>            Prints family tree of up to three generations from parent <uid>";
	cout << endl << "commands                          Reprint the list of commands";	
	cout << endl << "quit                              Exits program";
	cout << endl;
}