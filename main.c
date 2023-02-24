#include "treelib.h"

int main()
{
    tree* Medis = NULL;

    Medis = insertNode(Medis, 1);

    for(int i=1; i<50; i++){
        Medis = insertNode(Medis, i);
    }

    nodeOutput(Medis, 0);
    //nodeOutput_linear(Medis);


    if(contains(Medis, 20))
        printf("\n%d: Found\n", 20);
    else
        printf("\n%d: Not Found\n", 20);

    /*Medis = removeNode(Medis, 16);

    for(int i=5; i<10; i++){
        Medis = removeNode(Medis, i);
    }*/

    Medis->left = deleteTree(Medis->left);//blogai

    //nodeOutput(Medis, 0);

    Medis = balanceAfterDeletion(Medis);

    nodeOutput(Medis, 0);

    //nodeOutput_linear(Medis);

    printf("::: %d :::", getHeight(Medis->left));
    printf("::: %d :::", getHeight(Medis->right));


    return 0;
}
