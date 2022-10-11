/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masebast <masebast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:29:07 by masebast          #+#    #+#             */
/*   Updated: 2022/10/03 16:49:36 by masebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_other_commands(t_command *command_struct, char **envp)
{
	int		index;
	int		status;
	char	*path;
	char	**mypath;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		path = getenv("PATH");
		mypath = ft_split(path, ':');
		index = -1;
		while (mypath[++index])
			mypath[index] = ft_strjoin(mypath[index], "/");
		index = -1;
		while (mypath[++index])
		{
			path = ft_strjoin(mypath[index], command_struct->word_matrix[0]);
			if (access(path, R_OK) == 0)
				execve(path, command_struct->word_matrix, envp);
			free(path);
		}
		printf("minishell: %s: command not found\n", command_struct->word_matrix[0]);
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (status != 0)
			*g_exit_status = 127;
	}
	return (1);
}
