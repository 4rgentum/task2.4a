#ifndef ROOT_H
#define ROOT_H

typedef struct Node {
    char* key;
    char* value;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

Node* createNode(const char* key, const char* value);
int insertNode(Node** root, const char* key, const char* value);
Node* findMinimumNode(Node* node);
int removeNode(Node** root, const char* key);
void inorderTraversal(Node* root);
Node* searchNode(Node* root, const char* key);
Node* findClosestNode(Node* root, const char* targetKey);
void printTreeRecursive(Node* node, int level);
void printTree(Node* root);
int load(char **name, Node **root);
void destroyTree(Node* node);

#endif
