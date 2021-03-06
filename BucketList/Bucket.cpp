#include "Arduino.h"
#include "Bucket.h"

/* constructor, creates a new bucket of size 0 with a specified capacity
 * contains a pointer to the first node in the bucket, a pointer to the next bucket in the list,
 * a size listing the number of nodes currently in the bucket, and a capacity for the maximum
 * number of nodes allowed to be in this bucket
 */
Bucket::Bucket(int c) {
    front = nullptr;
    next = nullptr;
    size = 0;
    capacity = c;
}

/* destructor, deletes this bucket and all of its data
 */
Bucket::~Bucket() {
    clearData();
}

/* clears all of the data used by this object and frees up any used memory
 */
void Bucket::clearData() {
    ListNode* temp = front;
    while (temp != nullptr) {
        temp = temp->next;
        delete front;
        front = temp;
    }
}

/* add a new value to the bucket, accepts a double representing the value to add
 * if adding another value would overflow the capacity of the bucket, deletes the oldest value from the bucket
 * and then adds the new value
 */
void Bucket::add(double val) {
    ListNode* node = new ListNode(val);
    size++;
    if (front == nullptr) {
        front = node;
    } else {
        ListNode* temp = front;
        front = node;
        node->next = temp;
        if (size > capacity) {
            while (temp->next->next != nullptr) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
            size--;
        }
    }
}

/* calculates and returns the average of all the values in the bucket
 */
double Bucket::average() {
    double total = 0;
    ListNode* temp = front;
    while (temp != nullptr) {
        total += temp->value;
        temp = temp->next;
    }
    return total / size;
}

/* prints the bucket to Arduino's Serial monitor
 * I would've made this return a string but C strings are disgusting abominiations
 */
void Bucket::toString() {
    Serial.print("{");
    if (front != nullptr) {
        front->toString();
        ListNode* temp = front->next;
        while (temp != nullptr) {
            Serial.print(", ");
            temp->toString();
            temp = temp->next;
        }
    }
    Serial.print("}");
    if (front != nullptr) {
        Serial.print(" : ");
        Serial.print(average());
    }
}

