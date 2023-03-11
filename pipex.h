#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

void	test(int argc, char *argv[], int *fd);
void	exec(char *command, char **envp, int *num, int *fd);

#endif
