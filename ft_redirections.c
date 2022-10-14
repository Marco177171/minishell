/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masebast <masebast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:45:04 by masebast          #+#    #+#             */
/*   Updated: 2022/10/14 16:38:44 by masebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirect_in_append(char *output, int fd)
{
	ft_putstr_fd(output, fd);
}

void	ft_redirect_output(char *output, int fd)
{
	ft_putstr_fd(output, fd);
}

void	ft_delimiter(char *output, int fd)
{
	ft_putstr_fd(output, fd);
}

void	ft_redirect_input(char *output, int fd)
{
	ft_putstr_fd(output, fd);
}

void	ft_redirect(char **word_matrix, char *current_output, int current_index, int fd)
{
	if (ft_strncmp(word_matrix[current_index], ">>", 2) == 0)
		ft_redirect_in_append(current_output, fd);
	else if (ft_strncmp(word_matrix[current_index], ">", 1) == 0)
		ft_redirect_output(current_output, fd);
	else if (ft_strncmp(word_matrix[current_index], "<<", 2))
		ft_delimiter(current_output, fd);
	else if (ft_strncmp(word_matrix[current_index], "<", 1) == 0)
		ft_redirect_input(current_output, fd);
}
