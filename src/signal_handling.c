/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:14 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:15 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_int(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_termflag.is_reading)
		{
			g_termflag.last_exit_status = 1;
			rl_redisplay();
		}
		else
			g_termflag.last_exit_status = 130;
	}
}

void	handle_quit(int sig)
{
	if (sig == SIGQUIT)
	{
		if (*rl_line_buffer && !g_termflag.is_reading)
		{
			g_termflag.last_exit_status = 131;
			ft_putendl_fd("Quit: 3", 1);
		}
		else
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

int	set_signals(void)
{
	struct termios	new_terminal;

	if (tcgetattr(0, &(new_terminal)) == -1)
	{
		perror("tcgetattr");
		return (-1);
	}
	new_terminal.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &new_terminal) == -1)
	{
		perror("tcsetattr");
		return (-1);
	}
	signal(SIGINT, handle_int);
	signal(SIGQUIT, handle_quit);
	return (0);
}
