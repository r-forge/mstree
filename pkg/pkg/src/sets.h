#include <stddef.h>

typedef struct ufstruct{
  int *id;
  int *sz;
} *UFob;



UFob UFinit(int);
int UFfind(UFob, int, int);
void UFunion(UFob, int, int);
