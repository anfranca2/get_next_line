#include "get_next_line.h"
#include <stdio.h>

int	main()
{
	int	fd;
	char	buf[256];
	int		chars_read;

	fd = open("test.txt", O_RDONLY);

	while ((chars_read = read(fd, buf, 250)))
	{
		buf[chars_read] = '\0';
		printf("%s\n", buf);
	}
}
