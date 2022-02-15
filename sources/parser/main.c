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

int	main(void)
{
	t_command	*command;
	char		*str;
	int			i;

	g_info.env = ft_arrdup(getenv(), 0);
	str = readline("hello$ ");
	command = parse_string(str);
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
	return (0);
}
