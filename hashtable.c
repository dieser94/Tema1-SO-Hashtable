#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#include "hash.h"

Hashtable* initialisation_hashtable(unsigned int size){
	int i;
	
	struct Hashtable  *hash_t = (Hashtable*) malloc(sizeof(Hashtable));

	if( hash_t == NULL )
		return NULL;
	
	hash_t->bucket_list = (Node**) malloc(size * sizeof(Node*));

	if( hash_t->bucket_list == NULL )
	{	
		free(hash_t);
		return NULL;
	}

	for( i=0; i < size; i++)
	{
		hash_t->bucket_list[i] = NULL;
	}
	
	hash_t->size = size;
	return hash_t;
}

int add_element_to_hashtable(Hashtable *ht, char* element){
	int ret;
	unsigned int position = hash(element, ht->size);
	ret = add_element_to_list(element, &ht->bucket_list[position]);
	return ret;
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

int print_hashtable_bucket(Hashtable *ht, unsigned int pos, FILE *f){
	int ret_print;
	ret_print = print_linked_list(ht->bucket_list[pos],f);
	
	return ret_print;
}

int print_hashtable(Hashtable *ht, FILE *f){
	unsigned int i;
	int ret_print;
	for( i=0; i < ht->size; i++ )
	{
		ret_print = print_hashtable_bucket(ht, i, f);
		if( ret_print == -1 )
			return -1;
	}
	return 0;
}

Hashtable* double_size(Hashtable *ht){
	Hashtable *replacement = (Hashtable*) malloc(sizeof(Hashtable));
	if( replacement == NULL )
		return NULL;
	
	int i, add_ret;
	Node *temp;

	replacement->size = ht->size * 2;
	replacement->bucket_list =(Node**)malloc(replacement->size * sizeof(Node));
	if( replacement->bucket_list == NULL )
	{	
		free(replacement);
		return NULL;
	}

	for( i=0; i < replacement->size; i++)
	{
		replacement->bucket_list[i] = NULL;
	}

	for( i=0; i < ht->size; i++ )
	{
		temp = ht->bucket_list[i];
		while( temp != NULL )
		{
			add_ret = add_element_to_hashtable(replacement, temp->value);
			
			if( add_ret == -1 )
			{	
				free(replacement->bucket_list);
				free(replacement);
				return NULL;
			}
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
	if( replacement == NULL )
		return NULL;
	int i, add_ret;
	Node *temp;

	if( ht->size % 2 == 1 )
	{
		replacement->size = (ht->size - 1) / 2;
	}
	else
		replacement->size = ht->size / 2;
	
	replacement->bucket_list =(Node**)malloc(replacement->size * sizeof(Node));
	if( replacement->bucket_list == NULL )
	{	
		free(replacement);
		return NULL;
	}

	for( i=0; i < replacement->size; i++)
	{
		replacement->bucket_list[i] = NULL;
	}

	for( i=0; i < ht->size; i++ )
	{
		temp = ht->bucket_list[i];
		while( temp != NULL )
		{
			add_ret = add_element_to_hashtable(replacement, temp->value);
			
			if( add_ret == -1 )
			{	
				free(replacement->bucket_list);
				free(replacement);
				return NULL;
			}
			
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

int print_linked_list(Node* list, FILE *f){
	if(list == NULL)
		return;
	
	if( fprintf(f, "%s ",list->value) < 0 )
			return -1;

	while(list->next != NULL)
	{
		list = list->next;
		if( fprintf(f, "%s ",list->value) < 0 )
			return -1;
	}
	fprintf(f, "\n");
	
}

int add_element_to_list(char *element, Node** list){
	Node *temp,*new;

	if( *list == NULL )
	{
		*list = (Node*) malloc(sizeof(Node));
		if( *list == NULL )
		{
			fprintf(stderr, "Error adding element to bucket due to memory\n");
			return -1;
		}
		(*list)->value = (char*) malloc( (strlen(element) + 1) * sizeof(char));
		strcpy((*list)->value, element);
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
		if( new == NULL )
		{	
			free(*list);
			fprintf(stderr, "Error allocating memory\n");
			return -1;
		}
		new->value = (char*) malloc( (strlen(element) + 1)  * sizeof(char));
		strcpy(new->value, element);
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
		free(temp2->value);
		free(temp2);
	}
	free(temp->value);
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
	      	free(temp->value);
	      	free(temp);
	      	*list = NULL;
	      }
	      else
	      {
	      	*list = (*list)->next;
	      	free(temp->value);
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
	    	free(current->value);
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


/*
int main()
{
	Hashtable *ht;
	ht = initialisation_hashtable(10);
	add_element_to_hashtable(ht,"temple");
	add_element_to_hashtable(ht,"gulbrand");
	print_hashtable(ht,stdout);
	empty_hashtable(ht);
	free(ht->bucket_list);
	free(ht);

	return 0;
}

*/