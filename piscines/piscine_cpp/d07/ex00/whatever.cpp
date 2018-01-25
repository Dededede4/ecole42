#include <iostream>

template < typename T>
T const & max (T const & x , T const & y) {
	return (x >= y ? x : y);
}

template < typename T>
T const & min (T const & x , T const & y) {
    return (x <= y ? x : y);
}

template < typename T>
void swap(T & x, T & y) {
	T tmp;

	tmp = x;
	x = y;
	y = x;
}

int main()
{
	std::cout << max(42, -42) << std::endl;
	std::cout << min(42, -42) << std::endl;

	std::string str = "str";
	std::string str2 = "str2";
	
	swap(str, str2);

	std::cout << str << " " << str2 << std::endl;
	
	int a = 2;
	int b = 3;

	::swap( a, b );
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
	std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
	std::string c = "chaine1";
	std::string d = "chaine2";
	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
	std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;

	return (0);
}
