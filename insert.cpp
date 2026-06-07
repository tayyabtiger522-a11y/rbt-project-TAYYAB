#include "rbt.h"
// This header file contains all the code related to insertion


// determine whether we have a 2node, 3node or a 4node case
// 2node = parent is black   returns 2
// 3node = parent is red gp is black and uncle is black  returns 3
// 4node = parent is red gp is black and uncle is red    returns 4
int rbt::determine_case(Node* n, Node* parent, Node* grand_parent, Node* uncle)
{

    // 2node = parent is black
    if (parent->color == 'B')
    {
        return 2;
    }
    // 3node = parent is red gp is black and uncle is black
    else if (parent->color == 'R' && grand_parent->color == 'B')
    {
        if (uncle == nullptr || uncle->color == 'B')
        {
            return 3;
        }

        // 4node = parent is red gp is black and uncle is red
        // Now the uncle must be red
        return 4;
    }

    return -1; // error
}

// determine whether we have a 2node, 3node or a 4node case
// 2node = parent is black   returns 2
// 3node = parent is red gp is black and uncle is black  returns 3
// 4node = parent is red gp is black and uncle is red    returns 4
int rbt::determine_case(Node *n)
{
    //this version of determine_case gets called during the recursive 4 node case

    Node *parent = find_parent(n);
    // 2node = parent is black
    if (parent->color == 'B')
    {
        return 2;
    }

    Node *grand_parent = find_parent(parent);

    if (parent->color == 'R' && grand_parent->color == 'B')
    {
        // find uncle
        Node *uncle = nullptr;
        if (grand_parent->right == parent)
        {
            uncle = grand_parent->left;
        }
        else if (grand_parent->left == parent)
        {
            uncle = grand_parent->right;
        }

        // 3node = parent is red gp is black and uncle is black
        if (uncle == nullptr || uncle->color == 'B')
        {
            return 3;
        }

        // 4node = parent is red gp is black and uncle is red
        // Now the uncle must be red
        return 4;
    }

    return -1; // error
}

// inserts the Node n according to the rules of bst
int rbt::insert_like_bst(Node *n)
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
                return determine_case(n, parent, grand_parent, uncle);
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
                return determine_case(n, parent, grand_parent, uncle);
            }
        }
    }
}

// parent is red while grand_parent and uncle is black
// 3node = parent is red gp is black and uncle is black
void rbt::three_node_case(Node* n)
{

    Node* parent = find_parent(n);
    Node* grand_parent = find_parent(parent);

    grand_parent->color = 'R'; // gp color would be changed at every case regardless

    // first reduce the RL and LR cases if they are present

    // right-left case
    if (grand_parent->right == parent && parent->left == n)
    {
        rotate_right(n, grand_parent, parent); // RL -> RR

        // parent and child ptr get exchanged after rotation
        Node* tmp = n;
        n = parent;
        parent = tmp;
    }
    // left-right case
    else if (grand_parent->left == parent && parent->right == n)
    {
        rotate_left(n, grand_parent, parent); // LR -> LL

        // parent and child ptr get exchanged after rotation
        Node* tmp = n;
        n = parent;
        parent = tmp;
    }

    // left-left case
    if (grand_parent->left == parent && parent->left == n)
    {
        parent->color = 'B';

        // single right rotation i.e clock wise
        rotate_right(parent);
    }
    // right-right case
    else if (grand_parent->right == parent && parent->right == n)
    {
        parent->color = 'B';

        // single left rotation i.e anti clock wise
        rotate_left(parent);
    }
}

// Handles the 4node case where = parent is red gp is black and uncle is red
void rbt::four_node_case(Node* n)
{

    Node* parent = find_parent(n);
    Node* grand_parent = find_parent(parent);
    Node* uncle = nullptr;
    if (grand_parent->right == parent)
    {
        uncle = grand_parent->left;
    }
    else if (grand_parent->left == parent)
    {
        uncle = grand_parent->right;
    }

    // color flip
    grand_parent->color = 'R';
    uncle->color = 'B';
    parent->color = 'B';

    // simplest case also the base case for recursion
    if (grand_parent == root)
    {
        // root would always be black
        grand_parent->color = 'B';
        return;
    }

    int node_case = determine_case(grand_parent);

    //base case 2 for recursion
    if (node_case == 2)
    {
        return;
    }
    //base case 3 for recursion
    else if (node_case == 3)
    {
        three_node_case(grand_parent);
        return;
    }
    else if (node_case == 4)
    {
        // go until you find a 2node, 3node or root
        four_node_case(grand_parent);
        return;
    }
}


void rbt::insert(int value)
{
    //duplicate case
    Node* duplicate = search(value);

    //duplicate value found
    if (duplicate!=nullptr)
    {
        duplicate->counter++;
        return;
    }
    
    //duplicate not found
    Node *new_node = new Node{value, 'R', 1,nullptr, nullptr};

    if (root == nullptr)
    {
        root = new_node;
        root->color = 'B';

        return;
    }
    else
    {
        int node_case = insert_like_bst(new_node);

        if (node_case == 2)
        {
            // cout << "Simple 2 node case nothing\n";
            return;
        }
        else if (node_case == 3)
        {
            //cout << "3 node case \n";
            three_node_case(new_node);
            return;
        }
        else if (node_case == 4)
        {
            //cout << "4 node case \n";
            four_node_case(new_node);
            return;
        }
        else
        {
            cout << "Error \n";
            return;
        }
    }
}