#ifndef HASHTABLE_H_
#define HASHTABLE_H_


typedef struct Hashtable{
	struct Node** bucket_list;
	int size;
} Hashtable;


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