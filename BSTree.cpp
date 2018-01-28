#include "BSTree.h"

static bool _search(struct node *r, int key)
{
	if(r == NULL)
		return false;
	if(r->val == key)
		return true;
	if(r->val < key)
		return _search(r->right, key);
	return _search(r->left, key);
}

static struct node * _remove(struct node *r, int key)
{
	struct node *t;
	if(r == NULL)
		return r;

	if(r->val < key)
		r->right = _remove(r->right, key);
	else if(r->val > key)
		r->left = _remove(r->left, key);
	else {
		if(r->left == NULL) {
			t = r->right;
			delete r;
			return t;
		} else if(r->right == NULL) {
			t = r->left;
			delete r;
			return t;
		} else {
			t = r->right;
			while(t->left != NULL)
				t = t->left;
			r->val = t->val;
			r->right = _remove(r->right, t->val);
		}
	}
	return r;
}

static struct node * _insert(int key, struct node *r)
{
	if(r == NULL) {
		r = new struct node;
		r->val = key;
		r->left = NULL;
		r->right = NULL;
		return r;
	}

	if(r->val > key)
		r->left = _insert(key, r->left);
	else if(r->val < key)
		r->right = _insert(key, r->right);
	return r;
}

static int _LCA(struct node *root, int f, int s)
{
	if(root == NULL)
		return -1;
	if(root->val == f && root->val == s)
		return root->val;

	int rl = _LCA(root->left, f, s);
	if(rl != -1 && rl != f && rl != s) {
		return rl;
	}

	int rr = _LCA(root->right, f, s);
	if(rr != -1 && rr != f && rr != s) {
		return rr;
	}

	if(rl != -1 && rr != -1) {
		return root->val;
	} else if(f == root->val || s == root->val) {
		return root->val;
	}
	return rl == -1 ? rr : rl;
}

bstree :: bstree()
{
	root = NULL;
}

bstree :: ~bstree()
{
	this->destroy();
}

int bstree :: LCA(int f, int s)
{
	return _LCA(this->root, f, s);
}

int bstree :: insert(int key)
{
	this->root = _insert(key, this->root);
	return 0;
}

int bstree :: remove(int key)
{
	this->root = _remove(this->root, key);
	return 0;
}
bool bstree :: search(int key)
{
	return _search(this->root, key);
}
