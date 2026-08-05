class Solution {
public:
    int ans = 0;
    vector<int> col, diag1, diag2;

    void solve(int row, int n) {
        if (row == n) {
            ans++;
            return;
        }

        for (int c = 0; c < n; c++) {
            if (col[c] || diag1[row + c] || diag2[row - c + n - 1])
                continue;

            col[c] = diag1[row + c] = diag2[row - c + n - 1] = 1;

            solve(row + 1, n);

            col[c] = diag1[row + c] = diag2[row - c + n - 1] = 0;
        }
    }

    int totalNQueens(int n) {
        col = vector<int>(n, 0);
        diag1 = vector<int>(2 * n - 1, 0);
        diag2 = vector<int>(2 * n - 1, 0);

        solve(0, n);
        return ans;
    }
};
