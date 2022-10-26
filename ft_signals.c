/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masebast <masebast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:18:08 by masebast          #+#    #+#             */
/*   Updated: 2022/10/26 17:58:50 by masebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl_c(char **envp)
{
	int	n;

	n = fork();
	if (!n) 
	{
	char *cmd[] = {"/bin/stty", 0 };
	char *cmd_args[] = {" ", "-echoctl", 0};
	execve(cmd[0], cmd_args, envp);
	}
}

void	sig_new_line(int n)
{
	n = 0;
	// ft_putendl_fd("", 1);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_manage_signals(void)
{
	signal(SIGINT, sig_new_line);
	signal(SIGQUIT, SIG_IGN);
}
