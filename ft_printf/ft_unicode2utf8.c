#include "ft_printf.h"

size_t		ft_charsize(t_unicode c)
{
	if ((int)c < 128)
		return 1;
	else if ((int)c < 2048)
		return 2;
	else if ((int)c < 65536)
		return 3;
	else if ((int)c < 2097152)
		return 4;
	else
		return 5;
}

size_t		ft_strsize(t_unicode *str)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		size += ft_charsize(str[i]);
		i++;
	}
	return (size);
}

void printbits2(long v, size_t size) {
  long i; // for C89 compatability
  for(i = --size; i >= 0; i--){
                ft_putchar('0' + ((v >> i) & 1));
                if (i % 4 == 0)
                        ft_putchar(' ');
        };
}


t_utf8		*ft_unicode2utf8(t_unicode *i_str, size_t *size)
{
	t_utf8	*c_str;
	size_t	i;

	i = 0;
	*size = 0;
	if (!(c_str = (t_utf8*)ft_strnew(ft_strsize(i_str) + 1)))
		return (NULL);
	while (i_str[i])
	{
		size_t chars = ft_charsize(i_str[i]);
		int		nbr;
		int		save = i_str[i];

		if (i_str[i] < 0 || i_str[i] > 1114112 ||
			(i_str[i] >= 55296 && i_str[i] <= 57343))
			return (NULL);
		nbr = 0;
		if (chars == 1)
		{
			c_str[*size] = (t_utf8)i_str[i];
			i++;
			(*size)++;
			continue;
		}
		else if (chars == 2)
			nbr = 0xC080;
		else if (chars == 3)
			nbr = 0xE08080;
		else if (chars == 4)
			nbr = 0xF0808080;
		int 	toWrite = 0x3F;
		while (chars--)
		{
			nbr = (nbr | (save & toWrite));			
			save = save << 2;
			toWrite = toWrite << 8;
		}

		/*printbits2(nbr, 32);
		ft_putchar('\n');*/
		chars = ft_charsize(i_str[i]);
		(*size) += chars;
		while (chars--)
			c_str[(*size) - chars - 1] = (t_utf8)(nbr >> (8 * (chars)));
		i++;		
	}
	return c_str;
}