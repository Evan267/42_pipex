#include "pipex.h"

void	ft_number(int i, int ncmd, int *fd, int *ret)
{
	ret[1] = fd[0];
	ret[2] = fd[1];
	ret[3] = i;
	ret[4] = ncmd - 1;
	if (i == 0 && i != ncmd)
		ret[0] = 1;
	else if (i != 0 && i == ncmd - 1)
		ret[0] = 3;
	else if (i > 0 && i < ncmd)
		ret[0] = 2;
	else
		ret[0] = 4;
}

int	open_files(char *argv[], int argc, int *fd)
{
	if (fd[0] == -2)
		fd[1] = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd[1] = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd[1] == -1)
	{
		perror("pipex: output");
		exit(1);
	}
	if  (fd[0] == -2)
	{
		fd[0] = open(argv[1], O_RDONLY, 0);
		if (fd[0] == -1)
			perror("pipex: input");
	}
	return (1);
}

int	main(int argc, char *argv[], char **envp)
{
	int		i;
	int		y;
	int		status;
	int		ncom;
	pid_t	*pid;
	int		**pipes;
	int		fd[2];
	int		ret[5];

	i = 0;
	test(argc);
	fd[0] = -2;
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
	{
		ncom = argc - 4;
		y = 3;
	}
	else
	{
		ncom = argc - 3;
		y = 2;
	}
	pipes = malloc(sizeof(int *) * ncom - 1);
	while (i < ncom - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		i++;
	}
	pid = malloc(sizeof(pid_t) * ncom);
	if (ncom == argc - 4)
		fd[0] = here_doc(argv[2]);
	open_files(argv, argc, fd);
	i = 0;
	while (i < ncom - 1)
	{
		if (pipe(pipes[i]) == -1) 
		{	
			perror("pipe");
			exit(127);
		}
		i++;
	}
	i = 0;
	while (i < ncom)
	{
		pid[i] = fork();
		if (pid[i] == -1) {
			perror("fork");
			exit(127);
		}
		else if (pid[i] == 0) {
			ft_number(i, ncom, fd, ret);
			exec(argv[i + y], envp, ret, pipes);
		}
		i++;
	}
	i = 0;
	while (i < ncom - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < ncom - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
	i = 0;
	while (i < ncom)
	{
		pid[i] = waitpid(pid[i], &status, 0);
		i++;
	}
	free(pid);
	return (WEXITSTATUS(status));
}
