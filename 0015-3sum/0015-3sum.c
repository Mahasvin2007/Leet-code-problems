#include <stdlib.h>

int compare(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int** threeSum(int* nums, int numsSize, int* returnSize,
               int** returnColumnSizes) {

    *returnSize = 0;

    qsort(nums, numsSize, sizeof(int), compare);

    int capacity = 1024;

    int **result = malloc(capacity * sizeof(int *));
    *returnColumnSizes = malloc(capacity * sizeof(int));

    for (int i = 0; i < numsSize - 2; i++) {

        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int left = i + 1;
        int right = numsSize - 1;

        while (left < right) {

            long sum = (long)nums[i] +
                       (long)nums[left] +
                       (long)nums[right];

            if (sum == 0) {

                if (*returnSize >= capacity) {
                    capacity *= 2;

                    result = realloc(result,
                                     capacity * sizeof(int *));
                    *returnColumnSizes =
                        realloc(*returnColumnSizes,
                                capacity * sizeof(int));
                }

                result[*returnSize] = malloc(3 * sizeof(int));

                result[*returnSize][0] = nums[i];
                result[*returnSize][1] = nums[left];
                result[*returnSize][2] = nums[right];

                (*returnColumnSizes)[*returnSize] = 3;
                (*returnSize)++;

                while (left < right &&
                       nums[left] == nums[left + 1])
                    left++;

                while (left < right &&
                       nums[right] == nums[right - 1])
                    right--;

                left++;
                right--;
            }
            else if (sum < 0) {
                left++;
            }
            else {
                right--;
            }
        }
    }

    return result;
}