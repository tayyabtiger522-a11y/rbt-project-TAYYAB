#pragma once
#include <iostream>
#include "rbt.h"
using namespace std;

class menu
{
    void menu_options();
    int raw_input(const char* prompt);
    int menu_input(const char* prompt);


public:
    menu(rbt* rbt_tree);
    ~menu();
};

//take menu input choice from the user
int menu::menu_input(const char* prompt){

    int raw_inp = raw_input(prompt);

    while (raw_inp<1 || raw_inp>6)
    {
        cout<<"Invalid menu choice\n";
        raw_inp = raw_input(prompt);
    }
    
    return raw_inp;
}

//take a valid integer from the user
int menu::raw_input(const char* prompt){

    int x = 0;
    
    inp:
    cout<<prompt;
    cin>>x;

    if (!cin)
    {
        cin.clear();
        cin.ignore(1000,'\n');
        cout<<"Invaild input\n";

        goto inp;
    }
    
    return x;
}

void menu::menu_options(){

    cout<<"1) Insert value into RBT\n";
    cout<<"2) Display preorder\n";
    cout<<"3) Display inorder\n";
    cout<<"4) Display postorder\n";
    cout<<"4) Search value\n";
    cout<<"5) Delete value\n";
    cout<<"6) Quit\n";
}

menu::menu(rbt* rbt_tree)
{
    int choice = 0;

    while (true)
    {
        menu_options();
        choice = menu_input("\n>");


        if (choice == 1 )
        {
            int to_insert = raw_input("Enter value to insert: ");
            rbt_tree->insert(to_insert);
        }
        else if (choice == 2)
        {
            rbt_tree->preorder();
        }
        else if (choice == 2)
        {
            rbt_tree->preorder();
        }
        


        system("cls");
    }
    


}

menu::~menu()
{
}
