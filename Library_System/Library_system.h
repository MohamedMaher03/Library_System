#pragma once
#include"Book.h"
#include"User.h"
#include<vector>
#include<map>

class Library_system
{
private:
	vector<Book>books;
	vector<User>users;
	map<string, set<string>>prefix_books;
public:
	void run() {
		while (true) {
			int choice = menu();

			if (choice == 1)
				add_book();
			else if (choice == 2)
				search_books_by_prefix();
			else if (choice == 3)
				print_who_borrowed_book_by_name();
			else if (choice == 4)
				print_library_by_id();
			else if (choice == 5)
				print_library_by_name();
			else if (choice == 6)
				add_user();
			else if (choice == 7)
				user_borrow_book();
			else if (choice == 8)
				user_return_book();
			else if (choice == 9)
				print_users();
			else
				break;
		}
	}

	int menu() {
		int choice = -1;
		while (choice == -1) {
			cout << "\nLibrary Menu;\n";
			cout << "1) add_book\n";
			cout << "2) search_books_by_prefix\n";
			cout << "3) print_who_borrowed_book_by_name\n";
			cout << "4) print_library_by_id\n";
			cout << "5) print_library_by_name\n";
			cout << "6) add_user\n";
			cout << "7) user_borrow_book\n";
			cout << "8) user_return_book\n";
			cout << "9) print_users\n";
			cout << "10) Exit\n";

			cout << "\nEnter your menu choice [1 - 10]: ";
			cin >> choice;

			if (!(1 <= choice && choice <= 10)) {
				cout << "Invalid choice. Try again\n";
				choice = -1;	// loop keep working
			}
		}
		return choice;
	}
	void add_book() {
		Book b;
		b.read();
		b.generate_prefix(prefix_books);
		books.push_back(b);
	}
	void search_books_by_prefix() {
		cout << "Enter book name prefix: ";
		string prefix;
		cin >> prefix;
		int count_of_prefix = prefix_books[prefix].size();
		if(!count_of_prefix)
			cout << "No books with such prefix\n";
		else{
				auto it = prefix_books[prefix].begin();
				while (count_of_prefix--) {
					cout << *it;
					it++;
				}
			}
	}
	void add_user() {
		User u;
		u.read();
		users.push_back(u);
	}
	int find_book_idx_by_name(string name) {
		for (int i = 0; i < (int)books.size(); ++i) {
			if (books[i].checkname(name))
				return i;
		}
		return -1;
	}
	int find_user_idx_by_name(string name) {
		for (int i = 0; i < (int)users.size(); ++i) {
			if (users[i].checkname(name))
				return i;
		}
		return -1;
	}
	void print_who_borrowed_book_by_name()
	{
		string book_name;
		cout << "Enter book name: ";
		cin >> book_name;

		int book_idx = find_book_idx_by_name(book_name);
		if (book_idx == -1) {
			cout << "Invalid book name.\n";
			return;
		}
		int book_id = books[book_idx].getid();
		if (!books[book_idx].isborrowed()) {
			cout << "No borrowed copies\n";
			return;
		}
		for (int i = 0;i < users.size();i++) {
			if (users[i].checkbook(book_id))
				users[i].print_name();
		}
	}
	void print_library_by_id() {
		multiset<int>ids;
		for (int i = 0;i < books.size();i++) {
			ids.insert(books[i].getid());
		}
		for (const int& element : ids) {
			cout << element << " ";
		}
		cout << endl;
	}
	void print_library_by_name() {
		multiset<string>names;
		for (int i = 0;i < books.size();i++) {
			names.insert(books[i].getbook_name());
		}
		for (const string& element : names) {
			cout << element << " ";
		}
		cout << endl;
	}
	void print_users() {
		cout << "\n";
		for (User& u : users)
			u.print();
	}
	bool read_user_name_and_book_name(int& user_idx, int& book_idx, int trials =
		3) {
		string user_name;
		string book_name;

		while (trials--) {
			cout << "Enter user name and book name: ";
			cin >> user_name >> book_name;

			user_idx = find_user_idx_by_name(user_name);

			if (user_idx == -1) {
				cout << "Invalid user name. Try again\n";
				continue;
			}
			book_idx = find_book_idx_by_name(book_name);

			if (book_idx == -1) {
				cout << "Invalid book name. Try again\n";
				continue;
			}
			return true;
		}
		cout << "You did several trials! Try later.";
		return false;
	}
	void user_borrow_book() {
		int user_idx, book_idx;

		if (!read_user_name_and_book_name(user_idx, book_idx))
			return;

		int user_id = users[user_idx].getid();
		int book_id = books[book_idx].getid();

		if (!books[book_idx].borrow(user_id))
			cout << "No more copies available right now\n";
		else
			users[user_idx].borrow(book_id);
	}
	void user_return_book() {
		int user_idx, book_idx;

		if (!read_user_name_and_book_name(user_idx, book_idx))
			return;
		int book_id = books[book_idx].getid();
		books[book_idx].return_copy();
		users[user_idx].return_copy(book_id);
	}
};

