#ifndef NODE_
#define NODE_

#include <iostream>
#include <string>

#include "PresonalInfo.h"
template <class Key, class Content>
class Node {
    private:
        Key key_;
        Content content_;
        Node *left_;
        Node *right_;
    public:
        void setKey(Key key) {
            key_ = key;
        }
        Key getKey() {
            return key_;
        }
        void setContent(Content content) {
            content_ = content;
        }
        Content getContent() {
            return content_;
        }
        Node* getLeft() {
            return left_;
        }
        Node* getRight() {
            return right_;
        }
        void setLeft(Node *l) {
            left_ = l;
        }
        void setRight(Node *r) {
            right_ = r;
        }
        Node(Key key, Content content, Node *l = NULL, Node *r = NULL): key_(key), content_(content), left_(l), right_(r) {};
        bool operator>(Node &x) {
            return this.key_ > x.getKey();
        }
        bool operator==(Node &x) {
            return key_ == x.getKey() && content_ == x.getContent();
        }
        std::ostream & operator<<(std::ostream &s) {
            s << key_ << std::endl;
            s << content_ << std::endl;
            return s;
        }
};

#endif // NODE_
