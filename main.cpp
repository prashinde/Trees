#include <iostream>
#include <ctime>
#include "Tree.h"
#include "BSTree.h"
#include "AVLTree.h"
int main(int argc, char *argv[])
{
	FILE *tf;
	avltree *b = new avltree();
	int lca;

	int range = atoi(argv[1]);
	int key = atoi(argv[2]);
	tf = fopen("OTree.txt", "w+");
	for(int i = 0; i < range; i++)
		b->insert(i);
	//b->print_tree(tf);
	fclose(tf);
	//b->test_tree_prop();
	int start_s=clock();
	bool v = b->search(key);
	int stop_s=clock();
	cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
	cout << "Is key exist: " << v << endl;
	///b->postorder_it();

	delete b;
	return 0;
}
