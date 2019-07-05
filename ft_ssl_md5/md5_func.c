#include "ft_ssl.h"


uint32_t	func_f(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) | ((~x) & z));
}

uint32_t	func_g(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & z) | (y & (~z)));
}

uint32_t	func_h(uint32_t x, uint32_t y, uint32_t z)
{
	return (x ^ y ^ z);
}

uint32_t	func_i(uint32_t x, uint32_t y, uint32_t z)
{
	return (y ^ (x | (~z)));
}