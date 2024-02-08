end=$1
if [ $end -le 0 ];
then
	echo "Upp bound wanna be positive"
else
	start=1
	while [ $start -le $end ]
	do
		echo $start
		(( start++ ))
	done
fi
