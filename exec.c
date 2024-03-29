/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:31:38 by eberger           #+#    #+#             */
/*   Updated: 2023/03/28 14:57:35 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	split_quote(int *i, char **ret, char *c_ret)
{
	char	trim[2];

	trim[0] = i[2];
	trim[1] = 0;
	if (c_ret && (!ft_strchr(c_ret + 1, i[2])
			|| *(ft_strchr(c_ret + 1, i[2]) - 1) == '\\'))
	{
		i[1]++;
		while (!ft_strchr(ret[i[0] + i[1]], i[2])
			|| *(ft_strchr(ret[i[0] + i[1]], i[2]) - 1) == '\\')
		{
			ret[i[0]] = join_3_str(ret[i[0]], " ", ret[i[0] + i[1]]);
			i[1]++;
		}
		ret[i[0]] = join_3_str(ret[i[0]], " ", ret[i[0] + i[1]]);
		trim_by_char(&(ret[i[0]]), (char)i[2]);
		ret[i[0]] = test_ech(ret[i[0]]);
		while (ret[++(i[0])])
		{
			free(ret[i[0]]);
			ret[i[0]] = ret[i[0] + i[1]];
		}
	}
	else if (c_ret)
		trim_by_char(&(ret[i[0]]), (char)i[2]);
}

char	**split_command(char *command)
{
	char	**ret;
	int		i[3];
	char	*c_ret;

	command = test_sh(command);
	i[2] = test_quote(command);
	ret = ft_split(command, ' ');
	ret = test_space(ret);
	if (ft_strchr(command, i[2]) && ft_strchr(command, ' '))
	{
		i[0] = 0;
		i[1] = 0;
		while (ret[i[0]] && !c_ret)
		{
			c_ret = ft_strchr(ret[i[0]], i[2]);
			split_quote(i, ret, c_ret);
			i[0]++;
		}
	}
	return (ret);
}

int	close_all(int **pipes, int *num)
{
	int	i;

	i = 0;
	while (i < num[5] - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	close(num[1]);
	close(num[2]);
	return (1);
}

void	dup_in_out(int in, int out)
{
	if (dup2(in, STDIN_FILENO) == -1)
		exit(0);
	if (dup2(out, STDOUT_FILENO) == -1)
		exit(0);
}

void	exec(char *command, char **envp, int *num, int **pipes)
{
	char	*path;
	char	**args;

	args = split_command(command);
	path = ft_path(args, envp);
	if (num[0] == 1)
	{
		dup_in_out(num[1], pipes[num[3]][1]);
		close_all(pipes, num);
	}
	if (num[0] == 3)
	{
		dup_in_out(pipes[num[3] - 1][0], num[2]);
		close_all(pipes, num);
	}
	if (num[0] == 2)
	{
		dup_in_out(pipes[num[3] - 1][0], pipes[num[3]][1]);
		close_all(pipes, num);
	}
	if (execve(path, args, envp) == -1)
	{
		perror("execve");
		exit(127);
	}
}
