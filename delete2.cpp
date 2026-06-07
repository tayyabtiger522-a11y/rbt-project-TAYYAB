#include "rbt.h"
// This header file contains all the code related to deletion

bool rbt::deletenode(int v)
{
    Node *t = root;
    Node *p = nullptr;
    while (t != nullptr)
    {
        if (v == t->data)
        {
            //red leaf case
            if (t->left == nullptr && t->right == nullptr) // simply delete node
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
                if (t->color == 'B') // check color of node if red then simply delete
                {
                    if (t->left->color == 'R')
                        t->left->color = 'B';
                    else
                        checkdeletion(t->left); // if child and parent both are black that is double black problem
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
                Node *temp = t->right;
                Node *ptmp = t;
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
                    if (temp->right != nullptr && temp->right->color == 'R') // temp->right=child of node.
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

void rbt::checkdeletion(Node *t)
{

    while (t != root && t->color == 'B')
    {
        Node *sib = nullptr;
        Node *p = find_parent(t);

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
        else // just oppsite of the upper version
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