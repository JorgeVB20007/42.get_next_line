#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int	get_next_line(int fd, char **line)
{
	static char	*counter;
	char		*str;
	int			result;

	printf("fd: %d\n", fd);
	line = NULL;
	str = malloc(sizeof(char) * BUFFER_SIZE + 1);
	printf("Malloc: %lu\n", sizeof(char) * BUFFER_SIZE + 1);
	result = read(fd, str, BUFFER_SIZE);
	counter = counter + BUFFER_SIZE;
	printf("Result: %d\n", result);
	printf("Resultstr: %s\n", str);
	return (result);
}

int	main()
{
	int	actresult = 1;
	int fd;
	char **line;

	line = NULL;
	fd = open("/Users/jvacaris/get_next_line/gnl_testfile", O_RDONLY);
	while (actresult > 0)
	{
		actresult = get_next_line(fd, line);
		printf("1\n\n");
	}
	if (actresult == 0)
		printf("(0)");
	if (actresult == -1)
		printf("(-1)");
	printf("%d", actresult);
}