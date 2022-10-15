/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masebast <masebast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:45:04 by masebast          #+#    #+#             */
/*   Updated: 2022/10/15 18:45:11 by masebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirect(t_command *command_struct, int pipe_index, char **envp)
{
	int pid;
	int	fd;
	int	index;

	index = 0;
	pid = fork();
	if (pid == 0)
	{
		while (command_struct->word_matrix[index])
		{
			if (ft_strncmp(command_struct->word_matrix[index], ">>\0", 3) == 0)
			{
				printf(">> found\n");
				fd = open(command_struct->word_matrix[index + 1], O_APPEND|O_CREAT|O_WRONLY, 0777);
				dup2(fd, STDOUT_FILENO);
				ft_recognize_command(command_struct, pipe_index, envp);
				close(fd);
				close(STDOUT_FILENO);
				exit(0);
			}
			else if (ft_strncmp(command_struct->word_matrix[index], ">\0", 2) == 0)
			{
				printf("> found\n");
				fd = open(command_struct->word_matrix[index + 1], O_CREAT|O_WRONLY, 0777);
				dup2(fd, STDOUT_FILENO);
				ft_recognize_command(command_struct, pipe_index, envp);
				close(fd);
				close(STDOUT_FILENO);
				exit(0);
			}
			else if (ft_strncmp(command_struct->word_matrix[index], "<<\0", 3) == 0)
				printf("<< found \n");
			else if (ft_strncmp(command_struct->word_matrix[index], "<\0", 2) == 0)
				printf("< found \n");
			index++;
		}
	}
	else
		waitpid(pid, 0, 0);
}
