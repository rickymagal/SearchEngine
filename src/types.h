#ifndef TYPE_H
#define TYPE_H

#include <stdio.h>
#include <stdbool.h>

typedef void* data_type;

typedef int (*HashFunction)(int, void *);
typedef int (*CmpFunction)(void *k1, void *k2);
typedef void (*PrintFunction)(FILE *, void *);
typedef void (*DestroyFunction)(void *);
typedef void* Key;
typedef void* Value;


#endif // TYPE_H