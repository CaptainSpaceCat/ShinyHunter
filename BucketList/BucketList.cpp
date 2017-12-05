#include "Arduino.h"
#include "BucketList.h"

BucketList::BucketList(int cap = 10, double range = 1.4) {
    front = nullptr;
    bucketCapacity = cap;
    triggerRange = range;
}

BucketList::~BucketList() {
    clearData();
}


void BucketList::clearData() {
    Bucket* temp = front;
    while (temp != nullptr) {
        temp = temp->next;
        delete front;
        front = temp;
    }
}

bool BucketList::add(double val) {
    if (front == nullptr) {
        Bucket* newBucket = new Bucket(bucketCapacity);
        newBucket->add(val);
        front = newBucket;
    } else if (front->next == nullptr) {
        int choice = compareToBucket(val, front);
        if (choice == -1) {
                Bucket* newBucket = new Bucket(bucketCapacity);
                newBucket->add(val);
                newBucket->next = front;
                front = newBucket;
        } else if (choice == 0) {
                front->add(val);
        } else if (choice == 1) {
                Bucket* newBucket = new Bucket(bucketCapacity);
                newBucket->add(val);
                front->next = newBucket;
        } else {
            return true;
        }
    } else {
        Bucket* temp = front;
        while (true) {
            int choice = compareToBucket(val, temp->next);
            if (choice == -1) {
                    Bucket* newBucket = new Bucket(bucketCapacity);
                    newBucket->add(val);
                    newBucket->next = temp->next;
                    temp->next = newBucket;
                    break;
            } else if (choice == 0) {
                    temp->next->add(val);
                    break;
            } else if (choice == 1) {
                    temp = temp->next;
                    if (temp->next == nullptr) {
                        Bucket* newBucket = new Bucket(bucketCapacity);
                        newBucket->add(val);
                        temp->next = newBucket;
                        break;
                    }
            } else {
                return true;
            }
        }
    }
    return false;
}

int BucketList::compareToBucket(double val, Bucket* bucket) {
    double avg = bucket->average();
    if (abs(val - avg) < .1) {
        return 0;
    }
    if (val < avg) {
        return -1;
    } else if (abs(val - avg - triggerRange) < .1) {
        return 2;
    } else {
        return 1;
    }
}

void BucketList::toString() {
    Bucket* temp = front;
    Serial.print("{");
    if (temp != nullptr) {
        Serial.print(" "); temp->toString();
        temp = temp->next;
    }
    while (temp != nullptr) {
        Serial.println();
        Serial.print("  "); temp->toString();
        temp = temp->next;
    }
    Serial.println(" }\n");
}
