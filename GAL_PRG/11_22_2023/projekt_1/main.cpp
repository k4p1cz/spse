#include "lib.h"

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
