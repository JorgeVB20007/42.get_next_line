#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>

int	ft_strlen(char *s)
{
	int	n;

	n = 0;
	while (s[n] != 0)
		n++;
	return (n);
}

int	ft_search(char *s, char c)
{
	int	a;

	a = 0;
	while (s[a] != 0)
	{
		if (s[a] == c)
		{
			return (a);
		}
		a++;
	}
	return (-1);
}

char	*ft_strjoin(char *line, char *str)
{
	char	*temp;
	int		a;
	int		b;

	a = 0;
	b = 0;
	while (str[a] != 0 && str[a] != '\n')
		a++;
	temp = malloc(ft_strlen(line) + a + 1);
	a = 0;
	while (line[a])
	{
		temp[a] = line[a];
		a++;
	}
	while (str[b] != 0 && str[b] != '\n')
	{
		temp[a + b] = str[b];
		b++;
	}
	temp[a + b] = 0;
	free(line);
	line = malloc(sizeof(char *));
	return (temp);
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

char	*ft_copyandfree(char *s1, int n)
{
	int		cntr;
	char	*s2;

	cntr = 0;
	s2 = malloc(n + 1);
	while (cntr < n)
	{
		s2[cntr] = s1[cntr];
		cntr++;
	}
	s2[cntr] = 0;
	return (s2);
}