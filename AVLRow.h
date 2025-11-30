#ifndef AVL_ROW_H
#define AVL_ROW_H

#include <algorithm>
#include <vector>
using namespace std;

struct AVLNode {
    int key; // Seat index
    int height;
    int size; // Subtree size
    AVLNode *left, *right;

    AVLNode(int k) : key(k), height(1), size(1), left(nullptr), right(nullptr) {}
};

class AVLRow {
private:
    AVLNode* root;
    int n;

    int height(AVLNode* N) {
        if (N == nullptr) return 0;
        return N->height;
    }

    int size(AVLNode* N) {
        if (N == nullptr) return 0;
        return N->size;
    }

    void updateSize(AVLNode* N) {
        if (N != nullptr) {
            N->size = 1 + size(N->left) + size(N->right);
        }
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        updateSize(y);
        updateSize(x);

        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        updateSize(x);
        updateSize(y);

        return y;
    }

    int getBalance(AVLNode* N) {
        if (N == nullptr) return 0;
        return height(N->left) - height(N->right);
    }

    AVLNode* insert(AVLNode* node, int key) {
        if (node == nullptr) return new AVLNode(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));
        updateSize(node);

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    AVLNode* deleteNode(AVLNode* root, int key) {
        if (root == nullptr) return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                AVLNode* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                delete temp;
            } else {
                AVLNode* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (root == nullptr) return root;

        root->height = 1 + max(height(root->left), height(root->right));
        updateSize(root);

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    // Returns number of elements <= key
    int rank(AVLNode* root, int key) {
        if (root == nullptr) return 0;
        if (root->key == key) return size(root->left) + 1;
        if (root->key > key) return rank(root->left, key);
        return size(root->left) + 1 + rank(root->right, key);
    }
    
    // Helper to delete the entire tree
    void destroyTree(AVLNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    AVLRow(int size) : n(size), root(nullptr) {
        // Initially all seats are free
        for (int i = 0; i < n; i++) {
            root = insert(root, i);
        }
    }
    
    ~AVLRow() {
        destroyTree(root);
    }

    // Range update: O(K * log N)
    void reserveRange(int start, int end) {
        for (int i = start; i <= end && i < n; i++) {
            // We try to delete every key in range. 
            // Ideally we would check existence first but delete handles non-existence safely if logic is correct,
            // though standard delete assumes key exists or does nothing.
            // Our deleteNode does nothing if key not found.
            root = deleteNode(root, i);
        }
    }

    // Range query: O(log N)
    int queryFree(int l, int r) {
        // Count elements in [l, r]
        // rank(r) - rank(l-1)
        return rank(root, r) - rank(root, l - 1);
    }
};

#endif
