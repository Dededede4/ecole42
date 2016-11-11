#/bin/bash

errs=false
name_prefix="test_"

if [ -z "$1" ]; then
	files=`find . -name "${name_prefix}*.c" -type f -exec basename {} \;`
else
	files=$1
fi

for path2Test in $files; do
	path2Function="../${path2Test#$name_prefix}"

	echo "========= ${path2Test}  =========";
	rm ./a.out err errNorme 2> /dev/null

	norminette $path2Function
	echo ""
	gcc -Wall -Wextra -Werror $path2Test ../ft_*.c 2> err
	if [ "${?}" = "0" ]; then
		./a.out
		code=$?
		if [ "$code" != "0" ]; then
			echo "Test error: return ($code)";
			errs=true
		else
			echo "Test: ok"
		fi
	else
		echo "Erreur de compilation :"
		cat err
		errs=true
	fi
done

if [ "$errs" = false ]
then
	echo -e "\nLes tests sont passés."
fi
