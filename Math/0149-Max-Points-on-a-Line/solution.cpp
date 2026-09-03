class Solution {
public:
    int maxPoints(vector<vector<int>>& p) {
        int n=p.size(),ans=1;
        for(int i=0;i<n;i++){
            unordered_map<string,int> mp;
            for(int j=i+1;j<n;j++){
                int dx=p[j][0]-p[i][0];
                int dy=p[j][1]-p[i][1];
                int g=gcd(abs(dx),abs(dy));
                dx/=g;
                dy/=g;
                if(dx<0) dx=-dx,dy=-dy;
                if(dx==0) dy=1;
                if(dy==0) dx=1;
                string s=to_string(dx)+","+to_string(dy);
                ans=max(ans,++mp[s]+1);
            }
        }
        return ans;
    }
};
