#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "dialog.h"

int D_Insert(Node** root) {
  int rc;
  const char* errmsgs[] = {"Ok", "Duplicate"};
  printf("Input Key:\n");
  char *key = readline();
  if (key == NULL){
    free(key);
    printf("End Of File\n");
    return 0; 
  }
  printf("Input Info:\n");
  char *info = readline();
  if (info == NULL){
    free(info);
    printf("End Of File\n");
    return 0;
  }
  rc = insertNode(root, key, info);
  printf("\n");
  printf("%s: %s\n",errmsgs[rc], key);
  free(info);
  free(key);
  return 1;
}

int D_Erase(Node** root) {
  int rc;
  printf("Input Key:\n");
  char* key = readline();
  const char* errmsgs[] = {"Ok", "This Element Doesn't Exist", "Table Is Empty"};
  if (key == NULL){ 
    free(key);
    printf("End Of File\n");
    return 0; 
  }
  rc = removeNode(root, key);
  printf("\n");
  printf("%s \n", errmsgs[rc]);
  free(key);
  return 1;
}

int D_Inorder(Node** root) {
  int rc;
  const char* errmsgs[]={"Ok", "Table Is Empty"};
  if (root == NULL) {
    rc = 1;
  } else {
    inorderTraversal(*root);
    rc = 0;
  }
  printf("\n");
  printf("%s \n", errmsgs[rc]);
  return 1;
}

int D_Search(Node **root) {
  const char* errmsgs[] = {"Ok", "This Element Doesn't Exist"};
  printf("Input Key:\n");
  char* key = readline();
  if (key == NULL){
    free(key);
    printf("End Of File\n");
    return 0; 
  }
  int rc;
  Node* node = searchNode(*root, key);
  if (node == NULL) {
    rc = 1;
  } else {
    rc = 0;
    printTree(node);
  }
  printf("\n");
  printf("%s \n", errmsgs[rc]);
  free(key);
  destroyTree(node);
  return 1;
}

int D_TaskSearch(Node **root) {
  const char* errmsgs[] = {"Ok", "This Element Doesn't Exist"};
  printf("Input Key:\n");
  char* key = readline();
  if (key == NULL){
    free(key);
    printf("End Of File\n");
    return 0; 
  }
  int rc;
  Node* node = findClosestNode(*root, key);
  if (node == NULL) {
    rc = 1;
  } else {
    rc = 0;
    printTree(node);
  }
  printf("\n");
  printf("%s \n", errmsgs[rc]);
  free(key);
  return 1;
}

int D_Print(Node** root) {
  int rc;
  const char* errmsgs[]={"Ok", "Table Is Empty"};
  if (root == NULL) {
    rc = 1;
  } else {
    printTree(*root);
    rc = 0;
  }
  printf("\n");
  printf("%s \n", errmsgs[rc]);
  return 1;
}

int D_load(Node **root) {
  const char* errmsgs[]={"Table Is Loaded", "File Can't Be Open"}; 
  printf("Input File Name:\n");
  char *name = readline();
  if (!name) {
    printf("End");
    return 1;
  }
  int rc = load(&name, root);
  printf("\n");
  printf("%s %s\n", errmsgs[rc], name);
  free(name);
  return 1;
}

int D_Timing() {
  Node* root = NULL;
    int n = 10, cnt = 1000000, i, m;
    char key[10000];
    clock_t first, last;
    srand(time(NULL));
    while (n-- > 0) {
        for (i = 0; i < 10000; ++i) {
            key[i] = rand() * rand();
        }
        for (i = 0; i < cnt; ) {
            int k = rand() * rand();
            if (insertNode(&root, "key", "str")) {
                ++i;
            }
        }
        m = 0;
        first = clock();
        for (i = 0; i < 10000; ++i) {
            if (searchNode(root, "key") != NULL) {
                ++m;
            }
        }
        last = clock();
        printf("%d items were found\n", m);
        printf("test #%d, number of nodes = %d, time = %ld\n", 10 - n, (10 - n) * cnt, last - first);
    }
    destroyTree(root);
    return 1;
}

int dialog(const char* msgs[], int flag) {
  char* errmsg = "";
  int rc;
  do {
    puts(errmsg);
    errmsg = "Invalid Input, Repeat\n";
    for (int i = 0; i < flag; i++) {
      puts(msgs[i]);
    }
    puts("Enter:\n");
    rc = get_int();
    printf("\n");
    
  } while (rc < 0 || rc >= flag);
  return rc;
}
