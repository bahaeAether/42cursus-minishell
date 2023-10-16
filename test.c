#include "execution.h"

// test access function
int main(void)
{
	char *path = "../main";
	printf("access: %d\n", access(path, F_OK));
}
