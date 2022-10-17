/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masebast <masebast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:45:04 by masebast          #+#    #+#             */
/*   Updated: 2022/10/17 19:28:28 by masebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_heredoc(t_command *command_struct, int pipe_index, char **envp)
// {
// 	int	stdincpy;
	
// 	stdincpy = dup(0);
// }

void	ft_decrease_word_matrix(char **word_matrix)
{
	int		index;
	int		temp_index;
	char	**temp_matrix;

	index = 0;
	temp_index = 0;
	while (word_matrix[index])
		index++;
	temp_matrix = malloc(sizeof(char *) * index);
	temp_matrix[index] = NULL;
	index = 0;
	while (ft_strncmp(word_matrix[index], ">>\0", 3) != 0 &&
			ft_strncmp(word_matrix[index], ">\0", 2) != 0 &&
			word_matrix[index])
	{
		temp_matrix[temp_index] = ft_strdup(word_matrix[index]);
		index++;
		temp_index++;
	}
	temp_index = 0;
	while (temp_matrix[temp_index])
		temp_index++;
	ft_free_matrix(word_matrix);
	word_matrix = malloc(sizeof(char *) * temp_index + 1);
	word_matrix[temp_index] = NULL;
	temp_index = 0;
	while (temp_matrix[temp_index])
	{
		word_matrix[temp_index] = ft_strdup(temp_matrix[temp_index]);
		temp_index++;
	}
	ft_free_matrix(temp_matrix);
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
				ft_decrease_word_matrix(command_struct->word_matrix);
			}
			else if (ft_strncmp(command_struct->word_matrix[index], ">\0", 2) == 0)
			{
				fd = open(command_struct->word_matrix[index + 1], O_TRUNC|O_CREAT|O_WRONLY, 0644);
				ft_decrease_word_matrix(command_struct->word_matrix);
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
