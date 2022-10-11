/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmeoli <gmeoli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:34:31 by masebast          #+#    #+#             */
/*   Updated: 2022/09/26 14:20:33 by gmeoli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_split_pipes(t_command *command_struct)
{
	int	index;
	int	array_index;
	int	save;
	
	index = 0;
	command_struct->total_pipes = 1;
	array_index = 0;
	save = 0;
	while (command_struct->command_string[index])
	{
		if (command_struct->command_string[index] == '"')
		{
			while (command_struct->command_string[index] != '"')
				index++;
		}
		else if (command_struct->command_string[index] == '\'')
		{
			while (command_struct->command_string[index] != '\'')
				index++;
		}
		else if (command_struct->command_string[index] == '|' && 
			command_struct->command_string[index + 1] != '|' && 
				command_struct->command_string[index - 1] != '|')
			command_struct->total_pipes++;
		index++;
	}
	// printf("pipes counted: %d\n", command_struct->total_pipes);
	command_struct->pipe_matrix = malloc(sizeof(char *) * command_struct->total_pipes);
	command_struct->pipe_matrix[command_struct->total_pipes] = NULL;
	index = 0;
	// printf("pipe matrix allocated...\n");
	while (array_index < command_struct->total_pipes)
	{
		// printf("while pipe matrix. index: %d\n", array_index);
		while (command_struct->command_string[index])
		{
			if (command_struct->command_string[index] == '|' && 
				command_struct->command_string[index + 1] != '|' &&
					command_struct->command_string[index - 1] != '|')
					break ;
			index++;
		}
		command_struct->pipe_matrix[array_index] = malloc(sizeof(char) * index - save);
		command_struct->pipe_matrix[array_index][index - save] = '\0';
		array_index++;
		index++;
		save = index;
	}
	// printf("pipe strings allocated...\n");
	printf("command_struct->total_pipes: %d\n", command_struct->total_pipes);
	array_index = 0;
	save = 0;
	while (array_index < command_struct->total_pipes)
	{
		// printf("sto ciclando...\n");
		index = 0;
		while (command_struct->command_string[save] != '|' && command_struct->command_string[index])
		{
			command_struct->pipe_matrix[array_index][index] = command_struct->command_string[save];
			save++;
			index++;
		}
		if (command_struct->command_string[save] != '\0')
			save++;
		// printf("pipe %d: %s\n", array_index, command_struct->pipe_matrix[array_index]);
		array_index++;
	}
	// printf("pipe matrix created\n");
}