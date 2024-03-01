#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "get.h"
#include "root.h"

Node* createNode(const char* key, const char* value) {
  Node* newNode = (Node*) malloc(sizeof(Node));
  newNode->key = NULL;
  newNode->value = NULL;
  newNode->key = strdup(key);
  newNode->value = strdup(value);
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->parent = NULL;
  return newNode;
}

int insertNode(Node** root, const char* key, const char* value) {
  Node* newNode = createNode(key, value);
    if (*root == NULL) {
        *root = newNode;
        return 0;
    }
    Node* currentNode = *root;
    while (1) {
        if (strcmp(key, currentNode->key) < 0) {
            if (currentNode->left == NULL) {
                currentNode->left = newNode;
                newNode->parent = currentNode;
                return 0;
            }
            currentNode = currentNode->left;
        } else if (strcmp(key, currentNode->key) > 0) {
            if (currentNode->right == NULL) {
                currentNode->right = newNode;
                newNode->parent = currentNode;
                return 0;
            }
            currentNode = currentNode->right;
        } else {
            // Встречен дубликат ключа, игнорируем вставку
            free(newNode->key);
            free(newNode->value);
            free(newNode);
            return 1;
        }
    }
}

Node* findMinimumNode(Node* node) {
  while (node->left != NULL) {
    node = node->left;
  }
  return node;
}

int removeNode(Node** root, const char* key) {
  if (*root == NULL) {
    return 2;  // Дерево пустое, ничего не удаляем
  }
  Node* currentNode = *root;
  Node* nodeToDelete = NULL;
  while (currentNode != NULL) {
    if (strcmp(key, currentNode->key) == 0) {
      nodeToDelete = currentNode;
      break;
    } else if (strcmp(key, currentNode->key) < 0) {
      currentNode = currentNode->left;
    } else {
      currentNode = currentNode->right;
    }
  }
  if (nodeToDelete == NULL) {
    return 1;  // Элемент с заданным ключом не найден
  }
  Node* parentNode = nodeToDelete->parent;
  // Удаляем узел и перестраиваем связи
  if (nodeToDelete->left == NULL && nodeToDelete->right == NULL) {
    // У узла нет дочерних элементов
    if (parentNode != NULL) {
      if (parentNode->left == nodeToDelete) {
        parentNode->left = NULL;
      } else {
        parentNode->right = NULL;
      }
    } else {
      *root = NULL;
    }
  } else if (nodeToDelete->left != NULL && nodeToDelete->right != NULL) {
    // У узла есть оба дочерних элемента
    Node* successor = findMinimumNode(nodeToDelete->right);
    nodeToDelete->key = successor->key;
    nodeToDelete->value = successor->value;
    removeNode(&nodeToDelete->right, successor->key);
  } else {
    // У узла есть только один дочерний элемент
    Node* childNode = (nodeToDelete->left != NULL) ? nodeToDelete->left : nodeToDelete->right;
    if (parentNode != NULL) {
      if (parentNode->left == nodeToDelete) {
        parentNode->left = childNode;
      } else {
        parentNode->right = childNode;
      }
    } else {
      *root = childNode;
    }
    if (childNode != NULL) {
      childNode->parent = parentNode;
    }
  }
  free(nodeToDelete->key);
  free(nodeToDelete->value);
  free(nodeToDelete);
  return 0;
}

void inorderTraversal(Node* root) { // Обход дерева
  if (root == NULL) {
    return ;
  }
  if (root != NULL) {
    inorderTraversal(root->left);
    printf("Key: %s, Value: %s\n", root->key, root->value);
    inorderTraversal(root->right);
  }
}

Node* searchNode(Node* root, const char* key) {
  if (root == NULL || strcmp(key, root->key) == 0) {
    return root;
  } else {
    return NULL;
  }
  if (strcmp(key, root->key) < 0) {
    return searchNode(root->left, key);
  } else {
    return searchNode(root->right, key);
  }
}

Node* findClosestNode(Node* root, const char* targetKey) {
  Node* closestNode = NULL;
  int minDiff = INT_MAX;
  Node* current = root;
  while (current != NULL) {
    int diff = strcmp(targetKey, current->key);
    if (diff == 0) {
      // Если ключ совпадает, переходим к правому поддереву
      current = current->right;
    } else {
      // Если разница между ключами меньше текущей минимальной разницы,
      // обновляем ближайший узел и минимальную разницу
      if (abs(diff) < minDiff) {
        minDiff = abs(diff);
        closestNode = current;
      }
      // Переходим к левому или правому поддереву в зависимости от значения ключей
      if (diff < 0) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
  }
  return closestNode;
}

// Рекурсивная функция для вывода дерева в форматированном виде
void printTreeRecursive(Node* node, int level) {
    if (node == NULL) {
        return;
    }

    printTreeRecursive(node->right, level + 1);
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("%s\n", node->key);
    printTreeRecursive(node->left, level + 1);
}

void printTree(Node* root) {
  printTreeRecursive(root, 0);
}

int load(char **name, Node **root) {
  FILE *file = fopen(*name, "r");
  if (file == NULL) {
    return 1;
  }
  char* key = NULL;
  char* info = NULL;
  int count = 0;
  while (fscanf(file, "%s\n%s\n", key, info) == 2) {
    insertNode(root, key, info);
    count++;
    free(key);
    free(info);
  }
  if (!count) {
    fclose(file);
    return 1;
  }
  fclose(file);
  return 0;
}

void destroyTree(Node* node) {
  if (node == NULL) {
    return ;
  }
  destroyTree(node->left);
  destroyTree(node->right);
  free(node->key);
  free(node->value);
  free(node);
}
