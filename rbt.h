#pragma once
#include <iostream>
using namespace std;
//new branch
struct Node
{
    int data;
    char color; // r for red b for black
    Node* left;
    Node* right;
};

class rbt
{
public:
    Node* root;

    int insert_like_bst(Node* n);
    bool delete_like_bst(int value);
    int determine_case(Node* n, Node* parent, Node* grand_parent, Node* uncle);

    Node* search(int value);
    Node* smallest(Node* starting_node);
    void predisplay(Node* t);
public:
    rbt();
    ~rbt();

    void preorder();

    Node* find_parent(Node* n);
    Node* find_grand_parent(Node* n);
    Node* find_uncle(Node* n);

    void three_node_case(Node* n);
    void four_node_case(Node* n);

    void rotate_right(Node* n);
    void rotate_left(Node* n);

    void rotate_right(Node* n, Node* grand_parent, Node* parent);
    void rotate_left(Node* n, Node* grand_parent, Node* parent);

    void insert(int value);

    int determine_case(Node* n);

    bool deletenode(int v);

    bool delete_(int value);
    void checkdeletion(Node* t);

};

void rbt::predisplay(Node* t)
{
    if (t != nullptr)
    {
        cout << t->data << " ( " << t->color << " )" << endl << endl;

        predisplay(t->left);
        predisplay(t->right);
    }
}
void rbt::preorder()
{
    predisplay(root);
}


// determine whether we have a 2node, 3node or a 4node case
// 2node = parent is black   returns 2
// 3node = parent is red gp is black and uncle is black  returns 3
// 4node = parent is red gp is black and uncle is red    returns 4
int rbt::determine_case(Node* n)
{

    Node* parent = find_parent(n);
    // 2node = parent is black
    if (parent->color == 'b')
    {
        return 2;
    }

    Node* grand_parent = find_parent(parent);

    if (parent->color == 'r' && grand_parent->color == 'b')
    {
        // find uncle
        Node* uncle = nullptr;
        if (grand_parent->right == parent)
        {
            uncle = grand_parent->left;
        }
        else if (grand_parent->left == parent)
        {
            uncle = grand_parent->right;
        }

        // 3node = parent is red gp is black and uncle is black
        if (uncle == nullptr || uncle->color == 'b')
        {
            return 3;
        }

        // 4node = parent is red gp is black and uncle is red
        // Now the uncle must be red
        return 4;
    }

    return -1; // error
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
    grand_parent->color = 'r';
    uncle->color = 'b';
    parent->color = 'b';

    // simplest case also the base case for recursion
    if (grand_parent == root)
    {
        // root would always be black
        grand_parent->color = 'b';
        return;
    }

    // Node *great_grandparent = find_parent(grand_parent);

    int node_case = determine_case(grand_parent);

    if (node_case == 2)
    {
        return;
    }
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

// determine whether we have a 2node, 3node or a 4node case
// 2node = parent is black   returns 2
// 3node = parent is red gp is black and uncle is black  returns 3
// 4node = parent is red gp is black and uncle is red    returns 4
int rbt::determine_case(Node* n, Node* parent, Node* grand_parent, Node* uncle)
{

    // 2node = parent is black
    if (parent->color == 'b')
    {
        return 2;
    }
    // 3node = parent is red gp is black and uncle is black
    else if (parent->color == 'r' && grand_parent->color == 'b')
    {
        if (uncle == nullptr || uncle->color == 'b')
        {
            return 3;
        }

        // 4node = parent is red gp is black and uncle is red
        // Now the uncle must be red
        return 4;
    }

    return -1; // error
}

// rotate right around the pivot n
// assuming p and gp are valid
void rbt::rotate_left(Node* n, Node* grand_parent, Node* parent)
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
void rbt::rotate_right(Node* n, Node* grand_parent, Node* parent)
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

// parent is red while grand_parent and uncle is black
// 3node = parent is red gp is black and uncle is black
void rbt::three_node_case(Node* n)
{

    Node* parent = find_parent(n);
    Node* grand_parent = find_grand_parent(n);

    grand_parent->color = 'r'; // gp color would be changed at every case regardless

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
        parent->color = 'b';

        // single right rotation i.e clock wise
        rotate_right(parent);
    }
    // right-right case
    else if (grand_parent->right == parent && parent->right == n)
    {
        parent->color = 'b';

        // single left rotation i.e anti clock wise
        rotate_left(parent);
    }
}

// find the uncle of the given node
// if the node is not in the tree then it returns the would be uncle
Node* rbt::find_uncle(Node* n)
{

    if (n == root)
    {
        return root;
    }

    Node* tmp = root;
    Node* parent = root;
    Node* grand_parent = root;
    Node* uncle = root;

    while (true)
    {
        if (n->data < tmp->data)
        {
            // still have the left subtree to go through
            if (tmp->left != nullptr)
            {
                if (tmp->left != n)
                {
                    grand_parent = parent;
                    parent = tmp;
                    // uncle should be the opposite child to parent
                    if (grand_parent->left == parent)
                    {
                        uncle = grand_parent->right;
                    }
                    else if (grand_parent->left == parent)
                    {
                        uncle = grand_parent->right;
                    }

                    tmp = tmp->left;
                }
                else
                {
                    // found the node
                    return uncle;
                }
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
                if (tmp->right != n)
                {
                    grand_parent = parent;
                    parent = tmp;

                    // uncle should be the opposite child to parent
                    if (grand_parent->left == parent)
                    {
                        uncle = grand_parent->right;
                    }
                    else if (grand_parent->left == parent)
                    {
                        uncle = grand_parent->right;
                    }

                    tmp = tmp->right;
                }
                else
                {
                    // found the node
                    return uncle;
                }
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
Node* rbt::find_grand_parent(Node* n)
{

    if (n == root)
    {
        return root;
    }

    Node* tmp = root;
    Node* parent = root;
    Node* grand_parent = root;

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
void rbt::rotate_left(Node* n)
{
    Node* parent = find_parent(n);
    Node* grand_parent = find_grand_parent(n);

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

// find the parent of the given node
// if the node is not in the tree then it returns the would be parent
Node* rbt::find_parent(Node* n)
{
    if (n == root)
    {
        return root;
    }

    Node* tmp = root;
    Node* parent = root;
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
void rbt::rotate_right(Node* n)
{
    Node* parent = find_parent(n);
    Node* grand_parent = find_grand_parent(n);

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

// inserts the Node n according to the rules of bst
int rbt::insert_like_bst(Node* n)
{
    Node* parent = root;
    Node* grand_parent = root;
    Node* uncle = root;

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

void rbt::insert(int value)
{

    Node* new_node = new Node{ value, 'r', nullptr, nullptr };

    if (root == nullptr)
    {
        root = new_node;
        root->color = 'b';

        return;
    }
    else
    {
        int node_case = insert_like_bst(new_node);

        if (node_case == 2)
        {
            cout << "Simple 2 node case nothing\n";
            return;
        }
        else if (node_case == 3)
        {
            cout << "3 node case \n";
            three_node_case(new_node);
            return;
        }
        else if (node_case == 4)
        {
            cout << "4 node case \n";
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



bool rbt::deletenode(int v)
{
    Node* t = root;
    Node* p = nullptr;
    while (t != nullptr)
    {
        if (v == t->data)
        {

            if (t->left == nullptr && t->right == nullptr) //simply delete node
            {
                if (t == root)
                {
                    delete root;
                    root = nullptr;
                }
                else
                {
                    if (p->left == t)
                        p->left = nullptr;
                    else
                        p->right = nullptr;

                    delete t;
                }
                return true;
            }
            else if (t->left != nullptr && t->right == nullptr) // one child case
            {

                if (t == root)
                {
                    root = root->left;
                }
                else
                {
                    if (p->left == t)
                        p->left = t->left;
                    else
                        p->right = t->left;


                }
                if (t->color == 'B')  //check color of node if red then simply delete
                {
                    if (t->left->color == 'R')
                        t->left->color = 'B';
                    else
                        checkdeletion(t->left);//if child and parent both are black that is double black problem
                }
                delete t;
                return true;
            }

            else if (t->left == nullptr && t->right != nullptr)
            {
                if (t == root)
                {
                    root = root->right;

                }
                else
                {
                    if (p->left == t)
                        p->left = t->right;
                    else
                        p->right = t->right;
                }
                if (t->color == 'B')
                {
                    if (t->right->color == 'R')
                        t->right->color = 'B';
                    else
                        checkdeletion(t->right);
                }
                delete t;
                return true;
            }
            else if (t->left != nullptr && t->right != nullptr)
            {
                Node* temp = t->right;
                Node* ptmp = t;
                while (temp->left != nullptr)
                {
                    ptmp = temp;
                    temp = temp->left;
                }
                char deletedColor = temp->color;

                t->data = temp->data;
                if (ptmp->left == temp)
                    ptmp->left = temp->right;
                else
                    ptmp->right = temp->right;

                if (deletedColor == 'B')
                {
                    if (temp->right != nullptr && temp->right->color == 'R') //temp->right=child of node.
                        temp->right->color = 'B';
                    else
                        checkdeletion(temp->right);
                }


                delete temp;

                return true;
            }
        }
        else if (v < t->data)
        {
            p = t;
            t = t->left;
        }
        else if (v > t->data)
        {
            p = t;
            t = t->right;
        }
    }
    return false;
}

void rbt::checkdeletion(Node* t)
{

    while (t != root && t->color == 'B')
    {
        Node* sib = nullptr;
        Node* p = find_parent(t);

        if (p->left == t)
        {
            sib = p->right;
            if (sib->color == 'R')
            {
                sib->color = 'B';
                p->color = 'R';
                rotate_left(p);
                sib = p->right;
            }


            if (sib->left->color == 'B' && sib->right->color == 'B')
            {
                sib->color = 'R';
                t = p;
            }
            else
            {

                if (sib->right->color == 'B')
                {
                    sib->left->color = 'B';
                    sib->color = 'R';
                    rotate_right(sib);
                    sib = p->right;
                }

                sib->color = p->color;
                p->color = 'B';
                sib->right->color = 'B';
                rotate_left(p);
                t = root;
            }
        }
        else       // just oppsite of the upper version
        {
            sib = p->left;
            if (sib->color == 'R')
            {
                sib->color = 'B';
                p->color = 'R';
                rotate_right(p);
                sib = p->left;
            }


            if (sib->left->color == 'B' && sib->right->color == 'B')
            {
                sib->color = 'R';
                t = p;
            }
            else
            {

                if (sib->left->color == 'B')
                {
                    sib->left->color = 'B';
                    sib->color = 'R';
                    rotate_left(sib);
                    sib = p->left;
                }

                sib->color = p->color;
                p->color = 'B';
                sib->left->color = 'B';
                rotate_right(p);
                t = root;
            }
        }
    }
    t->color = 'B';
}

rbt::rbt() : root{ nullptr }
{
}

rbt::~rbt()
{
}
