#include<iostream>
#include<fstream>
#include"RedBlack.h"
//#include"AVL.h"
//#include"B_tree.h"
using namespace std;

int main()
{
	int option;
	cout << "Enter the respective tree in which you want to store the data:\n1) AVL Tree\n2) Red Black Tree\n3) B Tree\nOption: ";
	cin >> option;
	cout << endl;
	switch (option)
	{
	case 1: //AVL_tree();
		break;
	case 2: red_black();
		break;
	case 3: //b_tree();
		break;
	}
	return 0;
}