#include "../cub3d.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str && str[count] != '\0')
		count++;
	return (count);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	return (s1[i] - s2[i]);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*s1_now;
	char	*s2_now;
	char	*res;
	int		i;

	if (s2 == NULL)
		return ((char *)s1);
	i = 0;
	s1_now = (char *)s1;
	s2_now = (char *)s2;
	res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (res == 0)
		return (NULL);
	while (s1 && *s1_now != '\0')
		res[i++] = *s1_now++;
	while (*s2_now != '\0')
		res[i++] = *s2_now++;
	res[i] = '\0';
	free(s1);
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	char	*s_now;

	s_now = (char *)s;
	while ((int)*s_now != c && *s_now != '\0')
		(void)*s_now++;
	if ((int)*s_now == c)
		return (s_now);
	else
		return (0);
}

void	*ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*k;

	i = 0;
	k = s;
	while (i < n)
	{
		k[i] = '\0';
		i++;
	}
	return (s);
}
