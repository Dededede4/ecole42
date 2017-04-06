rm zaz.* me.*
#FILES=`find ../.. | grep "\.s$"`
FILES=`find ../..`
for path in $FILES
do
	echo $path
	cp $path zaz.s
	cp $path me.s
	../../samples_files/asm_zaz zaz.s
	../asm me.s
	if [ $? != 0 ]
	then
		exit;
	fi
	hexdump zaz.cor > zaz.txt
	hexdump me.cor > me.txt
	diff me.txt zaz.txt
	if [ $? != 0 ]
	then
		echo $path
		exit;
	fi
	rm -f zaz.s me.s zaz.txt me.txt
done
