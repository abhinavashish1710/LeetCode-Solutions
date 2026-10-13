class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        vector<long long> squares;

        for (int num : nums) {
            squares.push_back(1LL * num * num);
        }

        sort(squares.begin(), squares.end(), greater<long long>());

        int n = squares.size();
        long long ans = 0;

        // First ceil(n / 2) positions have positive signs.
        for (int i = 0; i < (n + 1) / 2; i++) {
            ans += squares[i];
        }

        // Remaining positions have negative signs.
        for (int i = (n + 1) / 2; i < n; i++) {
            ans -= squares[i];
        }

        return ans;
    }
};
