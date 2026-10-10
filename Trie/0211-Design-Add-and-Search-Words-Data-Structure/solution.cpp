class WordDictionary {
private:
    struct TrieNode {
        TrieNode* children[26];
        bool isEnd;

        TrieNode() {
            for (int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }
            isEnd = false;
        }
    };

    TrieNode* root;

    bool searchHelper(const string& word, int index, TrieNode* node) {
        if (index == word.size()) {
            return node->isEnd;
        }

        char ch = word[index];

        if (ch == '.') {
            for (int i = 0; i < 26; i++) {
                if (node->children[i] &&
                    searchHelper(word, index + 1, node->children[i])) {
                    return true;
                }
            }
            return false;
        }

        int pos = ch - 'a';

        if (!node->children[pos]) {
            return false;
        }

        return searchHelper(word, index + 1, node->children[pos]);
    }

public:
    WordDictionary() {
        root = new TrieNode();
    }

    void addWord(string word) {
        TrieNode* node = root;

        for (char ch : word) {
            int index = ch - 'a';

            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }

            node = node->children[index];
        }

        node->isEnd = true;
    }

    bool search(string word) {
        return searchHelper(word, 0, root);
    }
};

