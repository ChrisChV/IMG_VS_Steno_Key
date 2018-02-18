#!/bin/bash
rm -f resultados
for lsb in 1 2 3
do
	echo "lsb -> $lsb" >> resultados
	for img in 3600 62500 250000 480000 960000 1920000
	do
		echo "img -> $img" >> resultados
		for msg in 64 256 1024 8192 32768 524288
		do
			echo "msg -> $msg" >> resultados
			echo "./run -h  imgs/$img.bmp  msgs/$msg $lsb"
			./run -h imgs/$img.bmp  msgs/$msg $lsb >> resultados
			cp imgs/$img.cover.bmp  imgs/covers/
			echo "cp imgs/$img.cover.bmp  imgs/covers/"
			echo "./run -p imgs/$img.bmp  imgs/covers/$img.cover.bmp"
			./run -p imgs/$img.bmp  imgs/covers/$img.cover.bmp >> resultados
		done
	done
done

