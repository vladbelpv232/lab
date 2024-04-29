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

void reserveV(vectorVoid *v, const size_t newCapacity) {
    if (newCapacity == 0)
        v->data = NULL;
    else
        v->data = (int *) realloc(v->data, v->baseTypeSize *
                                           newCapacity);
    if (v->data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    if (v->size > newCapacity)
        v->size = newCapacity;
    v->capacity = newCapacity;
}


void shrinkToFitV(vectorVoid *v) {
    reserveV(v, v->size);
}


void clearV(vectorVoid *v) {
    v->size = 0;
}


void deleteVectorV(vectorVoid *v) {
    free(v->data);
}

// проверка на то, является ли вектор пустым.
bool isEmptyV(vectorVoid *v);

// проверка на то, является ли вектор полным.
bool isFullV(vectorVoid *v);

// записывает по адресу destination index-ый элемент вектора v.
void getVectorValueV(vectorVoid *v, size_t index, void *destination);

// возвращает i-ый элемент вектора v.
void setVectorValueV(vectorVoid *v, size_t index, void *source);

//проверка на то, является ли вектор пустым.
bool isEmptyV(vectorVoid *v) {
    return v->size == 0;
}

//проверка на то, является ли вектор полным.
bool isFullV(vectorVoid *v) {
    return v->size == v->capacity;
}

//возвращает i-ый элемент вектора v.
void getVectorValueV(vectorVoid *v, size_t index, void *destination) {
    char *source = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

//записывает на index-ый элемент вектора v значение, расположенное
//по адресу source.
void setVectorValueV(vectorVoid *v, size_t index, void *source) {
    char *destination = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

//удаляет последний элемент из вектора.
void popBackV(vectorVoid *v) {
    if (isEmptyV(v)) {
        fprintf(stderr, "The vector is empty, we cannot fulfill your request");
        exit(1);
    }
    v->size--;
}

//добавляет элемент x в конец вектора v.
void pushBackV(vectorVoid *v, void *source) {
    if (v->capacity == 0)
        reserveV(v, 1);
    else if (v->size == v->capacity)
        reserveV(v, v->size * 2);
    setVectorValueV(v, v->size++, source);

}