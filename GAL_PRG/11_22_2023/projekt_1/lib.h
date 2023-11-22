#ifndef LIB_H
#define LIB_H

#include <iostream>
using namespace std;

class Tree{
	
private:
	int type;
	int height;
public:
	Tree();
	Tree(int t, int h);
	bool setTree(int t, int h);
	int getType();
	int getHeight();
};


#endif
