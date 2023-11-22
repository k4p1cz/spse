#include "lib.h"

Tree::Tree(){
	this->type = 0;
	this->height = 0;
}
Tree::Tree(int t, int h){
	this->type = t;
	this->height = h;
}
bool Tree::setTree(int t, int h){
	if(t == 0 or h == 0){
		return false;
	}
	if(t > 10 or h > 100){
		return false;
	}
	if(t <= 0 or h <= 0){
		return false;
	}
	
	this->type = t;
	this->height = h;
	return true;
}
int Tree::getType(){
	return this->type;
}
int Tree::getHeight(){
	return this->height;
}

