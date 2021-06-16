#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int	ft_strlen(char *s)
{
	int	n;

	n = 0;
	while (s[n] != 0)
		n++;
	return (n);
}

char	*extend(char **line, char *str, int result)
{
	char	*str2;
	int		a;
	int		b;

	a = 0;
	b = 0;
	str2 = malloc(ft_strlen(line) + result + 1);
	while (*line[a] != 0)
	{
		str2[a] = *line[a];
		a++;
	}
	while (str[b] != 0 && b < result)
	{
		str2[a + b] = str[b];
		b++;
	}
	str2[a + b] = 0;
	free(*line);
	free(str);
	return (str2);
}

static char	*reading(int fd, char **line)
{
	int		readresult;
	char	*str;
	char	*str2;

	str2 = malloc(1);
	str2[0] = 0;
	while (1)
	{
		str = malloc(BUFFER_SIZE + 1);
		readresult = read(fd, str, BUFFER_SIZE);
		if (readresult <= 0)
			return(str2);
		str2 = extend(str2, str, readresult);
		free (str);
	}
}

int get_next_line(int fd, char **line)
{

}