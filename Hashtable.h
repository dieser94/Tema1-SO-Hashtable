#ifndef HASHTABLE_H_
#define HASHTABLE_H_


typedef struct Hashtable{
	struct Node** bucket_list;
	unsigned int size;
} Hashtable;

Hashtable* initialisation_hashtable(unsigned int size);
void add_element_to_hashtable(Hashtable *ht, char* element);
void delete_element_from_hashtable(Hashtable *ht, char* element);
void empty_hashtable(Hashtable *ht);
int hashtable_contains_element(Hashtable *ht, char* element);
void print_hashtable_bucket(Hashtable *ht, unsigned int pos);
void print_hashtable(Hashtable *ht);
Hashtable* double_size(Hashtable *ht);
Hashtable* half_size(Hashtable *ht);

typedef struct Node {
    char* value;
    struct Node* next;
} Node;

void print_linked_list(Node* list);
void add_element_to_list(char *element, Node** list);
void delete_list(Node** list);
void delete_element_from_list(char *element, Node** list);
int list_contains_element(char *element, Node** list);

#endif