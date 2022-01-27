/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 21:26:17 by dwillard          #+#    #+#             */
/*   Updated: 2021/12/17 21:26:20 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error(char *str)
{
	if (str)
		ft_putendl_fd(str, 2);
	if (errno && !str)
		ft_putendl_fd(strerror(errno), 2);
	exit(errno);
}

t_env	*lst_new(char *content)
{
	t_env	*nod;

	nod = malloc(sizeof (t_env *));
	if (!nod)
		return (NULL);
	nod->next = NULL;
	nod->str = content;
	return (nod);
}

void		lst_add_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	temp = *lst;
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

int	lst_len(t_command *lst)
{
	int		ret_counter;

	ret_counter = 0;
	while (lst)
	{
		ret_counter++;
		lst = lst->next;
	}
	return (ret_counter);
}
