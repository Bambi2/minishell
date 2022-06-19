/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:31:57 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:31:58 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	unset(t_minishell *minishell, char **argv)
{
	int	i;

	if (!argv[1])
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		g_termflag.last_exit_status = 1;
		return ;
	}
	i = 1;
	while (argv[i])
	{
		if (remove_env_var(minishell, argv[i]) == -1)
			g_termflag.last_exit_status = 1;
		else
			g_termflag.last_exit_status = 0;
		i++;
	}
}
