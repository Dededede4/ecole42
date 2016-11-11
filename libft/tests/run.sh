#/bin/bash

errs=false
name_prefix="test_"

files=`find . -name "${name_prefix}*.c" -type f -exec basename {} \;`

for path2Test in $files; do
	path2Function="../${path2Test#$name_prefix}"

	echo "========= ${path2Test}  =========";
	rm ./a.out 2> /dev/null
	gcc -Wall -Wextra -Werror $path2Test $path2Function 2> err
	if [ "${?}" = "0" ]; then
		./a.out
		code=$?
		if [ "$code" != "0" ]; then
			echo "Error: return ($code)";
			errs=true
		else
			echo "ok"
		fi
	else
		echo "Erreur de compilation:"
		cat err
		errs=true
	fi
done

if [ "$errs" = false ]
then
	echo "Les tests sont passés."
fi
