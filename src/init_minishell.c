/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:10 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 20:36:14 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_minishell	*init_minishell(char **envp)
{
	t_minishell	*minishell;

	minishell = (t_minishell *) malloc(sizeof(t_minishell));
	if (!minishell)
	{
		printf("Couldn't allocate memory\n");
		return (NULL);
	}
	minishell->is_wstatus = 0;
	minishell->envp = copy_strings(envp);
	if (!minishell->envp)
	{
		free(minishell);
		return (NULL);
	}
	return (minishell);
}
