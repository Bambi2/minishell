/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:31:52 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:31:53 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	env(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (!minishell->envp)
	{
		g_termflag.last_exit_status = 1;
		ft_putstr_fd("Memory error\n", 2);
		return ;
	}
	while (minishell->envp && minishell->envp[i])
	{
		ft_putstr_fd(minishell->envp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	g_termflag.last_exit_status = 0;
}
