
class Solution {
public:
    int digitSum(int n) {
        int sum = 0;
        while (n) {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    }

    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int>> arr;

        for (int x : nums) {
            arr.push_back({x, digitSum(x)});
        }

        sort(arr.begin(), arr.end(), [](auto& a, auto& b) {
            if (a.second != b.second)
                return a.second < b.second;
            return a.first < b.first;
        });

        unordered_map<int, int> pos;
        for (int i = 0; i < n; i++) {
            pos[arr[i].first] = i;
        }

        vector<bool> visited(n, false);
        int swaps = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i] || pos[nums[i]] == i)
                continue;

            int j = i;
            int cycle = 0;

            while (!visited[j]) {
                visited[j] = true;
                j = pos[nums[j]];
                cycle++;
            }

            swaps += cycle - 1;
        }

        return swaps;
    }
};
