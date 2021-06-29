/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:52:38 by jvacaris          #+#    #+#             */
/*   Updated: 2021/06/29 19:52:40 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_calloc(int a)
{
	int		b;
	char	*new;

	b = 0;
	new = malloc(a);
	while (b < a)
	{
		new[b] = 0;
		b++;
	}
	return (new);
}

int	eolcheck(char *str)
{
	int	a;

	a = 0;
	if (!str)
		return (0);
	while (str[a] != 0)
	{
		if (str[a] == '\n')
			return (1);
		a++;
	}
	return (0);
}

int	ft_strlen(char *s)
{
	int	n;

	n = 0;
	while (s[n] != 0)
		n++;
	return (n);
}

char	*ft_strdup(char *s1)
{
	int		cntr;
	int		cntr2;
	char	*s2;

	cntr = 0;
	cntr2 = 0;
	while (s1[cntr] != 0)
		cntr++;
	s2 = malloc(cntr + 1);
	if (!s2)
		return (NULL);
	while (cntr2 < cntr)
	{
		s2[cntr2] = s1[cntr2];
		cntr2++;
	}
	s2[cntr2] = 0;
	return (s2);
}

char	*ft_join(char *orig, char *add)
{
	char	*result;
	int		a;
	int		b;

	a = 0;
	b = 0;
	if (!orig)
	{
		result = ft_strdup(add);
		free (add);
		return (result);
	}
	result = ft_calloc(ft_strlen(orig) + ft_strlen(add) + 1);
	while (orig[++a - 1])
		result[a - 1] = orig[a - 1];
	while (add[++b - 1])
		result[a - 1 + b - 1] = add[b - 1];
	free (orig);
	free (add);
	return (result);
}
