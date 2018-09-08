int main(void)
{
	malloc(10000);
	realloc(malloc(10000), 10001));
	free(0);
	return (0);
}
