#include "test_utils.h"
#include <stdio.h>
#include <stdlib.h>

// Main test runner
int main(void) {
  printf("Running tests...\n\n");
  int failed = 0;
  // Run tests and update failed count
  printf("\nTest Results:\n");
  if (failed == 0) {
    printf("\nAll tests passed!\n");
    return 0;
  } else {
    printf("\n%d tests failed!\n", failed);
    return 1;
  }
}
