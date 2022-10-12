/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masebast <masebast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:29:36 by gmeoli            #+#    #+#             */
/*   Updated: 2022/10/12 16:52:29 by masebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_command *command_struct)
{
	if (command_struct->total_pipes == 1)
		printf("exit\n");
	if (command_struct->pipe_matrix)
		ft_free_matrix(command_struct->pipe_matrix);
	if (command_struct->word_matrix)
		ft_free_matrix(command_struct->word_matrix);
	if (command_struct->command_string)
		free(command_struct->command_string);
	free(g_exit_status);
	exit(0);
}
