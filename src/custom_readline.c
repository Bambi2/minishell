/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:31:59 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:00 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*custom_readline(t_minishell *minishell, char *prompt)
{
	char	*line;

	g_termflag.is_reading = 1;
	line = readline(prompt);
	if (line && *line)
		add_history(line);
	else if (line && !*line)
	{
		free(line);
		line = custom_readline(minishell, PROMPT);
	}
	else if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		exit(EXIT_SUCCESS);
	}
	g_termflag.is_reading = 0;
	return (line);
}
