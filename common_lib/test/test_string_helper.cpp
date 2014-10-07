#include <stdio.h>

#include "cupid_common.h"

int main(int argc, char* argv[])
{
	std::string s = "12a";
	if (cupid::is_digits(s))
	{
		printf("all digits\n");
	}
	else
	{
		printf("NOT all digits\n");
	}

	return 0;
}
