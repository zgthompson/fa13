//************************  intSLList.h  **************************
//           singly-linked list class to store integers

#ifndef INT_LINKED_LIST
#define INT_LINKED_LIST

class IntSLLNode {
public:
    IntSLLNode() {
        next = 0;
    }
    IntSLLNode(int el, IntSLLNode *ptr = 0) {
        info = el; next = ptr;
    }
    int info;
    IntSLLNode *next;
};

class IntSLList {
public:
    IntSLList() {
        head = tail = 0;
    }
    ~IntSLList();
    int isEmpty() {
        return head == 0;
    }
    void addToHead(int);
    void addToTail(int);
    int  deleteFromHead(); // delete the head and return its info;
    int  deleteFromTail(); // delete the tail and return its info;
    void deleteNode(int);
    bool isInList(int) const;
    void printAll() const;
    IntSLList* reverse() const;
    void printList() const;
    IntSLLNode* getHead() const;
    IntSLList* add(const IntSLList* arg1) const;
    IntSLList* smult(int k) const;
    IntSLList* factorial(int n) const;
    IntSLList* exponent(int a, int b) const;
private:
    IntSLLNode *head, *tail;
};

#endif
