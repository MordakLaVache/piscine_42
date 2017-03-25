
#include <stdlib.h>

#include "list.h"
#include "string.h"

t_list *create_list_elem(char data, int value)
{
	t_list *output;

	output = malloc(sizeof(t_list));
	if (output)
	{
		output->value = value;
		output->data = data;
		output->next = NULL;
	}
	return (output);
}

void put_list(t_list **begin_list, char data, int value)
{	
	t_list *list;
	
	list = *begin_list;
	if (list)
	{
		while(list->next)
			list = list->next;
		list->next = create_list_elem(data,value);
	}
	else
		*begin_list = create_list_elem(data,value);
}

void push_list(t_list **begin_list, char data)
{
   t_list *list;

   list = *begin_list;

   if(list)
   {
       list = create_list_elem(data,0);
       list->next = *begin_list;
       *begin_list = list;
   }
   else
       *begin_list = create_list_elem(data,0);
}

char pop_list (t_list **begin_list)
{
	char data;
	t_list *list;
	
	list = *begin_list;
	
	if (!list)
		return (0x00);
	
	data = list->data;
	
	*begin_list = list->next;
	free(list);
	
	return (data);
}

void ft_list_merge(t_list **begin_list1, t_list *begin_list2)
{
	t_list *list_ptr;
	
	list_ptr = *begin_list1;
	
	if (! list_ptr)
		return;
	
	while (list_ptr->next)
		list_ptr = list_ptr->next;

	if (begin_list2)			
		list_ptr->next = begin_list2;
}

int search_operator (t_list *begin_list)
{
	int i;
	
	i = 0;
	
	while (begin_list)
	{
		if (begin_list->data != 0x00)
			return (i);
		begin_list = begin_list->next;
		i++;
	}
	return (0);
}

int extract_value 		(t_list *begin_list, int n)
{
	int i;
	
	i = 0;

	while (i < n)
	{
		begin_list = begin_list->next;
		i++;
	}
	return (begin_list->value);
}

char extract_operator 	(t_list *begin_list, int n)
{
	int i;
	
	i = 0;

	while (i < n)
	{
		begin_list = begin_list->next;
		i++;
	}
	return (begin_list->data);
}

void replace_value (t_list *begin_list, int n, int value)
{
	int i;
	
	i = 0;

	while (i < n)
	{
		begin_list = begin_list->next;
		i++;
	}
	begin_list->value = value;
}

void cut_two_chains (t_list *begin_list, int n)
{
	int i;
	t_list *front;
	
	i = 0;
	
	while (i < n)
	{
		begin_list = begin_list->next;
		i++;
	}
	
	front = begin_list->next->next;
	
	begin_list->next = front->next;
}

void explore_list_int(t_list *begin_list)
{
	while (begin_list)
	{
		if (begin_list->data)
		{
			ft_putchar(begin_list->data);
			ft_putchar(' ');
		}
		else
		{
			putstr(ft_convert_int_value_to_string_with_another_base(begin_list->value, 10));
			ft_putchar(' ');
		}
		begin_list = begin_list->next;
	}
	ft_putchar('\n');
}

