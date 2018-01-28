#ifndef __AVLT_H_
#define __AVLT_H_

#include "Tree.h"

class avltree : public btree {
private:
	
public:
	avltree();
	~avltree();
	
	int insert(int key);
	int remove(int key);
	int LCA(int f, int s);
};

#endif
