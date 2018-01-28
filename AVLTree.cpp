#include "AVLTree.h"

static void update_hts(struct node *r) {
	if(r->left == NULL) {
		r->lht = 0;
	} else {
		r->lht = max(r->left->lht,r->left->rht)+1;
	}

	if(r->right == NULL) {
		r->rht = 0;
	} else {
		r->rht = max(r->right->lht, r->right->rht)+1;
	}
}

static struct node *LL(struct node *cr) {
	struct node *child;

	child = cr->left;
	cr->left = child->right;
	cr->lht = child->rht;
	child->right = cr;
	update_hts(child);
	return child;
}

static struct node *LR(struct node *cr) {
	struct node *child = cr->left;
	struct node *rnode = child->right;
	
	child->right = rnode->left;
	child->rht = rnode->lht;

	rnode->left = child;
	update_hts(rnode);	
	cr->left = rnode;
	update_hts(cr);
	return LL(cr);
}

static struct node *RR(struct node *cr) {
	struct node *child = cr->right;

	cr->right = child->left;
	cr->rht = child->lht;
	child->left = cr;
	update_hts(child);
	return child;
}

static struct node *RL(struct node *cr) {
	struct node *child = cr->right;
	struct node *lnode = child->left;

	child->left = lnode->right;
	child->lht = lnode->rht;
	lnode->right = child;
	update_hts(lnode);
	cr->right = lnode;
	update_hts(cr);
	return RR(cr);
}

static struct node *fix_avl(struct node *cr)
{
	struct node *res;
	if(cr->lht > cr->rht) {
		/* Left Rotations */
		if(cr->left->lht > cr->left->rht) {
			/* Left Rotation */
			res = LL(cr);
		} else {
			/* Right Rotation */
			res = LR(cr);
		}
	} else {
		/* Right Rotations */
		if(cr->right->rht > cr->right->lht) {
			/* Right Rotation*/
			res = RR(cr);
		} else {
			/* Left Rotations */
			res = RL(cr);
		}
	}
	return res;
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
		r->lht = 0;
		r->rht = 0;
		r->left = NULL;
		r->right = NULL;
		return r;
	}

	if(r->val > key) {
		r->left = _insert(key, r->left);
		//r->lht++;
	} else if(r->val < key) {
		r->right = _insert(key, r->right);
		//r->rht++;
	}

	update_hts(r);
	if(abs(r->lht-r->rht) > 1) {
		r = fix_avl(r);
	}
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

avltree :: avltree()
{
	root = NULL;
}

avltree :: ~avltree()
{
	this->destroy();
}

int avltree :: LCA(int f, int s)
{
	return _LCA(this->root, f, s);
}

int avltree :: insert(int key)
{
	this->root = _insert(key, this->root);
	return 0;
}

int avltree :: remove(int key)
{
	this->root = _remove(this->root, key);
	return 0;
}
