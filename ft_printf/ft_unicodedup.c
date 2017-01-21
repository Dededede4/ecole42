#include "ft_printf.h"

t_unicode	*ft_unicodedup(const t_unicode *s1)
{
	t_unicode	*s2;
	int			len;

	len = ft_unicodelen(s1) + 1;
	s2 = malloc((sizeof(*s2) * len));
	if (!s2)
		return (NULL);
	ft_intcpy(s2, s1, len);
	return (s2);
}
