class Solution {
public:
    string reverseWords(string s) {
        stringstream ss(s);
        vector<string> v;
        string w;
        
        while(ss>>w) v.push_back(w);
        reverse(v.begin(),v.end());
        
        string ans;
        for(string x:v)
            ans+=x+" ";
        
        ans.pop_back();
        return ans;
    }
};
