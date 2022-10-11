/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masebast <masebast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:19:47 by masebast          #+#    #+#             */
/*   Updated: 2022/10/11 17:34:26 by masebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_manage_pipes(t_command *command_struct, char **envp)
{
	int		index;
	int		pipes[2];
	int		*pid;
	int		stdin_cpy;
	int		stdout_cpy;

	stdin_cpy = dup(0);
	stdout_cpy = dup(1);
	index = 0;
	pid = malloc(sizeof(int) * command_struct->total_pipes);
	while (index < command_struct->total_pipes)
	{
		pipe(pipes);
		pid[index] = fork();
		command_struct->word_matrix = ft_split(command_struct->pipe_matrix[index], ' ');
		ft_remove_quotes(command_struct->word_matrix[0]);
		if (pid[index] == 0)
		{
			close(pipes[0]);
			if (index == command_struct->total_pipes - 1)
				dup2(stdout_cpy, STDOUT_FILENO);
			else
				dup2(pipes[1], STDOUT_FILENO);
			ft_recognize_command(command_struct, index, envp);
			exit(0);
		}
		else
		{
			dup2(pipes[0], STDIN_FILENO);
			close(pipes[0]);
			close(pipes[1]);
			ft_free_matrix(command_struct->word_matrix);
		}
		index++;
	}
	dup2(stdin_cpy, 0);
	close(stdin_cpy);
	close(stdout_cpy);
	index = -1;
	while (++index < command_struct->total_pipes)
		waitpid(pid[index], 0, 0);
	free(pid);
	free(command_struct->command_string);
	ft_free_matrix(command_struct->pipe_matrix);
}
