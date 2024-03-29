#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "dialog.h"

int main() {
  Node* root = NULL;
  const char* msgs[] = {"0. Quit", "1. Insert", "2. Erase", "3. Inorder", "4. Search", "5. Task Search", "6. Print", "7. Load File", "8. Timing"};
  const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
  int (*fptr[])(Node **) = {NULL, D_Insert, D_Erase, D_Inorder, D_Search, D_TaskSearch, D_Print, D_load, D_Timing};

  int rc;
  while (rc = dialog(msgs, NMsgs)) {
    if (!fptr[rc](&root)){
      break;
    }
  }
  printf("End\n");
  destroyTree(root);
  return 0;
}
