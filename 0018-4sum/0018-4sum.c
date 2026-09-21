#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    int val1 = *(const int *)a;
    int val2 = *(const int *)b;
    if (val1 < val2) return -1;
    if (val1 > val2) return 1;
    return 0;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned arrays and *returnColumnSizes array must be malloced, assume caller calls free().
 */
int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    
    // A quadruplet requires at least 4 elements
    if (numsSize < 4) {
        *returnColumnSizes = NULL;
        return NULL;
    }

    // Step 1: Sort the array
    qsort(nums, numsSize, sizeof(int), compare);

    // Initial allocation for the result array
    int capacity = 16;
    int** result = (int**)malloc(capacity * sizeof(int*));
    *returnColumnSizes = (int*)malloc(capacity * sizeof(int));

    // Step 2: Fix the first element
    for (int i = 0; i < numsSize - 3; i++) {
        // Skip duplicate values for the first element
        if (i > 0 && nums[i] == nums[i - 1]) continue;

        // Step 3: Fix the second element
        for (int j = i + 1; j < numsSize - 2; j++) {
            // Skip duplicate values for the second element
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;

            // Step 4: Two-pointer approach for the remaining two elements
            int left = j + 1;
            int right = numsSize - 1;

            while (left < right) {
                // Use long long to prevent integer overflow during addition
                long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];

                if (sum == target) {
                    // Resize results array if capacity is reached
                    if (*returnSize >= capacity) {
                        capacity *= 2;
                        result = (int**)realloc(result, capacity * sizeof(int*));
                        *returnColumnSizes = (int*)realloc(*returnColumnSizes, capacity * sizeof(int));
                    }

                    // Allocate memory for the current quadruplet
                    result[*returnSize] = (int*)malloc(4 * sizeof(int));
                    result[*returnSize][0] = nums[i];
                    result[*returnSize][1] = nums[j];
                    result[*returnSize][2] = nums[left];
                    result[*returnSize][3] = nums[right];
                    (*returnColumnSizes)[*returnSize] = 4;
                    (*returnSize)++;

                    // Skip duplicate values for the third element
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    // Skip duplicate values for the fourth element
                    while (left < right && nums[right] == nums[right - 1]) right--;

                    // Move pointers inward after finding a valid match
                    left++;
                    right--;
                } else if (sum < target) {
                    left++; // Sum is too small, move left pointer rightward
                } else {
                    right--; // Sum is too large, move right pointer leftward
                }
            }
        }
    }

    return result;
}
