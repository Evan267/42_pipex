#include "pipex.h"

char *find_path(char *command, char **envp)
{
	char	*envp_path;
	char	**paths;
	char	*cmd_path;
	char	*cmd;

	//Renvoyer une erreure si aucune commande ne correspond 
	envp_path = NULL;
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

void	exec(char *command, char **envp, int *num, int *fd)
{
	char	*path;
	char	**args;

	args = ft_split(command, ' ');
	path = find_path(args[0], envp);
	if (!path)
	{
		perror("Error: Commande introuvable");
		exit(127);
	}
	if (num[0] == 3 || num[0] == 2)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
	if (num[0] == 2)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(127);
		}
	}
	if (num[0] == 1 || num[0] == 2)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
	}
	if (num[0] == 3)
		dup2(num[1], STDOUT_FILENO);
	if (execve(path, args, envp) == -1)
	{
		perror("execve");
		exit(127);
	}
	//free l'espace allouer
}
