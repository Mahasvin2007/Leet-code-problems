#include <limits.h>

double findMedianSortedArrays(int* nums1, int m, int* nums2, int n) {
    // Ensure nums1 is the smaller array
    if (m > n) {
        return findMedianSortedArrays(nums2, n, nums1, m);
    }

    int left = 0, right = m;

    while (left <= right) {
        int partitionX = (left + right) / 2;
        int partitionY = (m + n + 1) / 2 - partitionX;

        int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int minRightX = (partitionX == m) ? INT_MAX : nums1[partitionX];

        int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minRightY = (partitionY == n) ? INT_MAX : nums2[partitionY];

        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {

            // Even total length
            if ((m + n) % 2 == 0) {
                int leftMax = (maxLeftX > maxLeftY) ? maxLeftX : maxLeftY;
                int rightMin = (minRightX < minRightY) ? minRightX : minRightY;

                return (leftMax + rightMin) / 2.0;
            }

            // Odd total length
            return (maxLeftX > maxLeftY) ? maxLeftX : maxLeftY;

        } else if (maxLeftX > minRightY) {
            right = partitionX - 1;
        } else {
            left = partitionX + 1;
        }
    }

    return 0.0; // Should never reach here for valid input
}