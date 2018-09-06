#include <iostream>
#include "p2.h"
using namespace std;


int sum(int a, int b) { return a + b; }
bool odd(int a) { return a % 2 == 0 ? false : true; }
bool even(int a) { return a % 2 == 1 ? false : true; }
int main() {
	tree_t tree1 = tree_make();
	for (int i = 1; i <= 4; i++) tree1 = tree_make(i, tree1, tree_make());
	tree_print(tree1);
	cout << endl;

	//tree_t tree2 = tree_make();
	//for (int i = 4; i >= 2; i--) tree2 = tree_make(i, tree2, tree_make());
	//tree_print(tree2);
	//cout << endl;
	//cout << contained_by(tree2, tree1) << endl;
	cout << tree_min(tree1) << endl;

	system("PAUSE");
	return 0;
}