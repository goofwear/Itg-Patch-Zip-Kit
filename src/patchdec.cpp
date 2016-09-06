#include <iostream>
#include <fstream>
#include "StdString.h"
#include "sha512.h"
#include "aescpp.h"
#include "aesopt.h"
#include <fcntl.h>
#include <memory.h>

typedef unsigned char uchar;

using namespace std;

const char *patchkey = "58691958710496814910943867304986071324198643072";

inline void printIntro();
void usage(char *);

int main(int argc, char *argv[])
{
	char *header, *workingDir, *chrBuf1, *chrBuf2, *outFile;
	int numcrypts, workingDirLen = 0;
	FILE *fdin, *fdout;
	unsigned int fileSize, subkeySize;
	CString SHASecret("");
	uchar SHADigest[65];
	uchar AESKey[24];
	uchar encbuf[4081], decbuf[4081];
	unsigned int dec_recv = 0;
	char var_178[16];
	long long totalbytes = 0;

	AESdecrypt ct;
	uchar checkbuf_in[16], checkbuf_out[16], subkey[1024];

	printIntro();

	encbuf[4080] = '\0';
	decbuf[4080] = '\0';

	if (argc < 2) {
		usage(argv[0]);
		return 0;
	}

	if (strstr(argv[1], "patch-dec.zip"))
	{
		cerr << "the source file cannot be named patch-dec.zip\n";
		return -1;
	}

	chrBuf1 = strchr(argv[1], '\\');
	if (chrBuf1 != NULL) {
		while (chrBuf1 != NULL) {
			chrBuf2 = chrBuf1;
			chrBuf1 = strchr(chrBuf1+1, '\\');
		}
		workingDirLen = chrBuf2 - argv[1] + 1;
		workingDir = (char*)malloc(sizeof(char) * workingDirLen);
		strncpy(workingDir, argv[1], workingDirLen);
		outFile = (char*)malloc(sizeof(char) * workingDirLen + 14);
		strcpy(outFile, workingDir);
		strcpy(outFile+workingDirLen, "patch-dec.zip");
		outFile[workingDirLen+13] = '\0';
	} else {
		outFile = "patch-dec.zip";
	}

	fdin = fopen(argv[1], "rb");
	fdout = fopen(outFile, "wb");

	header = new char(3);
	header[2] = '\0';

	if (! fdin )
	{
		cerr << "cannot open input file " << argv[1] << " (typo perhaps?) :(\n";
		return -1;
	}
	if (! fdout ) {
		cerr << "cannot open output file " << outFile << " :(\n";
		return -1;
	}
	//read(fdin, header, 2);
	fread(header, 2, 1, fdin);
	if (strcmp(header, "8O") != 0)
	{
		cerr << argv[1] << " is not an encrypted patch file :\\\n";
		return -1;
	}

	//read(fdin, &fileSize, 4);
	fread(&fileSize, 4, 1, fdin);
	
	printf("file size: %d bytes\n", fileSize);

	//read(fdin,(char*)&subkeySize, 4);
	fread((char*)&subkeySize, 4, 1, fdin);
	
	cout << "subkey size: " << subkeySize << "\n";

	//subkey = new uchar(subkeySize+1);
	
	//read(fdin, subkey, subkeySize);
	fread(subkey, subkeySize, 1, fdin);
	
	SHASecret.append(subkey, subkeySize);
	SHASecret.append(patchkey, 47);

	cout << "SHA512 Message length: " << SHASecret.length() << endl;

	SHA512_Simple(SHASecret.c_str(), subkeySize+47, SHADigest);

	SHADigest[64] = '\0';

	strncpy((char*)AESKey, (char*)SHADigest, 24);

	ct.key(AESKey, 24);

	cout << "verifying encryption key magic...";
	
	//read(fdin,(char*)checkbuf_in, 16);
	fread((char*)checkbuf_in, 16, 1, fdin);

	ct.decrypt(checkbuf_in, checkbuf_out);

	if (strstr((char*)checkbuf_out, ":D") != NULL)
	{
		cout << "verified :D\n";
	} else {
		cout << "VERIFICATION FAILED D:\n";
		return 1;
	}

	cout << "Writing to patch-dec.zip: 0%     ";
	putchar(0x0d);


	do
	{

		printf("Decrypting %s: %d%%     ", argv[1], ((totalbytes * 100) / fileSize));
		putchar(0x0d);


		//if ((dec_recv = read(fdin,encbuf, 4080)) == -1)
		if ((dec_recv = fread(encbuf, 1, 4080, fdin)) == -1)
		{
			cerr << "read() returned -1, bad shit happened :(\n";
			close(fdin);
			close(fdout);
			return 1;
		}
		numcrypts = dec_recv / 16;
		totalbytes += dec_recv;

		memset(var_178, '\0', 16);

		for (int j = 0; j < numcrypts; j++)
		{
			//memcpy(checkbuf_in, encbuf+(j*16), 16);
	
			ct.decrypt(encbuf+(j*16), checkbuf_out);
			for (int i = 0; i < 16; i++)
			{
				checkbuf_out[i] ^= (((unsigned char)var_178[i]) - i);
			}
			memcpy(var_178, encbuf+(j*16), 16);
			memcpy(decbuf+(j*16),checkbuf_out,16);
		}

		//write(fdout,decbuf, dec_recv);
		fwrite(decbuf, 1, dec_recv, fdout);

	} while (dec_recv > 0);

	cout << "Encrypting " << argv[1] << ": done\n";

	fclose(fdin);
	fclose(fdout);
	return 0;
}

// because...
inline void printIntro()
{
	cout << "ITG2 Arcade patch.zip decrypter (c) 2007 infamouspat\n\n";
}

void usage(char *argv0)
{
	cout << "Usage: " << argv0 << " <patch.zip location>\n--- decrypted contents will be placed in patch-dec.zip";
}
