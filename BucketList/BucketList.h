#ifndef BucketList_h
#define BucketList_h

#include "Arduino.h"
#include "Bucket.h"

class BucketList {

public:
    BucketList(int cap, double range);
    ~BucketList();
    Bucket* front;

    bool add(double val);
    int compareToBucket(double val, Bucket* bucket);

    int bucketCapacity;
    double triggerRange;

    void toString();
    void clearData();
};

#endif
