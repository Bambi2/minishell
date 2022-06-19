/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:33:02 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:33:03 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	int		i;

	i = 0;
	result = (char *) ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (s1[i])
	{
		*(result + i) = *(s1 + i);
		i++;
	}
	*(result + i) = '\0';
	return (result);
}
