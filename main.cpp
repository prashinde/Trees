#include <iostream>
#include "Tree.h"
#include "BSTree.h"
#include "AVLTree.h"
int main(int argc, char *argv[])
{
	FILE *tf;
	avltree *b = new avltree();
	int lca;

	int range = atoi(argv[1]);
	int f = atoi(argv[2]);
	int s = atoi(argv[3]);

	tf = fopen("OTree.txt", "w+");
	for(int i = 0; i < range; i++)
		b->insert(i);
	b->print_tree(tf);
	fclose(tf);
	b->postorder_it();

	delete b;
	return 0;
}
