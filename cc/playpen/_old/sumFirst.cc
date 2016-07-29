#include <stdio.h>

static const int thru1[] = {1};
static const int thru2[] = {1, 2};
static const int thru3[] = {1, 2, 3};

#define ARRAY_SIZE(a) (sizeof a / sizeof a[0])

int sumFirst1() {
    int sum = 0;
    for (size_t i = 0; i < ARRAY_SIZE(thru1); ++i)
        sum += thru1[i];
    return sum;
}

int sumFirst2() {
    int sum = 0;
    for (size_t i = 0; i < ARRAY_SIZE(thru2); ++i)
        sum += thru2[i];
    return sum;
}

int sumFirst3() {
    int sum = 0;
    for (size_t i = 0; i < ARRAY_SIZE(thru3); ++i)
        sum += thru3[i];
    return sum;
}

int main(void) {
    printf("1: %d\n", sumFirst1());
    printf("2: %d\n", sumFirst2());
    printf("3: %d\n", sumFirst3());
}
