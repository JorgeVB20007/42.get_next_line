#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int	get_next_line(int fd, char **line)
{
	static char	*mem;
	int			resp;
	char		*str;

	line = malloc(sizeof(char *));
	if (mem)
	{
		printf("@");
		*line = ft_strdup(mem);
		if (ft_search(mem, '\n') < 0)
		{
			printf("|%d|", ft_search(mem, '\n'));
			free(mem);
		}
		else
		{
			printf("|%d|", ft_search(mem, '\n'));
			printf("\n/// %s ///\n", *line);
			line[ft_search(mem, '\n') + 1] = 0;
			printf("\n/// %s ///\n", *line);
			free(line[ft_search(mem, '\n') + 1]);
			printf("\n/// %s ///\n", *line);
			str = ft_strdup(&mem[ft_search(mem, '\n') + 1]);
			free(mem);
			mem = str;
			printf("(a) %s", *line);
			return (1);
		}
	}
	*line = malloc(sizeof(char *));
	*line[0] = '\0';
	while (1)
	{
		str = malloc(BUFFER_SIZE + 1);
		resp = read(fd, str, BUFFER_SIZE);
		if (resp == 0 || resp == -1)
		{
			printf("(b) %s", *line);
			return (resp);
		}
			
		*line = ft_strjoin(*line, str);
		if (ft_search(str, '\n') != -1)
		{
			mem = ft_strdup(&str[ft_search(str, '\n') + 1]);
			printf("(c) %s", *line);
			return (1);
		}
		else if (ft_strlen(str) < BUFFER_SIZE)
		{
			printf("(d) %s", *line);
			return (0);
		}
			
		free(str);
	}
	
}


int main()
{
	int fd;
	char **line;
	int actresult;

	fd = open("/Users/jvacaris/get_next_line/gnl_testfile", O_RDONLY);
	actresult = 1;
	while (actresult > 0)
	{
		line = NULL;
		actresult = get_next_line(fd, line);
		printf("-\n");
	}
}