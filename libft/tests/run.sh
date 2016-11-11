#/bin/bash

errs=false
rm ./a.out 2> /dev/null


echo "========= ft_memset.c =========";
gcc -Wall -Wextra -Werror test_memset.c ../ft_memset.c > err
if [ "${?}" = "0" ]; then
	./a.out
	code=$?
	if [ "$code" != "0" ]; then
		echo "Error: return ($code)";
		errs=true
	fi
else
	echo "Erreur de compilation:"
	cat err
	errs=true
fi

if [ "$errs" = false ]
then
	echo "Les tests sont passés."
fi
