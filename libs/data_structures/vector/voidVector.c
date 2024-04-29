#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "voidVector.h"


vectorVoid createVectorV(size_t n, size_t baseTypeSize) {
    vectorVoid result = {(int *) malloc(baseTypeSize * n), 0, n,
                         baseTypeSize};
    if (result.data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    return result;
}