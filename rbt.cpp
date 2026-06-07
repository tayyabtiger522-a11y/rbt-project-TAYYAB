#pragma once
#include "rbt.h"
#include "insert.cpp"
#include "delete2.cpp"

void rbt::predisplay(Node *t)
{
    if (t != nullptr)
    {
        cout << t->data << " ( " << t->color << " )" << endl
             << endl;

        predisplay(t->left);
        predisplay(t->right);
    }
}
// NLR
void rbt::preorder()
{
    if (root == nullptr)
    {
        cout << "tree is empty\n";
        return;
    }

    predisplay(root);
}

void rbt::indisplay(Node* t)
{
    if (t != nullptr)
    {
        indisplay(t->left);
        cout << t->data << " ( " << t->color << " )" << endl << endl;
        indisplay(t->right);
    }
}
void rbt::inorder()
{
    if (root == nullptr)
    {
        cout << "tree is empty\n";
        return;
    }
    indisplay(root);
}

void rbt::postdisplay(Node* t)
{
    if (t != nullptr)
    {
        postdisplay(t->left);
        postdisplay(t->right);
        cout << t->data << " ( " << t->color << " )" << endl << endl;
    }
}
void rbt::postorder()
{
    if (root == nullptr)
    {
        cout << "tree is empty\n";
        return;
    }
    postdisplay(root);
}


// rotate right around the pivot n
// assuming p and gp are valid
void rbt::rotate_left(Node *n, Node *grand_parent, Node *parent)
{
    // can't rotate if no parent
    if (parent == n)
    {
        return;
    }

    // cant rotate left a left child of a parent
    if (parent->left == n)
    {
        return;
    }

    if (parent == root)
    {
        root = n;
    }

    parent->right = n->left;
    n->left = parent;

    // update whatever link of gp was affected
    if (grand_parent->right == parent)
    {
        grand_parent->right = n;
    }
    else if (grand_parent->left == parent)
    {
        grand_parent->left = n;
    }
}

// rotate right around the pivot n
// assuming p and gp are valid
void rbt::rotate_right(Node *n, Node *grand_parent, Node *parent)
{
    // can't rotate if no parent
    if (parent == n)
    {
        return;
    }

    // cant rotate right a right child of a parent
    if (parent->right == n)
    {
        return;
    }

    if (parent == root)
    {
        root = n;
    }

    parent->left = n->right;
    n->right = parent;

    // update whatever link of gp was affected
    if (grand_parent->right == parent)
    {
        grand_parent->right = n;
    }
    else if (grand_parent->left == parent)
    {
        grand_parent->left = n;
    }
}

// rotate left around the pivot n
// finds gp and parent automatically
void rbt::rotate_left(Node *n)
{
    Node *parent = find_parent(n);
    Node *grand_parent = find_parent(parent);

    // can't rotate if no parent
    if (parent == n)
    {
        return;
    }

    // cant rotate left a left child of a parent
    if (parent->left == n)
    {
        return;
    }

    if (parent == root)
    {
        root = n;
    }

    parent->right = n->left;
    n->left = parent;

    // update whatever link of gp was affected
    if (grand_parent->right == parent)
    {
        grand_parent->right = n;
    }
    else if (grand_parent->left == parent)
    {
        grand_parent->left = n;
    }
}

// rotate right around the pivot n
void rbt::rotate_right(Node *n)
{
    Node *parent = find_parent(n);
    Node *grand_parent = find_parent(parent);

    // can't rotate if no parent
    if (parent == n)
    {
        return;
    }

    // cant rotate right a right child of a parent
    if (parent->right == n)
    {
        return;
    }

    if (parent == root)
    {
        root = n;
    }

    parent->left = n->right;
    n->right = parent;

    // update whatever link of gp was affected
    if (grand_parent->right == parent)
    {
        grand_parent->right = n;
    }
    else if (grand_parent->left == parent)
    {
        grand_parent->left = n;
    }
}

// find the parent of the given node
// if the node is not in the tree then it returns the would be parent
Node *rbt::find_parent(Node *n)
{
    if (n == root)
    {
        return root;
    }

    Node *tmp = root;
    Node *parent = root;
    while (tmp != n)
    {
        if (n->data < tmp->data)
        {
            // still have the left subtree to go through
            if (tmp->left != nullptr)
            {
                parent = tmp;
                tmp = tmp->left;
            }
            else
            {
                // given node is not in the tree
                return parent;
            }
        }
        else if (n->data > tmp->data)
        {
            // still have the right subtree to go through
            if (tmp->right != nullptr)
            {
                parent = tmp;
                tmp = tmp->right;
            }
            else
            {
                // given node is not in the tree
                return parent;
            }
        }
    }
    return parent;
}


// given the value return the node where the value is located in the tree
Node *rbt::search(int value)
{
    Node *current = root;

    // if we haven't found the value then search for the value in the tree
    while (current->data != value)
    {
        // go to left subtree
        if (value < current->data)
        {
            current = current->left; // advance the child
        }
        else if (value > current->data)
        {
            // go to right subtree
            current = current->right; // advance the child
        }

        // value is not in the current tree
        if (current == nullptr)
            return current;
    }
    return current;
}

rbt::rbt() : root{nullptr}
{
}

rbt::~rbt()
{
}
