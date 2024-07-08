#include "stdlib.h"
#include "unistd.h"

int		close_quotes(char *s)
{
	char	*ptr;

	ptr = NULL;

	while (*s)
	{
		if (ptr == NULL && (*s == '\'' || *s == '\"'))
			ptr = s;
		if (s != ptr && ptr && *ptr == *s)
			ptr = NULL;
		s++;
	}
	if (ptr == NULL)
		return (1);
	return (0);
}

int main(void)
{
	return(close_quotes(""));
}