/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmeoli <gmeoli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:45:04 by masebast          #+#    #+#             */
/*   Updated: 2022/10/18 14:18:41 by gmeoli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_heredoc(t_command *command_struct, int pipe_index, char **envp)
// {
// 	int	stdincpy;
	
// 	stdincpy = dup(0);
// }

char	**ft_decrease_word_matrix(char **word_matrix)
{
	int		index;
	char	**temp_matrix;

	index = 0;
	while (word_matrix[index])
		index++;
	temp_matrix = malloc(sizeof(char *) * index);
	index = 0;
	while (ft_strncmp(word_matrix[index], ">>\0", 3) != 0 &&
			ft_strncmp(word_matrix[index], ">\0", 2) != 0 &&
			word_matrix[index])
	{
		temp_matrix[index] = ft_strdup(word_matrix[index]);
		index++;
	}
	temp_matrix[index] = NULL;
	// index = 0;
	// while (temp_matrix[index])
	// 	index++;
	// ft_free_matrix(word_matrix);
	// word_matrix = malloc(sizeof(char *) * index + 1);
	// index = 0;
	// while (temp_matrix[index])
	// {
	// 	word_matrix[index] = ft_strdup(temp_matrix[index]);
	// 	index++;
	// }
	// word_matrix[index] = NULL;
	// ft_free_matrix(temp_matrix);
	ft_free_matrix(word_matrix);
	return(temp_matrix);
}

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
			{
				fd = open(command_struct->word_matrix[index + 1], O_APPEND|O_CREAT|O_WRONLY, 0644);
				// ft_decrease_word_matrix(command_struct->word_matrix);
				// index++;
			}
			else if (ft_strncmp(command_struct->word_matrix[index], ">\0", 2) == 0)
			{
				fd = open(command_struct->word_matrix[index + 1], O_TRUNC|O_CREAT|O_WRONLY, 0644);
				command_struct->word_matrix = ft_decrease_word_matrix(command_struct->word_matrix);
				index++;
			}
			close(STDOUT_FILENO);
			dup2(fd, STDOUT_FILENO);
			ft_recognize_command(command_struct, pipe_index, envp);
			dup2(stdoutcpy, STDOUT_FILENO);
			close(fd);
		}
		else if (ft_strncmp(command_struct->word_matrix[index], "<<\0", 3) == 0)
		{
			// heredoc
			// ft_heredoc(command_struct, pipe_index, envp);
			printf("<< found \n");
		}
		else if (ft_strncmp(command_struct->word_matrix[index], "<\0", 2) == 0)
		{
			// redirect input
			printf("< found \n");
		}
		if (command_struct->word_matrix[index + 1] != NULL)
			index++;
		else
			return ;
	}
}
