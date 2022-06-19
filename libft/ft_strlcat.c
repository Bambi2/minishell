/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:33:06 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:33:07 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_length;

	if (!dstsize)
		return (ft_strlen(src));
	i = 0;
	dst_length = ft_strlen(dst);
	if (dst_length >= dstsize)
		return (ft_strlen(src) + dstsize);
	while (i < dstsize - dst_length - 1 && src[i])
	{
		dst[dst_length + i] = src[i];
		i++;
	}
	dst[dst_length + i] = '\0';
	return (ft_strlen(src) + dst_length);
}
