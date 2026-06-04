#include "rbt.h"


int main()
{
    //20 16 1 71 78 91 3 63 5 8 95
    rbt r;

    //LL works
    // r.insert(20);
    // r.insert(16);
    // r.insert(1);

    // //RR works
    // r.insert(20);
    // r.insert(71);
    // r.insert(78);

    // RL works
    // r.insert(20);
    // r.insert(71);
    // r.insert(50);

    //LR works
    r.insert(20);
    r.insert(1);
    r.insert(10);

    
    


    system("pause");
    return 0;
}