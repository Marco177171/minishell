/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masebast <masebast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:45:04 by masebast          #+#    #+#             */
/*   Updated: 2022/10/18 15:59:59 by masebast         ###   ########.fr       */
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
	int		temp_index;
	char	**temp_matrix;

	index = 0;
	while (word_matrix[index])
		index++;
	temp_matrix = malloc(sizeof(char *) * index);
	index = 0;
	temp_index = 0;
	while (word_matrix[index])
	{
		if (ft_strncmp(word_matrix[index], ">>\0", 3) == 0 ||
			ft_strncmp(word_matrix[index], ">\0", 2) == 0)
			index += 2;
		else
		{
			temp_matrix[temp_index] = ft_strdup(word_matrix[index]);
			printf("temp_matrix: Index = %d | word = %s\n", index, temp_matrix[index]);
			temp_index++;
			index++;
		}
	}
	temp_matrix[temp_index] = NULL;
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
	printf("matrix freed\n");
	return(temp_matrix);
}

void	print_matrix(char **word_matrix)
{
	int index;
	index = 0;
	while (word_matrix[index])
	{
		printf("index = %d | word = %s\n", index, word_matrix[index]);
		index++;
	}
}

void	ft_redirect_and_execute(t_command *command_struct, int pipe_index, char **envp, int fd, int stdoutcpy)
{
	close(STDOUT_FILENO);
	write(1,"stacippa\n",10);
	dup2(fd, STDOUT_FILENO);
	ft_recognize_command(command_struct, pipe_index, envp);
	dup2(stdoutcpy, STDOUT_FILENO);
	close(fd);
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
		if (ft_strcmp(command_struct->word_matrix[index], ">>") == 0 ||
			ft_strcmp(command_struct->word_matrix[index], ">") == 0)
		{
			if (ft_strcmp(command_struct->word_matrix[index], ">>") == 0)
			{
				fd = open(command_struct->word_matrix[index + 1], O_APPEND|O_CREAT|O_WRONLY, 0644);
				command_struct->word_matrix = ft_decrease_word_matrix(command_struct->word_matrix);
				print_matrix(command_struct->word_matrix);
				ft_redirect_and_execute(command_struct, pipe_index, envp, fd, stdoutcpy);
				break ;
			}
			else if (ft_strcmp(command_struct->word_matrix[index], ">") == 0)
			{
				fd = open(command_struct->word_matrix[index + 1], O_TRUNC|O_CREAT|O_WRONLY, 0644);
				command_struct->word_matrix = ft_decrease_word_matrix(command_struct->word_matrix);
				print_matrix(command_struct->word_matrix);
				ft_redirect_and_execute(command_struct, pipe_index, envp, fd, stdoutcpy);
				break ;
			}
			// close(STDOUT_FILENO);
			// dup2(fd, STDOUT_FILENO);
			// ft_recognize_command(command_struct, pipe_index, envp);
			// dup2(stdoutcpy, STDOUT_FILENO);
			// close(fd);
		}
		else if (ft_strcmp(command_struct->word_matrix[index], "<<") == 0)
		{
			// heredoc
			// ft_heredoc(command_struct, pipe_index, envp);
			printf("<< found \n");
		}
		else if (ft_strcmp(command_struct->word_matrix[index], "<") == 0)
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
