#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "hashtable.h"

#define BUFFER_SIZE 20000
#define MAX_COMMANDS 3

#define usage "Usage:./main hashtable_size (optional) file1.in file2.in ... \n"
#define available_commands "add,remove,find,clear,print,print_bucket,resize"
int isDigit(char d){
	if( d >= '0' && d <= '9' )
		return 1;
	else 
		return 0;
}

int isNumber(char *number){
	int i;
	int size_number = strlen(number);
	int number_digits = 0;

	for( i=0; i < size_number; i++ )
	{
		if( isDigit(number[i]) )
			number_digits++;
	}

	if( number_digits == size_number )
		return 1;
	else 
		return 0;
}

void free_hash(Hashtable *ht){

	empty_hashtable(ht);
	free(ht->bucket_list);
	free(ht);

}

void free_command_buff(char *commands[]){

	int i;
	for( i=0; i < MAX_COMMANDS; i++ )
	{
			free(commands[i]);
	}

}

int execute_command(Hashtable **ht, FILE *f){
		char buffer[BUFFER_SIZE];
		char *commands[MAX_COMMANDS];
		char *command;
		int  i, j, resize1, resize2, find, temp;
		unsigned int pos;
		FILE *a;
		char find_value[5];

		while( fgets(buffer, BUFFER_SIZE, f) != NULL )	
		{	
			
			for( i=0; i < MAX_COMMANDS; i++ )
			{
				commands[i] = NULL;
			}

			command = strtok(buffer, " \r\n");
			j = 0;

			while( command != NULL )
			{
				commands[j] = (char*)malloc((strlen(command)+1)*sizeof(char*));
				if( commands[j] == NULL )
				{
					fprintf(stderr, "Error allocating memory for command\n");
					free_command_buff(commands);
					return -1;
				}

				strcpy(commands[j],command);
				j++;
				command = strtok(NULL, " \r\n");
			}
			
			if( commands[0] != NULL ){

			if( strcmp(commands[0], "add") == 0 )
			{	
				if(commands[1] == NULL)
				{
					fprintf(stderr, "Invalid argument for add\n");
					free_command_buff(commands);
					return -1;
				}
				temp = add_element_to_hashtable(*ht, commands[1]);
				if( temp == -1 )
				{
					free_command_buff(commands);
					return -1;
				}
			}

			else if( strcmp(commands[0], "remove") == 0 )
			{
				delete_element_from_hashtable(*ht, commands[1]);
			}


			else if( strcmp(commands[0], "resize") == 0 )
			{	
				resize1 = strcmp(commands[1], "halve");
				if( resize1 == 0 )
				{	
					*ht = half_size(*ht);
					if( *ht == NULL )
					{
						fprintf(stderr, "Error allocating space\n");
						return -1;
					}
				}
				resize2 = strcmp(commands[1], "double");
				if( resize2 == 0 )
				{
					*ht = double_size(*ht);
					if( *ht == NULL )
					{
						fprintf(stderr, "Error allocating space\n");
						return -1;
					}
				}
				if( resize1 != 0 && resize2 != 0 )
				{
					fprintf(stderr, "Error resize argument (halve/double)\n");
					free_command_buff(commands);
					return -1;
				}

			}


			else if( strcmp(commands[0], "find") == 0 )
			{
				find = hashtable_contains_element(*ht, commands[1]);

				if( find == 1 )
					strcpy(find_value, "True");
				else
					strcpy(find_value, "False");

				if( commands[2] == NULL )
				{
					if( fprintf(stdout, "%s\n", find_value) < 0 )
					{
						free_command_buff(commands);
						fprintf(stderr, "Error printing\n");
						return -1;
					}
				}
				else
				{
					a = fopen(commands[2], "a");
					if( a == NULL )
					{
						fprintf(stderr,"Error openning file %s\n",commands[2]);
						free_command_buff(commands);
						return -1;
					}
					if( fprintf(a, "%s\n", find_value) < 0 )
					{
						free_command_buff(commands);
						fprintf(stderr, "Error printing\n");
						return -1;
					}	
					fclose(a);
				}

				
			}
			else if( strcmp(commands[0], "clear") == 0 )
			{
				empty_hashtable(*ht);
			}
			else if( strcmp(commands[0], "print") == 0 )
			{
				if( commands[1] != NULL )
				{	
					a = fopen(commands[1], "a");
					if( a == NULL )
					{
						fprintf(stderr,"Error openning file %s\n",commands[1]);
						free_command_buff(commands);
						return -1;
					}
					temp = print_hashtable(*ht, a);
					if( temp == -1 )
					{
						fclose(a);
						free_command_buff(commands);
						return -1;
					}
					fclose(a);
				}
				else{
					temp = print_hashtable(*ht, stdout);
					if( temp == -1 )
					{
						free_command_buff(commands);
						return -1;
					}
				}

			}
			else if( strcmp(commands[0], "print_bucket") == 0 )
			{
				if( commands[2] != NULL )
				{	

					if( isNumber(commands[1]) == 1 )	
					{	
						pos = atoi(commands[1]);
						if(  pos  < (*ht)->size )
						{
							a = fopen(commands[2], "a");
							if( a == NULL )
							{
								fprintf(stderr,"Error openning file \n");
								free_command_buff(commands);
								return -1;
							}
							temp = print_hashtable_bucket(*ht, pos , a);
							if(temp == -1 )
							{
								free_command_buff(commands);
								fclose(a);
								return -1;
							}

							fclose(a);
						}
						else
						{
							fprintf(stderr,"print_bucket invalid argument\n");
							free_command_buff(commands);
							return -1;

						}
					}
					else
						{
							fprintf(stderr,"print_bucket arg not number\n");
							free_command_buff(commands);
							return -1;

						}
					
				}
				else{

					if( isNumber(commands[1]) == 1 )	
					{	
						pos = atoi(commands[1]);
						if(  pos  < (*ht)->size )
						{
							temp = print_hashtable_bucket(*ht, pos , stdout);
							if(temp == -1 )
							{
								free_command_buff(commands);
								return -1;
							}
						}
						else
						{
							fprintf(stderr,"print_bucket invalid argument\n");
							free_command_buff(commands);
							return -1;
						}
					}
					else
						{
							fprintf(stderr,"print_bucket arg not number\n");
							free_command_buff(commands);
							return -1;

						}
				}
			}
			else
			{
				fprintf(stderr, "No such available command\n");
				fprintf(stderr, "Commands are : %s\n",available_commands);
				free_command_buff(commands);
				return -1;
			}

		}
					free_command_buff(commands);
		}
		
		return 0;

}

int main(int argc, char *argv[]){
	int i,ret;
	unsigned int hashtable_size;
	Hashtable *ht;
	FILE *f;

	if( argc < 2)
	{
		fprintf(stderr, "Not enough arguments\n%s", usage);
		return -1;
	}


	if( isNumber(argv[1]) != 1 )
	{
		fprintf(stderr, "first argument is not a number or >0\n%s", usage);
		return -1;

	}
	else
		hashtable_size = atoi(argv[1]);
	ht = initialisation_hashtable(hashtable_size);
	if( ht == NULL )
	{
		fprintf(stderr, "Error hashtable initialisation\n");
		return -1;
	}

	if( argc == 2 ){
		ret = execute_command(&ht, stdin);
		if( ret == -1 )
		{	
			free_hash(ht);
			return -1;
		}
	}
	else if( argc > 2)
	{
		i = 2;
		while( i < argc )
		{
			f = fopen(argv[i],"r");

			if( f == NULL )
			{
				fprintf(stderr, "Error openning file %s\n", argv[i]);
				free_hash(ht);
				return -1;
			}

			ret = execute_command(&ht, f);
			if( ret == -1 )
			{	
				free_hash(ht);
				return -1;
			}

			fclose(f);
			i++;
		}
	}

	free_hash(ht);

	return 0;
}