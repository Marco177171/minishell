/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmeoli <gmeoli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:36:26 by gmeoli            #+#    #+#             */
/*   Updated: 2022/10/27 12:00:22 by gmeoli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_remove_quotes2(char *command, int *index, int *res_index, char *result)
{
	while (command[*index])
	{
		if (command[*index] == '"')
		{
			(*index)++;
			while (command[*index] != '"')
			{
				result[*res_index] = command[*index];
				(*res_index)++;
				(*index)++;
			}
			(*index)++;
		}
		if (command[*index] == '\'')
		{
			(*index)++;
			while (command[*index] != '\'')
			{
				result[*res_index] = command[*index];
				(*res_index)++;
				(*index)++;
			}
			(*index)++;
		}
		else
		{
			result[*res_index] = command[*index];
			(*res_index)++;
			(*index)++;
		}
	}
}

void	ft_remove_quotes(char *command)
{
	int		index;
	int		res_index;
	char	*result;

	index = 0;
	res_index = 0;
	if (ft_check_quote(command) == 1)
	{
		while (command[index])
			index++;
		result = malloc(sizeof(char) * index);
		index = 0;
		ft_remove_quotes2(command, &index, &res_index, result);
		result[res_index] = '\0';
		free (command);
		command = malloc(sizeof(char) * res_index + 1);
		res_index = 0;
		while (result[res_index])
		{
			command[res_index] = result[res_index];
			res_index++;
		}
		command[res_index] = '\0';
		free(result);
		return ;
	}
	else
		return ;
}
