#include "pipex.h"

void	print_file(int fd)
{
	char	buf[1000];

	if(read(fd, buf, 999) == -1)
		write(2, "error\n", 8);
	write(2, buf, 999);
}


int	permission_denied(char *command)
{
	char	*error[2];

	error[0] = ft_strjoin("pipex: ", command);
	error[1] = ft_strjoin(error[0], ": permission denied");
	ft_putendl_fd(error[1], 2);
	free(error[0]);
	free(error[1]);
	exit(126);
}

int	command_not_found(char *command)
{
	char	*error[2];

	error[0] = ft_strjoin("pipex: ", command);
	error[1] = ft_strjoin(error[0], ": command not found");
	ft_putendl_fd(error[1], 2);
	free(error[0]);
	free(error[1]);
	exit(127);
}

char *find_path(char *command, char **envp)
{
	char	*envp_path;
	char	**paths;
	char	*cmd_path;
	char	*cmd;

	envp_path = NULL;
	if (!access(command, F_OK))
		return (command);
	while (*envp && !envp_path)
	{
		if (ft_strnstr(*envp, "PATH", 4))
			envp_path = ft_substr(*envp, 5, ft_strlen(*envp)- 5);
		envp++;
	}
	paths = ft_split(envp_path, ':');
	cmd = ft_strjoin("/", command);
	while (*paths)
	{
		cmd_path = ft_strjoin(*paths, cmd);
		if (!access(cmd_path, F_OK))
			break ;
		paths++;
		free(cmd_path);
	}
	free(cmd);
	return (cmd_path);
}

int	test_quote(char *command)
{
	if (ft_strchr(command, 34) 
			&& (ft_strchr(command, 34) < ft_strchr(command, 39)
				|| !ft_strchr(command, 39)))
		return (34);
	else
		return (39);
}

char **test_space(char **ret)
{
	int		i;
	int		y;
	char	*sh;
	char	*fr_ret;

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
				fr_ret = ret[y - 1];
				ret[y - 1] = ft_strjoin(ret[y - 1], "\\ ");
				free(fr_ret);
				fr_ret = ret[y - 1];
				ret[y - 1] = ft_strjoin(ret[y - 1], ret[y]);
				free(fr_ret);
				y--;
			}
			while (ret[++y])
			{
				ret[y] = ret[i + y];
			}
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
				if (tmp)
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
	int	test2;

	sh = ft_strnstr(command, ".sh", ft_strlen(command));
	test1 = ft_strnstr(command, "./", 3);
	test2 = ft_strchr(command, '/')
				&& ft_strchr(command, '/') < sh ? 1 : 0;
	if (sh && !test1 && !test2)
		command_not_found(command);
	else if (sh)
		command = test_ech(command);
	return (command);
}

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
				ret[i] = ret[i] + 1;
				ret[i][ft_strlen(ret[i]) - 1] = 0;
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
	/*while (*test)
	{
		printf("%s\n", *test);
		test++;
	}*/
	path = find_path(args[0], envp);
	if (!access(path, F_OK) && access(path, X_OK))
		permission_denied(command);
	else if (access(path, X_OK))
		command_not_found(command);
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
