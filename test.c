#include "pipex.h"

void	open_files(int argc, char *argv[], int *fd)
{
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
	{
		perror("open");
		exit(0);
	}
	fd[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd[1] == -1)
	{
		perror("open");
		exit(0);
	}
}

void	test(int argc, char *argv[], int *fd)
{
	if (argc < 4)
	{
		perror("Erreur : nombre d'arguments insuffisant");
		exit(127);
	}
	open_files(argc, argv, fd);
}
