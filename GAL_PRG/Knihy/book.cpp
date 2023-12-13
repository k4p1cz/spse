#include "header.h"

Book::Book(){
	this->id = 0;
	this->name = "";
	this->price = 0;
}
Book::Book(int id_, string name_, int price_){
	this->id = id_;
	this->name = name_;
	this->price = price_;
}

ostream &operator<<(ostream &output, Book x) {
	output << "ID: " << x.id << "\nName: " << x.name << "\nPrice: " << x.price << endl;
	
	return output;
}

istream &operator>>(istream &input, Book &x) {
	cout << "Enter book ID: ";
	input >> x.id;
	cout << "Enter book name: ";
	fflush(stdin);
	getline(input, x.name);
	cout << "Enter price: ";
	input >> x.price;
	
	return input;
}

