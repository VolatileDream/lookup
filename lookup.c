
// errno.
#include <errno.h>

#include <stdlib.h>

// for printf
#include <stdio.h>

void usage(char* name){
	printf("%s <name>\n", name);
	printf("  name - the file/directory to search for.\n");
	printf("Searches go up the current directory tree, in the\n");
	printf("  same way git searches for it's config directory.\n");
}

// for stat, getcwd
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef PATH_MAX
// PATH_MAX is defined on some systems
#define PATH_START_LENGTH PATH_MAX
#else
#define PATH_START_LENGTH 2048
#endif

static int get_path_r(char** out, size_t len){

	char * path_buffer = (char*)malloc(len);

	char * _t = getcwd(path_buffer, len);

	if( _t ){
		// success, we got the current path
		*out = path_buffer;
		return 0;
	}

	int err = errno;

	free(path_buffer);

	if( errno == ERANGE ){
		return get_path_r( out, len * 2 );
	}

	errno = err; // in case the free() would clear it

	perror("getpwd");

	return -1; // an error occured that we can not recover from.
}

// allocates a char* to hold the PWD
static int get_path(char** out){

	*out = NULL; // just in case someone is silly...

	return get_path_r(out, PATH_START_LENGTH);
}

// for strlen
#include <string.h>

static int lookup(char * lookup_name, int len){

	char * mutable_path = NULL;

	int rc = get_path( &mutable_path );

	if( rc != 0 ){
		return rc;
	}

	size_t path_len = strlen(mutable_path);

	char * tmp_path = mutable_path;

	// length of pwd + file name + trailing '/' + null byte
	mutable_path = (char*)malloc(path_len+len+2);

	// Doesn't do a null byte copy, we're about to write that in.
	memcpy( mutable_path, tmp_path, path_len );

	// cleanup after the old path
	free(tmp_path);
	tmp_path = NULL;

	// trailing slash was not included by getcwd
	mutable_path[path_len] = '/';
	mutable_path[path_len + 1] = '0';

	size_t offset = path_len; // always points at the last '/' in the path

	while( offset > 0 ){
		// copy in the lookup name
 		// include trailing slash for offset
		memcpy( mutable_path + offset + 1, lookup_name, len + 1 );

		struct stat data;

		rc = stat( mutable_path, &data );

		if( rc && errno != ENOENT ){
			break;
		}

		if( ! rc ){
			printf("%s\n", mutable_path);
			free(mutable_path);
			return 0;
		}

		// subtract one from offset, because it's currently a '/'
		offset--;

		// otherwise it doesn't exist, so get ready to look again
		while( offset && mutable_path[offset] != '/' ){
			offset--;
		}
	}

	// we ran out of path.

	fail:

	free(mutable_path);
	return 1;
}

int main(int argc, char** argv){

	if( argc < 2 ){
		usage( argv[0] );
		return 1;
	}

	return lookup( argv[1], strlen(argv[1]));
}
