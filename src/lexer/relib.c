/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relib.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:23 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:24 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	strjoin(char **s1, char *s2)
{	
	char	*str;

	if (s2 == 0)
		return (0);
	str = (char *) malloc (sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2) + 1));
	if (str == 0)
		return (0);
	ft_strlcpy(str, *s1, ft_strlen(*s1) + 1);
	ft_strlcat(str, s2, ft_strlen(*s1) + ft_strlen(s2) + 1);
	if (*s1 != 0)
		free (*s1);
	*s1 = str;
	return (1);
}

char	*strtrim(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	while ((str)[i] && (str)[i] == ' ')
		i ++;
	new_str = ft_substr(str, i - 1, ft_strlen(str) - i);
	return (new_str);
}
