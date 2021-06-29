#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

int		get_next_line(int fd, char **line);
char	*ft_calloc(int a);
int		eolcheck(char *str);
int		ft_strlen(char *s);
char	*ft_strdup(char *s1);
char	*ft_join(char *orig, char *add);

#endif