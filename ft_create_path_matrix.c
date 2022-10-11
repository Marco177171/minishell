/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_path_matrix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masebast <masebast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:29:07 by masebast          #+#    #+#             */
/*   Updated: 2022/09/09 18:46:45 by masebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	ft_other_commands(char *str, t_command *command_struct, char **envp)
//	Creare funzione:
//	1. Deve essere lanciata appena si runna ./minishell
//	2. Dall'ENVP si deve trovare la variabile "PATH"
//	3. Con la funzione "getenv", prendere il valore di "PATH"
//	4. Al valore restituito, aggiungere lo "/" con la funzione ft_strjoin
//	5. 