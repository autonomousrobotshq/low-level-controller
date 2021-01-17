#!/bin/sh

# copy and rename
for dir in */ ; do
	dir="$(echo $dir|tr -cd '[:alnum:]')"
	(
		cd $dir
		for file in ./*; do
			name="$(echo $file|cut -d. -f2 |tr -cd '[:alnum:]')"
			ext="$(echo $file | rev | cut -f1 -d. | rev)"
			if [ $ext == "cpp" ] || [ $ext == "hpp" ]; then
				[ $dir == "$name" ] && nFile="../$name.$ext" || nFile=../${dir}_${name}.$ext
				cp $file $nFile
				sed -i 's/$dir\/$name/$dir$name/g' $nFile
			fi
		done
	)
done


# replace all names
for dir in */ ; do
	dir="$(echo $dir|tr -cd '[:alnum:]')"
	(
		cd $dir
		for file in ./*; do
			name="$(echo $file|cut -d. -f2 |tr -cd '[:alnum:]')"
			ext="$(echo $file | rev | cut -f1 -d. | rev)"
			if [ $ext == "cpp" ] || [ $ext == "hpp" ]; then
				[ $dir == "$name" ] && nFile="../$name.$ext" || nFile=../${dir}_${name}.$ext
				(
					for file in ../*; do 
						ext="$(echo $file | rev | cut -f1 -d. | rev)"
						if [ "$ext" == "cpp" ] || [ "$ext" == "hpp" ]; then
							sed -i "s,${dir}/${name},${dir}_${name},g" $file
						fi
					done
				)
			fi
		done
	)
done

