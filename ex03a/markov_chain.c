#include "markov_chain.h"
#include <string.h>

int get_random_number(int max_number)
{
    return rand() % max_number;
}

MarkovNode* get_first_random_node(MarkovChain *markov_chain){
    Node* curr_node = markov_chain->database->first;
    int counter = get_random_number(markov_chain->database->size);
    while(counter > 0){
        counter--;
        curr_node = curr_node->next;
    }
    if(curr_node->data->data[strlen(curr_node->data->data) - 1] == '.'){
        return get_first_random_node(markov_chain);
    }
    return curr_node->data;
}

MarkovNode* get_next_random_node(MarkovNode *state_struct_ptr){
    int total = 0;
    int k = 0;
    for(int i=0;i<state_struct_ptr->total_elements;i++){
        total+=(state_struct_ptr->frequencies_list + i)->frequency;
    }
    k = get_random_number(total);
    total = -1;
    for(int i=0;i<state_struct_ptr->total_elements;i++)
    {
        total+=(state_struct_ptr->frequencies_list + i)->frequency;
        if(total>=k){
            return (state_struct_ptr->frequencies_list + i)->markov_node;
        }
    }
    return NULL;
}


void generate_tweet(MarkovChain *markov_chain, MarkovNode *
first_node, int max_length){
    if(first_node == NULL){
        first_node = get_first_random_node(markov_chain);
    }
    MarkovNode* temp_node = first_node;
    int curr_length = 1;
    printf("%s ",temp_node->data);
    while(curr_length <max_length){
        curr_length++;
        temp_node = get_next_random_node(temp_node);
        if(temp_node->data[strlen(temp_node->data) - 1] == '.'){
            printf("%s\n", temp_node->data);
            return;
        }
        printf("%s ", temp_node->data);
    }
}

void free_database(MarkovChain ** ptr_chain){
    if(ptr_chain == NULL || *ptr_chain == NULL){
        return;
    }
    Node *curr = (*ptr_chain)->database->first;
    Node *temp = NULL;
    while(curr) {
        temp = curr->next;
        free(curr->data->data);
        curr->data->data = NULL;
        free(curr->data->frequencies_list);
        curr->data->frequencies_list = NULL;
        free(curr->data);
        curr->data = NULL;
        free(curr);
        curr = temp;
    }
    free((*ptr_chain)->database);
    (*ptr_chain)->database = NULL;
    free(*ptr_chain);
    *ptr_chain = NULL;
}

bool add_node_to_frequencies_list(MarkovNode *first_node,
                              MarkovNode *second_node){
    MarkovNodeFrequency* temp = NULL;
    for(int i =0;i<first_node->total_elements;i++)
    {
        if((first_node->frequencies_list + i)->markov_node == second_node){
            (first_node->frequencies_list + i)->frequency+= 1;
            return true;
        }
    }
    first_node->total_elements+=1;
    temp = realloc(first_node->frequencies_list,
                   first_node->total_elements * sizeof(MarkovNodeFrequency));
    if(temp == NULL){
        first_node->total_elements-=1;
        return false;
    }
    first_node->frequencies_list = temp;
    (first_node->frequencies_list + (first_node->total_elements - 1))->
    frequency= 1;
    (first_node->frequencies_list +
     (first_node->total_elements - 1))->markov_node = second_node;
    return true;
}

Node* get_node_from_database(MarkovChain *markov_chain, char *data_ptr){
    Node* current = markov_chain->database->first;
    while(current != NULL) {
        if (strcmp(current->data->data, data_ptr) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Node* add_to_database(MarkovChain *markov_chain, char *data_ptr){
    MarkovNode* markov_node = NULL;
    Node *temp = NULL;
    char* data = NULL;
    unsigned int length = strlen(data_ptr);
    temp = get_node_from_database(markov_chain,data_ptr);
    if(temp != NULL){
        return temp;
    }
    data = malloc(length + 1);
    if(data == NULL){
        fprintf (stderr, "%s", ALLOCATION_ERROR_MASSAGE);
        return NULL;
    }
    markov_node = malloc(sizeof(MarkovNode));
    if(markov_node == NULL){
        free(data);
        data = NULL;
        fprintf (stderr, "%s", ALLOCATION_ERROR_MASSAGE);
        return NULL;
    }
    markov_node->frequencies_list = NULL;
    markov_node->total_elements = 0;


    strcpy(data,data_ptr);
    markov_node->data = data;
    if(add(markov_chain->database,markov_node)){
        free(markov_node->data);
        markov_node->data = NULL;
        free(markov_node);
        markov_node = NULL;
        return NULL;
    }
    return markov_chain->database->last;
}