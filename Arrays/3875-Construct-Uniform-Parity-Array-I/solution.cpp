class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        bool odd=false, even=false;

        for(int x:nums1){
            odd |= x&1;
            even |= !(x&1);
        }

        return true;
    }
};
