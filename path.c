/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:19:00 by eberger           #+#    #+#             */
/*   Updated: 2023/03/27 15:03:55 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_env_path(char **envp)
{
	char	*envp_path;

	envp_path = NULL;
	while (*envp && !envp_path)
	{
		if (ft_strnstr(*envp, "PATH", 4))
			envp_path = ft_substr(*envp, 5, ft_strlen(*envp) - 5);
		envp++;
	}
	return (envp_path);
}

char	*find_path(char *command, char *envp_path)
{
	char	**paths;
	char	*cmd_path;
	char	*cmd;
	int		i;

	paths = ft_split(envp_path, ':');
	cmd = ft_strjoin("/", command);
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!access(cmd_path, F_OK))
			return (free(cmd), cmd_path);
		i++;
		free(cmd_path);
	}
	free(cmd);
	if (!access(command, F_OK))
		return (command);
	return (NULL);
}

void	fork_whereis(int *pipes, char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(127);
	}
	else if (pid == 0)
	{
		close(pipes[0]);
		if (dup2(pipes[1], STDOUT_FILENO) == -1)
			exit(0);
		execve("/usr/bin/whereis", args, NULL);
	}
	pid = waitpid(pid, &status, 0);
	close(pipes[1]);
}

char	*find_notenv(char *command)
{
	int		pipes[2];
	char	*args[3];
	char	*path;
	char	*ret;

	args[0] = ft_strdup("whereis");
	args[1] = command;
	args[2] = NULL;
	if (pipe(pipes) == -1)
	{	
		perror("pipe");
		exit(127);
	}
	fork_whereis(pipes, args);
	path = get_next_line(pipes[0]);
	if (path)
	{
		ret = ft_strtrim(path, "\n");
		free(path);
	}
	else
		ret = command;
	free(args[0]);
	return (ret);
}

char	*ft_path(char **args, char **envp)
{
	char	*path;
	char	*envp_path;

	envp_path = find_env_path(envp);
	if (envp_path)
		path = find_path(args[0], envp_path);
	else
		path = find_notenv(args[0]);
	if (!access(path, F_OK) && access(path, X_OK))
		permission_denied(args[0]);
	else if (access(path, X_OK))
		command_not_found(args[0]);
	return (path);
}
