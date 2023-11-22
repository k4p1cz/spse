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


int main(){
	Tree myTree;
	int t = 0;
	int h = 0;
	do{
		system("cls");
		cout << "Enter type: " ;
		cin >> t;
		cout << "Enter height: " ;
		cin >> h;
	}while(!myTree.setTree(t, h));

	system("cls");
	
	cout << "  YOUR TREE\n\n" ;
	cout << "    Type: " << myTree.getType() << endl;
	cout << "   Height: " << myTree.getHeight() << endl;
	cout << "\n\n";
	cout << "       _-_" << endl;
	cout << "    /~~   ~~\\" << endl;
	cout << " /~~         ~~\\" << endl;
	cout << "{               }" << endl;
	cout << " \\  _-     -_  /" << endl;
	cout << "   ~  \\\\ //  ~" << endl;
	cout << "_- -   | | _- _" << endl;
	cout << "  _ -  | |   -_" << endl;
	cout << "      // \\\\" << endl;

	
	cout << "\n\n\n\n" ;

	return 0;
}
