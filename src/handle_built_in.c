/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:06 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:07 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_built_in(t_token *token)
{
	int	length;

	length = ft_strlen(token->token);
	if (ft_strncmp(token->token, "echo", length) == 0)
		return (1);
	if (ft_strncmp(token->token, "cd", length) == 0)
		return (1);
	if (ft_strncmp(token->token, "pwd", length) == 0)
		return (1);
	if (ft_strncmp(token->token, "export", length) == 0)
		return (1);
	if (ft_strncmp(token->token, "unset", length) == 0)
		return (1);
	if (ft_strncmp(token->token, "env", length) == 0)
		return (1);
	if (ft_strncmp(token->token, "exit", length) == 0)
		return (1);
	return (0);
}

int	handle_built_in(t_minishell *minishell, t_token	*token)
{
	char	**argv;

	argv = get_arguments(token, token->token);
	if (!argv)
	{
		g_termflag.last_exit_status = 1;
		return (-1);
	}
	if (ft_strncmp(token->token, "echo", 4) == 0)
		echo(argv);
	else if (ft_strncmp(token->token, "cd", 2) == 0)
		cd(minishell, argv);
	else if (ft_strncmp(token->token, "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(token->token, "export", 6) == 0)
		export(minishell, argv);
	else if (ft_strncmp(token->token, "env", 3) == 0)
		env(minishell);
	else if (ft_strncmp(token->token, "unset", 5) == 0)
		unset(minishell, argv);
	else if (ft_strncmp(token->token, "exit", 4) == 0)
		exit_cmd(argv);
	free_strings(argv, get_strings_count(argv) - 1);
	return (0);
}
