/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:41:32 by dwillard          #+#    #+#             */
/*   Updated: 2021/12/17 21:25:51 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int main(int argc, char **argv, char **envp)
{
	char *str;

	(void)argv;
	(void)argc;
	str = readline("minishell$ ");
	while (ft_strncmp(str, "exit", 4) && str)
	{
		command_center(envp, str);
		if (ft_strlen(str) > 0)
			add_history(str);
		str = readline("minishell$ ");
	}
	return (0);
}
