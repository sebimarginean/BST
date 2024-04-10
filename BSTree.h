#ifndef BSTREE_H_
#define BSTREE_H_

#include <string>
#include <iostream>
#include <sstream>

struct Node
{
    int key;      // key
    Node *parent; // pointer to parent
    Node *left;   // pointer to left child
    Node *right;  // pointer to right child

    static Node* Nil;

    Node(int k, Node *l = Nil, Node *r = Nil, Node *p = Nil) :
        key(k), parent(p), left(l), right(r) { }

    std::string toString()
    {
        std::ostringstream os;
        os << key;
        return os.str();
    }

    ~Node()
    {
        if(left != Node::Nil)
            delete left;
        if(right != Node::Nil)
            delete right;
    }
};

Node* Node::Nil = new Node(0);

struct BSTree
{
    Node* root;

    /* Default constructor: creates an empty tree */
    BSTree()
    {
        root = Node::Nil;
    }

    ~BSTree()
    {
        delete root;
    }

    Node* createNode(int key)
    {
        return new Node(key);
    }

    /**
     * return the node with key k from this tree, and null
     * if no such node exists
     */
    Node* search(int k)
    {
        return search(root, k);
    }

    Node* search(Node* w, int key)
    {
        if (w == Node::Nil || w->key == key)
            return w;
        return search( (key < w->key) ? w->left : w->right, key);
    }

    Node* maximum(Node* w)
    {
        Node* x = w;
        while (x->right != Node::Nil)
            x = x->right;
        return x;
    }


    Node* minimum(Node* w)
    {
        Node* x = w;
        while (x->left != Node::Nil)
            x = x->left;
        return x;
    }

    /**
     * return a pointer to the successor of node w in
     * this binary search tree
     */
    Node* successor(Node* w)
    {
        Node* x = w;
        if (x->right != Node::Nil) return minimum(x->right);
        if (x->parent == Node::Nil)
            return Node::Nil; // x has no successor
        Node* y = x->parent;
        while (y != Node::Nil && x == y->right)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    /**
     * return a pointer to the predecessor of node w in
     * this binary search tree
     */
    Node* predecessor(Node* w)
    {
        Node* x = w;
        if (x->left != Node::Nil) return maximum(x->left);
        if (x->parent == Node::Nil)
            return Node::Nil; // x has no predecessor
        Node* y = x->parent;
        while (y != Node::Nil && x == y->left)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }


    /*
     * Insert node z at the right place in the binary search tree
     */
    void insert(Node* z)
    {
        Node* y = Node::Nil;
        Node* x = root;
        while (x != Node::Nil)
        {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (y == Node::Nil)
            root = z; // tree was empty
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
    }


    /**
     * Removes node z from this tree
     */
    Node* transplant(Node* u, Node* v)
    {
        if (u->parent == Node::Nil)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v != Node::Nil)
            v->parent = u->parent;
        return u;
    }

    Node* del(Node* z)
    {
        if (z->left == Node::Nil)
            return transplant(z, z->right);
        else if (z->right == Node::Nil)
            return transplant(z, z->left);
        else
        {
            Node* y = minimum(z->right);
            if (y->parent != z)
            {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            return z;
        }
    }


    /**
     * This method performs the traversal in inorder
     * of the nodes of a binary tree.
     */
    void inorder(Node* T)
    {
        if (T != Node::Nil)
        {
            inorder(T->left);
            std::cout << T->toString() << ' ';
            inorder(T->right);
        }
    }

    void inorder()
    {
        inorder(root);
    }

    /**
     * Auxiliary method to display the content of a binary tree
     * in an indented way.
     */
    void display(Node* w, int indent)
    {
        if (w != Node::Nil)
        {
            display(w->right, indent + 2);
            for (int i = 0; i < indent; i++) std::cout << ' ';
            std::cout << w->toString() << '\n';
            display(w->left, indent + 2);
        }
    }

    void indentedDisplay()
    {
        std::cout << "The binary search tree is" << std::endl;
        display(root, 0);
    }

    int depth()
    {
        return depth(root);
    }

    int depth(Node* n)
    {
        if(n==Node::Nil)
            return -1;
        else
        {
            int lDepth = depth(n->left);
            int rDepth = depth(n->right);

            if(lDepth > rDepth)
                return lDepth+1;
            else
                return rDepth+1;
        }
    }
};

#endif /* BSTREE_H_ */
