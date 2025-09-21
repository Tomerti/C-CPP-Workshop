#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"

#define BUFFER 60
#define TWO 2
#define THREE 3
#define TEN 10
#define HUNDRED 100
#define THOUSAND 1000
#define TEST1PASSED "TEST 1 PASSED: V\n"
#define TEST1FAILED "TEST 1 FAILED: X\n"
#define TEST2PASSED "TEST 2 PASSED: V\n"
#define TEST2FAILED "TEST 2 FAILED: X\n"
#define TEST3PASSED "TEST 3 PASSED: V\n"
#define TEST3FAILED "TEST 3 FAILED: X\n"
#define TEST4PASSED "TEST 4 PASSED: V\n"
#define TEST4FAILED "TEST 4 FAILED: X\n"
#define TEST5PASSED "TEST 5 PASSED: V\n"
#define TEST5FAILED "TEST 5 FAILED: X\n"
#define TEST6PASSED "TEST 6 PASSED: V\n"
#define TEST6FAILED "TEST 6 FAILED: X\n"

/**
 * Chceks number of arguments and type, if fits returns 0 else 1.
 */
int args_check(int argc, char *argv[])
{
    if (argc != TWO)
    {
        return 1;
    }
    if (strcmp(argv[1], "by_duration") != 0 &&
        strcmp(argv[1], "by_distance") != 0 &&
        strcmp(argv[1], "by_name") != 0 &&
        strcmp(argv[1], "test") != 0)
    {
        printf("USAGE: invalid number/type of arguments\n");
        return 1;
    }
    return 0;
}

/**
 * function that receives number of lines to be inserted by user.
 */
size_t get_number_lines(char *buff)
{
    size_t num = 0;
    char *ptr;
    while (num <= 0)
    {
        printf("Enter number of lines. Then enter\n");
        fgets(buff, BUFFER, stdin);
        num = strtol(buff, &ptr, TEN);
        if (num <= 0)
        {
            printf("ERROR: Number of lines should be a positive integer\n");
        }
    }
    return num;
}

/**
 * function that receives lines details to insert to the array.
 */
void get_lines(BusLine *arr, int total_lines)
{
    char buffer[BUFFER];
    int index = 0;
    int flag;
    int i;
    while (index != total_lines)
    {
        i = 0;
        flag = 0;
        printf("Enter line info. Then enter\n");
        fgets(buffer, BUFFER, stdin);
        if (sscanf(buffer, "%[^,],%d,%d", &arr[index].name[0],
                   &arr[index].distance, &arr[index].duration) != THREE)
        {
            printf("ERROR: invalid input\n");
            continue;
        }
        if (arr[index].distance < 0 || arr[index].distance > THOUSAND)
        {
            printf("ERROR: invalid distance\n");
            continue;
        }
        if (arr[index].duration < TEN || arr[index].duration > HUNDRED)
        {
            printf("ERROR: invalid duration\n");
            continue;
        }
        while (arr[index].name[i] != '\0')
        {
            if (!isdigit(arr[index].name[i]) && !islower(arr[index].name[i]))
            {
                printf("ERROR: invalid line name\n");
                flag = 1;
                break;
            }
            i++;
        }
        if (flag == 1)
        {
            continue;
        }
        index++;
    }
}

/**
 * runs first half of tests.
 */
void a_tests(BusLine* database, BusLine* copy, int count){
    if (is_sorted_by_distance(copy, copy + count - 1))
    {
        printf(TEST1PASSED);
    } else
    {
        printf(TEST1FAILED);
    }
    if (is_equal(copy, copy + count - 1, database,
                 database + count - 1))
    {
        printf(TEST2PASSED);
    } else
    {
        printf(TEST2FAILED);
    }
    quick_sort(copy, copy + count - 1, DURATION);
    if (is_sorted_by_duration(copy, copy + count - 1))
    {
        printf(TEST3PASSED);
    } else
    {
        printf(TEST3FAILED);
    }
}

/**
 * runs second half of tests.
 */
void b_tests(BusLine* database, BusLine* copy,int count){
    if (is_equal(copy, copy + count - 1, database,
                 database + count - 1))
    {
        printf(TEST4PASSED);
    } else
    {
        printf(TEST4FAILED);
    }
    bubble_sort(copy, copy + count - 1);
    if (is_sorted_by_name(copy, copy + count - 1))
    {
        printf(TEST5PASSED);
    } else
    {
        printf(TEST5FAILED);
    }
    if (is_equal(copy, copy + count - 1, database,
                 database + count - 1))
    {
        printf(TEST6PASSED);
    } else
    {
        printf(TEST6FAILED);
    }
}

/**
 * A simple function that runs the test.
 */
void run_tests(BusLine* database, BusLine* copy,int count){
    a_tests(database,copy, count);
    b_tests(database, copy, count);
}

/**
 * Main function that gets info from user and runs according to given details.
 */
int main(int argc, char *argv[])
{
    char buff[BUFFER] = {0};
    if (args_check(argc, argv) == 1){
        return EXIT_FAILURE;
    }
    size_t lines = get_number_lines(buff);
    BusLine *database = malloc(sizeof(BusLine) * lines);
    if (database == NULL){
        printf("ERROR: MALLOC ISSUE\n");
        return EXIT_FAILURE;
    }
    get_lines(database, (int) lines);
    if (strcmp(argv[1], "test") != 0){
        if (strcmp(argv[1], "by_distance") == 0){
            quick_sort(database, database + lines - 1, DISTANCE);
        }
        if (strcmp(argv[1], "by_duration") == 0){
            quick_sort(database, database + lines - 1, DURATION);
        }
        if (strcmp(argv[1], "by_name") == 0){
            bubble_sort(database, database + lines - 1);
        }
        for (int i = 0; i < (int)lines; i++){
            printf("%s,%d,%d\n", database[i].name, database[i].distance,
                   database[i].duration);
        }
        free(database);
        return EXIT_SUCCESS;
    }
    BusLine *copy = malloc(sizeof(BusLine) * lines);
    if (copy == NULL){
        free(database);
        database = NULL;
        printf("ERROR: MALLOC ISSUE\n");
        return EXIT_FAILURE;
    }
    copy = memcpy(copy, database, sizeof(BusLine) * lines);
    quick_sort(copy, copy + lines - 1, DISTANCE);
    run_tests(database,copy,(int)lines);
    free(copy);
    copy = NULL;
    free(database);
    database = NULL;
    return EXIT_SUCCESS;
}
