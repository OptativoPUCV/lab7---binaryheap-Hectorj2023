#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq){
    if (pq->size == 0) { 
        return NULL;
    }
    return pq->heapArray[0].data; 
}



void heap_push(Heap* pq, void* data, int priority){
   if (pq->size == pq->capac) {
        pq->capac = pq->capac * 2 + 1;
        pq->heapArray = realloc(pq->heapArray, sizeof(heapElem) * pq->capac);
    }

    int i = pq->size;
    pq->heapArray[i].data = data;
    pq->heapArray[i].priority = priority;
    pq->size++;

    while (i != 0 && pq->heapArray[i].priority > pq->heapArray[(i-1)/2].priority) {
        heapElem temp = pq->heapArray[i];
        pq->heapArray[i] = pq->heapArray[(i-1)/2];
        pq->heapArray[(i-1)/2] = temp;

        i = (i-1)/2;
    }

}


void heap_pop(Heap* pq){
    if (pq->size == 0) { 
        return;
    }

    pq->size--;
    pq->heapArray[0] = pq->heapArray[pq->size];

    int i = 0;
    while (2*i+1 < pq->size) { 
        int maximoA = 2*i+1; 
        if (maximoA+1 < pq->size && pq->heapArray[maximoA+1].priority > pq->heapArray[maximoA].priority) {
            maximoA++;
        }
        if (pq->heapArray[i].priority >= pq->heapArray[maximoA].priority) {
            break;
        }
        heapElem temp = pq->heapArray[i];
        pq->heapArray[i] = pq->heapArray[maximoA];
        pq->heapArray[maximoA] = temp;
        i = maximoA;
    }

    if (pq->size < pq->capac/2) {
        pq->capac = (pq->capac-1) / 2;
        pq->heapArray = realloc(pq->heapArray, sizeof(heapElem) * pq->capac);
    }
}

Heap* createHeap(){

    Heap* heap = (Heap*)malloc(sizeof(Heap));
    
  heap->heapArray = (heapElem*)malloc(sizeof(heapElem) * 3);
    
    heap->capac = 3;
    heap->size = 0;
    
    return heap;
}
