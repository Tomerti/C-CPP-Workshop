#include "sort_bus_lines.h"


void swap(BusLine *a, BusLine *b)
{
    BusLine t = *a;
    *a = *b;
    *b = t;
}


void bubble_sort(BusLine *start, BusLine *end)
{
    int total = end - start;
    for (int i = 0; i < total; i++)
    {
        for (int k = 0; k <= total - i - 1; k++)
        {
            if (strcmp((start + k)->name, (start + k + 1)->name) > 0)
            {
                swap(start + k, start + k + 1);
            }
        }
    }
}


BusLine *partition(BusLine *start, BusLine *end, SortType sort_type)
{
    int lines = end - start;
    int pivot = lines;
    int i = -1;
    if (sort_type == DURATION)
    {
        for (int k = 0; k <= lines - 1; k++)
        {
            if ((start + k)->duration <= (start + pivot)->duration)
            {
                i++;
                swap(start + i, start + k);
            }
        }
        swap(start + i + 1, start + pivot);
        return start + i + 1;
    }
    for (int k = 0; k <= lines - 1; k++)
    {
        if ((start + k)->distance <= (start + pivot)->distance)
        {
            i++;
            swap(start + i, start + k);
        }
    }
    swap(start + i + 1, start + pivot);
    return start + i + 1;
}


void quick_sort(BusLine *start, BusLine *end, SortType sort_type)
{
    if (start < end)
    {
        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        BusLine *middle = partition(start, end, sort_type);
        quick_sort(start, middle - 1, sort_type);
        quick_sort(middle + 1, end, sort_type);
    }
}