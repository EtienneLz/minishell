#include <unistd.h>
#include <stdio.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
}

int	main()
{
	/*char *str;

	str = "\0";
	ft_putstr_fd(str, 2);
	printf("\nok\n");*/
	while (1)
		printf("go\n");
}
