
#include <unistd.h>
#include <stdlib.h>

#include "string.h"

void ft_convert_write_string(char *output,int output_string_size, int nbr, int base);

void ft_putchar(char c) 
{
    write (1, &c, 1);
}

void putstr (char *str)
{
	while (*str)
		write(1,str++,1);
}

int	ft_atoi(char *str)
{
    int        nb;
    int        i;
    int        negatif;

    negatif = 0;
    nb = 0;
    i = 0;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        i++;
    if (str[i] == '-')
        negatif = 1;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] >= 48 && str[i] <= 57)
    {
        nb *= 10;
        nb += str[i] - 48;
        i++;
    }
    if (negatif == 1)
        return (-nb);
    else
        return (nb);
}

void ft_convert_write_string(char *output,int output_string_size, int nbr, int base)
{
	int i;
	int j;
	int k;
	
	i = 0;
	while (i < output_string_size)
	{
		j = 1;
		k = 1;
		while (k < (output_string_size-i))
		{
			j *= base;
			k++;
		}
		if ((nbr / j) > 9)
			output[i] = ((nbr / j) + '7');
		else
			output[i] = ((nbr / j) + '0');
		nbr -= j * (nbr / j);
		i++;
	}	
}

char *ft_convert_int_value_to_string_with_another_base(int nbr, int base)
{
	char *output;
	int output_string_size;
	int i;
	
	output_string_size = 1;
	
	if (nbr < 0)
		output_string_size = 2;
	
	i = nbr;
	while (i/base)
	{
		output_string_size++;
		i/=base;
	}	
	output = malloc((output_string_size +1)*sizeof(char));
	
	if (nbr < 0)
	{
		output[0] = '-';
		ft_convert_write_string(output+1,output_string_size-1,-nbr,base);
	}
	else
		ft_convert_write_string(output,output_string_size,nbr,base);

	output[output_string_size] = 0x00;
	return (output);
}
