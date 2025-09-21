#include "test_bus_lines.h"

int total_lines(BusLine *start, BusLine *end)
{
    return end - start;
}

int is_sorted_by_distance(BusLine *start, BusLine *end)
{
    int total = total_lines(start, end);
    for (int i = 1; i < total; i++)
    {
        if ((start + i)->distance < (start + (i - 1))->distance)
        {
            return 0;
        }
    }
    return 1;
}

int is_sorted_by_duration(BusLine *start, BusLine *end)
{
    int total = total_lines(start, end);
    for (int i = 1; i < total; i++)
    {
        if ((start + i)->duration < (start + (i - 1))->duration)
        {
            return 0;
        }
    }
    return 1;
}

int is_sorted_by_name(BusLine *start, BusLine *end)
{
    int total = total_lines(start, end);
    int res;
    for (int i = 1; i < total; i++)
    {
        res = strcmp((start + i)->name, (start + (i - 1))->name);
        if (res < 0)
        {
            return 0;
        }
    }
    return 1;
}

int is_equal(BusLine *start_sorted,
             BusLine *end_sorted, BusLine *start_original,
             BusLine *end_original)
{
    int total_sorted = total_lines(start_sorted, end_sorted);
    int total_original = total_lines(start_original, end_original);
    int flag = 0;
    if (total_original != total_sorted)
    {
        return 0;
    }
    for (int i = 0; i < total_original; i++)
    {
        flag = 0;
        for (int k = 0; k < total_sorted; k++)
        {
            if (strcmp((start_original + i)->name, (start_sorted + k)->name) ==
                0)
            {
                flag = 1;
                continue;
            }
        }
        if (flag == 0)
        {
            return 0;
        }
    }
    return 1;
}