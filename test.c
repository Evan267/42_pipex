#include "pipex.h"

void	test(int argc)
{
	if (argc < 5)
	{
		perror("Erreur : nombre d'arguments insuffisant");
		exit(127);
	}
}
