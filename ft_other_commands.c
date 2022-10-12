/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmeoli <gmeoli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:29:07 by masebast          #+#    #+#             */
/*   Updated: 2022/10/12 15:55:10 by gmeoli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_sub_process(t_command *command_struct, char **envp)
{
	if (execve(command_struct->word_matrix[0], command_struct->word_matrix, envp) != 0)
	{
		write(2, "minishell: ", 11);  
		write(2, command_struct->word_matrix[0], ft_strlen(command_struct->word_matrix[0]));
		write(2, ": No such file or directory\n", 28);
	}
}

void	ft_child(t_command *command_struct, char **envp)
{
	int		index;
	char	*path;
	char	**mypath;
	
	path = getenv("PATH");
	mypath = ft_split(path, ':');
	index = -1;
	while (mypath[++index])
		mypath[index] = ft_strjoin(mypath[index], "/");
	index = 0;
	while (mypath[index])
	{
		path = ft_strjoin(mypath[index], command_struct->word_matrix[0]);
		if (access(path, R_OK) == 0)
			execve(path, command_struct->word_matrix, envp);
		else if (strncmp(command_struct->word_matrix[0], "./", 2) == 0)
		{
			ft_execute_sub_process(command_struct, envp);
			break ;
		}
		else if (access(path, R_OK) != 0)
		{
			*g_exit_status = 127;
			write(2, "minishell: ", 11);
			write(2, command_struct->word_matrix[0], ft_strlen(command_struct->word_matrix[0]));
			write(2, ": command not found\n", 20);
			break ;
		}
		else
			execve(command_struct->word_matrix[0], command_struct->word_matrix, envp);
		index++;
		free(path);
	}
	exit(1);
}

int	ft_other_commands(t_command *command_struct, char **envp)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == 0)
		ft_child(command_struct, envp);
	else
	{
		waitpid(pid, &status, 0);
		if (status != 0)
		{
			*g_exit_status = 127;
			// write(2, "minishell: ", 11);
			// write(2, command_struct->word_matrix[0], ft_strlen(command_struct->word_matrix[0]));
			// write(2, ": command not found\n", 20);
		}
	}
	return (1);
}
