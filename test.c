/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:18:10 by eberger           #+#    #+#             */
/*   Updated: 2023/03/27 17:01:19 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	test_quote(char *command)
{
	if (ft_strchr(command, 34)
		&& (ft_strchr(command, 34) < ft_strchr(command, 39)
			|| !ft_strchr(command, 39)))
		return (34);
	else
		return (39);
}

char	**test_space(char **ret)
{
	int		i;
	int		y;
	char	*sh;

	i = 1;
	sh = NULL;
	while (ret[i] && !sh)
	{
		sh = ft_strnstr(ret[i], ".sh", ft_strlen(ret[i]));
		if (sh)
		{
			y = i;
			while (y > 0)
			{
				ret[y - 1] = join_3_str(ret[y - 1], "\\ ", ret[y]);
				y--;
			}
			while (ret[++y])
				ret[y] = ret[i + y];
		}
		i++;
	}
	return (ret);
}

char	*test_ech(char *command)
{
	char	**split;
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = NULL;
	if (ft_strnstr(command, "\\", ft_strlen(command)))
	{
		split = ft_split(command, '\\');
		while (split[i])
		{
			if (!ret)
				ret = ft_strdup(split[i]);
			else
			{
				tmp = ret;
				ret = ft_strjoin(ret, split[i]);
				free(tmp);
			}
			i++;
		}
		command = ret;
	}
	return (command);
}

char	*test_sh(char *command)
{
	char	*sh;
	char	*test1;
	int		test2;

	sh = ft_strnstr(command, ".sh", ft_strlen(command));
	test1 = ft_strnstr(command, "./", 3);
	test2 = 0;
	if (ft_strchr(command, '/')
		&& ft_strchr(command, '/') < sh)
		test2 = 1;
	if (sh && !test1 && !test2)
		command_not_found(command);
	else if (sh)
		command = test_ech(command);
	return (command);
}

void	test(int argc, int *ret, char **argv)
{
	ret[1] = -2;
	if (argc < 5)
	{
		perror("Erreur : nombre d'arguments insuffisant");
		exit(127);
	}
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
	{
		ret[5] = argc - 4;
		ret[6] = 3;
	}
	else
	{
		ret[5] = argc - 3;
		ret[6] = 2;
	}
}
