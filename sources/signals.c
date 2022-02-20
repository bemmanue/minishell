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
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_signals(void)
{
	signal(SIGQUIT, SIG_IGN);			// cntrl '\'
	signal(SIGTERM, SIG_IGN);			// cntrl D
	signal(SIGINT, ft_signal_cltr_c);	// cntrl C
}

void	signal_in_child(void)
{
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
