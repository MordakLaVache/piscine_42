
#include "split_math.h"
#include "npi.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
		
	init_npi_stacks();
	split_math(argv[1],&fill_npi_stacks);
	
	if (resolve())
		return (0);
		
	return (0);
}