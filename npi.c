
#include <stdlib.h>

#include "npi.h"
#include "list.h"
#include "split_math.h"
#include "string.h"

int get_priority (char operateur);
int evalue_list (char *str);

static t_list *lifo;
static t_list *fifo;

void init_npi_stacks(void)
{
	lifo = NULL;
	fifo = NULL;
}

int get_priority (char operateur)
{
	if (operateur == '*' || operateur == '/' || operateur == '%')
		return (13);
	else if (operateur == '(' || operateur == ')')
		return (16);
	else
		return (12);
}

int evalue_list (char *str)
{
	char tmp;
	
	if ((*str == '-' || *str == '+') && str[1] != 0x00)
		return (0);
			 			
	if (lifo == NULL)								// -> Si la pile est vide, pousser l'opérateur sur la pile
		push_list(&lifo,*str);
	
	else if (*str == '(')							// -> Si c'est une parenthèse ouvrante, la mettre sur la pile
		push_list(&lifo,'(');	

	else if (lifo->data == '(')						// -> Si le sommet de la pile est une parenthèse ouvrante, pousser l'opérateur sur la pile
		push_list(&lifo,*str);	

	else if (*str == ')')							// -> Si c'est une parenthèse fermante, enlever les opérateurs de la pile et les placer sur le fichier de sortie jusqu'à ce que l'on rencontre la parenthèse ouvrante, que l'on élimine.
	{
		while (lifo && lifo->data != '(')
		{
			tmp = pop_list(&lifo);
			put_list(&fifo,tmp,0);
		}
		tmp = pop_list(&lifo);
	}
	else
	{
		while (lifo && lifo->data != '(' && (get_priority(*str) <= get_priority(lifo->data)))
		{
			tmp = pop_list(&lifo);					
			put_list(&fifo,tmp,0);
		}
		push_list(&lifo,*str);
	}
	return (1);
}

void fill_npi_stacks(char *str)
{
	char charset[] = OPERATORS;
	int i;
	int ret_value;

	ret_value = 0;
	i = 0;
	while (i <= OPERATORS_NBR)
	{
		if (*str == charset[i])
		{
			ret_value = evalue_list(str);
			break;
		} 	
		i++;
	}
	if (!ret_value && ((*str >= '0' && *str <= '9') || *str == '-' || *str == '+'))
		put_list(&fifo,0x00,ft_atoi(str));
}

int resolve(void)
{
	char op;
	int i;
	int j;
	
	ft_list_merge(&fifo, lifo);
		
	while ((op = extract_operator(fifo,(i = search_operator(fifo)))))
	{
		explore_list_int(fifo);
		
		if (op == '+')
			j = extract_value(fifo,i-2)+extract_value(fifo,i-1);
		else if (op == '-')
			j = extract_value(fifo,i-2)-extract_value(fifo,i-1);
		else if (op == '*')
			j = extract_value(fifo,i-2)*extract_value(fifo,i-1);
		else if (op == '/')
			j = extract_value(fifo,i-2)/extract_value(fifo,i-1);
		else
			j = extract_value(fifo,i-2)%extract_value(fifo,i-1);

		replace_value(fifo,i-2,j);	
		cut_two_chains(fifo,i-2);
	}
	explore_list_int(fifo);
	
	return (j);
}

/*
Math:	associativité naturelle symbole Addition && Multiplication				(contrairement à la soustraction, la division ou le modulo)
			associativité à gauche pour tous les symboles addition, soustraction, multiplacation, divison, modulo
 			La multiplication, la division ou le modulo ont toutes une priorité forte de 13
			L'addition et la soustraction n'ont qu'une priorité de 12
			CF --> http://www-verimag.imag.fr/~moy/cours/poly-c/html/node343.html

tant qu’il y a des tokens à lire:
    lire le token.

        si c’est un nombre l’ajouter à la sortie.
        si c'est une fonction, le mettre sur la pile.
        si c'est un séparateur d'arguments de fonction (par exemple une virgule) :

            jusqu'à ce que l'élément au sommet de la pile soit une parenthèse gauche, retirer l'élément du sommet de la pile et l'ajouter à la sortie. Si toute la pile est dépilée sans trouver de parenthèse gauche, 
            c’est qu’il y a un mauvais parenthésage.

        si c’est un opérateur o1 alors

        1) tant qu’il y a un opérateur o2 sur le haut de la pile et si l’une des conditions suivantes est remplie.

                    o1 est associatif ou associatif à gauche et sa priorité est inférieure ou égale à celle d’o2, ou
                    o1 est associatif à droite et sa priorité est inférieure à celle d’o2,

            retirer o2 de la pile pour le mettre dans la sortie

        2) mettre o1 sur la pile

        si le token est une parenthèse gauche, le mettre sur la pile.
        si le token est une parenthèse droite, alors dépiler les opérateurs et les mettre dans la sortie jusqu’à la parenthèse gauche qui elle aussi sera dépilée, mais pas mise dans la sortie. 
        	Après cela, si le token au sommet de la pile est une fonction, le dépiler également pour l'ajouter à la sortie. Si toute la pile est dépilée sans trouver de parenthèse gauche c’est qu’il y a un mauvais parenthésage.
après la lecture du dernier token, s'il reste des éléments dans la pile il faut tous les dépiler pour les mettre dans la sortie (il ne doit y avoir que des opérateurs. 
Si on trouve une parenthèse gauche alors il y a eu un mauvais parenthésage).
CF ---> https://fr.wikipedia.org/wiki/Notation_polonaise_inverse

Tant qu'il y a des tokens en entrée {					// TUDO PARTIELLEMENT FAUX CI-DESSOUS, CELUI DE WIKIPEDIA AU DESSUS EST + JUSTE !

    Examiner le token courant sur le fichier d'entrée
    Si c'est un opérande, le placer sur le fichier de sortie
    Si c'est une parenthèse ouvrante, la mettre sur la pile											OK
    Si c'est un opérateur, alors
        Si la pile est vide, pousser l'opérateur sur la pile										OK		
        Si le sommet de la pile est une parenthèse ouvrante, pousser l'opérateur sur la pile		OK
        Si l'opérateur est prioritaire sur celui au sommet de la pile, pousser l'opérateur sur la pile		
        Sinon, enlever l'opérateur de la pile et le mettre sur le fichier de sortie. Replacer ensuite l'opérateur courant sur la pile
    Si c'est une parenthèse fermante, enlever les opérateurs de la pile et les placer sur le fichier de sortie jusqu'à ce que l'on rencontre la parenthèse ouvrante, que l'on élimine.

}
Enlever tous les opérateurs restants et les placer sur le fichier de sortie.
*/
