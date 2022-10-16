/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masebast <masebast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:45:04 by masebast          #+#    #+#             */
/*   Updated: 2022/10/16 18:07:55 by masebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirect(t_command *command_struct, int pipe_index, char **envp)
{
	int	fd;
	int	index;
	int stdoutcpy;

	index = 0;
	stdoutcpy = dup(1);
	while (command_struct->word_matrix[index])
	{
		if (ft_strncmp(command_struct->word_matrix[index], ">>\0", 3) == 0 ||
			ft_strncmp(command_struct->word_matrix[index], ">\0", 2) == 0)
		{
			if (ft_strncmp(command_struct->word_matrix[index], ">>\0", 3) == 0)
				fd = open(command_struct->word_matrix[index + 1], O_APPEND|O_CREAT|O_WRONLY, 0644);
			else if (ft_strncmp(command_struct->word_matrix[index], ">\0", 2) == 0)
				fd = open(command_struct->word_matrix[index + 1], O_TRUNC|O_CREAT|O_WRONLY, 0644);
			close(STDOUT_FILENO);
			dup2(fd, STDOUT_FILENO);
			ft_recognize_command(command_struct, pipe_index, envp);
			dup2(stdoutcpy, STDOUT_FILENO);
			close(fd);
		}
		else if (ft_strncmp(command_struct->word_matrix[index], "<<\0", 3) == 0)
			printf("<< found \n");
		else if (ft_strncmp(command_struct->word_matrix[index], "<\0", 2) == 0)
			printf("< found \n");
		index++;
	}
}
