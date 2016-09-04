//****************************************************************************
//       CLASS:  CSCE-2100.021
//  ASSIGNMENT:  Program 4
//     STUDENT:  Andrew Tolle
// DESCRIPTION:  This program creates an address book. It loads data from a 
//				 .csv file.
//
//				 This file contains classes for Person (people in the address 
//				 book) and Address Book (which stores the people).
//
//
// REQUIRED SOURCE FILES:   D_00_P4_main.cpp   
//							D_00_P4_func.cpp			
//							D_00_P4_func.h						
//
//
//****************************************************************************
#include <iostream>		// declares iostream header for cin cout
#include <iomanip>		// declares iomanip to format output
#include <string>		// declares string header for string manipulation
#include <limits>		// declares limits header to check for correct input
#include <fstream>		// declares header file for file i/o
#include <sstream>		// declares header file for string streams
#include <list>			// declares header file for list in STL
#include <algorithm>	// declares header file for sorting
#include <sys/ioctl.h>	// declares header file for window width formatting
using namespace std;

class Person			// class for people to be entered in Address Book
{
private:

	string ID;				// person ID number
	string firstname;
	string lastname;
	string address;		// i.e. 1234 some road
	string city;
	string state;
	string zip;
	string birthday;
	string wedding_date;
	string death_date;
	Person *spouse_ptr;		// pointer to spouse's location in list
	int num_child;
	list<Person *> children;			// list of pointers to the children


public:

	Person(){}				// contructor that does nothing

	Person(string id)			// constructor for adding people from the menu
	{
		set_ID(id);			// calls set functions for person's information
	}

	Person(string id, string fn, string ln)	// constructor for to initialize from loaded .csv file
	{
		set_ID(id);				// sets ID and last name to passed values
		set_firstname(fn);
		set_lastname(ln);
		address = "";
		city = "";
		state = "";
		zip = "";
		birthday = "";
		wedding_date = "";
		death_date = "";
		num_child = 0;
		spouse_ptr = NULL;
	}

	string get_ID()				{ return ID; }				// get functions for private data
	string get_lastname()		{ return lastname; }
	string get_firstname()		{ return firstname; }
	string get_name()			{ return firstname + " " + lastname; }
	string get_address()		{ return address; }
	string get_city()			{ return city; }
	string get_state()			{ return state; }
	string get_zip()			{ return zip; }
	string get_birthday()		{ return birthday; }
	string get_deathdate()		{ return death_date; }
	string get_weddingdate()	{ return wedding_date; }
	Person *get_spouseptr()		{ return spouse_ptr; }
	int get_numchild()			{ return num_child; }
	list<Person *> get_children() { return children; }
	
	bool has_spouse()			
	{ 
		if (spouse_ptr != NULL)
			return true;
		else
			return false;
	}

	void set_ID(string id)			{ ID = id; }	// sets ID to passed value PASS WHEN MAKING NEW PERESON SO IT'LL ITERATE

	void set_firstname(string first)		{ firstname = first; }	// sets first name to passed variable

	void set_lastname(string last)		{ lastname = last; }	// sets last name to passed variable

	void set_address(string a)		{ address = a; }		// sets address to passed variable

	void set_city(string c)			{ city = c; }				// sets city to passed variable

	void set_state(string s)		{ state = s; }			// sets state to passed variable

	void set_zip(string z)			{ zip = z; }			// sets zip to passed variable

	void set_birthday(string b)		{ birthday = b; }		// sets birthday to passed variable

	void set_deathdate(string d)	{ death_date = d; }		// sets death date to passed variable

	void set_weddingdate(string w)	{ wedding_date = w; }	// sets wedding date to passed variable

	void set_spouseptr(Person *node) { spouse_ptr = node; }	// sets spouse pointer to spouse's node

	void set_child(Person *child)							// adds a child pointer to the list of child pointers
	{
		children.push_back(child);
		num_child++;
	}

	void printperson()			// prints person's information
	{
		cout << endl << setw(14) << right <<"UID: " << ID;						// right justifies the information for the person
		cout << endl << setw(14) << right << "NAME: " << get_name();			// prints each field
		cout << endl << setw(14) << right << "ADDRESS1: " << address;
		cout << endl << setw(14) << right << "CITY: " << city;
		cout << endl << setw(14) << right << "STATE: " << state;
		cout << endl << setw(14) << right << "ZIP: " << zip;
		cout << endl << setw(14) << right << "DATE BIRTH: " << birthday;
		cout << endl << setw(14) << right << "DATE DEATH: " << death_date;
		cout << endl << setw(14) << right << "DATE WEDDING: " << wedding_date;
		if (spouse_ptr != NULL)		// if the person has a spouse
			cout << endl << setw(14) << right << "SPOUSE: " << spouse_ptr->get_name();
		else                        // if no spouse
			cout << endl << setw(14) << right << "SPOUSE: ";
		if (!children.empty())						// checks to see if person has children
		{
			list<Person *>::iterator iter;
			int i = 1;							// counter for num_children
			for (iter = children.begin(); iter != children.end(); ++iter)			// prints each child
			{
				cout << endl << setw(11) << right << "CHILD" << i << ": " << (*iter)->get_name();
				i++;
			}
		}
		else                  // if no children
			cout << endl << setw(14) << right << "CHILD1: " << endl;
	}
};

struct CompareNames									// overload for sorting algorithm
{													// sorts Person objects by name
	bool operator()(Person &a, Person &b)
	{
		return (a.get_lastname() + a.get_firstname()) < (b.get_lastname() + b.get_firstname());
	}
};

class Address_Book			// address book class to collect persons
{
private:

	list<Person> person_list;				// creates list for people in address book
	int p_cnt;								// counter for all people, used to make IDs

public:

	Address_Book()
	{
		p_cnt = 1;							// initializes first ID number
	}

	int get_pcnt()		{ return p_cnt; }
	
	void add_name(istream &stream = cin)			// function for adding new person
	{																			// stream defaults to cin unless passed a file
		stringstream ss;			// string stream to format ID
		string name, ID, fname, lname, input;			// string for ID and name

		ss << setw(3) << setfill('0') << p_cnt;		// formats ID to IDxxx
		ID = "ID" + ss.str();

		if (&stream == &cin)						// if the stream is cin it reads until newline
		{
			getline(stream, fname, ' ');
			getline(stream, lname, '\n');
		}
		else                                       // if the stream is file it reads until comma
		{
			getline(stream, fname, ' ');
			getline(stream, lname, ',');
		}

		fname.erase(remove(fname.begin(), fname.end(), ','), fname.end());	// strips commas from names
		lname.erase(remove(lname.begin(), lname.end(), ','), lname.end());

		name = fname + ' ' + lname;					// combines first and last name

		list<Person>::iterator iter;											// iterator to check for duplicate names

		for (iter = person_list.begin(); iter != person_list.end(); ++iter)		// checks for duplicate names
		{
			if (name == iter->get_name())
			{
				cout << endl << "DUPLICATE: " << iter->get_name() << "  UID: " << iter->get_ID() << endl;
				return;
			}
		}

		Person p(ID,fname,lname);		// creates person with unique id

		person_list.push_back(p);					// adds person to end of list and prints success message

		cout << endl << "ADDED: " << person_list.back().get_name() << "  UID: " << person_list.back().get_ID() << endl;

		person_list.sort(CompareNames());			// sorts list

		p_cnt++;				// increments ID for next person
	}

	void add_spouse(string homeID, istream &stream = cin)								// function for adding spouse
	{																					// stream defaults to cin unless passed a file
		stringstream ss;				// string stream to format ID
		string ID, fname, lname, name;	// strings for ID, name, first and last name
		int ID_check = 0;					// int to check if ID is in list
		list<Person>::iterator iter;		// iterators to navigate list

		for (iter = person_list.begin(); iter != person_list.end(); ++iter)		// checks for ID in list
		{
			if (homeID == iter->get_ID())											// if ID is in list, ID_check is set to true
				ID_check = 1;
		}

		if (ID_check == 0)			// prints error if ID not in list
		{
			cout << endl << "Error: Spouse ID not in list" << endl;

			if (&stream != &cin)
				getline(stream, ID, '\r');	// clears rest of input from file
			else
				getline(stream, ID, '\n');

			return;
		}
		else                       // if ID in list
		{
			ss << setw(3) << setfill('0') << p_cnt;		// formats ID to IDxxx
			ID = "ID" + ss.str();

		if (&stream == &cin)						// if the stream is cin it reads until newline
		{
			getline(stream, fname, ' ');
			getline(stream, lname, '\n');
		}
		else                                       // if the stream is file it reads until carriage return
		{
			getline(stream, fname, ' ');
			getline(stream, lname, '\r');
		}

			fname.erase(remove(fname.begin(), fname.end(), ','), fname.end());	// strips commas from names
			lname.erase(remove(lname.begin(), lname.end(), ','), lname.end());

			name = fname + ' ' + lname;					// combines names

			for (iter = person_list.begin(); iter != person_list.end(); ++iter)		// checks for duplicate names
			{
				if (name == iter->get_name())
				{
					cout << endl << "ALREADY IN LIST: " << iter->get_name() << "  UID: " << iter->get_ID() << endl;
					return;
				}
			}

			Person p(ID, fname, lname);		// creates person with unique id

			person_list.push_back(p);					// adds person to end of list and prints success message

			cout << endl << "ADDED: " << person_list.back().get_name() << "  UID: " << person_list.back().get_ID() << endl;

			for (iter = person_list.begin(); iter != person_list.end(); ++iter)		// sets spouse pointer
			{
				if (homeID == iter->get_ID())										// finds home ID
				{
					iter->set_spouseptr(&person_list.back());	// sets spouse pointers to each other		
					person_list.back().set_spouseptr(&*iter);
				}
			}

			person_list.sort(CompareNames());	// sorts list

			p_cnt++;				// increments ID for next person
		}
	}
	
	void add_child(string homeID, istream &stream = cin)										// function for adding child
	{																					// stream defaults to cin unless passed a file
		stringstream ss;				// string stream to format ID
		string ID, fname, lname, name;	// strings for ID, name, first and last name
		int ID_check = 0;					// int to check if ID is in list
		list<Person>::iterator iter;		// iterators to navigate list

		for (iter = person_list.begin(); iter != person_list.end(); ++iter)		// checks for ID in list
		{
			if (homeID == iter->get_ID())											// if ID is in list, ID_check is set to true
				ID_check = 1;
		}
		
		if (ID_check == 0)			// prints error if ID not in list
		{
			cout << endl << "Error: Parent ID not in list" << endl;

			if (&stream != &cin)
				getline(stream, ID, '\r');	// clears rest of input from file
			else
				getline(stream, ID, '\n');

			return;
		}
		else                       // if ID in list
		{
			ss << setw(3) << setfill('0') << p_cnt;		// formats ID to IDxxx
			ID = "ID" + ss.str();

		if (&stream == &cin)						// if the stream is cin it reads until newline
		{
			getline(stream, fname, ' ');
			getline(stream, lname, '\n');
		}
		else                                       // if the stream is file it reads until carriage return
		{
			getline(stream, fname, ' ');
			getline(stream, lname, '\r');
		}

			fname.erase(remove(fname.begin(), fname.end(), ','), fname.end());	// strips commas from names
			lname.erase(remove(lname.begin(), lname.end(), ','), lname.end());

			name = fname + ' ' + lname;				// combines names
				
			for (iter = person_list.begin(); iter != person_list.end(); ++iter)		// checks for duplicate names
			{
				if (name == iter->get_name())
				{
					cout << endl << "ALREADY IN LIST: " << iter->get_name() << "  UID: " << iter->get_ID() << endl;
					return;
				}
			}

			Person p(ID, fname, lname);		// creates person with unique id

			person_list.push_back(p);					// adds person to end of list and prints success message

			cout << endl << "ADDED: " << person_list.back().get_name() << "  UID: " << person_list.back().get_ID() << endl;

			for (iter = person_list.begin(); iter != person_list.end(); ++iter)		// sets spouse pointer
			{
				if (homeID == iter->get_ID())											// sets spouse to point to other spouse
					iter->set_child(&person_list.back());
			}

			person_list.sort(CompareNames());	// sorts list

			p_cnt++;				// increments ID for next person
		}
	}

	void add_address(string ID, istream &stream = cin)									// function to add city to person
	{																					// stream defaults to cin unless passed a file
		string address;

		list<Person>::iterator iter;											// iterator to check ID

		for (iter = person_list.begin(); iter != person_list.end(); ++iter)		// checks for ID
		{
			if (ID == iter->get_ID())				// if ID exists 
			{
				if (&stream == &cin)						// if the stream is cin it reads until newline
					getline(stream, address, '\n');
				else                                       // if the stream is file it reads until carriage return
					getline(stream, address, '\r');

				address.erase(remove(address.begin(), address.end(), ','), address.end());	// strips commas from input

				iter->set_address(address);
				cout << endl << "ADDED ADDRESS1: " << iter->get_address() << "  UID: " << iter->get_ID() << endl;
				return;
			}
		}

		cout << endl << "Error: ID not in list" << endl;		// if ID not found

		if (&stream == &cin)						// clears input
			getline(stream, address);
	}

	void add_city(string ID, istream &stream = cin)										// function to add city to person
	{																					// stream defaults to cin unless passed a file
		string city;

		list<Person>::iterator iter;											// iterator to check ID

		for (iter = person_list.begin(); iter != person_list.end(); ++iter)		// checks for ID
		{
			if (ID == iter->get_ID())				// if ID exists 
			{
				if (&stream == &cin)						// if the stream is cin it reads until newline
					getline(stream, city, '\n');
				else                                       // if the stream is file it reads until carriage return
					getline(stream, city, '\r');				

				city.erase(remove(city.begin(), city.end(), ','), city.end());	// strips commas from input

				iter->set_city(city);
				cout << endl << "ADDED CITY: " << iter->get_city() << "  UID: " << iter->get_ID() << endl;
				return;
			}
		}
													
		cout << endl << "Error: ID not in list" << endl;	// if city not found

		if (&stream == &cin)						// clears input
			getline(stream, city);
	}

	void add_state(string ID, istream &stream = cin)				// function to add state to person
	{
		string state;

		list<Person>::iterator iter;											// iterator to check ID

		for (iter = person_list.begin(); iter != person_list.end(); ++iter)		// checks for ID
		{
			if (ID == iter->get_ID())				// if ID exists 
			{
				if (&stream == &cin)						// if the stream is cin it reads until newline
					getline(stream, state, '\n');
				else                                       // if the stream is file it reads until carriage return
					getline(stream, state, '\r');				

				state.erase(remove(state.begin(), state.end(), ','), state.end());	// strips commas from input

				iter->set_state(state);
				cout << endl << "ADDED STATE: " << iter->get_state() << "  UID: " << iter->get_ID() << endl;
				return;
			}
		}

		cout << endl << "Error: ID not in list" << endl;	// if ID not found

		if (&stream == &cin)						// clears input
			getline(stream, state);
	}

	void add_zip(string ID, istream &stream = cin)										// function to add zip to person
	{																					// stream defaults to cin unless passed a file
		string zip;

		list<Person>::iterator iter;											// iterator to check ID

		for (iter = person_list.begin(); iter != person_list.end(); ++iter)		// checks for ID
		{
			if (ID == iter->get_ID())				// if ID exists
			{
				if (&stream == &cin)						// if the stream is cin it reads until newline
					getline(stream, zip, '\n');
				else                                       // if the stream is file it reads until carriage return
					getline(stream, zip, '\r');				

				zip.erase(remove(zip.begin(), zip.end(), ','), zip.end());	// strips commas from input

				iter->set_zip(zip);
				cout << endl << "ADDED ZIP: " << iter->get_zip() << "  UID: " << iter->get_ID() << endl;
				return;
			}
		}

		cout << endl << "Error: ID not in list" << endl;		// if ID not found

		if (&stream == &cin)						// clears input
			getline(stream, zip);
	}

	void add_birthday(string ID, istream &stream = cin)									// function to add birthday to person
	{																					// stream defaults to cin unless passed a file
		string birthday;

		list<Person>::iterator iter;											// iterator to check ID

		for (iter = person_list.begin(); iter != person_list.end(); ++iter)		// checks for ID
		{
			if (ID == iter->get_ID())				// if ID exists 
			{
				if (&stream == &cin)						// if the stream is cin it reads until newline
					getline(stream, birthday, '\n');
				else                                       // if the stream is file it reads until carriage return
					getline(stream, birthday, '\r');	

				birthday.erase(remove(birthday.begin(), birthday.end(), ','), birthday.end());	// strips commas from input								

				iter->set_birthday(birthday);
				cout << endl << "ADDED BIRTHDAY: " << iter->get_birthday() << "  UID: " << iter->get_ID() << endl; 
				return;
			}
		}

		cout << endl << "Error: ID not in list" << endl;		// if ID not found

		if (&stream == &cin)						// clears input
			getline(stream, birthday);
	}

	void add_deathdate(string ID, istream &stream = cin)								// function to add death date to person
	{																					// stream defaults to cin unless passed a file
		string deathdate;

		list<Person>::iterator iter;											// iterator to check ID

		for (iter = person_list.begin(); iter != person_list.end(); ++iter)		// checks for ID
		{
			if (ID == iter->get_ID())				// if ID exists 
			{
				if (&stream == &cin)						// if the stream is cin it reads until newline
					getline(stream, deathdate, '\n');
				else                                       // if the stream is file it reads until carriage return
					getline(stream, deathdate, '\r');	

				deathdate.erase(remove(deathdate.begin(), deathdate.end(), ','), deathdate.end());	// strips commas from input								

				iter->set_deathdate(deathdate);
				cout << endl << "ADDED DEATH DATE: " << iter->get_deathdate() << "  UID: " << iter->get_ID() << endl; 
				return;
			}
		}

		cout << endl << "Error: ID not in list" << endl;	// if ID not found

		if (&stream == &cin)						// clears input
			getline(stream, deathdate);
	}

	void add_weddingdate(string ID, istream &stream = cin)								// function to add wedding date to person
	{																					// stream defaults to cin unless passed a file
		string weddingdate;

		list<Person>::iterator iter;											// iterator to check ID

		for (iter = person_list.begin(); iter != person_list.end(); ++iter)		// checks for ID
		{
			if (ID == iter->get_ID())				// if ID exists
			{
				if (&stream == &cin)						// if the stream is cin it reads until newline
					getline(stream, weddingdate, '\n');
				else                                       // if the stream is file it reads until carriage return
					getline(stream, weddingdate, '\r');				

				weddingdate.erase(remove(weddingdate.begin(), weddingdate.end(), ','), weddingdate.end());	// strips commas from input				

				iter->set_weddingdate(weddingdate);
				cout << endl << "ADDED WEDDING DATE: " << iter->get_weddingdate() << "  UID: " << iter->get_ID() << endl;
				return;
			}
		}

		cout << endl << "Error: ID not in list" << endl;		// if ID not found

		if (&stream == &cin)						// clears input
			getline(stream, weddingdate);
	}

	void search(istream &stream = cin)		// search function to find person
	{										// stream defaults to cin unless passed a file
		string name, fname, lname;	// name to search for

		if (&stream == &cin)						// if stream is cin
			getline(stream, name);					// gets name
		else                                    // if stream is fule
		{
			getline(stream, fname, ' ');		// reads names until comma
			getline(stream, lname, ',');

			name = fname + " " + lname;			// combines names
		}

		list<Person>::iterator iter;		// iterator to search list

		for (iter = person_list.begin(); iter != person_list.end(); ++iter)
		{
			if (iter->get_name() == name)	// if name is found
			{
				cout << endl << "FOUND: " << iter->get_name() << "  UID: " << iter->get_ID() << endl;
				return;			// returns to menu
			}
		}
		// if name is not found
		cout << endl << "NOT FOUND: " << name << endl;
	}

	void print(string ID, istream &stream = cin)									// function to print info for a person
	{																					// stream defaults to cin unless passed a file
		string input;

		list<Person>::iterator iter;	// iterator to navigate list

		if (person_list.size() > 0)		// checks to make sure people are in list
		{
			for (iter = person_list.begin(); iter != person_list.end(); ++iter)
			{
				if (ID == iter->get_ID())		// looks up ID
				{
					iter->printperson();		// prints person's info
					cout << endl;
					return;
				}
			}
		}
		else		// if no people in list
		{
			getline(cin, input, '\n');				// clears input
			cout << endl << "No entires in Address Book" << endl;
			return;
		}

		cout << endl << "Error: ID not in list" << endl;	// if ID not found

		if (&stream == &cin)						// clears input
			getline(stream, input);					
	}

	void printall()	// function to print info for a person
	{
		string input;

		list<Person>::iterator iter;	// iterator to navigate list

		if (person_list.size() > 0)		// checks to make sure people are in list
		{
			for (iter = person_list.begin(); iter != person_list.end(); ++iter)
				cout << endl << setw(20) << left << iter->get_name() << "UID: " << iter->get_ID() << endl;				
		}
		else		// if no people in list
			cout << endl << "No entires in Address Book" << endl;
	}

	void print_tree(string ID, istream &stream = cin)	// spw = spouse width, nspw = no spouse width
	{				
  		struct winsize w;			// gets window width
    	ioctl(0, TIOCGWINSZ, &w);

    	int pw = w.ws_col / 2;		// sets window width for parents
    	int cw = 0;					// width for children
    	int grw = 0;				// width for grandchildren
		int ID_check = 0;		// to check ID in list
		int grchcounter;		// to count grandchildren to account for spouses

		list<Person>::iterator iter;	// iterator to navigate list
		list<Person *>::iterator ch_iter; // iterator for children
		list<Person *>::iterator gr_iter; // iterator for children
		list<Person *> childlist;			// list of children
		list<Person *> grchildlist;			// list of grandchildren

		if (person_list.size() > 0)		// checks to make sure people are in list
		{
			for (iter = person_list.begin(); iter != person_list.end(); ++iter)
			{
				if (ID == iter->get_ID())		// looks up ID
				{
					ID_check = 1;				// if ID is found
					break;
				}
			}

			if (ID_check)	// if ID found
			{
				// ********************
				// ** PRINTS PARENTS **
				// ********************
				if (iter->has_spouse())		// prints parent node for spouse or no spouse
					cout << setw(pw - iter->get_name().size() - 4) << right << "|" << iter->get_name() << "|--+--|" << iter->get_spouseptr()->get_name() << "|" << endl; // - 4 to account for the 
				else 																																					 // ||--
					cout << setw(pw - (iter->get_name().size() / 2) - 1) << right << "|" << iter->get_name() << "|" << endl;
				
				if (iter->get_numchild() > 0)	// if parent node has children
				{	
					// ****************************
					// ** PRINTS | BELOW PARENTS **
					// ****************************
					if (iter->has_spouse())		// prints formatting | line below parent node
						cout << setw(pw) << "|" << endl;
					else
						cout << setw(pw) << "|" << endl;

					childlist = iter->get_children();		// copies list of children

					cw = w.ws_col / iter->get_numchild() / 2;		// reset width for number of children
																		// divided by two to get middle of area

					// ***************************************************
					// ** PRINTS --- ABOVE SIBLINGS OR | IF NO SIBLINGS **
					// ***************************************************
					if (iter->get_numchild() > 1)
					{
						cout << setw(cw - 1) << right << "";
						int child = 1;
						cout << "|";
						while (child < iter->get_numchild())
						{
							for (int i = 0; i < ((cw * 2) - 1); i++)	// (cw * 2) - 1 is for twice the width of the children to reach each node minus one
								cout << "-";							// to leave room for the | at the end
							cout << "|";
							child++;
						}
						cout << endl;
					}
					else if (iter->get_numchild() == 1)
					{
						cout << setw(cw - 1) << right << "";
						cout << "|";
						cout << endl;
					}

					// *********************
					// ** PRINTS CHILDREN **
					// *********************
					for (ch_iter = childlist.begin(); ch_iter != childlist.end(); ++ch_iter)	// print children
					{
						if ((*ch_iter)->has_spouse())	// if child has spouse
						{								// spaces name to cw (which is middle of area), then back the size of first spouse minus 4 for the formatting brackets
							cout << setw(cw - (*ch_iter)->get_name().size() - 4) << right << "|" << (*ch_iter)->get_name() << "|--+--|" << (*ch_iter)->get_spouseptr()->get_name() << "|";
							cout << setw(cw - (*ch_iter)->get_spouseptr()->get_name().size() - 4) << right << "";	// moves cursor to end of spouse bracket
						}
						else							// if no spouse
						{								// spaces name to cw (which is middle of area), then back half of the size of the name minus 1 for one side of the bracket
							cout << setw(cw - ((*ch_iter)->get_name().size() / 2) - 1) << right << "|" << (*ch_iter)->get_name() << "|";
							if ((*ch_iter)->get_name().size() % 2 == 0)
								cout << setw(cw - ((*ch_iter)->get_name().size() / 2)) << right << "";				// moves cursor to end of bracket
							else 
								cout << setw(cw - ((*ch_iter)->get_name().size() / 2) - 1) << right << "";				// moves cursor to end of bracket
						}				
					}

					cout << endl;	// next line

					// *****************************
					// ** PRINTS | BELOW CHILDREN **
					// *****************************
					for (ch_iter = childlist.begin(); ch_iter != childlist.end(); ++ch_iter)		// formatting | line below children
					{
						if(!(*ch_iter)->get_children().empty())		// if child has children then it'll print a line below them
						{
							if ((*ch_iter)->has_spouse())			// prints formatting line below each child
							{
								cout << setw(cw) << right << "|";
								cout << setw(cw) << right << "";
							}
							else
							{
								cout << setw(cw) << right << "|";
								cout << setw(cw) << right << "";
							}
						}
						else										// if child doesn't have children it move to the end of the area for that child
							cout << setw(cw * 2) << right << "";
					}

					cout << endl;	// next line

					grw = w.ws_col / iter->get_numchild() / 2;	// sets width for grandchildren - screen width divided by number of children
																	// divided by two to get middle of area

					// **************************************************************
					// ** PRINTS --- ABOVE GRANDCHILD SIBLINGS OR | IF NO SIBLINGS **
					// **************************************************************
					for (ch_iter = childlist.begin(); ch_iter != childlist.end(); ++ch_iter)
					{
						grchildlist = (*ch_iter)->get_children();	// creates list of grandchildren for each child node
					
						if (grchildlist.empty())									// if no grandchildren for the particular child node, then 
							cout << setw(w.ws_col / iter->get_numchild()) << "";	// that area is filled with blank space (width of screen divided by num of children)

						else if ((*ch_iter)->get_numchild() > 1)
						{
							if (grchildlist.size() == 3 && iter->get_numchild() == 2) 	// if number of kids is two it accounts for the spacing for 3 kids
							{
								cout << setw((grw / grchildlist.size()) - 1) << right << "";
								int child = 1;
								cout << "|";
								while (child < (*ch_iter)->get_numchild())
								{
									for (int i = 0; i < (((grw / grchildlist.size()) * 2) - 1); i++)	// grw is divided by grchildlist size to find space between grandchildren
										cout << "-";													// - 1 to leave room for the | at the end
									cout << "|";
									child++;
								}
								cout << setw(grw / grchildlist.size()) << right << "";
							}
							else if (grchildlist.size() == 3)
							{
								cout << setw((grw / grchildlist.size()) - 1) << right << "";
								int child = 1;
								cout << "|";
								while (child < (*ch_iter)->get_numchild())
								{
									for (int i = 0; i < (((grw / grchildlist.size()) * 2)); i++)	// grw is divided by grchildlist size to find space between grandchildren
										cout << "-";													// - 1 to leave room for the | at the end
									cout << "|";
									child++;
								}
								cout << setw(grw / grchildlist.size()) << right << "";
							}
							else
							{
								cout << setw((grw / grchildlist.size()) - 1) << right << "";
								int child = 1;
								cout << "|";
								while (child < (*ch_iter)->get_numchild())
								{
									for (int i = 0; i < (((grw / grchildlist.size()) * 2) - 1); i++)	// grw is divided by grchildlist size to find space between grandchildren
										cout << "-";													// - 1 to leave room for the | at the end
									cout << "|";
									child++;
								}
								cout << setw(grw / grchildlist.size()) << right << "";
							}

						}
						else if ((*ch_iter)->get_numchild() == 1)		// if no siblings exist this prints a single | above the grandchild
						{
							cout << setw(grw - 1) << right << "";
							cout << "|";
							cout << setw(grw / grchildlist.size()) << right << "";
						}

					}

					cout << endl;		

					// **************************
					// ** PRINTS GRANDCHILDREN **
					// **************************
					for (ch_iter = childlist.begin(); ch_iter != childlist.end(); ++ch_iter)
					{
						grchildlist = (*ch_iter)->get_children();	// creates list of grandchildren for each child node
					
						grchcounter = 0;

						if (grchildlist.empty())									// if no grandchildren for the particular child node, then 
							cout << setw(w.ws_col / iter->get_numchild()) << right << "";	// that area is filled with blank space (width of screen divided by num of children)
						else														
						{
							for (gr_iter = grchildlist.begin(); gr_iter != grchildlist.end(); ++gr_iter)
							{
								if ((*gr_iter)->has_spouse())
									grchcounter += 2;					// counts grandchildren including spouses for spacing
								else
									grchcounter++;
							}

							for (gr_iter = grchildlist.begin(); gr_iter != grchildlist.end(); ++gr_iter)
							{
								if ((*gr_iter)->has_spouse() && grchildlist.size() == 1)
								{	// prints grandchild spaced by width divided by number of grandchildren 
									cout << setw((grw / grchildlist.size()) - (*gr_iter)->get_name().size() - 4) << right << "|" << (*gr_iter)->get_name() << "|--+--|" << (*gr_iter)->get_spouseptr()->get_name() << "|";
									cout << setw((grw / grchildlist.size()) - (*gr_iter)->get_spouseptr()->get_name().size() - 4) << "";	// moves cursor
								}
								else if ((*gr_iter)->has_spouse())	// if grandchild has spouse
								{	// prints grandchild spaced by width divided by number of grandchildren 
									cout << setw((grw / grchcounter) - (*gr_iter)->get_name().size() - 4) << right << "|" << (*gr_iter)->get_name() << "|--+--|" << (*gr_iter)->get_spouseptr()->get_name() << "|";
									cout << setw((grw / grchcounter) - (*gr_iter)->get_spouseptr()->get_name().size() - 4) << "";	// moves cursor
								}
								else if(!(*gr_iter)->has_spouse() && grchcounter > grchildlist.size())	// if no spouse but grandchild has sibling with a spouse
								{
									if ((*gr_iter)->get_name().size() % 2 == 0)	// if name is even then it doesn't need to account for the extra letter when divided by two
									{
										cout << setw((grw / grchcounter) - ((*gr_iter)->get_name().size() / 2) - 1) << right << "|" << (*gr_iter)->get_name() << "|";
										cout << setw((grw / grchcounter) - ((*gr_iter)->get_name().size() / 2) + 2) << "";				// moves cursor
									}
									else	// if name is odd then it accounts for the extra letter by - 1
									{		
										cout << setw((grw / grchcounter) - ((*gr_iter)->get_name().size() / 2) - 1) << right << "|" << (*gr_iter)->get_name() << "|";
										cout << setw((grw / grchcounter) - ((*gr_iter)->get_name().size() / 2) - 1) << "";				// moves cursor	
									}
								}
								else							// if no spouse
								{	// prints grandchild spaced by width divided by number of grandchildren
									cout << setw((grw / grchildlist.size()) - ((*gr_iter)->get_name().size() / 2) - 1) << right << "|" << (*gr_iter)->get_name() << "|";
									if ((*gr_iter)->get_name().size() % 2 == 0)	// if name is even then it doesn't need to account for the extra letter when divided by two
										cout << setw((grw / grchildlist.size()) - ((*gr_iter)->get_name().size() / 2) + 1) << "";				// moves cursor
									else										// if name is odd then it accounts for the extra letter by - 1
										cout << setw((grw / grchildlist.size()) - ((*gr_iter)->get_name().size() / 2) - 1) << "";				// moves cursor	
								}	
							}
						}
					}
				}
			}
			else	// if ID not in list
				cout << endl << "Error: ID not in list" << endl;
		}
	}


	void file()		// function for reading from .csv file
	{
		ifstream file;			// opens in stream
		string filename;
		string input;			// reads each word
		string fname, lname;	// to read in names
		string addy;			// address info

		getline(cin, filename, '\n');	// reads in filename

		file.open(filename.c_str());	// opens file

		if (!file)		// if file could not open
			cout << endl << "ERROR: File could not be opened" << endl;
		else
		{
			while (file.good())	// loops until EOF
			{
				getline(file, input, ',');	// reads up to first comma

				if (input == "add" || input == "ADD")
				{
					getline(file, input, ',');	// reads until comma
					
					if (input == "name" || input == "NAME")
					{
						add_name(file);
						getline(file, input, '\n');		// clears rest of line
					}
					else if (input == "spouse" || input == "SPOUSE")
					{
						string homeID;
						getline(file, homeID, ',');
						add_spouse(homeID, file);	// calls add spouse function
						getline(file, input, '\n');		// clears rest of line
					}
					else if (input == "child" || input == "CHILD")
					{
						string homeID;
						getline(file, homeID, ',');
						add_child(homeID, file);	// calls add child function
						getline(file, input, '\n');		// clears rest of line
					}
					else if (input == "address1" || input == "ADDRESS1")
					{
						string ID;
						getline(file, ID, ',');
						add_address(ID, file);
						getline(file, input, '\n');		// clears rest of line
					}
					else if (input == "city" || input == "CITY")			// calls add city function
					{
						string ID;
						getline(file, ID, ',');
						add_city(ID, file);	// calls add city function
						getline(file, input, '\n');		// clears rest of line
					}
					else if (input == "state" || input == "STATE")
					{
						string ID;
						getline(file, ID, ',');
						add_state(ID, file);	// calls add state function
						getline(file, input, '\n');		// clears rest of line
					}
					else if (input == "zip" || input == "ZIP")
					{
						string ID;
						getline(file, ID, ',');
						add_zip(ID, file);	// calls add zip function
						getline(file, input, '\n');		// clears rest of line
					}
					else if (input == "date_birth" || input == "DATE_BIRTH")
					{
						string ID;
						getline(file, ID, ',');
						add_birthday(ID, file);	// calls add birthday function
						getline(file, input, '\n');		// clears rest of line
					}
					else if (input == "date_wedding" || input == "DATE_WEDDING")
					{
						string ID;
						getline(file, ID, ',');
						add_weddingdate(ID, file);	// calls add wedding date function
						getline(file, input, '\n');		// clears rest of line
					}
					else if (input == "date_death" || input == "DATE_DEATH")
					{
						string ID;
						getline(file, ID, ',');
						add_deathdate(ID, file);	// calls add wedding date function
						getline(file, input, '\n');		// clears rest of line
					}
					else if (input == "")				// skips blank input
						getline(file, input, '\n');
					else
					{
						string input;
						getline(file, input, '\n');					// clears rest of input
						cout << endl << "Invalid input!" << endl;	// prints error
					}
				}
				else if (input == "search" || input == "SEARCH")
				{
					search(file);	// calls search function
					getline(file, input, '\n');		// clears rest of input
				}
				else if (input == "print" || input == "PRINT")
				{
					getline(file, input, ',');

					if (input == "all" || input == "ALL")
					{
						printall();		// calls print all function 
						getline(file, input, '\n');		// clears rest of input
					}
					else
					{
						print(input, file);				// calls print function
						getline(file, input, '\n');		// clears rest of input
					}
				}	
				else if (input == "ftree" || input == "FTREE")		// calls family tree print function
				{
					getline(file,input,',');				// gets ID
					print_tree(input, file);
					getline(file, input, '\n');
				}
				else if (input == "")				// skips blank input
					getline(file, input, '\n');
				else
				{
					string input;
					getline(file, input, '\n');					// clears rest of input
					cout << endl << "Invalid input!" << endl;	// prints error
				}
			}

			file.close();		// closes file
			cout << endl;		// formatting newline
		}
	}
};
