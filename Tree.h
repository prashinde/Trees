#ifndef __BTREE_H_
#define __BTREE_H_
#include <assert.h>

#include <iostream>
#include <queue>
#include <stack>
#include <stdlib.h>
using namespace std;

struct node {
	int val;
	int lht;
	int rht;
	struct node *right;
	struct node *left;
};

class btree {
public:
	btree();
	~btree();
	
	int swap();
	int longest_path();
	void print_tree(FILE *file);
	int insert(int key);
	int remove(int key);
	int destroy();
	void inorder();
	int LCA(int f, int s);

	void inorder_it();
	void postorder_it();
	void preorder_it();
	void test_tree_prop();
private:
	queue<struct node *> Q;
protected:
	struct node *root;
};

#endif
