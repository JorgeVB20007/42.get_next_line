#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int get_next_line(int fd, char **line)
{
	static char	*estatico;
	char		*prestatico;
	char		*preprestatico;
	int			newspace; // newspace can be replaced by i or j.
	int			i;
	int			j;

//	printf("Estatico: %s\n\n  ************\n\n", estatico);

	prestatico = malloc(BUFFER_SIZE + 2);
	newspace = read(fd, prestatico, BUFFER_SIZE);
	prestatico[newspace] = '\n';
	prestatico[newspace + 1] = '\0';
	printf("%%%s%%\n", prestatico);
	if (newspace < 1)
		return (newspace);
	i = 0;
	j = 0;
	if (!estatico)
		preprestatico = malloc(strlen(prestatico) + 1);
	else
		preprestatico = malloc(strlen(estatico) + strlen(prestatico) + 1);
	if (estatico)
		while(estatico[i] != '\0')
		{
			preprestatico[i] = estatico[i];
			i++;
		}
	while(prestatico[j] != '\0')
	{
		preprestatico[i + j] = prestatico[j];
		j++;
	}
	preprestatico[i + j] = '\0';
	free(estatico);
	free(prestatico);
	estatico = preprestatico;
//	free(line);
//	printf("%s\n\n", estatico);
	line = ft_split(estatico, '\n');
	while (*line)
		printf("=== %s ===\n", *line++);
	if (newspace < BUFFER_SIZE)
		return (0);
	return (1);
}


int	main()
{
	int	actresult = 1;
	int fd;
	char **line;
	int a = 0;

	line = NULL;
	fd = open("/Users/jvacaris/get_next_line/gnl_testfile", O_RDONLY);
	while (actresult > 0)
	{
		actresult = get_next_line(fd, line);
		printf("'''''''''^'''''''''^'''''''''^'''''''''^\n\n\n");
		a++;
	}
	if (actresult == 0)
		printf("(0)");
	if (actresult == -1)
		printf("(-1)");
	printf("%d", actresult);
}