#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#include <iostream>
#include <algorithm>

template <class Type>
class node{
    public:
        Type key;
        int balance; //height(right)-height(left)
        node *left, *right, *parent;
        node(Type k, node* p): key(k), balance(0), left(nullptr), right(nullptr),parent(p){}
        ~node(){
            delete left;
            delete right;
        }
};

template<class Type>
class tree{
	public:
	    node<Type>* root;
		tree():root(nullptr) {}
		~tree() {delete root;}
		bool insert(Type k);
		void remove(const Type k);
		void inorder(node<Type>* n);
	private:
		int height(node<Type> *n);
	    void rebalance(node<Type> *n);
	    void setBalance(node<Type> *n);
		node<Type>* rotateLeft(node<Type> *x);
	    node<Type>* rotateRight(node<Type> *x);
	    node<Type>* rotateLeftThenRight(node<Type> *x);
	    node<Type>* rotateRightThenLeft(node<Type> *x);
};

template<class Type>
int tree<Type>::height(node<Type> *n){
	if(n == nullptr)
		return -1;
	return 1 + std::max(height(n->right),height(n->left));
}

template<class Type>
void tree<Type>::setBalance(node<Type> *n){
	n->balance = height(n->right)-height(n->left);
}

template<class Type>
void tree<Type>::rebalance(node<Type> *n){
	setBalance(n);

	if(n->balance == -2){
		if(height(n->left->left) >= height(n->left->right))
			n = rotateRight(n);
		else
			n = rotateLeftThenRight(n);
	}
	else if(n->balance == 2){
		if(height(n->right->right) >= height(n->right->left))
			n = rotateLeft(n);
		else
			n = rotateRightThenLeft(n);
	}

	if(n->parent != nullptr)
		rebalance(n->parent);
	else
		root = n;
}

template<class Type>
node<Type>* tree<Type>::rotateLeft(node<Type> *x){
	node<Type>* y = x->right;
	y->parent = x->parent;
	x->right = y->left;

	if(x->right != nullptr){
		x->right->parent = x;
	}
	y->left = x;
	x->parent = y;

	if(y->parent != nullptr){
		if(y->parent->right == x)
			y->parent->right = y;
		else
			y->parent->left = y;
	}
	setBalance(x);
	setBalance(y);
	return y;
}

template<class Type>
node<Type>* tree<Type>::rotateRight(node<Type> *x){
	node<Type>* y = x->left;
	y->parent = x->parent;
	x->left = y->right;

	if(x->left != nullptr){
		x->left->parent = x;
	}
	y->right = x;
	x->parent = y;

	if(y->parent != nullptr){
		if(y->parent->right == x)
			y->parent->right = y;
		else
			y->parent->left = y;
	}
	setBalance(x);
	setBalance(y);
	return y;
}

template<class Type>
node<Type>* tree<Type>::rotateLeftThenRight(node<Type> *x){
	x->left = rotateLeft(x->left);
	return rotateRight(x);
}

template<class Type>
node<Type>* tree<Type>::rotateRightThenLeft(node<Type> *x){
	x->right = rotateRight(x->right);
	return rotateLeft(x);
}

template<class Type>
bool tree<Type>::insert(Type k){

	if(root == nullptr){
		root = new node<Type>(k,nullptr);
	}
	else{
		node<Type> *trav = root, *trav_p;
		while(1){
			if(trav->key == k)
				return false;

			trav_p = trav;
			bool goLeft = trav->key > k;
			trav = goLeft ? trav->left : trav->right;

			if(trav == nullptr){
				if(goLeft)
					trav_p->left = new node<Type>(k,trav_p);
				else
					trav_p->right = new node<Type>(k,trav_p);

				rebalance(trav_p);
				break;
			}
		}
	}
	return true;
}

template<class Type>
void tree<Type>::remove(const Type k){
	if(root == nullptr)
		return;

	node<Type> *trav = root, *trav_p = root, *trav_c = root, *delNode;
	while(trav_c != nullptr){
		trav_p = trav;
		trav = trav_c;
		trav_c = k >= trav->key ? trav->right : trav->left;
		if(k == trav->key)
			delNode = trav;
	}

	if(delNode != nullptr){
		delNode->key = trav->key;
		trav_c = (trav->left != nullptr) ? trav->left :trav->right;

		if(root->key == k){
			root = trav_c;
		}
		else{
			if(trav_p->left == trav)
				trav_p->left = trav_c;
			else
                trav_p->right = trav_c;

		}
		rebalance(trav_p);
	}
}
template<class Type>
void tree<Type>::inorder(node<Type>* n){
	if (n == nullptr)
        return;
    inorder(n->left);
    std::cout << n->key << " ";
    inorder(n->right);
}

#endif
