#include "Arduino.h"
#include "BucketList.h"

/* constructor, creates a new linked list of buckets, stored in ascending order
 * accepts an integer defining the maximum capacity for all of its buckets
 * and a double defining how long the shiny animation takes for detection purposes
 * initializes the list to have 0 buckets
 */
BucketList::BucketList(int cap = 10, double range = 1.4) {
    front = nullptr;
    bucketCapacity = cap;
    triggerRange = range;
}

/* destructor, deletes all of the buckets and all of their data
 */
BucketList::~BucketList() {
    clearData();
}

/* clears all of the data used by this object and frees up any used memory
 */
void BucketList::clearData() {
    Bucket* temp = front;
    while (temp != nullptr) {
        temp = temp->next;
        delete front;
        front = temp;
    }
}

/* this function accepts a double representing a DS screen measurement, and tries to add it to one of the buckets
 * if a bucket contains an average value close to this new value, this value will be added to that bucket,
 * otherwise a new bucket will be created for it
 * if this value is within the triggerRange margin, the function assumes the measurement came from a shiny pokemon and returns true
 * otherwise, it returns false
 */
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

/* this function accepts a DS screen measurement, and a bucket to compare the measurement to
 * if the measurement is smaller than the bucket, returns -1
 * if the measurement falls within this bucket, returns 0
 * if the measurement is above the size of this bucket, returns 1
 * if the measurement is within the triggering range, it's likely a shiny, and the function returns 2
 */
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

/* prints the bucketlist to Arduino's Serial monitor
 * I would've made this return a string but C strings are disgusting abominiations
 */
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
