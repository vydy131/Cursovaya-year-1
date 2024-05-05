#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Classes.h"

using namespace std;

extern float COMMISION;												// Defined in Classes 

int main() {

	// Open datafile
	ifstream input("users.txt");
	if (!input.is_open()) {
		cout << "ERROR: can't open users.txt for read\n";			// This file must be created BEFORE running
		return -1;
	}

	// Read datafile
	bool tmpbb = false;
	User tmp;
	string line, part_line;
	vector<User> users;
	vector<string> lines;
	if (input.peek() != EOF) {										// This IF helps to work with files which have no text or
		while (!input.eof()) {										//		with empty files
			getline(input, line);
			for (char& symbol : line) {
				if (symbol == '|') {
					lines.push_back(part_line);
					part_line.clear();
					continue;
				}
				part_line.push_back(symbol);
			}
			tmp.rewrite(lines[0], lines[1], lines[2]);
			users.push_back(tmp);
			lines.clear();											// Here all data file is written into memory as vector of User-objects
		}
	}


	// User interface
	string tmps, tmpss;
	string phrase;
	bool tmpb = false;
	int tmpi;
	float money;

	vector <Oper> oper_vec;											// Print a manual

	cout << "Possible commands: \n'users' for show users \n'user' for new user \n'erase' for erase user \n'oper' for new operation \n'opers' for show operations \n'exit' for leaving\n\n";

	cout << "Enter the command: ";
	cin >> phrase;
	while (true) {

		if (phrase == "users") {									// Show all info about every user
			cout << "#\n";
			for (User& user : users) {								
				cout << "Name: " << user.getname() << 
					"\nPhone: " << user.getphone() << 
					"\nOperator: " << user.getoprtr() << 
					"\n#\n";
			}
		}

		if (phrase == "user") {										// Create new user
			string tmp1, tmp2, tmp3;
			cout << "Name: ";
			cin >> tmp1;
			cout << "Phone number: ";
			cin >> tmp2;
			if (users.size() != 0) {								// If list of users is not empty, search for users with same names and phones
				for (User& user : users) {
					if (tmp1 == user.getname() && tmp2 == user.getphone()) {
						cout << "That user is already inside, you can't create another profile\n";
						tmpb = true;
						break;										// Looking for another user with same data
					}
				}
			}
			if (tmpb == false) {
				cout << "Operator: ";								// Continue registration if there is no such user in database
				cin >> tmp3;
				tmp.rewrite(tmp1, tmp2, tmp3);
				users.push_back(tmp);
				cout << "Created\n";
			}
			tmpb = false;
		}

		if (phrase == "erase") {
			cout << "Enter the name: ";
			cin >> tmps;
			tmpb = false;
			for (int i = 0; i < users.size(); i++) {
				tmp = users[i];										// Try to find the position of FIRST object with that name
				if (tmp.getname() == tmps) {
					tmpb = true;
					tmpi = i;
					break;
				}
			}

			if (!tmpb) {
				cout << "There is no such user\n";
				tmps = " ";											// This code is here because of some old bug solving
				phrase = " ";										// Maybe this part doesn't matter IDK
				cin.ignore(100, '\n');
				continue;
			}
			else {
				cout << tmps << " has been erased\n";
				users.erase(users.begin() + tmpi);					// Here console will tell us that object has been erased
			}

		}

		if (phrase == "oper") {										// New operation

			cout << "Enter your phone number: ";
			cin >> tmps;
			for (User& user : users) {								// Try to find a first user with that phone number in database
				if (user.getphone() == tmps) {
					cout << "We have found a profile with that phone number. Is your name " << user.getname()
						<< " and your operator " << user.getoprtr() << "?\t";
					cin >> tmpss;

					if (tmpss == "no") {							// If this user was last with this number, the program goes to 'Enter the command'
						cout << "Ok, we will try to find another profile :)\n";
						continue;
					}

					if (tmpss == "yes") {							// Start to make operation
						cout << "Commision is " << COMMISION * 100 << "%\n";
						cout << "Enter your money: ";
						cin >> money;
						Oper* oper_ptr = new Oper(user, money);
						oper_vec.push_back(*oper_ptr);				// Save info about operation into memory
						oper_ptr->print_info();						// Print info about operation
						break;
						delete oper_ptr;
					}
				}
			}
		}

		if (phrase == "opers") {									// Print info about all operation from during session
			for (Oper& oper : oper_vec) {							//	does not include info about previos sessions
				oper.print_info();
			}
		}

		if (phrase == "exit") {
			break;													// Go to the futher code
		}

		cout << "Enter the command: ";
		cin >> phrase;
	}

	
	for (Oper& oper : oper_vec) {
		oper.add_to_file("operlog.txt");							// Save all operations from during session into file
	}																//	with 'add to the end' mode


	// Close read file, open as write file and save changes
	input.close();
	ofstream output("users.txt");									// Rewrite file only after all input
	if (!output.is_open()) {										//	so there is almost no chance to lost any data because crash
		cout << "ERROR: can't open users.txt for write\n";
		return -2;
	}
	for (int i = 0; i < users.size(); i++) {
		tmp = users[i];
		output << tmp.getname() << '|' << tmp.getphone() << '|' << tmp.getoprtr() << '|';
		if (i != users.size() - 1) {								// This line helps to avoid cases when the last line of the output file is empty
			output << '\n';
		}
	}
	output.close();
}