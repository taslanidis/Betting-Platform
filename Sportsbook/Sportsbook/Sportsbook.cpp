// Sportsbook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

int main(int argc, char *argv[])
{
	//for starters we are not going to use the preprocessing #ifdef, but remain in a known environment of argv,argc
	char parameter = atof(argv[0]);
	string username, password, appuser;
	bool registration_flag = true;
	// Eggrafi part
	// #ifdef -R    // preproccesing compilation of registration part
	if (parameter == 'R') {
		cout << "<username>" << endl << "<password>" << endl;
		cin >> username;
		cout << endl;
		cin >> password;
		fstream file("registrations.csv");
		if (file.is_open()) {
			while (!file.eof()) {
				getline(file, appuser); //this takes the line and put it to string appuser
				if ((appuser.find(username, 0)) != string::npos) { //this takes the line and check if there is a word in there mathcing to the given username
					cout << "There is already a register with that username." << endl;
					file.close(); //to kleinw prin termatisei to programma
					return 0;
				}
			}
			cout << "Registration succesfull" << endl;
			//this is the part where registration is succesfull, the user logins and his username and password are passed in csv
		}
		else {
			cout << "Can't open file.";
			return 0;
		}
	}
	// end of eggrafi!
	// #endif 
	cout << "Welcome to sportsbook" << endl << "Please enter your username and password for signing in. If you don't have an account please press enter, or type guest" << endl;
	registration_flag = false; //esto oti o xristis den exei eggrafei akoma
	cout << "Username: ";
	cin >> username;
	if (username != "guest") {
		fstream file("registrations.csv");
		if (file.is_open()) {
			while (!file.eof()) {
				getline(file, appuser);
				if ((appuser.find(username, 0)) != string::npos) {
					registration_flag = true;
					break;
				}
			}
			if (!registration_flag) {
				cout << "There is no register with that username. Please try again! " << endl;
			}
			cout << endl << "Password: ";
			cin >> password;
			cout << endl;
			bool is_password_correct = check_for_password(username); //sinartisi pou psaxnei an to password einai to sosto gia to username pou exei dothei
			if (is_password_correct) {
				cout << "You have been logged in to the system succesfully" << endl;
				file.close(); //apti stigmi pou den tha ksanaxreiastei to arxeio me ta registrations
			}
		}
		else {
			cout << "Registration files are missing. End of program!";
				return 0;
		}
	} //else -> an telika ekane type guest os username!!! --> xreiazetai enchancement na erxetai edo kai an apla pataei enter !!! <--
	else { 
		cout << "Logged in as guest" << endl;
	}
    return 0;
}

