#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
// EX2_REPO_SORTBUSLINES_H
#include <string.h>

#define NAME_LEN 21
/**
 * Basic struct of BusLine that holds the name, distance and duration
 * of each line.
 */
typedef struct BusLine
{
    char name[NAME_LEN];
    int distance, duration;
} BusLine;
typedef enum SortType
{
    DISTANCE,
    DURATION
} SortType;

/**
 * Using bubble sort to fix the array by dictionary value
 * (with strcmp function)
 */
void bubble_sort(BusLine *start, BusLine *end);

/**
 * Using quick sort to fix the array by sort type (distance or duration)
 */
void quick_sort(BusLine *start, BusLine *end, SortType sort_type);

/**
 * Simple partition (high mid low) used in quick_sort.
 */
BusLine *partition(BusLine *start, BusLine *end, SortType sort_type);
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
// EX2_REPO_SORTBUSLINES_H
#endif //EX2_REPO_SORTBUSLINES_H
