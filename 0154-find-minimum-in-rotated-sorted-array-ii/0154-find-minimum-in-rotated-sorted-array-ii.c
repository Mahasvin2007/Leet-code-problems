#include <stdio.h>

int findMin(int* nums, int numsSize) {
    int left = 0;
    int right = numsSize - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] < nums[right]) {
            // The minimum element is in the left half, including mid
            right = mid;
        } else if (nums[mid] > nums[right]) {
            // The minimum element is strictly to the right of mid
            left = mid + 1;
        } else {
            // Ambiguity due to duplicate elements; safely shrink the window
            right--;
        }
    }

    // When left == right, we have converged on the minimum element
    return nums[left];
}
