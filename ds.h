#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

class DSNode {
public:
	string name;
	int age;
	DSNode* nextname;
	DSNode* nextage;
	DSNode() {
		nextname = 0;
		nextage = 0;
		age = 0;
	}
	DSNode(string& n, int& a, DSNode* nextn = 0, DSNode* nexta = 0) {
		name = n; age = a; nextname = nextn; nextage = nexta;
	}
};

class DSList {
public:
	DSList() {
		headn = heada = 0;
	}
	void add(string name, int age);
	bool remove(string name);
	void update(string name, int age);
	void printByAge();
	void printByName();
	void loadFile(string filename);
	void saveToFileByAge(string filename);
	void saveToFileByName(string filename);
	~DSList();

protected:
	DSNode* headn, * heada;

};

void DSList::add(string name, int age) {
	DSNode* newnode = new DSNode(name, age);
	if (headn == 0 && heada == 0) {
		headn = heada =newnode;
	}
	else {
		if (heada->nextage == NULL) {
			if (newnode->age > heada->age) {
				heada->nextage = newnode;
			}
			else {
				DSNode* temp = heada;
				heada = newnode;
				newnode->nextage = temp;
			}
		}
		else {
			DSNode* temp1 = heada;
			DSNode* temp2 = heada->nextage;
			DSNode* old;
			while (temp1 != NULL) { 
				if (newnode->age < heada->age) { //new node is smaller than head
					old = heada;
					heada = newnode;
					newnode->nextage = old;
					break;
				}
				if (newnode->age >= temp1->age) {
					if (temp2 == NULL or newnode->age <= temp2->age) { //new node is bigger then all of them or between them
						old = temp1->nextage;
						temp1->nextage = newnode;
						temp1->nextage->nextage = old;
						break;
					}
				}
				temp1 = temp2;
				temp2 = temp2->nextage;
			}
		}
		if (headn->nextname == NULL) {
			if (newnode->name[0] > headn->name[0]) {
				headn->nextname = newnode;
			}
			else {
				DSNode* temp = headn;
				headn = newnode;
				newnode->nextname = temp;
			}
		}
		else {
			DSNode* temp1 = headn;
			DSNode* temp2 = headn->nextname;
			DSNode* old;
			while (temp1 != NULL) {			
				if (newnode->name[0] < headn->name[0]) { //new node is smaller than head
					old = headn;
					headn = newnode;
					newnode->nextname = old;
					break;
				}
				if (newnode->name[0] >= temp1->name[0]) {
					if (temp2 == NULL or newnode->name[0] <= temp2->name[0]) { //new node is bigger then all of them or between them
						//cout << temp1->name << endl;
						old = temp1->nextname;
						temp1->nextname = newnode;
						//cout << temp1->nextname->name << endl;
						temp1->nextname->nextname = old;
						break;
					}
				}
				temp1 = temp2;
				temp2 = temp2->nextname;
			}
		}
	}	
}
void DSList::printByAge() {
	DSNode* temp = heada;
	while (temp != NULL) {
		cout <<temp->name<< temp->age << endl;
		temp = temp->nextage;
	}
}
void DSList::printByName() {
	DSNode* temp = headn;
	while (temp != NULL) {
		cout << temp->name <<temp->age<< endl;
		temp = temp->nextname;
	}
}
bool DSList::remove(string name) {
	DSNode* temp1 = headn;
	DSNode* temp2 = temp1->nextname;
	int agetodelete;
	if (temp1->name == name) {
		headn = temp2;
		agetodelete = temp1->age;
		temp1 = NULL;
	}
	else {
		while (temp2->name != name) {
			temp1 = temp2;
			if (temp2->nextname == NULL) {
				return 0;
			}
			temp2 = temp2->nextname;
		}
		agetodelete = temp2->age;
		temp1->nextname = temp2->nextname;
		temp2 = NULL;
	}
	temp1 = heada;
	temp2 = temp1->nextage;
	if (temp1->age == agetodelete) {
		heada = temp2;
		temp1 = NULL;
	}
	else {
		while (temp2->age != agetodelete) {
			temp1 = temp2;
			if (temp2->nextage == NULL) {
				return 0;
			}
			temp2 = temp2->nextage;
		}
		temp1->nextage = temp2->nextage;
		temp2 = NULL;
	}
	return 1;
}
void DSList::update(string name, int age) {
	remove(name);
	add(name, age);
}
void DSList::loadFile(string filename)
{
	ifstream file;
	file.open(filename.c_str());
	int age;
	string name;
	while (file >> name) {
		file >> age;
		add(name, age);
	}
	file.close();
}
void DSList::saveToFileByAge(string filename) {
	ofstream file;
	file.open(filename.c_str());
	DSNode* node = heada;
	while (node != NULL) {
		file <<node->name<< node->age << endl;
		node = node->nextage;
	}
	file.close();
}
void DSList::saveToFileByName(string filename) {
	ofstream file;
	file.open(filename.c_str());
	DSNode* node = headn;
	while (node != NULL) {
		file << node->name <<node->age<< endl;
		node = node->nextname;
	}
	file.close();
}
DSList::~DSList() {
	DSNode* current = headn;
	while (current != 0) {
		DSNode* next = current->nextname;
		delete current;
		current = next;
	}
	headn = 0;
	heada = 0;
}
