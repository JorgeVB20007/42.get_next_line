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
	int			i;

	while(1)
	{
		str = malloc(BUFFER_SIZE + 1);
		resp = read(fd, str, BUFFER_SIZE);
		if (resp == 0 || resp == -1)
			return (resp);
		str[resp] = '\0';
		i = 0;
		while (str[i] != 0 || str[i] != '\n')
			i++;
		if (!line)
			*line = malloc(i + 1);
		else
		{
			*line = ft_strjoin(*line, str);
		}
		if (BUFFER_SIZE > i)
		{
			free(mem);
			return (0);
		}
		if (str[i] == '\n')
		{
			mem = ft_strdup(&str[i + 1]);
			return (1);
		}
		free(str);
	}
}

int main()
{

}