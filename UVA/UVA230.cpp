#define LOCAL

#include <cstdio>
#include <string>
#include <iostream>
#include <queue>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

struct Book{
	string title;
	string author;
	Book(const string title, const string author): title(title), author(author){}
	bool operator < (const Book& b) const {
		if(this->author != b.author)
			return (this->author).compare(b.author) < 0;
		return (this->title).compare(b.title) <0;
	}
	bool operator == (const Book& b) const {
		return (this->title) == b.title;
	}
	bool operator > (const Book& b) const {
		return !(*this < b);
	}
};

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	string line, title, author, command;
	list<Book> books;
	priority_queue<Book, vector<Book>, greater<Book> > r_books;
	map<string, string> m_book;
	list<Book>::iterator it;
	while(1){
		getline(cin, line);
		if(line[0] == 'E')
			break;
		int del = line.find('"', 1);
		title = line.substr(0, del+1);
		author = line.substr(del+5);
		books.push_back(Book(title, author));
		m_book[title] = author;
	}

	books.sort();

	while(1){
		getline(cin, line);
		if(line[0] == 'E')
			break;
		if(line[0] == 'S'){
			while(!r_books.empty()){
				cout << "Put " << r_books.top().title;
				it = upper_bound(books.begin(), books.end(), r_books.top());
				if(it == books.begin())
					cout << " first" << endl;
				else{
					it--;
					cout << " after " << (*it).title << endl;
				}
				books.insert(++it, r_books.top());
				r_books.pop(); 
			}
			printf("END\n");
		} else{
			title = line.substr(7);
			Book b(title, m_book[title]);
			if(line[0] == 'B'){
				it = find(books.begin(), books.end(), b);
				// if(it == books.end()){
				// 	cout << title << endl;
				// }else
				books.erase(it);
			} else {
				r_books.push(b);
			}
		}
	}
	return 0;
}