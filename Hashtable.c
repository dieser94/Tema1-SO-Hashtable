#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashtable.h"

void print_linked_list(Node* list){
	Node* temp;
	if(list == NULL)
		return;

	printf("%s ",list->value);

	temp = list;
	while(temp->next != NULL){
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





int main()
{	
	int i;
	Node** list = (Node**) malloc(10 * sizeof(Node*));
	for(i=0; i < 10; i++)
		list[i] = NULL;

	add_element_to_list("Test", list);
	add_element_to_list("Test", list);
	add_element_to_list("Test2", list);
	print_linked_list((*list));
	delete_element_from_list("Test", list);
	print_linked_list((*list));
	delete_list(list);
	printf("\n");
	print_linked_list((*list));
	free(list);

	return 0;
}