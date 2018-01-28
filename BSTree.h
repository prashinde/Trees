#ifndef __BST_H_
#define __BST_H_

#include "Tree.h"

class bstree : public btree {
public:
	bstree();
	~bstree();

	bool search(int key);	
	int insert(int key);
	int remove(int key);
	int LCA(int f, int s);
};

#endif
