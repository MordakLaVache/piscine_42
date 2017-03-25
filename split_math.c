
#include <stdlib.h>

#include "split_math.h"
#include "npi.h"

char *split_math_strncpy (char* src, int n);
void split_math_set_numeric_chain(char *str, void(*f)(char*));
void split_math(char *str, void(*f)(char*));

char *split_math_strncpy (char* src, int n)
{
	char *dest;
	int i;
	
	dest = malloc((n+1) * sizeof(char));
	dest[n] = 0x00;
	
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

void split_math_set_numeric_chain(char *str, void(*f)(char*))								
{
	char *output;
	int size;
	
	size = 0;
	
	if (str[size] == '-' || str[size] == '+')
		size++;
		
	while (str[size] && str[size] <= '9' && str[size] >= '0')
		size++;
	
	f(output = split_math_strncpy(str,size));
	free(output);
}

int split_math_set_op_chain(char *str, int *op_founded, void(*f)(char*))
{
	char *output;

	if (*str == '-' || *str == '+')
	{
		if (*op_founded == 1)												
		{
			split_math_set_numeric_chain(str,f);
			return(1);
		}
	}
	if (!(*str == '(' || *str == ')'))											
		*op_founded = 1;

	output = malloc (2 * sizeof(char));
	output[0] = *str;
	output[1] = 0x00;

	f(output);
	free(output);
	return(0);
}

void split_math(char *str, void(*f)(char*))
{
	int i;
	int trigger;
	int op_founded;
	
	char charset_op[] = OPERATORS;
	char charset_nb[] = NUMBERS;
	
	trigger = 0;
	op_founded = 1;
	
	while (*str)
	{
		i = 0;
		while (charset_op[i])
		{
			if (*str == charset_op[i++])
			{
				trigger = split_math_set_op_chain(str,&op_founded,f);
				break;
			}
		}
		i = 0;
		while (charset_nb[i])
		{
			if (*str == charset_nb[i++])
			{	
				if (trigger == 0)														
				{
					split_math_set_numeric_chain(str,f);				
					trigger = 1;
				}	
				op_founded = 0;
				break;
			}
		} 		
		str++;
	}
}
