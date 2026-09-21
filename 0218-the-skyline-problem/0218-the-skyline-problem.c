#include <stdio.h>
#include <stdlib.h>

// Structure to represent critical X-coordinate sweep events
typedef struct {
    int x;
    int height; // Negative for start of building, positive for end
} Event;

// Comparison function for sorting events
int compareEvents(const void* a, const void* b) {
    Event* e1 = (Event*)a;
    Event* e2 = (Event*)b;
    if (e1->x != e2->x) {
        return (e1->x < e2->x) ? -1 : 1;
    }
    // If X-coordinates are equal, sorting by height natively handles all edge cases
    return (e1->height < e2->height) ? -1 : 1;
}

// Max-Heap implementation to keep track of active heights
typedef struct {
    int* data;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* createHeap(int initialCapacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->data = (int*)malloc(initialCapacity * sizeof(int));
    heap->size = 0;
    heap->capacity = initialCapacity;
    return heap;
}

void pushHeap(MaxHeap* heap, int val) {
    if (heap->size >= heap->capacity) {
        heap->capacity *= 2;
        heap->data = (int*)realloc(heap->data, heap->capacity * sizeof(int));
    }
    int i = heap->size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap->data[p] >= val) break;
        heap->data[i] = heap->data[p];
        i = p;
    }
    heap->data[i] = val;
}

// Lazy deletion: instead of an expensive item removal, we find it and extract it
void removeHeap(MaxHeap* heap, int val) {
    int idx = -1;
    for (int i = 0; i < heap->size; i++) {
        if (heap->data[i] == val) {
            idx = i;
            break;
        }
    }
    if (idx == -1) return; // Value not found

    heap->size--;
    if (idx == heap->size) return;

    int lastVal = heap->data[heap->size];
    int i = idx;
    
    // Bubble down or up depending on replacement location
    heap->data[i] = lastVal;
    while (2 * i + 1 < heap->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        if (heap->data[left] > heap->data[largest]) largest = left;
        if (right < heap->size && heap->data[right] > heap->data[largest]) largest = right;
        if (largest == i) break;
        int temp = heap->data[i];
        heap->data[i] = heap->data[largest];
        heap->data[largest] = temp;
        i = largest;
    }
}

int getMax(MaxHeap* heap) {
    return (heap->size > 0) ? heap->data[0] : 0;
}

void freeHeap(MaxHeap* heap) {
    free(heap->data);
    free(heap);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 */
int** getSkyline(int** buildings, int buildingsSize, int* buildingsColSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    if (buildingsSize == 0) {
        *returnColumnSizes = NULL;
        return NULL;
    }

    // Step 1: Generate Sweep-Line Events
    int numEvents = buildingsSize * 2;
    Event* events = (Event*)malloc(numEvents * sizeof(Event));
    int eventIdx = 0;
    for (int i = 0; i < buildingsSize; i++) {
        events[eventIdx].x = buildings[i][0];
        events[eventIdx].height = -buildings[i][2]; // Negative for Start
        eventIdx++;
        events[eventIdx].x = buildings[i][1];
        events[eventIdx].height = buildings[i][2];  // Positive for End
        eventIdx++;
    }

    // Step 2: Sort the critical events
    qsort(events, numEvents, sizeof(Event), compareEvents);

    // Initial allocations for final return structures
    int resultCapacity = 32;
    int** result = (int**)malloc(resultCapacity * sizeof(int*));
    *returnColumnSizes = (int*)malloc(resultCapacity * sizeof(int));

    MaxHeap* heap = createHeap(buildingsSize);
    int prevMaxHeight = 0;

    // Step 3: Iterate through sorted events
    for (int i = 0; i < numEvents; i++) {
        int currentX = events[i].x;
        int currentH = events[i].height;

        if (currentH < 0) {
            // Start event: add building height to the active heap
            pushHeap(heap, -currentH);
        } else {
            // End event: remove building height from active heap
            removeHeap(heap, currentH);
        }

        int currentMaxHeight = getMax(heap);

        // If the maximum height changes, we found a key outline contour point
        if (currentMaxHeight != prevMaxHeight) {
            if (*returnSize >= resultCapacity) {
                resultCapacity *= 2;
                result = (int**)realloc(result, resultCapacity * sizeof(int*));
                *returnColumnSizes = (int*)realloc(*returnColumnSizes, resultCapacity * sizeof(int));
            }
            
            result[*returnSize] = (int*)malloc(2 * sizeof(int));
            result[*returnSize][0] = currentX;
            result[*returnSize][1] = currentMaxHeight;
            (*returnColumnSizes)[*returnSize] = 2;
            (*returnSize)++;
            
            prevMaxHeight = currentMaxHeight;
        }
    }

    // Cleanup memory
    free(events);
    freeHeap(heap);

    return result;
}
