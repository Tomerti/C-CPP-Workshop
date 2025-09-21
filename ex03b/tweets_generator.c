#include "markov_chain.h"
#include <string.h>
#include <stdio.h>
#define MAX_BUFFER (1000)
#define MAXIMAL (2147483647)
#define MAXIM (20)
#define FIVE (5)
#define FOUR (4)
#define TEN (10)

static void print_func (void *data)
{
    char *str = (char *) data;
    printf (" %s", str);
}

static int compare_func (void *data1, void *data2)
{
    char *str1 = (char *) data1;
    char *str2 = (char *) data2;
    return strcmp (str1, str2);
}

static void free_data (void *data)
{
    char *str = (char *) data;
    free (str);
}

static void *copy_func (void *data)
{
    char *str = (char *) data;
    char *cpy = malloc (sizeof (char) * (strlen (str) + 1));
    if (cpy == NULL)
    {
        return NULL;
    }
    memcpy (cpy, str, sizeof(char) * (strlen(str) + 1));
    return cpy;
}

static bool is_last (void *data)
{
    char *str = (char *) data;
    if(str[strlen (str) - 1] == '.'){
        return true;
    }
    return false;
}

int fill_database (FILE *fp, int words_to_read, MarkovChain *markov_chain){
    int counter = 0;
    char line[MAX_BUFFER];
    char *word;
    Node* temp1;
    Node* temp2;
    while(fgets(line,MAX_BUFFER,fp) && counter<words_to_read){
        strtok(line,"\n");
        word = strtok(line," ");
        temp1 = add_to_database(markov_chain,word);
        if(temp1 == NULL){
            return EXIT_FAILURE;
        }
        counter++;
        while(word != NULL && counter<words_to_read){
            word = strtok(NULL, " ");
            if(word == NULL){
                break;
            }
            temp2 = add_to_database(markov_chain,word);
            if(temp2 == NULL){
                return EXIT_FAILURE;
            }
            if(!add_node_to_frequencies_list(
                    temp1->data, temp2->data,markov_chain)){
                return EXIT_FAILURE;
            }
            counter++;
            temp1 = temp2;
        }
    }
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]){
    char *ptr;
    if(argc!=FOUR && argc!=FIVE){
        printf("Usage: Error, 3 or 4 arguments only!\n");
        return EXIT_FAILURE;}
    unsigned int seed = strtol(argv[1], &ptr, TEN);
    int tweets_num = strtol(argv[2], &ptr, TEN);
    srand(seed);
    char* path = argv[3];
    int words_to_read = MAXIMAL;
    if(argc == FIVE){
        words_to_read = strtol(argv[4], &ptr, TEN);}
    LinkedList* database = malloc (sizeof (LinkedList));
    if(database == NULL){
        printf(ALL_ERROR);
        return EXIT_FAILURE;}
    MarkovChain* markov_chain = malloc (sizeof (MarkovChain));
    if(markov_chain == NULL){
        free(database);
        database = NULL;
        printf(ALL_ERROR);
        return EXIT_FAILURE;}
    markov_chain->database = database;
    markov_chain->database->first = NULL;
    markov_chain->database->last = NULL;
    markov_chain->database->size = 0;
    markov_chain->free_data = &free_data;
    markov_chain->copy_func = &copy_func;
    markov_chain->comp_func = &compare_func;
    markov_chain->is_last = &is_last;
    markov_chain->print_func = &print_func;
    FILE* fp = fopen(path,"r");
    if(fp == NULL){
        printf("ERROR: Path invalid or file is not accessible.");
        free(database);
        database = NULL;
        free(markov_chain);
        markov_chain = NULL;
        return EXIT_FAILURE;}
    if(fill_database(fp,words_to_read,markov_chain)){
        free_database(&markov_chain);
        fclose(fp);
        return EXIT_FAILURE;}
    for(int i =1;i<=tweets_num; i++){
        printf("Tweet %d:",i);
        generate_tweet(markov_chain,
                       get_first_random_node(markov_chain),
                       MAXIM);}
    free_database(&markov_chain);
    fclose(fp);
    return EXIT_SUCCESS;}