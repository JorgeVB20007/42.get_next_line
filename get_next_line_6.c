//#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>


void	ft_print(char *str, int f)
{
	int	a;

	a = 0;
	if (f == -1)
	{
		while (str[a] != 0)
		{
			write(1, &str[a], 1);
			a++;
		}
	}
	else
	{
		while (a < f)
		{
			write(1, &str[a], 1);
			a++;
		}
	}
}

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
	free (s1);
	return (s2);
}

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
		return (ft_strdup(add));
	result = ft_calloc(ft_strlen(orig) + ft_strlen(add) + 1);
	while (orig[a])
	{
		result[a] = orig[a];
		a++;
	}
	printf("\n\n.%s.\n\n", add);
	while (add[b])
	{
		printf("%c", add[b]);
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
	str = ft_calloc(a + 1);
	a = 0;
	while (memory[a] != '\n' && memory[a] != 0)
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
	{
		a = ft_search(memory);
	}
	else
	{
		a = ft_strlen(memory);
	}
	b = ft_strlen(memory);
	str = ft_calloc(b - a);
	b = 0;
	if (a > 0)
	{
		a++;
		while (memory[a + b] != 0 && memory[a + b] != '\n')
		{
			str[b] = memory[b + a];
			b++;
		}
	}
	str[b] = 0;
	free (memory);
	return (str);
}

int	get_next_line(int fd, char **line)
{
	static char	*memory;
	char		*temp;
	int			readresult;

	readresult = 1;
	if (fd <= 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (memory)
	{
		write(1, "\n\nStarting MEMORY: \"", 20);
		ft_print(memory, -1);
		write(1, "\"\n", 2);
	}
	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (-1);
	while ((readresult > 0) && (ft_search(memory) == -1))
	{
		if (memory)
		{
			write(1, "\n\nACTUAL MEMORY: \"", 18);
			ft_print(memory, -1);
			write(1, "\"\n", 2);
		}
		readresult = read(fd, temp, BUFFER_SIZE);
		if (memory)
		{
			write(1, "\n\nACTUAL MEMORY: \"", 18);
			ft_print(memory, -1);
			write(1, "\"\n", 2);
		}
		if (readresult <= -1)
		{
			free(temp);
			return (-1);
		}
		temp[readresult] = 0;
		write(1, "Memo: [", 7);
		if (memory)
			ft_print(memory, -1);
		write(1, "]\nTmp: [", 8);
		ft_print(temp, -1);
		write(1, "]\n\n", 3);
		memory = ft_join(memory, temp);
		//printf("\n%s ", memory);
	}
	*line = linefinder(memory);
	memory = memfinder(memory);

	if (temp)
		free (temp);
	write(1, "\n***** Memory: [", 16);
	ft_print(memory, -1);
	write(1, "] *****\n***** Result: [", 23);
	ft_print(*line, -1);
	write(1, "] *****\n\n", 9);
	return (1);
}

int main()
{
	int a = 1;
	char **line;
	int fd = 1;

	line = malloc(sizeof(char *));
	fd = open("/Users/jvacaris/get_next_line/gnl_testfile", O_RDONLY);
	printf("Buffer size: %d\n", BUFFER_SIZE);
	while (a > 0)
	{
		a = get_next_line(fd, line);
		write(1, "&\n\nLINE SUCCESSFULLY READ! ^_^\n", 32);
		printf("%d: %s\n\n\n", a, *line);
	}
}