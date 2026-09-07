class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n=nums.size();
        if(n<2) return 0;

        int mn=*min_element(nums.begin(),nums.end());
        int mx=*max_element(nums.begin(),nums.end());
        if(mn==mx) return 0;

        long long size=max(1LL,(long long)(mx-mn+n-2)/(n-1));
        int cnt=(mx-mn)/size+1;

        vector<long long> lo(cnt,LLONG_MAX),hi(cnt,LLONG_MIN);

        for(int x:nums){
            int i=(x-mn)/size;
            lo[i]=min(lo[i],(long long)x);
            hi[i]=max(hi[i],(long long)x);
        }

        long long ans=0,prev=mn;

        for(int i=0;i<cnt;i++){
            if(lo[i]==LLONG_MAX) continue;
            ans=max(ans,lo[i]-prev);
            prev=hi[i];
        }

        return ans;
    }
};
