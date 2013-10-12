//************************  intSLList.h  **************************
//           singly-linked list class to store integers

#ifndef INT_LINKED_LIST
#define INT_LINKED_LIST

class IntSLLNode {
public:
    IntSLLNode() {
        next = 0;
    }
    IntSLLNode(long long el, IntSLLNode *ptr = 0) {
        info = el; next = ptr;
    }
    long long info;
    IntSLLNode *next;
};

class IntSLList {
public:
    IntSLList() {
        head = tail = 0;
    }
    IntSLList(IntSLLNode* node);
    ~IntSLList();
    int isEmpty() {
        return head == 0;
    }
    void addToHead(long long);
    void addToTail(long long);
    long long deleteFromHead(); // delete the head and return its info;
    long long deleteFromTail(); // delete the tail and return its info;
    void deleteNode(long long);
    bool isInList(long long) const;
    void printAll() const;
    IntSLList* reverse() const;
    void printList() const;
    IntSLLNode* getHead() const;
    IntSLList* newCopy() const;
    IntSLList* add(const IntSLList* arg1) const;
    IntSLList* smult(long long k) const;
    IntSLList* mult(const IntSLList* multList) const;
    static IntSLList* factorial(long long n);
    static IntSLList* exponent(long long a, long long b);
    static IntSLList* exp(IntSLList* x, long long n);
private:
    IntSLLNode *head, *tail;
};

#endif