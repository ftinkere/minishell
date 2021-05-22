/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftinkere <ftinkere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:21:21 by ftinkere          #+#    #+#             */
/*   Updated: 2020/11/03 21:33:48 by ftinkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stddef.h>

void	ft_bzero(void *dest, size_t n)
{
	size_t	i;
	size_t	end;
	size_t	count;

	count = n / sizeof(int);
	end = n % sizeof(int);
	i = 0;
	while (i < count)
		((int *)dest)[i++] = (int)0;
	i = 0;
	while (i < end)
		((char *)dest)[i++] = (char)0;
}
