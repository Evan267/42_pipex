/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:30:47 by eberger           #+#    #+#             */
/*   Updated: 2023/03/28 14:58:19 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

void	exec(char *command, char **envp, int *num, int **fd);
int		open_files(char *argv[], int argc, int *num);
char	*test_command(char *command);

int		command_not_found(char *command);
int		permission_denied(char *command);
int		close_all(int **pipes, int *num);

void	test(int argc, int *ret, char **argv);
int		test_quote(char *command);
char	**test_space(char **ret);
char	*test_ech(char *command);
char	*test_sh(char *command);

char	*find_env_path(char **envp);
char	*find_path(char *command, char *envp_path);
char	*find_notenv(char *command);
char	*ft_path(char **args, char **envp);

int		here_doc(char *limiter);

char	*join_3_str(char *str1, char *str2, char *str3);
void	trim_by_char(char **ret, char c);

#endif
