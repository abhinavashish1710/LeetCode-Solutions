class Solution {
public:
    unordered_set<string> st;
    unordered_map<int,vector<string>> dp;
    string s;

    vector<string> dfs(int i) {
        if(i==s.size()) return {""};
        if(dp.count(i)) return dp[i];

        vector<string> res;
        for(int j=i+1;j<=s.size();j++) {
            string w=s.substr(i,j-i);
            if(!st.count(w)) continue;
            for(string x:dfs(j))
                res.push_back(w+(x.empty()?"":" "+x));
        }
        return dp[i]=res;
    }

    vector<string> wordBreak(string str, vector<string>& wordDict) {
        s=str;
        st.insert(wordDict.begin(),wordDict.end());
        return dfs(0);
    }
};
