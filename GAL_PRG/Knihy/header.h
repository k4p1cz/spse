#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <cmath>
#include <string.h>
using namespace std;

class Book{
private:
	int id;
	string name;
	int price;
public:
	Book();
	Book(int id_, string name_, int price_);
	friend ostream &operator<<(ostream &output, Book x);
	friend istream &operator>>(istream &input, Book &x);
};

class Library{
private:
	int id;
	int books[999];
	int length;
public:
	Library();
	Library(int id_, int books_[999], int length_);
	friend ostream &operator<<(ostream &output, Library x);
	friend istream &operator>>(istream &input, Library &x);
};


#endif
