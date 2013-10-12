#include "intSLList.h"
#include <iostream>

IntSLLNode* delete_last(IntSLLNode* &myList) {
    if (myList == NULL) {
        return NULL;
    }
    else if (myList -> next == NULL) {
        IntSLLNode* tempNode = myList;
        myList = NULL;
        return tempNode;
    }
    else {
        delete_last(myList -> next);
    }
}

int main(void) {
    IntSLLNode* myList = new IntSLLNode(1, new IntSLLNode(2, new IntSLLNode(3)));
    for (IntSLLNode* tempNode = myList; tempNode != NULL; tempNode = tempNode -> next)
        std::cout << tempNode -> info << " ";
    std::cout << std::endl;

    IntSLLNode* deletedNode = delete_last(myList);
    std::cout << "Deleted node: " << deletedNode -> info << std::endl;

    for (IntSLLNode* tempNode = myList; tempNode != NULL; tempNode = tempNode -> next)
        std::cout << tempNode -> info << " ";
    std::cout << std::endl;
}
