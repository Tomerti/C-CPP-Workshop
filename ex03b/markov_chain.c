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
    if(markov_chain->is_last(curr_node->data->data) == 1){
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
    markov_chain->print_func(temp_node->data);
    while(curr_length <max_length){
        curr_length++;
        temp_node = get_next_random_node(temp_node);
        if(markov_chain->is_last(temp_node->data) == 1){
            markov_chain->print_func(temp_node->data);
            printf("\n");
            return;
        }
        markov_chain->print_func(temp_node->data);
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
        (*ptr_chain)->free_data(curr->data->data);
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
                                  MarkovNode *second_node,
                                  MarkovChain *markov_chain){
    MarkovNodeFrequency* temp = NULL;
    if (markov_chain->is_last (first_node->data))
    {
        first_node->frequencies_list = NULL;
        return true;
    }
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

Node* get_node_from_database(MarkovChain *markov_chain, void *data_ptr){
    Node* current = markov_chain->database->first;
    while(current != NULL) {
        if (markov_chain->comp_func(current->data->data, data_ptr) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Node* add_to_database(MarkovChain *markov_chain, void *data_ptr){
    Node* node = get_node_from_database(markov_chain,data_ptr);
    if (node!=NULL){
        return node;
    }
    void* cpy = markov_chain->copy_func(data_ptr);
    if(cpy == NULL){
        return NULL;
    }
    MarkovNode *marknode = malloc(sizeof(MarkovNode));
    if(marknode == NULL){
        markov_chain->free_data(cpy);
        cpy = NULL;
        return NULL;
    }
    marknode->data = cpy;
    marknode->frequencies_list = NULL;
    marknode->total_elements = 0;
    if(add(markov_chain->database,marknode) == 1){
        markov_chain->free_data(cpy);
        cpy = NULL;
        free(marknode);
        marknode = NULL;
        return NULL;
    }
    return markov_chain->database->last;
}