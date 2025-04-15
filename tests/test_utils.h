#ifndef TEST_H
#define TEST_H

// Simple test assertion macro
#define ASSERT(message, test) \
do { \
    if (!(test)) { \
        printf("Assertion failed: %s\n", message); \
        return 1; \
    } else { \
        printf("Test passed: %s\n", message); \
    } \
} while (0)


// Function prototypes for test functions
// TODO: Add more test functions as needed





#endif // TEST_H