/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masebast <masebast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:45:04 by masebast          #+#    #+#             */
/*   Updated: 2022/10/18 19:03:42 by masebast         ###   ########.fr       */
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
			temp_index++;
			index++;
		}
	}
	temp_matrix[temp_index] = NULL;
	ft_free_matrix(word_matrix);
	return(temp_matrix);
}

char	*ft_update_pipe_text(char *pipe)
{
	int		index;
	int		count;
	char	*updated;

	index = 0;
	count = 0;
	while (pipe[index])
	{
		if (pipe[index] == '>' || pipe[index] == '<')
		{
			index++;
			while (pipe[index] != ' ' && pipe[index])
				index++;
			while (pipe[index] == ' ' && pipe[index])
				index++;
			while (pipe[index] != ' ' && pipe[index])
				index++;
		}
		else
		{
			count++;
			index++;
		}
	}
	updated = malloc(sizeof(char) * count + 1);
	updated[count + 1] = '\0';
	index = 0;
	count = 0;
	while (pipe[index])
	{
		if (pipe[index] == '>' || pipe[index] == '<')
		{
			index++;
			while (pipe[index] != ' ' && pipe[index])
				index++;
			while (pipe[index] == ' ' && pipe[index])
				index++;
			while (pipe[index] != ' ' && pipe[index])
				index++;
		}
		else
		{
			updated[count] = pipe[index];
			count++;
			index++;
		}
	}
	free(pipe);
	return (updated);
}

void	ft_redirect_and_execute(t_command *command_struct, int pipe_index, char **envp, int fd, int stdoutcpy)
{
	command_struct->pipe_matrix[pipe_index] = ft_update_pipe_text(command_struct->pipe_matrix[pipe_index]);
	command_struct->word_matrix = ft_decrease_word_matrix(command_struct->word_matrix);
	close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	ft_recognize_command(command_struct, pipe_index, envp);
	dup2(stdoutcpy, STDOUT_FILENO);
	close(fd);
}

void	ft_append(t_command *command_struct, int pipe_index, char **envp, int stdoutcpy, int index, int fd)
{
	if (command_struct->word_matrix[index + 1] == NULL)
	{
		ft_unexpected_token();
		return ;
	}
	fd = open(command_struct->word_matrix[index + 1], O_APPEND|O_CREAT|O_WRONLY, 0644);
	ft_redirect_and_execute(command_struct, pipe_index, envp, fd, stdoutcpy);
}

void	ft_trunc(t_command *command_struct, int pipe_index, char **envp, int stdoutcpy, int index, int fd)
{
	if (command_struct->word_matrix[index + 1] == NULL)
	{
		ft_unexpected_token();
		return ;
	}
	fd = open(command_struct->word_matrix[index + 1], O_TRUNC|O_CREAT|O_WRONLY, 0644);
	ft_redirect_and_execute(command_struct, pipe_index, envp, fd, stdoutcpy);
}

void	ft_redirect(t_command *command_struct, int pipe_index, char **envp)
{
	int		fd;
	int		index;
	int		check_index;
	int		stdoutcpy;
	char	*end_word;
	char	*swap;
	char	*swap_and_space;
	char	*sub_readline;

	fd = 0;
	index = 0;
	stdoutcpy = dup(1);
	while (command_struct->word_matrix[index])
	{
		if (ft_strcmp(command_struct->word_matrix[index], ">>") == 0 ||
			ft_strcmp(command_struct->word_matrix[index], ">") == 0)
		{
			if (ft_strcmp(command_struct->word_matrix[index], ">>") == 0)
			{
				ft_append(command_struct, pipe_index, envp, stdoutcpy, index, fd);
				break ;
			}
			else if (ft_strcmp(command_struct->word_matrix[index], ">") == 0)
			{
				ft_trunc(command_struct, pipe_index, envp, stdoutcpy, index, fd);
				break ;
			}
		}
		else if (ft_strcmp(command_struct->word_matrix[index], "<<") == 0 ||
			ft_strcmp(command_struct->word_matrix[index], "<") == 0)
		{
			if (ft_strcmp(command_struct->word_matrix[index], "<<") == 0)
			{
				index++;
				if (command_struct->word_matrix[index] == NULL)
				{
					ft_unexpected_token();
					return ;
				}
				end_word = strdup(command_struct->word_matrix[index]);
				while (1)
				{
					swap = ft_strdup(command_struct->pipe_matrix[pipe_index]);
					swap_and_space = ft_strjoin(swap, " ");
					sub_readline = readline("> ");
					free(command_struct->pipe_matrix[pipe_index]);
					command_struct->pipe_matrix[pipe_index] = ft_strjoin(swap_and_space, sub_readline);
					free(swap);
					free(swap_and_space);
					free(sub_readline);
					ft_free_matrix(command_struct->word_matrix);
					command_struct->word_matrix = ft_split(command_struct->pipe_matrix[pipe_index], ' ');
					check_index = 0;
					while (command_struct->word_matrix[check_index + 1] != NULL)
						check_index++;
					if (ft_strcmp(command_struct->word_matrix[check_index], end_word) == 0)
					{
						ft_recognize_command(command_struct, pipe_index, envp);
						break ;
					}
				}
				free(end_word);
				return ;
			}
			else if (ft_strcmp(command_struct->word_matrix[index], "<") == 0)
			{
				// redirect input
				printf("< found \n");
				break ;
			}
		}
		if (command_struct->word_matrix[index + 1] != NULL)
			index++;
		else
			return ;
	}
}
