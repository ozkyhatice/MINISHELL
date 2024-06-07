#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	**args;

	args = malloc(sizeof(char *) * 3);
	args[0] = "ls";
	args[1] = "-l";
	args[2] = NULL;


	if (execve("/bin/ls", args, NULL) == -1)
	{
		printf("Oops execve !\n");
	}
	printf("Oops something went wrong !\n");
	system("leaks a.out");
	return (0);
	
}

// 2 while 
// 1. while head in sonuna kadar gitmesi için
// 2. while pipe kadar gitmesi için burda 
// len execnode->**cmd = malloc(len)
// next

