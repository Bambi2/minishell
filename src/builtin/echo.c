/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:31:49 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:31:50 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo(char **argv)
{
	int	i;

	i = 1;
	if (argv && argv[1] && ft_strncmp(argv[1], "-n", ft_strlen(argv[1])) == 0)
	{
		i++;
		while (argv[i])
		{
			ft_putstr_fd(argv[i++], 1);
			if (argv[i] != NULL)
				ft_putstr_fd(" ", 1);
		}
	}
	else
	{
		while (argv && argv[i])
		{
			ft_putstr_fd(argv[i++], 1);
			if (argv[i] != NULL)
				ft_putstr_fd(" ", 1);
		}
		ft_putstr_fd("\n", 1);
	}
	g_termflag.last_exit_status = 0;
}
