
#ifndef __NPI_H__
#define __NPI_H__

#define NUMBERS			"0123456789"
#define OPERATORS		"+-*/%()"
#define OPERATORS_NBR	7

void init_npi_stacks(void);
void fill_npi_stacks(char *str);
int resolve(void);

#endif

