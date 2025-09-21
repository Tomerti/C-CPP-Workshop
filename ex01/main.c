#include "cipher.h"
#include "tests.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define TEST_ARGC (2)
#define CIPHER_ARGC (5)
#define MAX_BUFFER (1024)
#define TEN (10)

// your code goes here
/**
 * Runs all mandatory tests as described in pdf.
 * @return 0 if passed, 1 otherwise.
 */
int runtests(void)
{
    if (test_encode_non_cyclic_lower_case_positive_k ()
    != EXIT_SUCCESS ||
    test_encode_cyclic_lower_case_special_char_positive_k ()
    != EXIT_SUCCESS ||
    test_encode_non_cyclic_lower_case_special_char_negative_k ()
    != EXIT_SUCCESS ||
    test_encode_cyclic_lower_case_negative_k ()
    != EXIT_SUCCESS ||
    test_encode_cyclic_upper_case_positive_k ()
    != EXIT_SUCCESS ||
    test_decode_non_cyclic_lower_case_positive_k ()
    != EXIT_SUCCESS ||
    test_decode_cyclic_lower_case_special_char_positive_k ()
    != EXIT_SUCCESS ||
    test_decode_non_cyclic_lower_case_special_char_negative_k ()
    != EXIT_SUCCESS ||
    test_decode_cyclic_lower_case_negative_k ()
    != EXIT_SUCCESS ||
    test_decode_cyclic_upper_case_positive_k ()
    != EXIT_SUCCESS)
    {
    return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * runs initial tests as described in pdf, as described in 4.2.2
 * @param args = number of arguments
 * @param argv = arguments received from CLI.
 * @return 0 if passed, 1 otherwise.
 */
int initial(int args, char *argv[])
{
    int status = EXIT_FAILURE;
    if (args != TEST_ARGC && args != CIPHER_ARGC)
    {
        fprintf(stderr,"The program receives 1 or 4 arguments only.\n");
        goto cleanup;
    }
    if (args == TEST_ARGC)
    {
        if (strcmp(argv[1], "test") != 0)
        {
            fprintf(stderr,"Usage: cipher test\n");
            goto cleanup;
        }
        else
        {
            status = runtests();
            if (status != EXIT_SUCCESS)
            {
                goto cleanup;
            }
        }
    }
    if (args == CIPHER_ARGC)
    {
        if (strcmp(argv[1], "encode") != 0 && strcmp(argv[1], "decode") != 0)
        {
            fprintf(stderr, "The given command is invalid.\n");
            goto cleanup;
        }
    }
    status = EXIT_SUCCESS;
cleanup:
return status;
}

/**
 * Function that gets value of k, makes sure if valid as integer.
 * @param str string of 2nd argument (k input) from CLI.
 * @param k pointer to address which k will be saved to.
 * @return 0 if passed, 1 otherwise.
 */
int get_k_value(char *str, long *k)
{
    char *ptr = NULL;
    long k_value;

    if (k == NULL || str == NULL)
    {
        return EXIT_FAILURE;
    }
    k_value = strtol(str, &ptr, TEN);
    if (*ptr != '\0')
    {
        fprintf(stderr,"The given shift value is invalid.\n");
        return EXIT_FAILURE;
    }

    *k = k_value;
    return EXIT_SUCCESS;
}

/**
 * Function that opens input and output files, checks their validity.
 * Will close opened files once done.
 * @param input_file input file pointer received from CLI.
 * @param output_file output file pointer received from CLI.
 * @param input pointer to address where input data will be saved to.
 * @param output pointer to address where output data will be saved to.
 * @return 0 if passed, 1 otherwise (file operations failed).
 */
int open_files(char *input_file, char *output_file, FILE **input,
               FILE **output)
{
    int status = EXIT_FAILURE;
    FILE *tempinput = NULL;
    FILE *tempoutput = NULL;

    if(input_file == NULL || output_file == NULL)
    {
        goto cleanup;
    }

    tempinput = fopen(input_file,"r");
    tempoutput = fopen(output_file,"w");
    if(tempinput == NULL || tempoutput == NULL)
    {
        fprintf(stderr,"The given file is invalid.\n");
        goto cleanup;
    }
    *input = tempinput;
    *output = tempoutput;
    tempinput = NULL;
    tempoutput = NULL;
    status = EXIT_SUCCESS;

cleanup:
    if(tempoutput != NULL)
    {
        fclose(tempoutput);
    }
    if(tempinput != NULL)
    {
        fclose(tempinput);
    }
    return status;
}

/**
 * Function that encodes given file with k parameter.
 * @param in input file address.
 * @param out output file address.
 * @param k k parameter for encoding.
 * @return 0.
 */
int encode_file(FILE *in, FILE *out, int k)
{
    char line[MAX_BUFFER] = { 0 };
    while(fgets(line,MAX_BUFFER,in))
    {
        encode(line,k);
        fputs(line,out);
    }
    return EXIT_SUCCESS;
}

/**
 * Function that decodes given file with k parameter.
 * @param in input file address.
 * @param out output file address.
 * @param k k parameter for decoding.
 * @return 0.
 */
int decode_file(FILE *in, FILE *out, int k)
{
    char line[MAX_BUFFER] = { 0 };
    while(fgets(line,MAX_BUFFER,in))
    {
        decode(line,k);
        fputs(line,out);
    }
    return EXIT_SUCCESS;
}

/**
 * Main program function, will encode/decode/run unit tests
 * as described in pdf according to user input from CLI.
 * @param argc = number of arguments.
 * @param argv = arguments inserted by user.
 * @return 0 if passed (and creates/rewrites the encoded/decoded out file),
 * 1 otherwise.
 */
int main(int argc, char *argv[])
{
    int status = EXIT_FAILURE;
    long kval = 0;
    FILE *input = NULL;
    FILE *output = NULL;
    if (initial(argc, argv) != EXIT_SUCCESS)
    {
        goto cleanup;
    }
    if (strcmp(argv[1],"test") == 0)
    {
        status = EXIT_SUCCESS;
        goto cleanup;
    }
    if (get_k_value(argv[2], &kval) != EXIT_SUCCESS)
    {
        goto cleanup;
    }

    if (open_files(argv[3],argv[4], &input, &output) != EXIT_SUCCESS)
    {
        goto cleanup;
    }
    if (strcmp(argv[1],"encode") == 0)
    {
        encode_file(input,output,kval);
        status = EXIT_SUCCESS;
        goto cleanup;
    }
    if (strcmp(argv[1],"decode") == 0)
    {
        decode_file(input,output,kval);
        status = EXIT_SUCCESS;
        goto cleanup;
    }

cleanup:
    if (output != NULL)
    {
        fclose(output);
    }
    if (input != NULL)
    {
        fclose(input);
    }
    return status;
}
