#pragma once
#include "Users_categories.h"
#include "stdafx.h"
#include "hierarchy.h"


class BetAtzis {
private:
	long double profits;
	double promitheia;
	string type_ofProfits;
	//string Current_lvl;
	User* user; // deikths ston current user
	Home* home; // to home den einai node opote to vazw edw ksexorista gia na exw panta prosvasi xoris pollapla back//
	Node* node;
	vector <User*> users;
	vector <Node*> nodes;
	vector <bet*> bets;
public:
	BetAtzis();
	~BetAtzis();
	void print_location() {
		node->print_location();
	}

	void print_options() {
		node->print_options();
	}

	void print_operations() {
		user->Print_Operations();
	}

	void set_user(User *usr) {
		user = usr;
	}

	User* get_user() {
		return user;
	}
	
	Node* get_node() {
		return node;
	}

	User* get_userptr(int user_id) {
		return users[user_id];
	}

	void set_level(int lvl) {
		//Current_lvl = lvl;
		node = node->get_next(lvl);
	}

	Node* get_level() {
		return node;
	}

	Node* get_home() {
		return home;
	}

	void return_home() {
		node = home;
	}

	void place() {
		user->place(this);
	}

	void set_bet(string node_id, double stake);

//functions for vector changes
	void set_new_username(string OLD, string NEW);
	void set_new_password(string name, string NEW);
	void set_new_balance(string name, double ADD);
	bool operation(string, BetAtzis*);
//vector save
	bool save();

	string get_bet(int bet_id);

	User * current_user(string usrnm);
};

//functions for vector initialization

int extract_id(string);

string extract_username(string);

string extract_password(string);

string extract_fullname(string);

double extract_balance(string);

string extract_status(string);

int extract_type(string);

int extract_betid(string);

int extract_userid(string);

double extract_stake(string);

string extract_result(string);

string extract_nodeid(string);