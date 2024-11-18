#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

#include "json.hpp"

using namespace std;
using json = nlohmann::json;






class person {
public:
	string name;
	string age;
	string email;
	string PhoneNum;
	string address;

	person(string n, string ag, string em, string num, string ad) {// Constructor
		name = n;
		age = ag;
		email = em;
		PhoneNum = num;
		address = ad;
	}

	void ListPerson() {
		cout << "Name :" << name << endl;
		cout << "Age :" << age << endl;
		cout << "Phone Number :" << PhoneNum << endl;
		cout << "Address :" << address << endl;
		cout << "E-mail :" << email << endl;
	}

	


};

vector<person> PersonList;

void AddPerson() {
	
	string age, name, email, PhoneNum, address;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
	cout << "Name:" <<endl;
	getline(cin,name);
	cout << "Age:" << endl;
	getline(cin,age);
	cout << "E-mail:" << endl;
	getline(cin,email);
	cout << "Phone Number:" << endl;
	getline(cin,PhoneNum);
	cout << "address:" << endl;
	getline(cin,address);
	person Person1(name, age, email, PhoneNum, address);
	PersonList.push_back(Person1);
}

void ListPeople() {
	for (int i = 0; i < PersonList.size(); i++) {
		cout << endl;
		PersonList[i].ListPerson();
		cout << endl;
	}
}

void FindPerson() {
	cout << "Person Finder" << endl;
	cout << "write anything you know (if u dont know asked parameter print none)" << endl;
	string name,age,email,PhoneNum,address;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
	cout << "name:" << endl;
	getline(cin, name);
	cout << "age:" << endl;
	getline(cin, age);
	cout << "email:" << endl;
	getline(cin, email);
	cout << "PhoneNum:" << endl;
	getline(cin, PhoneNum);
	cout << "address:" << endl;
	getline(cin, address);
	int BestMatch = 0;
	int BestMPA = 0;
	for(int i = 0; i < PersonList.size(); i++) {
		cout << "...";
		cout << endl;
		int MPA = 0;
		if (name == PersonList[i].name) {
			MPA++;
		}
		if (age == PersonList[i].age) {
			MPA++;
		}
		if (email == PersonList[i].email) {
			MPA++;
		}
		if (PhoneNum == PersonList[i].PhoneNum) {
			MPA++;
		}
		if (address == PersonList[i].address) {
			MPA++;
		}
		if (MPA == 0) {
			continue;
		}
		else {
			if (MPA > BestMPA) {
				BestMatch = i;
				BestMPA = MPA;
			}
		}
	}

	PersonList[BestMatch].ListPerson();
	
	
}

void saveData(const std::vector<person>& contacts, const std::string& filename) {
    json jContacts = json::array();
    for (const auto& person : contacts) {
        jContacts.push_back({{"name", person.name}, {"age", person.age}, {"email", person.email}, {"Phone Number", person.PhoneNum}, {"address", person.address}});
    }
    std::ofstream outFile(filename);
    outFile << jContacts.dump(4);
    outFile.close();
}

void loadData(std::vector<person>& contacts, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Cannot open file for reading");
    }
    json jContacts;
    inFile >> jContacts;

    for (const auto& jPerson : jContacts) {
        contacts.emplace_back(jPerson.at("name").get<std::string>(), jPerson.at("age").get<string>(), jPerson.at("email").get<std::string>(), jPerson.at("Phone Number").get<std::string>(), jPerson.at("address").get<std::string>());
    }
    inFile.close();
}

int main() {
	bool quit = false;
	loadData(PersonList,"data.json");
	while (true) {

		cout << endl;
		cout << endl;
		cout << endl;
		int action = 0;
		cout << "1. Add person" << endl;
		cout << "2. Find person" << endl;
		cout << "3. Print List" << endl;
		cout << "4. Save and quit" << endl;
		cin >> action;
		switch (action) {
		case 1:
			AddPerson();
			break;
		case 2:
			FindPerson();
			break;
		case 3:
			
			ListPeople();
			break;
		case 4:
			saveData(PersonList,"data.json");
			quit = true;
			break;
		default:
			cout << "Error" << endl;
			quit = true;
			break;
		}
		if(quit){
			break;
		}
		
	}
	
	
	return 0;
}