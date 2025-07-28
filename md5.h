#ifndef MD5_H
#define MD5_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include<openssl/md5.h>

/*
 * Create an MD5 hex digest from a string.asm
 * 33-byte string is malloc'd by this functions
 */
char* md5(const char *str, int length);

#endif