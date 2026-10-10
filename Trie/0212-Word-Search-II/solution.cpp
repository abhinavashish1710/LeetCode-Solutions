
class Solution {
private:
    struct TrieNode {
        TrieNode* children[26]{};
        string word = "";
    };

    TrieNode* root = new TrieNode();

    void insert(const string& word) {
        TrieNode* node = root;

        for (char ch : word) {
            int idx = ch - 'a';

            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
            }

            node = node->children[idx];
        }

        node->word = word;
    }

    void dfs(vector<vector<char>>& board, int r, int c,
             TrieNode* node, vector<string>& result) {
        char ch = board[r][c];

        if (ch == '#') return;

        TrieNode* next = node->children[ch - 'a'];
        if (!next) return;

        if (!next->word.empty()) {
            result.push_back(next->word);
            next->word = "";  // Avoid duplicate results
        }

        board[r][c] = '#';  // Mark cell as visited

        int rows = board.size();
        int cols = board[0].size();

        if (r > 0) dfs(board, r - 1, c, next, result);
        if (r + 1 < rows) dfs(board, r + 1, c, next, result);
        if (c > 0) dfs(board, r, c - 1, next, result);
        if (c + 1 < cols) dfs(board, r, c + 1, next, result);

        board[r][c] = ch;  // Restore cell

        // Remove exhausted Trie branches to speed up future searches
        if (next->word.empty()) {
            bool hasChild = false;

            for (TrieNode* child : next->children) {
                if (child) {
                    hasChild = true;
                    break;
                }
            }

            if (!hasChild) {
                node->children[ch - 'a'] = nullptr;
                delete next;
            }
        }
    }

public:
    vector<string> findWords(vector<vector<char>>& board,
                              vector<string>& words) {
        for (const string& word : words) {
            insert(word);
        }

        vector<string> result;
        int rows = board.size();
        int cols = board[0].size();

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                dfs(board, r, c, root, result);
            }
        }

        return result;
    }
};
