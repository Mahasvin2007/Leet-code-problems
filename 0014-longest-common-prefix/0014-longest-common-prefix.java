class Solution {
    public String longestCommonPrefix(String[] strs) {
        if (strs==null||strs.length==0){
            return "";
        }
        Arrays.sort(strs);
        String first=strs[0];
        String last =strs[strs.length-1];
        int index =0;
        while (index < first.length() && index < last.length()){
             if (first.charAt(index) == last.charAt(index)) {
                index++;
            }else{
                break;
            }
        }
        return first.substring(0,index);
        
    }
}