#ifndef ListNode_h
#define ListNode_h

#include "Arduino.h"

class ListNode {

public:
    ListNode(double val);
    double value;
    ListNode* next;
    void toString();

};

#endif
