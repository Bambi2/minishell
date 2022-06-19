/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:07 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 20:35:40 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_cmd(t_minishell *minishell, t_token *cmd)
{
	if (cmd == NULL)
		return (-1);
	if (is_built_in(cmd))
	{
		minishell->is_wstatus = 0;
		handle_built_in(minishell, cmd);
	}
	else
	{
		minishell->is_wstatus = 1;
		handle_bin(minishell, cmd);
	}
	return (0);
}
