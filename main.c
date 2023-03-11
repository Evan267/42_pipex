#include "pipex.h"

void	ft_number(int i, int argc, char *argv[], int *ret)
{
	ret[1] = 0;
	if (i == 2 && i != argc - 2)
		ret[0] = 1;
	else if (i != 2 && i == argc - 2)
	{
		ret[0] = 3;
		ret[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (ret[1] == -1)
		{
			perror("open");
			exit(0);
		}
	}
	else if (i > 2 && i < argc - 2)
		ret[0] = 2;
	else
	{
		ret[0] = 4;
		ret[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		printf("%s\n", argv[argc - 1]);
		if (ret[1] == -1)
		{
			perror("open");
			exit(0);
		}
	}
}

int	main(int argc, char *argv[], char **envp)
{
	int	i;
	int	status;
	pid_t	pid;
	int		fd[2];
	int	ret[2];

	i = 2;
	//tester les parametre, les 2 fichiers utiliser, etc...
	test(argc, argv, fd);
	//executer les commandes
	
	if (pipe(fd) == -1) {	
		perror("pipe");
		exit(127);
	}

	while (i < argc - 1)
	{	
		pid = fork();
		if (pid == -1) {
			perror("fork");
			exit(127);
		}
		else if (pid == 0) {
			ft_number(i, argc, argv, ret);
			exec(argv[i], envp, ret, fd);
		}
		i++;
	}
	close(fd[0]);
	close(fd[1]);
	pid = wait(&status);
	WIFEXITED(status);
	while (pid > 0)
	{
		pid = wait(&status);
		WIFEXITED(status);
	}
	return (WEXITSTATUS(status));
}
