class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int a=0,b=0;
        for(int n:nums){
            a=(a^n)&~b;
            b=(b^n)&~a;
        }
        return a;
    }
};
