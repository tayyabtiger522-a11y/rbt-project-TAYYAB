#pragma once
#include <iostream>
using namespace std;

struct Node
{
    int data;
    char color; // r for red b for black
    Node *left;
    Node *right;
};

class rbt
{
public:
    Node *root;

    char insert_like_bst(Node *n);

public:
    rbt();
    ~rbt();

    Node *find_parent(Node *n);
    Node *find_grand_parent(Node *n);
    Node *find_uncle(Node *n);

    void three_node_case(Node *n);

    void rotate_right(Node *n);
    void rotate_left(Node *n);

    void rotate_right(Node *n, Node *grand_parent, Node *parent);
    void rotate_left(Node *n, Node *grand_parent, Node *parent);

    void insert(int value);
};

// rotate right around the pivot n
// assuming p and gp are valid
void rbt::rotate_left(Node *n, Node *grand_parent, Node *parent)
{
    // can't rotate if no parent
    if (parent == n)
    {
        return;
    }

    //cant rotate left a left child of a parent
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

    //cant rotate right a right child of a parent
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

// parent is red while grand_parent and uncle is black
void rbt::three_node_case(Node *n)
{

    Node *parent = find_parent(n);
    Node *grand_parent = find_grand_parent(n);

    grand_parent->color = 'r'; // gp color would be changed at every case regardless

    // first reduce the RL and LR cases if they are present

    // right-left case
    if (grand_parent->right == parent && parent->left == n)
    {
        rotate_right(n,grand_parent,parent); // RL -> RR
    
        // parent and child ptr get exchanged after rotation
        Node *tmp = n;
        n = parent;
        parent = tmp;
    }
    // left-right case
    else if (grand_parent->left == parent && parent->right == n)
    {
        rotate_left(n,grand_parent,parent); // LR -> LL
    
        // parent and child ptr get exchanged after rotation
        Node *tmp = n;
        n = parent;
        parent = tmp;
    }

    // left-left case
    if (grand_parent->left == parent && parent->left == n)
    {
        parent->color = 'b';

        // single right rotation i.e clock wise
        rotate_right(parent);
    }
    // right-right case
    else if (grand_parent->right == parent && parent->right == n)
    {
        parent->color = 'b';

        // single left rotation i.e anti clock wise
        rotate_right(parent);
    }
}

// find the uncle of the given node
// if the node is not in the tree then it returns the would be uncle
Node *rbt::find_uncle(Node *n)
{

    if (n == root)
    {
        return root;
    }

    Node *tmp = root;
    Node *parent = root;
    Node *grand_parent = root;
    Node *uncle = root;

    while (tmp != n)
    {
        if (n->data < tmp->data)
        {
            // still have the left subtree to go through
            if (tmp->left != nullptr)
            {
                grand_parent = parent;
                uncle = grand_parent->right;
                parent = tmp;
                tmp = tmp->left;
            }
            else
            {
                // given node is not in the tree
                return uncle;
            }
        }
        else if (n->data > tmp->data)
        {
            // still have the right subtree to go through
            if (tmp->right != nullptr)
            {
                grand_parent = parent;
                uncle = grand_parent->right;
                parent = tmp;
                tmp = tmp->right;
            }
            else
            {
                // given node is not in the tree
                return uncle;
            }
        }
    }
    return uncle;
}

// find the grand parent of the given node
// if the node is not in the tree then it returns the would be grand parent
Node *rbt::find_grand_parent(Node *n)
{

    if (n == root)
    {
        return root;
    }

    Node *tmp = root;
    Node *parent = root;
    Node *grand_parent = root;

    while (tmp != n)
    {
        if (n->data < tmp->data)
        {
            // still have the left subtree to go through
            if (tmp->left != nullptr)
            {
                grand_parent = parent;
                parent = tmp;
                tmp = tmp->left;
            }
            else
            {
                // given node is not in the tree
                return grand_parent;
            }
        }
        else if (n->data > tmp->data)
        {
            // still have the right subtree to go through
            if (tmp->right != nullptr)
            {
                grand_parent = parent;
                parent = tmp;
                tmp = tmp->right;
            }
            else
            {
                // given node is not in the tree
                return grand_parent;
            }
        }
    }
    return grand_parent;
}

// rotate left around the pivot n
// finds gp and parent automatically
void rbt::rotate_left(Node *n)
{
    Node *parent = find_parent(n);
    Node *grand_parent = find_grand_parent(n);

    // can't rotate if no parent
    if (parent == n)
    {
        return;
    }

    //cant rotate left a left child of a parent
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

// rotate right around the pivot n
void rbt::rotate_right(Node *n)
{
    Node *parent = find_parent(n);
    Node *grand_parent = find_grand_parent(n);

    // can't rotate if no parent
    if (parent == n)
    {
        return;
    }

    //cant rotate right a right child of a parent
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

// inserts the Node n according to the rules of bst
char rbt::insert_like_bst(Node *n)
{
    Node *parent = root;
    Node *grand_parent = root;
    Node *uncle = root;

    while (true)
    {
        if (n->data < parent->data)
        {
            // still have the left subtree to go through
            if (parent->left != nullptr)
            {
                grand_parent = parent;
                uncle = grand_parent->right;
                parent = parent->left;
            }
            else
            {
                // found the node
                parent->left = n;
                // determine whether we have 2node, 3node or a 4node case
                if (parent->color == 'b')
                {
                    return '2';
                }
                else if (parent->color == 'r' && grand_parent->color == 'b')
                {
                    if (uncle == nullptr || uncle->color == 'b')
                    {
                        return '3';
                    }
                    return '4';
                }
                else
                {
                    return '4';
                }
            }
        }
        else if (n->data > parent->data)
        {
            // still have the right subtree to go through
            if (parent->right != nullptr)
            {
                grand_parent = parent;
                uncle = grand_parent->left;
                parent = parent->right;
            }
            else
            {
                // found the node
                parent->right = n;
                // determine whether we have 2node, 3node or a 4node case
                if (parent->color == 'b')
                {
                    return '2';
                }
                else if (parent->color == 'r' && grand_parent->color == 'b')
                {
                    if (uncle == nullptr || uncle->color == 'b')
                    {
                        return '3';
                    }
                    return '4';
                }
                else
                {
                    return '4';
                }
            }
        }
    }
}

void rbt::insert(int value)
{

    Node *new_node = new Node{value, 'r', nullptr, nullptr};

    if (root == nullptr)
    {
        root = new_node;
        root->color = 'b';

        return;
    }
    else
    {
        char node_case = insert_like_bst(new_node);

        if (node_case == '2')
        {
            cout << "Simple 2 node case nothing\n";
            return;
        }
        else if (node_case == '3')
        {
            cout << "3 node case \n";
            three_node_case(new_node);
            return;
        }
        else if (node_case == '4')
        {
            cout << "4 node case \n";
            return;
        }
    }
}

rbt::rbt() : root{nullptr}
{
}

rbt::~rbt()
{
}
