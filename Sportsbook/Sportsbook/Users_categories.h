#pragma once
#include "stdafx.h"
#include "Main_functions.h"
#include "hierarchy.h"
//#include "BetAtzis.h"

using namespace std;
class BetAtzis;
class User {
	int user_id;
	string username;
	string fullname;
	string password;
	int type;
public:
	User (string Username = "-", string Fullname = "-", string Password = "-" , int Type = 0) {
		username = Username;
		fullname = Fullname;
		password = Password;
		type = Type;
	}
	void print_username() { cout << username; }
	void print_fullname() { cout << fullname; }
	void print_password() { cout << password; }
	string get_username() { return username; }
	string get_fullname() { return fullname; }
	virtual void print_balance(){}
	virtual void print_freebets(){}
	virtual bool Operation(string, BetAtzis&) { return 1; }
	virtual void Bets(){}
	virtual void Print_Operations(){}
};

class Guest : public User{ 
public:
	Guest ():User() {
		std::cout << "Welcome!" << endl;
	}
	bool Operation(string, BetAtzis&);
	void Bets() {}
	void Print_Operations();

};

class Wallet {
private:
	double amount;
public:
	Wallet(double money) {
		amount = money;
	}
	void print_wallet() { cout << amount; }
};

class Punter : public User{
private:
	string status;
	Wallet balance;
	string freebets;
public:
	Punter (string username, string fullname, string password, double money): User(username, fullname, password, 1), balance(money) {
		status = get_status(username);
		freebets = get_freebets(username);
		std::cout << "Welcome mr." << username << endl;
	}
	bool Operation(string, BetAtzis&);
	void Bets() {}
	void Print_Operations();
	void print_balance() { balance.print_wallet(); }
	void print_freebets() { cout << freebets; }
};

class Trader : public User{
public:
	Trader (string username, string fullname, string password):User(username, fullname, password, 2){
		std::cout << "Welcome back mr." << username << endl;
	}
	bool Operation(string, BetAtzis&);
	void Bets();
	void Print_Operations();
};

class Director : public User{
public:
	Director (string username, string fullname, string password):User(username, fullname, password, 3) {
		std::cout << "Welcome back boss" << endl;
	}
	bool Operation(string, BetAtzis&);
	void Bets();
	void Print_Operations();
};