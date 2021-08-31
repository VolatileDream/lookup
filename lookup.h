#ifndef __LOOKUP_H__
#define __LOOKUP_H__

// Given the name of a file or directory to search for, recursively
// go up the file tree to find it.
//
// Returns 0 when found, and sets *outpath to point to allocated
//   memory containing the path. Callers must free it.
// Returns non-zero on error.
int lookup(char * lookup_name, int len, char** outpath);

#endif /* __LOOKUP_H__ */
