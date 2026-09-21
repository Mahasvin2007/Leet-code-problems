#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Hash table node for bucket storage
typedef struct {
    long long bucketId;
    long long value;
    bool isOccupied;
} HashNode;

// Simple hash function for the open-addressed table
int hashFunc(long long bucketId, int capacity) {
    int h = bucketId % capacity;
    if (h < 0) h += capacity;
    return h;
}

// Insert or update a bucket in the hash table
void insertBucket(HashNode* hashTable, int capacity, long long bucketId, long long value) {
    int idx = hashFunc(bucketId, capacity);
    while (hashTable[idx].isOccupied) {
        if (hashTable[idx].bucketId == bucketId) {
            hashTable[idx].value = value;
            return;
        }
        idx = (idx + 1) % capacity;
    }
    hashTable[idx].bucketId = bucketId;
    hashTable[idx].value = value;
    hashTable[idx].isOccupied = true;
}

// Search for a bucket value in the hash table
bool getBucketValue(HashNode* hashTable, int capacity, long long bucketId, long long* outValue) {
    int idx = hashFunc(bucketId, capacity);
    int startIdx = idx;
    while (hashTable[idx].isOccupied) {
        if (hashTable[idx].bucketId == bucketId) {
            *outValue = hashTable[idx].value;
            return true;
        }
        idx = (idx + 1) % capacity;
        if (idx == startIdx) break;
    }
    return false;
}

// Remove a bucket from the hash table using standard linear probing deletion
void removeBucket(HashNode* hashTable, int capacity, long long bucketId) {
    int idx = hashFunc(bucketId, capacity);
    while (hashTable[idx].isOccupied) {
        if (hashTable[idx].bucketId == bucketId) {
            hashTable[idx].isOccupied = false;
            
            // Rehash cluster elements to maintain linear probing integrity
            int nextIdx = (idx + 1) % capacity;
            while (hashTable[nextIdx].isOccupied) {
                long long rehashId = hashTable[nextIdx].bucketId;
                long long rehashVal = hashTable[nextIdx].value;
                hashTable[nextIdx].isOccupied = false;
                insertBucket(hashTable, capacity, rehashId, rehashVal);
                nextIdx = (nextIdx + 1) % capacity;
            }
            return;
        }
        idx = (idx + 1) % capacity;
    }
}

// Helper to calculate mapped bucket ID avoiding C integer division issues with negatives
long long getBucketId(long long val, long long w) {
    return val < 0 ? (val + 1) / w - 1 : val / w;
}

bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int indexDiff, int valueDiff) {
    if (numsSize < 2 || indexDiff < 1 || valueDiff < 0) return false;

    // Use a hash table capacity scaled roughly to twice the sliding window size
    int capacity = (indexDiff < numsSize ? indexDiff : numsSize) * 2 + 7;
    HashNode* hashTable = (HashNode*)calloc(capacity, sizeof(HashNode));

    long long w = (long long)valueDiff + 1;

    for (int i = 0; i < numsSize; i++) {
        long long val = nums[i];
        long long bucketId = getBucketId(val, w);
        long long checkVal;

        // Condition 1: Same bucket check
        if (getBucketValue(hashTable, capacity, bucketId, &checkVal)) {
            free(hashTable);
            return true;
        }

        // Condition 2: Left adjacent bucket check
        if (getBucketValue(hashTable, capacity, bucketId - 1, &checkVal) && llabs(val - checkVal) <= valueDiff) {
            free(hashTable);
            return true;
        }

        // Condition 3: Right adjacent bucket check
        if (getBucketValue(hashTable, capacity, bucketId + 1, &checkVal) && llabs(val - checkVal) <= valueDiff) {
            free(hashTable);
            return true;
        }

        // Insert current number into hash table map
        insertBucket(hashTable, capacity, bucketId, val);

        // Evict elements outside the sliding window boundary
        if (i >= indexDiff) {
            long long oldVal = nums[i - indexDiff];
            long long oldBucketId = getBucketId(oldVal, w);
            removeBucket(hashTable, capacity, oldBucketId);
        }
    }

    free(hashTable);
    return false;
}
