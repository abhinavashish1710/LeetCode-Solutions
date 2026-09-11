class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        vector<int> freq(10, 0);

        for(int x : digits)
            freq[x]++;

        int ans = 0;

        for(int num = 100; num <= 999; num++) {
            if(num % 2 != 0)
                continue;

            int x = num;
            vector<int> need(10, 0);

            for(int i = 0; i < 3; i++) {
                need[x % 10]++;
                x /= 10;
            }

            bool ok = true;

            for(int d = 0; d <= 9; d++) {
                if(need[d] > freq[d]) {
                    ok = false;
                    break;
                }
            }

            if(ok)
                ans++;
        }

        return ans;
    }
};
