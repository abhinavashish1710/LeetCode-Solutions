class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int x = 0, n = nums.size();
        
        for (int a : nums) x ^= a;
        
        if (x) return n;
        
        for (int a : nums)
            if (a) return n - 1;
        
        return 0;
    }
};
