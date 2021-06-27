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
	write(1, " {", 2);
	ft_print(result, -1);
	write(1, "}\n", 2);
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
	str = malloc(a + 1);
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

	write(1, "$ ", 2);
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

	readresult = 1;
	if (fd <= 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
		if (memory)
			ft_print(memory, -1);
	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (-1);
	while ((readresult > 0) && (ft_search(memory) == -1))
	{
		readresult = read(fd, temp, BUFFER_SIZE);
		write(1, "\n__ ", 4);
		if (memory)
			ft_print(memory, -1);
		write(1, " __\n", 4);
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
		write(1, "\n>> ", 4);
		ft_print(memory, -1);
		write(1, " <<\n", 4);
		//printf("\n%s ", memory);
	}
	
	write(1, " :DDDDDDDDDDDDDDDD \n", 20);
	*line = linefinder(memory);
	memory = memfinder(memory);
	free (temp);
	write(1, "\n***** Memory: [", 16);
	ft_print(memory, -1);
	write(1, "] *****\n***** Result: [", 22);
	ft_print(*line, -1);
	write(1, "] *****\n\n", 9);
	return (readresult);
}

int main()
{
	int a = 1;
	char **line;
	int fd = 1;

	line = malloc(sizeof(char *));
	fd = open("/Users/jvacaris/get_next_line/gnl_testfile", O_RDONLY);
	printf(">> %d\n", BUFFER_SIZE);
	while (a > 0)
	{
		write(1, "& ", 1);
		a = get_next_line(fd, line);
		write(1, "&\n", 2);
		printf("%c\n%s\n", a + 48, *line);
	}
}