#pragma once
#ifndef BOOK_H
#define BOOK_H
#include<iostream>
#include <cassert>
#include<map>
#include<set>
using namespace std;
class Book
{
private:
	string book_name;
	int total_quantity;
	int total_borrowed;
	int id;
public:
	static int sid;
	Book()
	{
		sid++;
		id = sid;
		total_borrowed = 0;
	}
	void read() {
		cout << "Enter book info:name & total quantity: ";
		cin >> book_name >> total_quantity;
		total_borrowed = 0;
	}

	void print() {
		cout << "id = " << id << " name = " << book_name << " total_quantity "
			<< total_quantity << " total_borrowed " << total_borrowed
			<< "\n";
	}
	bool borrow(int user_id) {
		if (total_quantity - total_borrowed == 0)
			return false;
		++total_borrowed;
		return true;
	}

	void return_copy() {
		assert(total_borrowed > 0);
		--total_borrowed;
	}

	void generate_prefix(map<string,set<string>>&mp) {
		int bookname_len = book_name.length();
		string s = "";
		for (int i = 0;i < bookname_len - 1;i++) {
			s += book_name[i];
			mp[s].insert(book_name);
		}
	}
	bool checkname(string name) {
		if (book_name == name)
			return true;
		return false;
	}
	bool isborrowed() {
		if (total_borrowed > 0)
			return true;
		return false;
	}
	int getid() {
		return id;
	}
	string getbook_name() {
		return book_name;
	}
};

#endif