#include "ft_printf.h"
#include <stdio.h>

size_t		ft_strsize(int *str)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] < 128)
			size++;
		else if (str[i] < 2048)
			size += 2;
		else if (str[i] < 65536)
			size += 3;
		else if (str[i] < 2097152)
			size += 4;
		else
			size += 5;
		i++;
	}
	return (i);
}
/**
**  98  : b
**  0110 0010
**  The first bit is zero. We can send to write.
**
**  233 : é
**  1110 1001
**  Need to apply the mask : 110x xxxx 10xx xxxx
**  0000 0011   10 1001 (= 233)
**  110x xxxx 10xx xxxx
**  =
**  1100 0011 1010 1001 (= C3A9)
**  So, send to write  (write(1, "\xc3\xa9", 2) cause hexa value is C3A9)
**  
**  First, save bits that would have been overwritten by the mask
**  0000 0000 1110 1001
**  &
**  0000 0000 1100 0000 (C0)
**  =
**  0000 0000 1100 0000 (set to "tmp")
**  233 & C0 = C0
** 
**  Secondly, move "tmp" two bits to the left
**  0000 0000 1100 0000 << 2 = 0000 0011 0000 0000 (set to "tmp")
**
**  Thirdly, apply the positive bits of the mask
**  0000 0011 0000 0000
** 	|
**  1100 0000 1000 0000 (C080)
**  =
**  1100 0011 1000 0000
**  
**  Fourthly, apply the negative bits of the mask
**  1101 1111 1011 1111 (DFBF)
**  &
**  1100 0011 1000 0000
**  =
**  1100 0011 1010 0000
**
**	Fifth, save bit no overwritten by the mask (see step one)
**  0000 0000 1110 1001
**  &
**  0000 0000 0011 1111 (3F)
**  0000 0000 0010 1001
**
**  Finally apply bit no overwritten by the mask
**  0000 0000 0010 1001
**  |
**  1100 0011 1010 0000
**  =
**  1100 0011 1010 1001
**  12483 : ッ
**  =========================================================
**  65509 : ￥
**
**  0000 0000 0000 0000 1111 1111 1110 0101
**  Need to apply the mask : 110x xxxx 10xx xxxx 10xx xxxx
**  0000 0000 0000 1111   11 1111   10 0101
**  0000 0000 1110 xxxx 10xx xxxx 10xx xxxx
**  =
**  0000 0000 1100 1111 1011 1111 1010 0101
**  0000 0000 1100 1111 1011 1111 1010 0101
**  0000 0000 1100 1111 1011 1111 1010 0101
**  0000 0000 1110 1111 1011 1111 1010 0101
**
**
**  Algorithm
**  First, save bits that would have been overwritten by the mask
**  0000 0000 0000 0000 1111 1111 1110 0101
**  &
**  0000 0000 0000 0000 1111 1111 1100 0000 (FFC0)
**  =
**  0000 0000 0000 0000 1111 1111 1100 0000
**
**  Secondly, move it two bits to the left
**  0000 0000 0000 0000 1111 1111 1100 0000 << 2 = 0000 0000 0000 0011 1111 1111 0000 0000
**

0000 0000 1110 xxxx 10xx xxxx 10xx xxxx
0000 0000 0000 0000 1111 1111 1100 0000
&
0000 0000 0000 0000 1111 0000 0000 0000 (F000)
=
0000 0000 0000 0000 1111 0000 0000 0000
0000 0000 1110 xxxx 10xx xxxx 10xx xxxx

0000 0000 0000 0000 1111 0000 0000 0000 << 4 = 0000 0000 0000 1111 0000 0000 0000 0000

Purge useless
0000 0000 1110 xxxx 10xx xxxx 10xx xxxx
0000 0000 0000 0011 1111 1111 0000 0000
&
0000 0000 0000 0000 0011 1111 0000 0000 (3F00)
=
0000 0000 0000 0000 0011 1111 0000 0000


Mix
0000 0000 0000 0000 0011 1111 0000 0000
|
0000 0000 0000 1111 0000 0000 0000 0000 ()
=
0000 0000 0000 1111 0011 1111 0000 0000
0000 0000 1110 xxxx 10xx xxxx 10xx xxxx

**  
**  Thirdly, apply the positive bits of the mask
**  0000 0000 0000 1111 0011 1111 0000 0000
**  |
**  0000 0000 1110 0000 1000 0000 1000 0000 (E08080)
**  =
**  0000 0000 1100 1111 1011 1111 1000 0000
**
**  Fourthly, apply the negative bits of the mask
**  0000 0000 1100 1111 1011 1111 1000 0000
**  &
**  1111 1111 1110 1111 1011 1111 1011 1111 (FFEFBFBF)
**  =
**  0000 0000 1100 1111 1011 1111 1000 0000
**
**	Fifth, save bit no overwritten by the mask (see step one)
**  0000 0000 0000 0000 1111 1111 1110 0101
**  &
**  0000 0000 0001 0000 0000 0000 0011 1111 (10003F)
**  =
**  0000 0000 0000 0000 0000 0000 0010 0101
**
**  Finally apply bit no overwritten by the mask
**  0000 0000 0000 0000 0000 0000 0010 0101
**  |
**  0000 0000 1100 1111 1011 1111 1000 0000
**  =
**  0000 0000 1100 1111 1011 1111 1010 0101
**/

void printbits(long v, size_t size) {
  long i; // for C89 compatability
  for(i = --size; i >= 0; i--){
  		ft_putchar('0' + ((v >> i) & 1));
  		if (i % 4 == 0)
  			ft_putchar(' ');
  	};
}

char	*ft_strwrite(int *i_str)
{
	char	*c_str;
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	if (!(c_str = ft_strnew(ft_strsize(i_str))))
		return (NULL);
	while (i_str[i])
	{
		if (i_str[i] < 128)
		{
			c_str[size] = (char)i_str[i];
			size++;
		}
		else if (i_str[i] < 2048)
		{
			int save = i_str[i] & 0xC0;
			save = save << 2;
			save = save | 0xC080;
			save = save & 0xDFBF;

			int save2 = i_str[i] & 0x3F;
			save = save2 | save;

			c_str[size] = (char)(save >> 8);
			c_str[size + 1] = (char)save;
			size += 2;
		}
		else if (i_str[i] < 65536)
		{
			int val = i_str[i];
			int save = val;
			save = save & 0xFFC0;

			int move = save << 2;
			int move2 = save & 0xF000;
			move2 = move2 << 4;
			

			move = move & 0x3F00;

			move = move | move2;
			

			move = move | 0xE08080;
			move = move & 0xFFEFBFBF;

			val = val & 0x10003F;
			

			int result = val | move;
			c_str[size] = (char)(result >> 16);
			c_str[size + 1] = (char)(result >> 8);
			c_str[size + 2] = (char)(result);

			size += 3;
		}
		else if (i_str[i] < 2097152)
		{
			size += 4;
		}
		i++;		
	}
	return c_str;
}

void	ft_wputstr(int *str)
{
	char *output = ft_strwrite(str);
	write(1, output, ft_strlen(output));
}




void	ft_printf_wputstr(wchar_t *str, t_args *a)
{
	size_t	spaces;
	size_t len;

	len = 0;
	if (a->precision == -1)
		while (str[len])
			len++;
	else
		while (str[len] && len < (size_t)a->precision)
			len++;
	spaces = a->width - len;
	if (a->width != -1)
		a->tmp = a->width;
	else
		a->tmp = len;
	if (a->width != -1 && a->minus == -1)
		while (spaces--)
			ft_putchar(' ');
	write(1, str, len * sizeof(wchar_t));
	if (a->width != -1 && a->minus != -1)
		while (spaces--)
			ft_putchar(' ');
}

int		ft_printf_not_printable(void *s)
{
	wchar_t c;

	/*ft_putchar('*');
	write(1, s, 4);*/
	c = *((wchar_t*)s);
	if (c == L'\n')
	{
		return (1);
	}
	return (0);
}

void	ft_rwwrite(int fd, wchar_t *str, size_t len)
{
	wchar_t		*finded;

	if (*str == L'\0')
		return;
	finded = ft_memchrf(str, ft_printf_not_printable, len * 4);
	if (finded == NULL)
	{
		write(fd, str, len * sizeof(wchar_t));
	}
	else
	{
		write(fd, str, (finded - str) * 4);
		if (*finded == L'\n')
		{
			write(fd, L"\\n", 8);
		}
		else
			write(fd, finded, 4);
		ft_rwwrite(fd, finded + 1, len - 1 - ((finded - str)));
	}
}

void	ft_printf_rwputstr(wchar_t *str, t_args *a)
{
	size_t	spaces;
	size_t len;

	len = 0;
	if (a->precision == -1)
		while (str[len])
			len++;
	else
		while (str[len] && len < (size_t)a->precision)
			len++;
	spaces = a->width - len;
	if (a->width != -1)
		a->tmp = a->width;
	else
		a->tmp = len;
	if (a->width != -1 && a->minus == -1)
		while (spaces--)
			ft_putchar(' ');
	ft_rwwrite(1, str, len);
	if (a->width != -1 && a->minus != -1)
		while (spaces--)
			ft_putchar(' ');
}
