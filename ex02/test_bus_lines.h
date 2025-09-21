#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H
// write only between #define EX2_REPO_TESTBUSLINES_H and
// #endif //EX2_REPO_TESTBUSLINES_H
#include "sort_bus_lines.h"

/**
 * returns if array sorted by distance
 */
int is_sorted_by_distance (BusLine *start, BusLine *end);

/**
 * returns if array sorted by duration
 */
int is_sorted_by_duration (BusLine *start, BusLine *end);

/**
 * returns if array sorted by name
 */
int is_sorted_by_name (BusLine *start, BusLine *end);

/**
 * returns if arrays are equal by line names and sizes.
 */
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original);
// write only between #define EX2_REPO_TESTBUSLINES_H and #endif
// EX2_REPO_TESTBUSLINES_H

/**
 * Function that gets start and end of given array,
 * returns total amount of elements in given array.
 */
int total_lines(BusLine *start, BusLine *end);
#endif //EX2_REPO_TESTBUSLINES_H
