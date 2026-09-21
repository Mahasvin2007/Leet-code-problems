#include <stdio.h>
#include <stdlib.h>

// Helper function to find the first (leftmost) occurrence of the target
int findFirst(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1;
    int firstIdx = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            firstIdx = mid;      // Record candidate index
            right = mid - 1;     // Keep searching left to find the first occurrence
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return firstIdx;
}

// Helper function to find the last (rightmost) occurrence of the target
int findLast(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1;
    int lastIdx = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            lastIdx = mid;       // Record candidate index
            left = mid + 1;      // Keep searching right to find the last occurrence
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return lastIdx;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* result = (int*)malloc(2 * sizeof(int));
    
    // Find the starting and ending positions using the helper functions
    result[0] = findFirst(nums, numsSize, target);
    result[1] = findLast(nums, numsSize, target);
    
    return result;
}
