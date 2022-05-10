#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <fstream>
#include "User.h"
#include <map>
using namespace std;

class File
{
public:
	File();
	bool read_user_file(User &user);
	void read_messages(vector<Message>& all_msg);
	User check_user(string user_name, string pass); 
	void add_users(User user);
	void write_messages(vector<Message>& all_msg);
	void read_user_contacts(map<int, vector<pair<int, bool>>>& contacts);
	void write_contacts(map<int, vector<pair<int, bool>>>& contacts);
	int last_id();


	
};


