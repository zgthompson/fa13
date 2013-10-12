//************************  intSLList.cpp  **************************

#include <iostream>
#include <iomanip>
#include "intSLList.h"

IntSLList::~IntSLList() {
    for (IntSLLNode *p; !isEmpty(); ) {
        p = head->next;
        delete head;
        head = p;
    }
}

void IntSLList::addToHead(int el) {
    head = new IntSLLNode(el,head);
    if (tail == 0)
       tail = head;
}

void IntSLList::addToTail(int el) {
    if (tail != 0) {      // if list not empty;
         tail->next = new IntSLLNode(el);
         tail = tail->next;
    }
    else head = tail = new IntSLLNode(el);
}

int IntSLList::deleteFromHead() {
    int el = head->info;
    IntSLLNode *tmp = head;
    if (head == tail)     // if only one node on the list;
         head = tail = 0;
    else head = head->next;
    delete tmp;
    return el;
}

int IntSLList::deleteFromTail() {
    int el = tail->info;
    if (head == tail) {   // if only one node on the list;
         delete head;
         head = tail = 0;
    }
    else {                // if more than one node in the list,
         IntSLLNode *tmp; // find the predecessor of tail;
         for (tmp = head; tmp->next != tail; tmp = tmp->next);
         delete tail;
         tail = tmp;      // the predecessor of tail becomes tail;
         tail->next = 0;
    }
    return el;
}

void IntSLList::deleteNode(int el) {
    if (head != 0)                     // if non-empty list;
         if (head == tail && el == head->info) { // if only one
              delete head;                       // node on the list;
              head = tail = 0;
         }
         else if (el == head->info) {  // if more than one node on the list
              IntSLLNode *tmp = head;
              head = head->next;
              delete tmp;              // and old head is deleted;
         }
         else {                        // if more than one node in the list
              IntSLLNode *pred, *tmp;
              for (pred = head, tmp = head->next; // and a non-head node
                   tmp != 0 && !(tmp->info == el);// is deleted;
                   pred = pred->next, tmp = tmp->next);
              if (tmp != 0) {
                   pred->next = tmp->next;
                   if (tmp == tail)
                      tail = pred;
                   delete tmp;
              }
         }
}

bool IntSLList::isInList(int el) const {
    IntSLLNode *tmp;
    for (tmp = head; tmp != 0 && !(tmp->info == el); tmp = tmp->next);
    return tmp != 0;
}

void IntSLList::printAll() const {
    for (IntSLLNode *tmp = head; tmp != 0; tmp = tmp->next)
        std::cout << tmp->info << " ";
    std::cout << std::endl;
}

IntSLList* IntSLList::reverse() const {
    // Output: a new list that is a reversal of this list
    // Precondition: none
    // Sample: 10 8 7 -> 7 8 10

    IntSLList* reverseList = new IntSLList();
    for (IntSLLNode* curNode = head; curNode != NULL; curNode = curNode -> next) {
        reverseList -> addToHead(curNode -> info);
    }

    return reverseList;
}

void IntSLList::printList() const {
    // Output: Prints the list as an integer
    // Precondition: Head of list contains least significant digit
    // Sample: 34567 56 3 -> 30005634567

    IntSLList* numList = reverse();
    IntSLLNode* curNode = numList -> getHead();

    if (curNode == NULL) {
        std::cout << 0 << std::endl;
        return;
    }

    std::cout << curNode -> info;

    curNode = curNode -> next;

    while (curNode != NULL) {
        std::cout << std::setw(5) << std::setfill('0') << curNode -> info;
        curNode = curNode -> next;
    }
}


IntSLLNode* IntSLList::getHead() const {
    // Output: returns the head of this list
    // Precondition: none

    return head;
}

IntSLList* IntSLList::add(const IntSLList* arg1) const {
    // Output: Creates a new list that is the addition of this list with arg1
    // Precondition: arg1 and this list are positive
    // Sample: 11111 1 + 11111 1 -> 22222 2

    IntSLList* resultList = new IntSLList();
    IntSLLNode *node1 = head, *node2 = arg1 -> getHead();
    int carry = 0, val1, val2, curVal;

    while (node1 != NULL || node2 != NULL) {
        val1 = val2 = 0;

        if (node1 != NULL) {
            val1 = node1 -> info;
            node1 = node1 -> next;
        }

        if (node2 != NULL) {
            val2 = node2 -> info;
            node2 = node2 -> next;
        }

        curVal = val1 + val2 + carry;

        resultList -> addToTail(curVal % 100000);
        carry = curVal / 100000;
    }

    if (carry != 0) {
        resultList -> addToTail(carry);
    }

    return resultList;
}

IntSLList* IntSLList::smult(int k) const {
    // Output: Creates a new list that is this list multiplied by k
    // Precondition: k is positive
    // Sample -> 11111 1 * 5 -> 55555 5

    IntSLList* resultList = new IntSLList();
    int carry = 0, curVal;

    for (IntSLLNode* curNode = head; curNode != NULL; curNode = curNode -> next) {
        curVal = (curNode -> info) * k + carry;
        resultList -> addToTail(curVal % 100000);
        carry = curVal / 100000;
    }

    if (carry != 0) {
        resultList -> addToTail(carry);
    }

    return resultList;
}


IntSLList* IntSLList::factorial(int n) const {
    // Output: Creates a new list that is n factorial
    // Precondition: n is positive and nonzero
    // Sample -> factorial(5) -> 120

    IntSLList *resultList = new IntSLList(), *tempList;
    resultList -> addToHead(1);
    for (int i = n; i > 1; i--) {
        tempList = resultList;
        resultList = resultList -> smult(i);
        delete tempList;
    }
    return resultList;
}

IntSLList* IntSLList::exponent(int a, int b) const {
    // Output: Creates a new list that is a^b
    // Precondition: a and b are positive and nonzero
    // Sample -> exponent(5, 2) -> 25

    IntSLList *resultList =  new IntSLList(), *tempList;
    resultList -> addToHead(1);
    for (int i = 0; i < b; i++) {
        tempList = resultList;
        resultList = resultList -> smult(a);
        delete tempList;
    }
    return resultList;
}
