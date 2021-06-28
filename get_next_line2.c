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
	int			a;
//	printf("\n@@%s@@\n", mem);
	line = malloc(sizeof(char *));
	a = 0;
	if (mem)
	{
		if (ft_search(mem, '\n') < 0)
		{
			*line = ft_strdup(mem);
			free(mem);
		}
		else
		{
			*line = ft_copyandfree(mem, ft_search(mem, '\n'));
			str = ft_strdup(&mem[ft_search(mem, '\n') + 1]);
			free(mem);
			mem = ft_strdup(str);
			free(str);
//			printf("(a) %s", *line);
			return (1);
		}
	}
	else
	{
		*line = malloc(sizeof(char *));
		*line[0] = '\0';
	}
	while (1)
	{
		str = malloc(BUFFER_SIZE + 1);
//		printf("%s, ", str);
		resp = read(fd, str, BUFFER_SIZE);
//		printf("%d %s					%s\n", resp, *line, str);
		if (resp == 0 || resp == -1)
		{
//			printf("(b) %s", *line);
			return (resp);
		}
		if (resp < BUFFER_SIZE)
		{
			str[resp] = 0;
			*line = ft_strjoin(*line, str);
		}
		else
			*line = ft_strjoin(*line, str);
		if (ft_search(str, '\n') != -1)
		{
			mem = ft_strdup(&str[ft_search(str, '\n') + 1]);
			free(str);
			printf("(c) %s", *line);
			return (1);
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
//		printf("- %s\n", *line);
	}
}