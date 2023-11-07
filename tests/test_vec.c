#include "../include/common.h"
#include <assert.h>

int main(void) {
  // addition
  printf("TESTING add_vec\n");
  vec3 u = {2, 5, -10};
  vec3 v = {4, 2, 3};
  vec3 add = add_vec(u, v);
  print_vec(add);
  assert(eq_vec(add, (vec3){6, 7, -7}));
  printf("add_vec OKAY\n");
}
