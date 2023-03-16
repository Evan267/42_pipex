#include "pipex.h"

char *find_path(char *command, char **envp)
{
	char	*envp_path;
	char	**paths;
	char	*cmd_path;
	char	*cmd;

	envp_path = NULL;
	if (!access(command, X_OK))
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
		if (!access(cmd_path, X_OK))
			break ;
		paths++;
		free(cmd_path);
	}
	free(cmd);
	return (cmd_path);
}

int	test_quote(char *command)
{
	if (ft_strchr(command, 34))
		return (34);
	else
		return (39);
}

char	**split_command(char *command)
{
	char	*c;
	char	**ret;
	int		i;
	int		y;
	char	*c_ret;
	int		r;

	r = test_quote(command);
	c = ft_strchr(command, r);
	if (c)
	{
		ret = ft_split(command, ' ');
		i = 0;
		y = 0;
		while (ret[i] && !c_ret)
		{
			c_ret = ft_strchr(ret[i], r);
			if (c_ret)
			{
				y++;
				while (!ft_strchr(ret[i + y], r))
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
				while (ret[++i])
					ret[i] = ret[i + y];
			}
			i++;
		}
		return (ret);
	}
	return (ft_split(command, ' '));
}

void	exec(char *command, char **envp, int *num, int **fd)
{
	char	*path;
	char	**args;
	char	**test;
   
	args = split_command(command);
	test = args;
	path = find_path(args[0], envp);
	if (num[0] == 1)
	{
		if (dup2(num[1], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(0);
		}
		close(fd[0][0]);
		if (dup2(fd[0][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(0);
		}
	}
	if (num[0] == 3)
	{
		close(fd[num[3] - 1][1]);
		if (dup2(fd[num[3] - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(0);
		}
		if (dup2(num[2], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(0);	
		}
	}
	if (num[0] == 2)
	{
		close(fd[num[3] - 1][1]);
		dup2(fd[num[3] - 1][0], STDIN_FILENO);
		close(fd[0][0]);
		dup2(fd[0][1], STDOUT_FILENO);
		
	}
	if (execve(path, args, envp) == -1)
	{
		perror("execve");
		exit(127);
	}
	//free l'espace allouer
	free(path);
}
