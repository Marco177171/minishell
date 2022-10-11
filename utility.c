/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masebast <masebast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:46:29 by gmeoli            #+#    #+#             */
/*   Updated: 2022/10/03 17:10:55 by masebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(void)
{
	printf("error\n");
	exit(0);
}

int	ft_count_pipes(char *str)
{
	int	index;
	int	count;

	index = 0;
	count = 1;
	while (str[index])
	{
		if (str[index] == '|')
			count++;
		index++;
	}
	return (count);
}

void	ft_free_matrix(char **m)
{
	int	i;

	i = 0;
	if (m[0])
	{
		while (m[i])
		{
			free(m[i]);
			i++;
		}
		free(m);
	}
}

int	ft_pipe_total(char *input)
{
	int	pipe_total;
	int	index;

	pipe_total = 0;
	index = 0;
	while (input[index])
	{
		if (input[index] == '"')
		{
			while (input[index] != '"')
				index++;
		}
		else if (input[index] == '\'')
		{
			while (input[index] != '\'')
				index++;
		}
		else if (input[index] == '|')
			pipe_total++;
		index++;
	}
	return (pipe_total);
}
