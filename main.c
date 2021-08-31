#include "lookup.h"

#include <string.h>
#include <stdio.h>

void usage(char* name){
	printf("%s <name>\n", name);
	printf("  name - the file/directory to search for.\n");
	printf("Searches go up the current directory tree, in the\n");
	printf("  same way git searches for it's config directory.\n");
}

int main(int argc, char** argv){

	if( argc < 2 ){
		usage( argv[0] );
		return 1;
	}

	return lookup( argv[1], strlen(argv[1]));
}
