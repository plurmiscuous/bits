#include <stdio.h>

#define REPLICATE(FN) FN(1) FN(2) FN(3)

static const int thru1[] = {1};
static const int thru2[] = {1, 2};
static const int thru3[] = {1, 2, 3};

#define SUMFIRST_TEMPLATE(N)                \
    int sumFirst##N() {                     \
        int sum = 0;                        \
        for (size_t i = 0; i < N; ++i)      \
            sum += thru##N[i];              \
        return sum;                         \
    }
REPLICATE(SUMFIRST_TEMPLATE)

int main(void) {
    printf("1: %d\n", sumFirst1());
    printf("2: %d\n", sumFirst2());
    printf("3: %d\n", sumFirst3());
}

// // a better main():
// int main(void) {
//     #define PRINT_SUMFIRST_TEMPLATE(N) printf(#N ": %d\n", sumFirst##N());
//     REPLICATE(PRINT_SUMFIRST_TEMPLATE)
// }
