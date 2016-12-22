#include "my_ls.h"

int main(int argc, char* argv[])
{
	if (argv[1] != NULL)
		do_ls(argv[1]);	
	else
		do_ls(".");
	return 0;
}
