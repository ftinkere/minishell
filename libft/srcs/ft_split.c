/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftinkere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:36:54 by ftinkere          #+#    #+#             */
/*   Updated: 2020/11/10 16:53:41 by ftinkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

static int	count_words(const char *s, char c)
{
	int		res;

	while (*s == c && *s != '\0')
		s++;
	if (ft_strlen(s) == 0)
		return (0);
	res = 1;
	while (*s)
	{
		if (*s == c)
		{
			res++;
			while (*s == c)
				s++;
		}
		else
			s++;
	}
	if (*s == '\0' && s[-1] == c)
		res--;
	return (res);
}

static int	get_n_word_index(const char *s, char c, int n)
{
	int			i;
	const char	*start;

	start = s;
	while (*s == c && *s != '\0')
		s++;
	i = 0;
	while (i < n && *s)
	{
		if (*s == c)
		{
			i++;
			while (*s == c)
				s++;
		}
		else
			s++;
	}
	return ((int)(s - start));
}

static int	strclen(const char *s, char c)
{
	int		res;

	res = 0;
	while (*s == c)
		s++;
	while (s[res] && s[res] != c)
		res++;
	return (res);
}

static char	**free_mem(char **s)
{
	char	*arr;

	arr = *s;
	if (s != NULL)
	{
		while (*s != NULL)
			free(*s++);
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		words;
	int		i;

	if (s == NULL)
		return (NULL);
	words = count_words(s, c);
	res = malloc((words + 1) * sizeof(char *));
	if (res == (NULL))
		return (NULL);
	i = 0;
	while (i < words)
	{
		res[i] = ft_substr(s, get_n_word_index(s, c, i),
				strclen(s + get_n_word_index(s, c, i), c));
		if (res[i++] == NULL)
			return (free_mem(res));
	}
	res[i] = NULL;
	return (res);
}
