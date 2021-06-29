#include "get_next_line_bonus.h"

char	*firstpart(char *str)
{
	int		a;
	char	*res;

	a = 0;
	if (eolcheck(str))
	{
		while (str[a] != '\n')
			a++;
		res = ft_calloc(a + 1);
		a = 0;
		while (str[a] != '\n')
		{
			res[a] = str[a];
			a++;
		}
	}
	else
		res = ft_strdup(str);
	return (res);
}

char	*secondpart(char *str)
{
	int		a;
	int		b;
	char	*res;

	a = 0;
	b = 1;
	if (eolcheck(str))
	{
		while (str[a] != '\n')
			a++;
		res = ft_strdup(&str[a + 1]);
		free (str);
		return (res);
	}
	else
	{
		free (str);
		return (NULL);
	}
}

int	finalpart(char *buffr, char **line, char **memory, int readresult)
{
	*line = firstpart(buffr);
	*memory = secondpart(buffr);
	if (!readresult)
	{
		free (*memory);
		return (0);
	}
	return (1);
}

void	extraspace(char **memory, char **buffr)
{
	if (*memory)
	{
		*buffr = ft_strdup(*memory);
		free (*memory);
	}
}

int	get_next_line(int fd, char **line)
{
	static char	*memory[FD_SETSIZE];
	char		*temp;
	char		*buffr;
	int			readresult;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || fd > FD_SETSIZE)
		return (-1);
	buffr = NULL;
	readresult = 1;
	extraspace(&memory[fd], &buffr);
	while (!eolcheck(buffr) && readresult > 0)
	{
		temp = ft_calloc(BUFFER_SIZE + 1);
		readresult = read(fd, temp, BUFFER_SIZE);
		if (readresult == -1)
		{
			free (temp);
			return (-1);
		}
		buffr = ft_join(buffr, temp);
	}
	return (finalpart(buffr, line, &memory[fd], readresult));
}
