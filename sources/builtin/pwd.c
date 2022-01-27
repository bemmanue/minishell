/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 20:57:17 by dwillard          #+#    #+#             */
/*   Updated: 2022/01/14 20:57:18 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

int	pwd(void)
{
	char	*temp;

	temp = getcwd(NULL, MAX_DIR);
	if (!temp)
		return (-1);
	ft_putendl_fd(temp, 1);
	free(temp);
	return (0);
}