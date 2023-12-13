#include "header.h"

Library::Library(){
	this->id = 0;
	this->length = 0;
}

Library::Library(int id_, int books_[999], int length_){
	this->id = id_;
	this->length = length_;
	this->books = books_;
}

ostream &operator<<(ostream &output, Library x) {
	//output << "ID: " << x.id << "\nName: " << x.name << "\nPrice: " << x.price << endl;
	output << "ID: " << x.id << endl;
	for(int i =0; i < x.length; i++){
		
	}
	return output;
}

istream &operator>>(istream &input, Library &x) {
	cout << "Enter book ID: ";
	input >> x.id;
	cout << "Enter book name: ";
	fflush(stdin);
	getline(input, x.name);
	cout << "Enter price: ";
	input >> x.price;
	
	return input;
}

