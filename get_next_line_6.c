//#include "get_next_line.h"
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

int	ft_search(char *str)
{
	int	a;

	a = 0;
	if (!str)
		return (-1);
	while (str[a])
	{
		if (str[a] == '\n')
			return (a);
		a++;
	}
	return (-1);
}

char	*ft_join(char *orig, char *add)
{
	char	*result;
	int		a;
	int		b;

	a = 0;
	b = 0;
	if (!orig)
		return (add);
	result = malloc(ft_strlen(orig) + ft_strlen(add) + 1);
	while (orig[a])
	{
		result[a] = orig[a];
		a++;
	}
	while (add[b])
	{
		result[a + b] = add[b];
		b++;
	}
	result[a + b] = 0;
	free (orig);
	return (result);
}

char	*linefinder(char *memory)
{
	int		a;
	char	*str;

	a = 0;
	if (ft_search(memory) >= 0)
		a = ft_search(memory);
	else
		a = ft_strlen(memory);
	printf("%s", memory);
	str = malloc(a + 1);
	a = 0;
	while (memory[a] != '\n' || memory[a] != 0)
	{
		str[a] = memory[a];
		a++;
	}
	str[a] = 0;
	return (str);
}

char	*memfinder(char *memory)
{
	int		a;
	int		b;
	char	*str;

	a = 0;
	if (ft_search(memory) >= 0)
		a = ft_search(memory);
	else
		a = ft_strlen(memory);
	b = ft_strlen(memory);
	str = malloc(b - a + 1);
	while (memory[a] != 0)
	{
		str[a] = memory[a];
		a++;
	}
	str[a] = 0;
	free (memory);
	return (str);
}

int	get_next_line(int fd, char **line)
{
	static char	*memory;
	char		*temp;
	int			readresult;

	readresult = BUFFER_SIZE;
	if (fd <= 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (-1);
	while ((readresult > 0) && (ft_search(memory) == -1))
	{
		readresult = read(fd, temp, BUFFER_SIZE);
		if (readresult <= -1)
		{
			free(temp);
			return (-1);
		}
		temp[readresult] = 0;
		memory = ft_join(memory, temp);
	}
	write(1, " :D ", 4);
	*line = linefinder(memory);
	memory = memfinder(memory);
	free (temp);
	return (readresult);
}

int main()
{
	int a = 1;
	char **line;
	int fd = 1;

	line = malloc(sizeof(char *));
	fd = open("/Users/jvacaris/get_next_line/gnl_testfile", O_RDONLY);
	printf("%d", BUFFER_SIZE);
	while (a > 0)
	{
		write(1, "$", 1);
		a = get_next_line(fd, line);
		write(1, "$\n", 2);
		printf("%d\n%s\n", a, *line);
	}
}