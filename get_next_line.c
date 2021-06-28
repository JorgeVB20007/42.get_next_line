#include "get_next_line.h"


/****************************
*                           *
*       GNL       HERE      *
*                           *
****************************/

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

int	get_next_line(int fd, char **line)
{
	static char	*memory;
	char		*temp;
	char		*buffr;
	int			readresult;

	if (fd <= 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	buffr = NULL;
	readresult = 1;
	if (memory)
	{
		buffr = ft_strdup(memory);
		free (memory);
	}
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
	*line = firstpart(buffr);
	memory = secondpart(buffr);
//	printf("Memory = '%s'\n", memory);
	if (!readresult)
	{
		free (memory);
		return (0);
	}
	return (1);
}

/*
int main()
{
	int a = 1;
	char **line;
	int fd = 1;
	int b = 0;

	line = malloc(sizeof(char *));
	fd = open("/Users/jvacaris/get_next_line/gnl_testfile", O_RDONLY);
	printf("Buffer size: %d\n", BUFFER_SIZE);
	while (a > 0 && b < 15)
	{
		a = get_next_line(fd, line);
		write(1, "LINE SUCCESSFULLY READ! ^_^\n", 28);
		printf("%d: %s\n\n", a, *line);
		b++;
	}
}*/