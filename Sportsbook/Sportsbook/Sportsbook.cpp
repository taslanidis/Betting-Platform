// Sportsbook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Users_categories.h"
#include "Main_functions.h"
#include "hierarchy.h"
#include "BetAtzis.h"

using namespace std;

int main(int argc, char *argv[])
{
	//for starters we are not going to use the preprocessing #ifdef, but remain in a known environment of argv,argc
	string username, password, appuser;
	string parameter;
	if (argv[1] != NULL) {
		parameter = argv[1];
	}
	bool registration_flag = true;
	// Eggrafi part
	// #ifdef -R    // preproccesing compilation of registration part
	if (parameter == "-R") {
		cout << "<username> ";
		cin >> username;
		fstream file("users.csv", std::fstream::in);
		if (file.is_open()) {
			getline(file, appuser); //this takes the line and put it to string appuser
			while (!appuser.empty() && !file.eof()) {
				size_t pos1, pos2;
				pos1 = appuser.find("|");
				appuser = appuser.substr(pos1+1);
				pos2 = appuser.find("|");
				appuser = appuser.erase(pos2);
				if ((appuser.compare(username) == 0)) { //this takes the line and check if there is a word in there mathcing to the given username
					cout << "There is already a register with that username!" << endl;
					registration_flag = false;
					file.close(); //to kleinw prin termatisei to programma
					return 0;
				}
				getline(file, appuser);
			}
			file.close();
			cout << "<password> ";
			cin >> password;
			cout << "Please enter your full name: ";
			string fullname;
			cin >> fullname;
			cout << endl;
			cout << "Registration succesfull" << endl;
			string last_appuser; 
			//get last line
			file.open("users.csv", std::fstream::in);
			do {
				last_appuser = appuser;
				getline(file, appuser); //mexri na ftasei stin teleutaia grammi
			} while (!appuser.empty() && !file.eof());
			string last_app = last_appuser;
			int id;
			last_app.erase((last_app.begin() + 1), last_app.end());
			if (last_app.compare("u") || last_app.compare("U")) {
				id = get_id(last_appuser);
				id++;
			}
			else {
				id = 1;
			}
			string sid = to_string(id);
			string stype = to_string(1);
			file.close();
			file.open("users.csv", std::fstream::out | std::fstream::app);
			string new_user;
			new_user = sid + "|" + username + "|" + fullname + "|" + password + "|" + stype + "|" + "-" + "|" + "-" + "|" + "-" + "|";
			if (id == 1) {
				file << endl << new_user << endl;
			}
			else {
				file << new_user << endl;
			}
			file.close();
		}
		else {
			cout << "Can't open file.";
			return 0;
		}
	}
	// end of registration!
	// #endif 
	//Loading hierarchy

	cout << "Welcome to sportsbook" << endl << "Please enter your username and password for signing in. If you don't have an account please press enter, or type guest" << endl;
	registration_flag = false; //esto oti o xristis den exei eggrafei akoma
	User * uptr = new User;
	cout << "Username: ";
	cin >> username;
	if (username != "guest") {
		fstream file("users.csv", std::fstream::in);
		if (file.is_open()) {
			while (!file.eof() || appuser.empty()) {
				getline(file, appuser);
				//here will have to be a line where delete all the useless part of the line, and keeps only the username
				if ((appuser.find(username, 0)) != string::npos) {
					registration_flag = true;
					break;
				}
			}
			if (!registration_flag) {
				cout << "There is no register with that username. Please try again! " << endl;
			}
			cout << "Password: ";
			cin >> password;
			cout << endl;
			bool is_password_correct = check_for_password(username, password); //sinartisi pou psaxnei an to password einai to sosto gia to username pou exei dothei
			if (is_password_correct == true) {
				cout << "You have been logged in to the system succesfully" << endl;
				//procedure for finding the type
				//type in .csv is the 5th element
				int type = get_type(username);
				if (type == 1) {
					Punter punter(username, get_fullname(username), get_password(username), get_balance(username));
					uptr = &punter;
				}
				else if (type == 2) {
					Trader trader(username, get_fullname(username), get_password(username));
					uptr = &trader;
				}
				else if (type == 3) {
					Director director(username, get_fullname(username), get_password(username));
					uptr = &director;
				}
			}
			else {
				cout << "Password incorrect. Please try again!" << endl;
				return 0;
			}
		} //an den anoigei o fakelos!!!
		else {
			cout << "User files are missing. End of program!";
			return 0;
		}
	} //else -> an telika ekane type guest os username!!! --> xreiazetai enchancement na erxetai edo kai an apla pataei enter !!! <--
	else {
		cout << "Logged in as guest" << endl;
		Guest guest;
		uptr =  &guest;
	}
	BetAtzis* Interface = new BetAtzis;
	Interface->set_user(uptr);
	bool flag = true;
	string operation;
	do {
		cout << endl << "Location: ";
		Interface->print_location(); //ektupwnei thn trexon topo8esia
		Interface->print_options(); //ektupwnei tous komvous stous opoious mporoume na metavoume
		Interface->print_operations(); //ektupwnei tis leitourgies tou xrhsth
		cin >> operation;
		if ((isdigit(operation[0])==0)) {
			cout << "Input is character" << endl;
		}
		else {
			cout << "Input is number" << endl;
			int choice;
			if (!(istringstream(operation) >> choice)) choice = 0;
			Interface->set_level(choice);
			//flag = Interface->operation(operation); 
			
		}
	} while (flag == true);
	system("pause");
	return 0;
}