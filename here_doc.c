/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:30:35 by eberger           #+#    #+#             */
/*   Updated: 2023/03/24 16:30:38 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_here_doc(int *pipes, char *limiter)
{
	char	*tmp;

	close(pipes[0]);
	tmp = get_next_line(0);
	while (ft_strncmp(limiter, tmp, ft_strlen(tmp) - 1)
			|| ft_strlen(limiter) > ft_strlen(tmp) - 1)
	{
		ft_putstr_fd(tmp, pipes[1]);
		free(tmp);
		tmp = get_next_line(0);
	}
	free(tmp);
	exit(0);
}

int	here_doc(char *limiter)
{
	int		pipes[2];
	pid_t	pid;
	int		status;

	if (pipe(pipes) == -1) 
	{	
		perror("pipe");
		exit(127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("pipe");
		exit(127);
	}
	else if (pid == 0)
		child_here_doc(pipes, limiter);
	waitpid(pid, &status, 0);
	close(pipes[1]);
	return (pipes[0]);
}
