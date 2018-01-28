#include "Tree.h"

void _in_it(struct node *root)
{
	stack<struct node *> s;

	while(!s.empty() || root != NULL) {
		if(root != NULL) {
			s.push(root);
			root = root->left;
		} else {
			root = s.top();
			s.pop();
			cout << "Root->val:" << root->val << endl;
			root = root->right;
		}
	}
}

void _pre_it(struct node *root)
{
	stack<struct node *> s;

	while(!s.empty() || root != NULL) {
		if(root != NULL) {
			s.push(root);
			cout << "Root->val:" << root->val << endl;
			root = root->left;
		} else {
			root = s.top();
			s.pop();
			root = root->right;
		}
	}
}

void _post_it(struct node *root)
{
	stack<pair<struct node *, int>> s;

	while(!s.empty() || root != NULL) {
		if(root != NULL) {
			s.push(pair<struct node *, int>(root, 1));
			root = root->left;
		} else {
			pair<struct node *, int> p = s.top();
			if(p.second == 1) {
				root = p.first;
				s.pop();
				s.push(pair<struct node *, int>(root, 2));
				root = root->right;
			} else if(p.second == 2) {
				cout << "Node VAlue:" << p.first->val << endl;
				s.pop();
			}
		}
	}
}

void btree::inorder_it()
{
	_in_it(this->root);
}

void btree::postorder_it()
{
	_post_it(this->root);
}

void btree::preorder_it()
{
	_pre_it(this->root);
}

int _lp(struct node *r, int &maxl)
{
	if(r != NULL) {
		int ll = _lp(r->left, maxl);
		int rl = _lp(r->right, maxl);
		
		maxl = max(maxl, ll+rl+1);
		return max(ll, rl)+1;
	}
	return 0;
}

int btree :: longest_path()
{
	int maxl = 0;
	_lp(this->root, maxl);
	return maxl;
}

static void _swap(struct node *r)
{
	if(r != NULL) {
		struct node *t;
		_swap(r->left);
		_swap(r->right);
		t = r->left;
		r->left = r->right;
		r->right = t;
	}
}

static void bt_print_dot_null(int key, int nullcount, FILE* stream)
{
	fprintf(stream, "	 null%d [shape=point];\n", nullcount);
	fprintf(stream, "	 %d -> null%d;\n", key, nullcount);
}

static void bt_print_dot_aux(struct node *n, FILE* stream)
{
	static int nullcount = 0;

	if (n->left)
	{
		fprintf(stream, "	 %d -> %d;\n", n->val, n->left->val);
		bt_print_dot_aux(n->left, stream);
	}
	else
		bt_print_dot_null(n->val, nullcount++, stream);

	if (n->right)
	{
		fprintf(stream, "	 %d -> %d;\n", n->val, n->right->val);
		bt_print_dot_aux(n->right, stream);
	}
	else
		bt_print_dot_null(n->val, nullcount++, stream);
}

static void bt_print_dot(struct node *tree, FILE *stream)
{
	fprintf(stream, "digraph BST {\n");
	fprintf(stream, "	 node [fontname=\"Arial\"];\n");

	if (!tree)
		fprintf(stream, "\n");
	else if (!tree->right && !tree->left)
		fprintf(stream, "	 %d;\n", tree->val);
	else
		bt_print_dot_aux(tree, stream);

	fprintf(stream, "}\n");
}

void btree :: print_tree(FILE *file)
{
	bt_print_dot(this->root, file);
}

static void _inorder(struct node *root)
{
	if(root != NULL) {
		_inorder(root->left);
		cout <<	root->val << endl;
		_inorder(root->right);
	}
}

static void delete_tree(struct node *r)
{
	if(r != NULL) {
		delete_tree(r->left);
		delete_tree(r->right);
		delete r;
	}
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

btree :: btree()
{
	root = NULL;
}

btree :: ~btree()
{
	this->destroy();
}

void btree :: inorder()
{
	struct node *root = this->root;
	_inorder(root);
}

int btree :: LCA(int f, int s)
{
	return _LCA(this->root, f, s);
}

int btree :: insert(int key)
{
	struct node *n;
	struct node *temp;
	n = new struct node;
	n->val = key;
	n->left = NULL;
	n->right = NULL;

	if(this->root == NULL) {
		this->root = n;
		Q.push(root);		
	} else {
		temp = Q.front();
		if(temp->left == NULL) {
			temp->left = n;
		} else if(temp->right == NULL) {
			temp->right = n;
			Q.pop();
		}
		Q.push(n);
	}
	return 0;
}

int btree :: swap()
{
	_swap(this->root);
	return 0;
}

int btree :: remove(int key)
{
	return 0;
}

int btree :: destroy()
{
	struct node *r = this->root;
	delete_tree(r);
	this->root = NULL;	
	return 0;
}
