class Solution {
public:
    Node* connect(Node* root) {
        if (root == NULL) {
            return root;
        }

        Node* leftmost = root;

        while (leftmost->left != NULL) {
            Node* current = leftmost;

            while (current != NULL) {
                // Connect left child to right child
                current->left->next = current->right;

                // Connect right child to next node's left child
                if (current->next != NULL) {
                    current->right->next = current->next->left;
                }

                current = current->next;
            }

            leftmost = leftmost->left;
        }

        return root;
    }
};
