/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemmanue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:00:00 by bemmanue          #+#    #+#             */
/*   Updated: 2022/02/28 17:17:09 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_signal_cltr_c(int sig)
{
	(void) sig;
	write(2, "\n", 1);
//	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_info.last_prcs = 1;
	g_info.sig = 1;
}

void	set_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, ft_signal_cltr_c);
	g_info.sig = 0;
}

void	signal_in_child(void)
{
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, ft_signal_cltr_c);
}

void	ft_signal_pipes(int sig)
{
	signal(SIGINT, SIG_IGN);
	(void) sig;
}

void	signal_in_pipes(void)
{
	signal(SIGINT, ft_signal_pipes);
	signal(SIGQUIT, ft_signal_pipes);
}
