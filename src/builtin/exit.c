/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:31:53 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:31:54 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_long(char *str)
{
	int			i;
	int			len;
	long long	temp;

	if (str[0] != '-' && !ft_isdigit(str[0]))
		return (-1);
	i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	len = ft_strlen(str);
	if (len > 19 || (len > 20 && str[0] == '-'))
		return (-1);
	if ((len == 19 && str[len - 1] > '7') || (len == 20 && str[len - 1] > '6'))
		return (-1);
	temp = ft_atoi(str);
	if (temp > __LONG_MAX__ || temp < LONG_MIN)
		return (-1);
	return (0);
}

void	exit_cmd(char **argv)
{
	int	status;

	unlink(".input");
	if (!argv[1])
	{
		ft_putstr_fd("exit\n", 2);
		exit(EXIT_SUCCESS);
	}
	if (get_strings_count(argv) > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_termflag.last_exit_status = 1;
		return ;
	}
	if (is_long(argv[1]) == -1)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit(255);
	}
	ft_putstr_fd("exit\n", 2);
	status = ft_atoi(argv[1]) % 256;
	exit(status);
}
