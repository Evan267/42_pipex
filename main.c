/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:55:25 by eberger           #+#    #+#             */
/*   Updated: 2023/03/27 17:11:07 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_number(int i, int ncmd, int *ret)
{
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

int	open_files(char *argv[], int argc, int *num)
{
	if (num[1] == -2)
		num[2] = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		num[2] = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (num[2] == -1)
	{
		perror("pipex: output");
		exit(1);
	}
	if (num[1] == -2)
	{
		num[1] = open(argv[1], O_RDONLY, 0);
		if (num[1] == -1)
			perror("pipex: input");
	}
	return (1);
}

int	**create_pipes(int argc, char **argv, int *num)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * num[5] - 1);
	while (i < num[5] - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		i++;
	}
	if (num[5] == argc - 4)
		num[1] = here_doc(argv[2]);
	open_files(argv, argc, num);
	i = 0;
	while (i < num[5] - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(127);
		}
		i++;
	}
	return (pipes);
}

pid_t	*multi_fork(int *num, char **envp, int **pipes, char *argv[])
{
	int		i;
	pid_t	*pid;

	i = 0;
	pid = malloc(sizeof(pid_t) * num[5]);
	while (i < num[5])
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("fork");
			exit(127);
		}
		else if (pid[i] == 0)
		{
			ft_number(i, num[5], num);
			exec(argv[i + num[6]], envp, num, pipes);
		}
		i++;
	}
	return (pid);
}

int	main(int argc, char *argv[], char **envp)
{
	int		i[2];
	int		status;
	pid_t	*pid;
	int		**pipes;
	int		ret[7];

	test(argc, ret, argv);
	pipes = create_pipes(argc, argv, ret);
	pid = multi_fork(ret, envp, pipes, argv);
	close_all(-1, -1, pipes, ret[5] - 1);
	i[0] = 0;
	while (i[0] < ret[5] - 1)
	{
		free(pipes[i[0]]);
		(i[0])++;
	}
	free(pipes);
	i[0] = 0;
	while (i[0] < ret[5])
	{
		pid[i[0]] = waitpid(pid[i[0]], &status, 0);
		(i[0])++;
	}
	free(pid);
	return (WEXITSTATUS(status));
}
