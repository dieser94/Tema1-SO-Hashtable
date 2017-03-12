#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashtable.h"
#include "hash.h"

Hashtable* initialisation_hashtable(unsigned int size){
	int i;
	struct Hashtable  *hash_t = (Hashtable*) malloc(sizeof(Hashtable));
	hash_t->bucket_list = (Node**) malloc(size * sizeof(Node*));
	for( i=0; i < size; i++)
	{
		hash_t->bucket_list[i] = NULL;
	}
	hash_t->size = size;
	return hash_t;
}

void add_element_to_hashtable(Hashtable *ht, char* element){
	unsigned int position = hash(element, ht->size);
	add_element_to_list(element, &ht->bucket_list[position]);
}

void delete_element_from_hashtable(Hashtable *ht, char* element){
	unsigned int position = hash(element, ht->size);
	delete_element_from_list(element, &ht->bucket_list[position]);
}

void empty_hashtable(Hashtable *ht){
	unsigned int i;
	for( i=0; i < ht->size; i++ )
	{	
		delete_list(&(ht->bucket_list[i]));
	}
}

int hashtable_contains_element(Hashtable *ht, char* element){
	unsigned int position;
	int pos_in_bucket;

	position = hash(element, ht->size);
	pos_in_bucket = list_contains_element(element, &ht->bucket_list[position]);
	if( pos_in_bucket == -1 )
		return 0;
	else 
		return 1;
}

void print_hashtable_bucket(Hashtable *ht, unsigned int pos){
	print_linked_list(ht->bucket_list[pos]);
}

void print_hashtable(Hashtable *ht){
	unsigned int i;

	for( i=0; i < ht->size; i++ )
	{
		print_hashtable_bucket(ht, i);
	}
}

Hashtable* double_size(Hashtable *ht){
	Hashtable *replacement = (Hashtable*) malloc(sizeof(Hashtable));
	int i;
	Node *temp;

	replacement->size = ht->size * 2;
	replacement->bucket_list =(Node**)malloc(replacement->size * sizeof(Node));
	for( i=0; i < replacement->size; i++)
	{
		replacement->bucket_list[i] = NULL;
	}

	for( i=0; i < ht->size; i++ )
	{
		temp = ht->bucket_list[i];
		while( temp != NULL )
		{
			add_element_to_hashtable(replacement, temp->value);
			temp = temp->next;
		}
		delete_list(&ht->bucket_list[i]);
	}

	free(ht->bucket_list);
	free(ht);

	return replacement;


}

Hashtable* half_size(Hashtable *ht){
	Hashtable *replacement = (Hashtable*) malloc(sizeof(Hashtable));
	int i;
	Node *temp;

	if( ht->size % 2 == 1 )
	{
		replacement->size = (ht->size - 1) / 2;
	}
	else
		replacement->size = ht->size / 2;
	
	replacement->bucket_list =(Node**)malloc(replacement->size * sizeof(Node));
	for( i=0; i < replacement->size; i++)
	{
		replacement->bucket_list[i] = NULL;
	}

	for( i=0; i < ht->size; i++ )
	{
		temp = ht->bucket_list[i];
		while( temp != NULL )
		{
			add_element_to_hashtable(replacement, temp->value);
			temp = temp->next;
		}
		delete_list(&ht->bucket_list[i]);
	}

	free(ht->bucket_list);
	free(ht);

	return replacement;
}

/*
List functions
*/

void print_linked_list(Node* list){
	Node* temp;
	if(list == NULL)
		return;

	printf("%s ",list->value);

	temp = list;
	while(temp->next != NULL)
	{
		temp = temp->next;
		printf("%s ",temp->value);
	}
	printf("\n");
}

void add_element_to_list(char *element, Node** list){
	Node *temp,*new;

	if( *list == NULL )
	{
		*list = (Node*) malloc(sizeof(Node));
		(*list)->value = element;
		(*list)->next = NULL;
	}
	else{
		temp = *list;

		if( strcmp(element, temp->value) == 0 )
			return;
		
		while( temp->next != NULL)
		{

			temp = temp->next;

			if( strcmp(element, temp->value) == 0 )
			return;
		}

		new = (Node*) malloc(sizeof(Node));
		new->value = element;
		new->next = NULL;
		temp->next = new; 
	}
}


void delete_list(Node** list){
	Node *temp = *list, *temp2;

	if( temp == NULL )
		return;

	while(temp->next != NULL)
	{

		temp2 = temp;
		temp = temp->next;
		free(temp2);
	}

	free(temp);
	*list = NULL;	
}


void delete_element_from_list(char *element, Node** list){
	Node *temp, *current;
	int pos = list_contains_element(element, list);
	int i;
	temp = *list;

	switch(pos) 
	{

	   case -1 :
	      return;
		
	   case 0  :
	      if( temp->next == NULL )
	      {
	      	free(temp);
	      	*list = NULL;
	      }
	      else
	      {
	      	*list = (*list)->next;
	      	free(temp);

	      }

	      break;

	    default :
	    	i = pos;
	    	current = temp->next;
	    	while( i > 1 )
	    	{
	    		temp = temp->next;
	    		current = temp->next;
	    		i--;
	    	}

	    	temp->next = current->next;
	    	free(current);

	    	break;

	}
}

int list_contains_element(char *element, Node** list){
	Node *temp = *list;
	int i=0;

	if( temp == NULL )
		return -1;

	while( temp->next != NULL )
	{
		if( strcmp(element, temp->value) == 0)
		{
			return i;
		}
		i++;
		temp = temp->next;
	}

	if( strcmp(element, temp->value) == 0)
		{
			return i;
		}

	return -1;
}


void run(Hashtable** ht){

	add_element_to_hashtable(*ht, "Test");
	print_hashtable(*ht);
	add_element_to_hashtable(*ht, "Test"); 
	add_element_to_hashtable(*ht, "rece");
	print_hashtable(*ht);
	if( hashtable_contains_element(*ht, "rece") == 1)
		printf("da contine elementul rece\n");
	else
		printf("nu contine elementul rece\n");

	*ht = double_size(*ht);
	*ht = half_size(*ht);
	print_hashtable(*ht);
	empty_hashtable(*ht);
	

}


int main()
{	
	Hashtable *ht = initialisation_hashtable(10);
	run(&ht);

	

	free(ht->bucket_list);
	free(ht);
	return 0;
}