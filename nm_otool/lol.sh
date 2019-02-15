echo $(wc -c $1 | awk '{print $1}')

newfsize=$(expr $(wc -c $1 | awk '{print $1}') - 21)

while [ "$newfsize" -ge 0 ]
do
	newfsize=$(expr $(wc -c $1 | awk '{print $1}') - 21)
       head -c $newfsize $1 > .tmp
		mv .tmp $1

		ls -l $1
done
