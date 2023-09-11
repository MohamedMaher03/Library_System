#pragma once
#include<iostream>
#include<set>
using namespace std;
class User
{
private:
	int id;
	string user_name;
	set<int> borrowed_books_ids;
public:
	User() {
		user_name = "";
		id = -1;
	}
	void read() {
		cout << "Enter user name & national id: ";
		cin >> user_name >> id;
	}
	void borrow(int book_id) {
		borrowed_books_ids.insert(book_id);
	}
	void return_copy(int book_id) {
		auto it = borrowed_books_ids.find(book_id);

		if (it != borrowed_books_ids.end())
			borrowed_books_ids.erase(it);
		else
			cout << "User " << user_name << " never borrowed book id " << book_id
			<< "\n";
	}
	void print() {
		cout << "user " << user_name << " id " << id << " borrowed books ids: ";
		for (int book_id : borrowed_books_ids)
			cout << book_id << " ";
		cout << "\n";
	}
	bool checkname(string name) {
		if (user_name == name)
			return true;
		return false;
	}
	bool checkbook(int book_id) {
		auto it = borrowed_books_ids.find(book_id);
		return it != borrowed_books_ids.end();
	}
	void print_name() {
		cout << user_name << endl;
	}
	int getid() {
		return id;
	}
};

