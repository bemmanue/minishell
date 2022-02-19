/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:00:00 by bemmanue          #+#    #+#             */
/*   Updated: 2022/02/18 18:00:00 by bemmanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_signal_cltr_c(int sig)
{
	(void) sig;
	write(2, "\n", 1);
	rl_on_new_line();
//	rl_replace_line("", 0);
//	rl_redisplay();
}

void	ft_signal_cltr_d(int sig)
{
	(void) sig;
	exit(0);
}

void	set_signals(void)
{
	signal(SIGQUIT, SIG_IGN);	// cntrl '\'
	signal(SIGTERM, ft_signal_cltr_d);	// cntrl D
	signal(SIGINT, ft_signal_cltr_c);	// cntrl C
}
