
#ifndef __LIST_H__
#define __LIST_H__
typedef struct		s_list		
{
	struct s_list	*next;
	char			data;
	int				value;
}					t_list;

t_list *create_list_elem(char data, int value);
void 	push_list	(t_list **begin_list, char data);				// mechanisme de pile PUSH
char 	pop_list	(t_list **begin_list);							// mechanisme de pile POP
void 	put_list	(t_list **begin_list, char data, int value);	// Ajout fond de liste. 
void 	ft_list_merge(t_list **begin_list1, t_list *begin_list2);   // concatene deux listes

int 	search_operator (t_list *begin_list);
int 	extract_value 		(t_list *begin_list, int n);
char	extract_operator 	(t_list *begin_list, int n);
void 	replace_value		(t_list *begin_list, int n, int value);
void 	cut_two_chains		(t_list *begin_list, int n);

void 	explore_list_int(t_list *begin_list);						// permet d'afficher les listes.
#endif
