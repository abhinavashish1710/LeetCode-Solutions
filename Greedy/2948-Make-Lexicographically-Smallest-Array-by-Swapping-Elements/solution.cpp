class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        // Store {value, original index}
        vector<pair<int, int>> arr;

        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }

        sort(arr.begin(), arr.end());

        int start = 0;

        while (start < n) {
            int end = start;

            // Find all values connected by valid swaps
            while (end + 1 < n &&
                   arr[end + 1].first - arr[end].first <= limit) {
                end++;
            }

            // Collect original indices of this group
            vector<int> indices;

            for (int i = start; i <= end; i++) {
                indices.push_back(arr[i].second);
            }

            // Smallest values should go to smallest indices
            sort(indices.begin(), indices.end());

            int k = 0;

            for (int i = start; i <= end; i++) {
                nums[indices[k++]] = arr[i].first;
            }

            start = end + 1;
        }

        return nums;
    }
};
