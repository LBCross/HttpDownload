#bin/bash/
export ROOT=`pwd`
if [ $# == 0 ]; then
	mkdir -p bin;
	cd src/;
	make;
	
elif [ $# == 1 ]; then
	if [ $1 == 'clean' ]; then
		rm -rf bin/* bin/main;
		cd src/;
	fi
fi
