class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if(numerator==0) return "0";

        long long a=numerator,b=denominator;
        string ans;

        if((a<0)^(b<0)) ans+="-";
        a=abs(a);
        b=abs(b);

        ans+=to_string(a/b);
        a%=b;

        if(!a) return ans;
        ans+=".";

        unordered_map<long long,int> mp;

        while(a){
            if(mp.count(a)){
                ans.insert(mp[a],"(");
                ans+=")";
                break;
            }

            mp[a]=ans.size();
            a*=10;
            ans+=to_string(a/b);
            a%=b;
        }

        return ans;
    }
};
