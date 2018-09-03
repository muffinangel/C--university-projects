#ifndef MYMAP_
#define MYMAP_

#include "Node.h"
#include <sstream>

template <class Key, class Content>
class MyMap {
    private:
        Node<Key, Content> *head_;
    public:
        MyMap() {
            head_ = NULL;
        }
        void setHead(Node<Key, Content> *newhead) {
            head_ = newhead;
        }
        Node<Key, Content> *getHead() {
            return head_;
        }

        // if there is no node with key, then NULL is returned
        Node<Key, Content> *findNode(Node<Key, Content> *x, Key key) {
            if(x == NULL || x->getKey() == key) return x;
            if(x->getKey() > key) return findNode(x->getLeft(), key);
            return findNode(x->getRight(), key);
        }

        void insertNode(Node<Key, Content> *ins) {
            Node<Key, Content> *y = NULL;
            Node<Key, Content> *x = head_;
            while(x!= NULL) {
                y = x;
                if(x->getKey() > ins->getKey()) x = x->getLeft();
                else x = x->getRight();
            }
            if(y == NULL) //empty tree
                head_ = ins;
            else {
                if(y->getKey() > ins->getKey()) y->setLeft(ins);
                else y->setRight(ins);
            }
        }

        std::ostream & inorder(std::ostream &s, Node<Key, Content> *root){
            if (root != NULL)
            {
                inorder(s, root->getLeft());
                s << root->getKey() << std::endl;
                s << root->getContent() << std::endl;
                inorder(s, root->getRight());
            }
            return s;
         }

         Node<Key, Content> *minValueNode(Node<Key, Content> *node) {
             Node<Key, Content> *current = node;
             // finding the leftmost leaf
             if(!current) return current;
             while (current->getLeft() != NULL)
                current = current->getLeft();
             return current;
         }

        //function deletes node and returns new root
         Node<Key, Content> *deleteNode(Node<Key, Content> *root, Key key) {
             if(!root) return root;
             //key can lie either in left subtree or in right subtree or in the node
             if(root->getKey() > key) root->setLeft(deleteNode(root->getLeft(), key));
             else if(key > root->getKey()) root->setRight(deleteNode(root->getRight(), key));
             else { //key is the same as root's key
                //root with 0 or 1 child
                if(root->getLeft() == NULL) {
                    Node<Key, Content> *tmp = root->getRight();
                    free(root);
                    return tmp;
                }
                else if(root->getRight() == NULL) {
                    Node<Key, Content> *tmp = root->getLeft();
                    free(root);
                    return tmp;
                }
                //root with 2 children: it needs finding the inorder successor and then copy it to this node and then deleting
                Node<Key, Content> *tmp = minValueNode(root->getRight());
                root->setKey(tmp->getKey());
                root->setContent(tmp->getContent());
                root->setRight(deleteNode(root->getRight(), tmp->getKey()));
             }
             return root;
         }

         void freeMemory(Node<Key, Content> *root) {
             if(root) {
                freeMemory(root->getLeft());
                freeMemory(root->getRight());
                free(root);
                root = NULL;
             }
         }

};

#endif // MYMAP_

