#include "rbt.cpp"


int main()
{
    rbt r;

    //long example values
    // r.insert(20);
    // r.insert(2);
    // r.insert(10);
    // r.insert(25);
    // r.insert(17);
    // r.insert(23);
    // r.insert(5);
    // r.insert(30);
    // r.insert(40);
    // r.insert(29);
    // r.insert(50);
    // r.insert(55);
    // r.insert(45);
    // r.insert(46);
    // r.insert(49);
    // r.insert(47);
    // r.insert(48);
    // r.insert(123);
    // r.insert(51);
    // r.insert(100);
    // r.insert(110);
    // r.insert(115);
    // r.insert(125);
    // r.insert(120);

    //short example values
    r.insert(20);
    r.insert(2);
    r.insert(10);
    r.insert(25);
    r.insert(17);
    r.insert(100);
    r.insert(110);
    r.insert(115);
    r.insert(125);


    r.preorder();
    //r.inorder();
    //r.postorder();
    
    


    system("pause");
    return 0;
}