/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:00:00 by bemmanue          #+#    #+#             */
/*   Updated: 2022/02/15 14:00:00 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "parser.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	*command;
	t_command	*temp;
	char		*str;
	int			i;
	(void)argc;
	(void)argv;
	(void)envp;

	g_info.env = ft_arrdup(envp, 0);
	str = readline("hello$ ");
	temp = parse_string(str);
	command = temp;
	while (command)
	{
		printf("s = |%s|\n", command->name);
		i = 0;
		while (command->argv && command->argv[i])
		{
			printf("argv = |%s|\n", command->argv[i]);
			i++;
		}
		i = 0;
		while (command->rdrct && command->rdrct[i])
		{
			printf("rdrct = |%s|\n", command->rdrct[i]);
			i++;
		}
		command = command->next;
	}
	free_command(temp);
	while (1)
		NULL;
	return (0);
}
