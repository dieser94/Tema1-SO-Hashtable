#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

typedef struct Hashtable{
	struct Node** bucket_list;
	unsigned int size;
} Hashtable;

Hashtable* initialisation_hashtable(unsigned int size);
int add_element_to_hashtable(Hashtable *ht, char* element);
void delete_element_from_hashtable(Hashtable *ht, char* element);
void empty_hashtable(Hashtable *ht);
int hashtable_contains_element(Hashtable *ht, char* element);
int print_hashtable_bucket(Hashtable *ht, unsigned int pos, FILE* f);
int print_hashtable(Hashtable *ht, FILE* f);
Hashtable* double_size(Hashtable *ht);
Hashtable* half_size(Hashtable *ht);

typedef struct Node {
    char* value;
    struct Node* next;
} Node;

int print_linked_list(Node* list, FILE* f);
int add_element_to_list(char *element, Node** list);
void delete_list(Node** list);
void delete_element_from_list(char *element, Node** list);
int list_contains_element(char *element, Node** list);

#endif