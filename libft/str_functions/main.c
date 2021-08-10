#include "libft.h"

int main()
{
	char	**splited;
	int		i = 0;

	splited = ft_split("aaacaaacaaa", 'c');
	while (splited[i])
		printf("%s\n", splited[i++]);

}