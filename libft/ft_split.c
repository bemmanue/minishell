/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 14:52:54 by bemmanue          #+#    #+#             */
/*   Updated: 2021/05/04 13:11:23 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static void	ft_free(char **mass, int i)
{
	while (i != 0)
	{
		free(mass[i]);
		i++;
	}
	free(mass);
	mass = NULL;
}

static char	*ft_memandcopy(char *str, int ch, char const *s)
{
	char	*buf;

	str = malloc(sizeof(*str) * ch + 1);
	if (str == NULL)
		return (NULL);
	buf = str;
	while (--ch >= 0)
		*buf++ = *s++;
	*buf = '\0';
	return (str);
}

static char	*ft_char(int i, char **mass, char const *s, char c)
{
	int	ch;
	int	w;

	w = 0;
	while (*s)
	{
		ch = 0;
		if (*s != c)
		{
			while (*s != c && *s != '\0')
			{
				ch++;
				s++;
			}
			w++;
		}
		if (i == w - 1)
			return (ft_memandcopy(mass[i], ch, s - ch));
		else
			s++;
	}
	return (ft_memandcopy(mass[i], ch, s));
}

static int	ft_word(char const *s, char c)
{
	int	word;

	word = 0;
	while (*s)
	{
		if (*s != c)
		{
			word++;
			while (*s != c && *s != '\0')
				s++;
		}
		else
			s++;
	}
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**mass;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	mass = malloc(sizeof(*mass) * ft_word(s, c) + 1);
	if (mass == NULL)
		return (NULL);
	while (i < ft_word(s, c))
	{
		mass[i] = ft_char(i, mass, s, c);
		if (mass[i] == NULL)
		{
			ft_free(mass, i);
			return (NULL);
		}
		i++;
	}
	mass[i] = NULL;
	return (mass);
}
