#include <stdio.h>

int search(int* nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // If target is found, return its index
        if (nums[mid] == target) {
            return mid;
        }

        // Case 1: Check if the left half is sorted
        if (nums[left] <= nums[mid]) {
            // Check if the target lies within the sorted left half
            if (nums[left] <= target && target < nums[mid]) {
                right = mid - 1; // Narrow down to the left
            } else {
                left = mid + 1;  // Search the right half
            }
        } 
        // Case 2: The right half must be sorted
        else {
            // Check if the target lies within the sorted right half
            if (nums[mid] < target && target <= nums[right]) {
                left = mid + 1;  // Narrow down to the right
            } else {
                right = mid - 1; // Search the left half
            }
        }
    }

    // Target was not found in the array
    return -1;
}
