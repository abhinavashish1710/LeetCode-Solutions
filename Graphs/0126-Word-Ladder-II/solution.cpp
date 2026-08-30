#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
    unordered_map<string, int> mpp; // Stores the level/distance of each word from beginWord
    vector<vector<string>> ans;
    string bWord;

    void dfs(string word, vector<string>& seq) {
        if (word == bWord) {
            vector<string> reverseSeq = seq;
            reverse(reverseSeq.begin(), reverseSeq.end());
            ans.push_back(reverseSeq);
            return;
        }

        int steps = mpp[word];
        int sz = word.size();

        // Try changing each character to find parent words at level (steps - 1)
        for (int i = 0; i < sz; i++) {
            char original = word[i];
            for (char ch = 'a'; ch <= 'z'; ch++) {
                word[i] = ch;
                if (mpp.find(word) != mpp.end() && mpp[word] == steps - 1) {
                    seq.push_back(word);
                    dfs(word, seq);
                    seq.pop_back(); // Backtrack
                }
            }
            word[i] = original;
        }
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> st(wordList.begin(), wordList.end());
        
        if (st.find(endWord) == st.end()) return {};

        bWord = beginWord;
        queue<string> q;
        q.push(beginWord);
        mpp[beginWord] = 1;
        st.erase(beginWord);

        int sz = beginWord.size();

        // Step 1: BFS to find the shortest level/distance of each reachable word
        while (!q.empty()) {
            string word = q.front();
            q.pop();

            int steps = mpp[word];

            if (word == endWord) break;

            for (int i = 0; i < sz; i++) {
                char original = word[i];
                for (char ch = 'a'; ch <= 'z'; ch++) {
                    word[i] = ch;
                    if (st.find(word) != st.end()) {
                        q.push(word);
                        st.erase(word); // Prevent visiting again in deeper levels
                        mpp[word] = steps + 1;
                    }
                }
                word[i] = original;
            }
        }

        // Step 2: DFS from endWord back to beginWord to collect all paths
        if (mpp.find(endWord) != mpp.end()) {
            vector<string> seq;
            seq.push_back(endWord);
            dfs(endWord, seq);
        }

        return ans;
    }
};
