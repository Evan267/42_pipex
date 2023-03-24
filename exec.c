/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:31:38 by eberger           #+#    #+#             */
/*   Updated: 2023/03/24 16:46:40 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**split_command(char *command)
{
	char	*c;
	char	**ret;
	int		i;
	int		y;
	char	*c_ret;
	int		r;

	command = test_sh(command);
	r = test_quote(command);
	c = ft_strchr(command, r);
	ret = ft_split(command, ' ');
	ret = test_space(ret);
	if (c && ft_strchr(command, ' '))
	{
		i = 0;
		y = 0;
		while (ret[i] && !c_ret)
		{
			c_ret = ft_strchr(ret[i], r);
			if (c_ret 
					&& (!ft_strchr(c_ret + 1, r) 
					|| *(ft_strchr(c_ret + 1, r) - 1) == '\\'))
			{
				y++;
				while (!ft_strchr(ret[i + y], r) 
						|| *(ft_strchr(ret[i + y], r) - 1) == '\\')
				{
					c = ret[i];
					ret[i] = ft_strjoin(ret[i], " ");
					free(c);
					c = ret[i];
					ret[i] = ft_strjoin(ret[i], ret[i + y]);
					free(c);
					y++;
				}
				c = ret[i];
				ret[i] = ft_strjoin(ret[i], " ");
				free(c);
				c = ret[i];
				ret[i] = ft_strjoin(ret[i], ret[i + y]);
				free(c);
				c = ret[i];
				if (r == 34)
					ret[i] = ft_strtrim(ret[i], "\"");
				else if (r == 39)
					ret[i] = ft_strtrim(ret[i], "\'");
				free(c);
				ret[i] = test_ech(ret[i]);
				while (ret[++i])
					ret[i] = ret[i + y];
			}
			else if (c_ret)
			{
				ret[i] = ret[i] + 1;
				ret[i][ft_strlen(ret[i]) - 1] = 0;
			}
			i++;
		}
	}
	return (ret);
}

int	close_all(int in, int out, int **pipes, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (i != in)
			close(pipes[i][0]);
		if (i != out)
			close(pipes[i][1]);
		i++;
	}
	return (1);
}

void	exec(char *command, char **envp, int *num, int **fd)
{
	char	*path;
	char	**args;
	char **test;

	args = split_command(command);
	test = args;
	path = ft_path(args, envp);
	if (num[0] == 1)
	{
		close_all(-1, num[3], fd, num[4]);
		if (dup2(num[1], STDIN_FILENO) == -1)
			exit(0);
		if (dup2(fd[num[3]][1], STDOUT_FILENO) == -1)
			exit(0);
	}
	if (num[0] == 3)
	{
		close_all(num[3] - 1, -1, fd, num[4]);
		if (dup2(fd[num[3] - 1][0], STDIN_FILENO) == -1)
			exit(0);
		if (dup2(num[2], STDOUT_FILENO) == -1)
			exit(0);	
	}
	if (num[0] == 2)
	{
		close_all(num[3] - 1, num[3], fd, num[4]);
		if (dup2(fd[num[3] - 1][0], STDIN_FILENO) == -1)
			exit(0);
		if (dup2(fd[num[3]][1], STDOUT_FILENO) == -1)
			exit(0);
	}
	if (execve(path, args, envp) == -1)
	{
		perror("execve");
		exit(127);
	}
}
