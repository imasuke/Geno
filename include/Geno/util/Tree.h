// Tree.h
#ifndef TREE_HEADER
#define TREE_HEADER

#include "Geno/util/random.h"

namespace Geno{
    // Definition
    template <class T> class Tree;
    template <class T> unsigned int countSubNodes(Tree<T> *n);
	template <class T> Tree<T>* randomSubNode(Tree<T> *n);

	// Template Node class for Tree structure
	template <class T>
	class Tree {
	public:
		Tree(void) : right(nullptr), left(nullptr){
		}
		Tree(const T &value) : value(value), right(nullptr), left(nullptr){
		}
		Tree(const T &value, Tree *right, Tree *left) : value(value), right(right), left(left){
		}
		Tree(const Tree &n){
			this->value = n.value;
			this->right = new Tree(*n.right);
			this->left = new Tree(*n.left);
		}
		Tree<T>& operator=(const Tree &c){
			this->value = c.value;
			this->right = new Tree(*c.right);
			this->left = new Tree(*c.left);
			return(*this);
		}
		virtual ~Tree(){
			if(right != nullptr) delete right;
			if(left != nullptr) delete left;
		}
		size_t numOfNodes(void){
			return countSubNodes(this);
		}

	public:
		T value;
		Tree* right;
		Tree* left;
	};

    // Count number of sub nodes
    template <class T>
	unsigned int countSubNodes(Tree<T> *n){
        unsigned int count = 1;
        if(n->left != nullptr){
            count += countSubNodes(n->left);
        }
        if(n->right != nullptr){
            count += countSubNodes(n->right);
        }
        return count;
    }

	// Pick up random sub node
	template <class T> 
	Tree<T>* randomSubNode(Tree<T> *n){
		Randomizer rand;
		Tree<T> *ptr = n;
		unsigned int numOfNodes = n->numOfNodes(), depth = 1;

		while(n->left != nullptr || n->right != nullptr){
			bool isPtrChosen = rand.randomDouble(1.0) < (1.0 / numOfNodes * depth);
			if(isPtrChosen){
				return ptr;
			}
			else{
				if(n->left != nullptr && n->right != nullptr){
					ptr = rand.randomBool() ? n->left : n->right;
				}
				else if(n->left != nullptr){
					ptr = n->left;
				}
				else if(n->right != nullptr){
					ptr = n->right;
				}
				depth++;
			}
		}
		// return leaf node
		return ptr;
	}
}

#endif