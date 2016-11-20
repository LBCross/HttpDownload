all:
	cd init;make;cd ..;
	cd net;make;cd ..;
	cd work;make;cd ..;
	cd http;make;cd ..;
	cd main;make;cd ..;
	cd ..;
	$(CC) -o $(ROOT)/bin/main $(ROOT)/bin/*.o
	$(ROOT)/bin/main
	
#	$(ROOT)/bin/main


