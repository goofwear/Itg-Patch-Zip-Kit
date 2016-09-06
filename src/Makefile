all: patchdec patchenc

crypto:
	gcc -c sha512.c -o sha512.o
	gcc -c aeskey.c -o aeskey.o
	gcc -c aestab.c -o aestab.o
	gcc -c aescrypt.c -o aescrypt.o

patchdec: crypto
	g++ -c patchdec.cpp -o patchdec.o -fpermissive
	g++ -o patchdec.exe patchdec.o sha512.o aeskey.o aestab.o aescrypt.o

patchenc: crypto
	g++ -c patchenc.cpp -o patchenc.o -fpermissive
	g++ -o patchenc.exe patchenc.o sha512.o aeskey.o aestab.o aescrypt.o
	

clean:
	rm -f patch-dec.zip
	rm -f keytrace.txt
	rm -f patchenc.exe patchdec.exe *.o

