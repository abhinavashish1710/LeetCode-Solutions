class Solution {
public:
    Node* connect(Node* root) {
        Node* current = root;

        while (current != NULL) {
            Node* nextLevelStart = NULL;
            Node* prev = NULL;

            while (current != NULL) {
                if (current->left != NULL) {
                    if (prev != NULL) {
                        prev->next = current->left;
                    } else {
                        nextLevelStart = current->left;
                    }
                    prev = current->left;
                }

                if (current->right != NULL) {
                    if (prev != NULL) {
                        prev->next = current->right;
                    } else {
                        nextLevelStart = current->right;
                    }
                    prev = current->right;
                }

                current = current->next;
            }

            current = nextLevelStart;
        }

        return root;
    }
};
