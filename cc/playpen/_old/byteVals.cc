#include <stdio.h>
#include <stdint.h>

#define REPLICATE(FN) FN(8) FN(16) FN(32)

static const uint8_t vals8[] = {1};
static const uint16_t vals16[] = {1, 2};
static const uint32_t vals32[] = {1, 2, 3, 4};

#define BYTEVALS_TEMPLATE(N)                \
    uint##N##_t byteVals##N() {             \
        uint##N##_t ret = 0;                \
        for (size_t i = 0; i < N / 8; ++i)  \
            ret += vals##N[i];              \
        return ret;                         \
    }
REPLICATE(BYTEVALS_TEMPLATE)

int main(void) {
    printf("%d\n", byteVals8());
    printf("%d\n", byteVals16());
    printf("%d\n", byteVals32());
}
