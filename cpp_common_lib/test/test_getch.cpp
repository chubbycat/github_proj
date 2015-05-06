#include <stdio.h>

#include "cupid_common.h"

int main(int argc, char* argv[])
{
	while (true)
	{
		char c = cupid::cupid_getch();
		printf("%d\n", c);
	}

	return 0;
}
