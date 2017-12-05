#include "Arduino.h"
#include "ListNode.h"

ListNode::ListNode(double val = 0) {
    value = val;
    next = nullptr;
}

void ListNode::toString() {
    Serial.print(value);
}
