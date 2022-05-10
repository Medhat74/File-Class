#include "File.h"
#include <sstream>
#include <string>
#include <vector>
#include "Message.h"
File::File() {

}
bool File:: read_user_file(User &user) {

	user = check_user(user.get_user_name(), user.get_password());

	return user.get_user_name() != "none";

}
void File::read_messages(vector <Message> &all_msg) {
	ifstream message_file;
	message_file.open("Messages.txt", ios::in);
	int i = 0;
	string line;
	string* elements=new string[4];
	while (getline(message_file, line))
	{
	
		
		int start = 0;
		int end = line.find("/");
		int index = 0;
		string elementsArray[5];
		while (end != -1 && index != 5) {
			elementsArray[index] = line.substr(start, end - start);
			start = end + 1;
			end = line.find("/", start);
			index++;
		}
		Message m;
		m.set_id(stoi(elementsArray[0]));
		m.set_sent_id(stoi(elementsArray[1]));
		m.set_body( elementsArray[2]);
		m.set_recived_id(stoi(elementsArray[3]));
		m.set_fav_message( (elementsArray[4] == "1"));

		all_msg.push_back(m);
		
		i++;

		
	}
	message_file.close();
}
 
void File::read__contacts(map<int, vector<pair<int, bool>>> &contacts) {
	ifstream contact_file;
	contact_file.open("contacts.txt", ios::in);
	while (!contact_file.eof())
	{
		int user_id;
		pair<int , bool> contact;
		contact_file >> user_id >> contact.first >> contact.second;
		if (contact.first == 0)
			continue;
		contacts[user_id].push_back(contact);
		
	}
	contact_file.close();
}







void File::write_contacts(map<int, vector<pair<int, bool>>> &contacts) {
	ofstream contact_file("contacts.txt");
	map<int, vector<pair<int, bool>>>::iterator it;
	vector<pair<int, bool>>::iterator it2;
	it = contacts.begin();
	while (it != contacts.end())
	{
		it2 = it->second.begin();
		while (it2 != it->second.end())
		{
			if (it2->first == 0) {
				it2++;
				continue;
			}
			contact_file << it->first << " ";
			contact_file << it2->first << " " << it2->second << "\n";
			it2++;
		}
		it++;
	}
	contact_file.close();
}

void File::write_messages(vector<Message>& all_msg) {
	ofstream msg_file("Messages.txt" );
	int i = 0;
	for (int i = 0; i < all_msg.size(); i++) {
		msg_file  << all_msg[i].get_id() << "/" << all_msg[i].get_sent_id()
			     << "/" << all_msg[i].get_body() << "/" << all_msg[i].get_recived_id()
			     << "/" << all_msg[i].get_fav_message()<< "/" << "\n";
		
	}
	
	msg_file.close();
}

int File::last_id() {
	ifstream user_file;
	user_file.open("users_information.txt", ios::in);
	int id;
	while (!user_file.eof())
	{
		
		string name;
		string password;
		user_file >> id >> name >> password;
	
	}
	user_file.close();
	return id;
}

User File::check_user(string user_name, string pass) {
	ifstream user_file;
	user_file.open("users_information.txt", ios::in);
	User user;
	while (!user_file.eof())
	{
		int id;
		string name;
		string password;
		user_file >> id >> name >> password;
		if (name == user_name && password == pass)
		{

			user = User(id, name, password);
			user_file.close();

			return user;
		}
	}
	user_file.close();
	return user = User();
}

void File::add_users(User user) {
	ofstream user_file("users_information.txt", ios::app);

	user_file << "\n" << user.get_id() << " " << user.get_user_name() << " " << user.get_password();
	user_file.close();
}
