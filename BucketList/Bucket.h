#ifndef Bucket_h
#define Bucket_h

#include "Arduino.h"
#include "ListNode.h"

class Bucket {

public:
    Bucket(int c);
    ~Bucket();
    ListNode* front;
    Bucket* next;
    int size;
    int capacity;

    double average();
    void add(double val);

    void toString();
    void clearData();

};

#endif
