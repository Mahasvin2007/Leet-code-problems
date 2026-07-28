class Solution {
    public String smallestPalindrome(String s) {
        int[] count = new int[26];
        for (char c : s.toCharArray()) {
            count[c - 'a']++;
        }
        StringBuilder leftHalf = new StringBuilder();
        char middleChar = 0;
        for (int i = 0; i < 26; i++) {
            if (count[i] > 0) {
                if (count[i] % 2 != 0) {
                    middleChar = (char) ('a' + i);
                }
                for (int j = 0; j < count[i] / 2; j++) {
                    leftHalf.append((char) ('a' + i));
                }
            }
        }
        
        StringBuilder result = new StringBuilder(leftHalf);
        
        if (middleChar != 0) {
            result.append(middleChar);
        }
        
        result.append(new StringBuilder(leftHalf).reverse());
        
        return result.toString();
    }
}