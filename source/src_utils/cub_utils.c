#include "cub3D.h"

char	*ft_delete_nl(char *str)
{
	int		len;
	char	*tmp;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (str[len - 1] == '\n')
	{
		tmp = ft_substr(str, 0, len - 1);
		ft_free_null_void_return(&str);
		return (tmp);
	}
	return (str);
}
