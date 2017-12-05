#include "Arduino.h"
#include "ListNode.h"

/* constructor
 * this is a simple node object storing a double and a pointer to the next node
 */
ListNode::ListNode(double val = 0) {
    value = val;
    next = nullptr;
}

/* prints the bucket to Arduino's Serial monitor
 * I would've made this return a string but C strings are disgusting abominiations
 */
void ListNode::toString() {
    Serial.print(value);
}
