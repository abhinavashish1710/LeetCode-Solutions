class Solution {
public:
    long long countCommas(long long n) {
        long long totalCommas = 0;
        
        for (long long threshold = 1000; threshold <= n; threshold *= 1000) {
            totalCommas += (n - threshold + 1);
        }
        
        return totalCommas;
    }
};
