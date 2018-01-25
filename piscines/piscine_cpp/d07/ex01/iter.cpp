#include <iostream>

template < typename T>
void iter(T * array, size_t length, void (*f)(T))
{
	size_t i = 0;

	while (i < length)
		f(array[i++]);
}

template < typename T>
void display(T x) {
	std::cout << x << std::endl;
}

int main()
{
	int truc[] = {12, 24, 56};
	std::string machins[] = {"Y'a pas de saisons pour que vive la musique", "Laisse tomber les filles"}; 
	iter(truc, 3, ::display);
	iter(machins, 2, ::display);
	return (0);
}
