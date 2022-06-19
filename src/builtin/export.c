/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:31:54 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:31:55 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	find_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static int	export_new_var(t_minishell *minishell,
	char *new_var, int equal_sign)
{
	char	*var_name;
	char	*check;

	var_name = ft_substr(new_var, 0, equal_sign);
	if (!var_name)
	{
		g_termflag.last_exit_status = 1;
		return (-1);
	}
	check = get_env_var(minishell->envp, var_name);
	if (check)
	{
		free(check);
		change_env(minishell, var_name, new_var + equal_sign + 1);
	}
	else
		add_env_var(minishell, var_name, new_var + equal_sign + 1);
	free(var_name);
	return (0);
}

void	export(t_minishell *minishell, char **argv)
{
	int		i;
	int		equal_sign;

	i = 1;
	if (!argv[1])
		env(minishell);
	while (argv[i])
	{
		equal_sign = find_equal_sign(argv[i]);
		if (!ft_isalpha(argv[i][0]))
		{
			ft_putchar_fd(argv[i][0], 2);
			ft_putstr_fd(" : not a valid identifier\n", 2);
			i++;
			g_termflag.last_exit_status = 1;
			continue ;
		}
		else if (equal_sign != -1)
			export_new_var(minishell, argv[i], equal_sign);
		else if (equal_sign == -1)
			g_termflag.last_exit_status = 0;
		i++;
	}
}
