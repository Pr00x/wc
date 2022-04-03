#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#define VERSION "v1.0.0"

unsigned long long chars(const char *str) {
	FILE *file = fopen(str, "r");

	if(!file) {
		char err[strlen(str) + 5];
		err[0] = 'w';
		err[1] = 'c';
		err[2] = ':';
		err[3] = ' ';
		strcat(err, str);
		perror(err);
		exit(-1);
	}

	int c;
	unsigned long long i = 0;

	while((c = fgetc(file)) != EOF)	i++;
	
	fclose(file);

	return i;
}

unsigned int lines(const char *str) {
	FILE *file = fopen(str, "r");

	if(!file) {
		char err[strlen(str) + 5];
    err[0] = 'w';
    err[1] = 'c';
    err[2] = ':';
    err[3] = ' ';
    strcat(err, str);
    perror(err);
		exit(-1);
	}

	int c;
	unsigned int i = 0;
	
	while((c = fgetc(file)) != EOF && i < 10000000)
		if(c == '\x0A')
			i++;

	fclose(file);
	
	return i;
}

unsigned int words(const char *str) {
	FILE *file = fopen(str, "r");

	if(!file) {
		char err[strlen(str) + 5];
    err[0] = 'w';
    err[1] = 'c';
    err[2] = ':';
    err[3] = ' ';
    strcat(err, str);
    perror(err);
		exit(-1);
	}

	int c;
	unsigned int i = 0;
	char prev;

	while((c = fgetc(file)) != EOF) {
		if((prev != ' ' && prev != '\x0A') && (c == ' ' || c == '\x0A'))	i++;
		prev = c;
	}

	fclose(file);

	return i;
}

int main(int argc, char **argv) {
	if(argc < 2) {
		putchar('\x0A');
		return -1;
  }
  else if(*(argv + 1) && (strncmp(*(argv + 1), "--help", 7) == 0 || strncmp(*(argv + 1), "-h", 3) == 0)) {
    puts("EloDev wc, a rewrite of GNU wc.\x0AUsage:\x0A\twc [OPTION]... [FILE]...\x0A\twc [OPTION]... --files0-from=F\x0APrint newline, word, any byte counts for each FILE, and a total line if\x0Amore than one FILE is specified. A word is a non-zero-length sequence of\x0Aprintable characters delimited by white space.\x0A\x0AWith no FILE, or when FILE is -, read standard input.\x0A\x0AThe option below may be used to select which counts are printed, always in\x0Athe following order: newline, word, character, byte, maximum line length.\x0A\t-c, --bytes\t\tprint the byte counts\x0A\t-m, --chars\t\tprint the character counts\x0A\t-l, --lines\t\tprint the newline counts\x0A\t--files0-from=F\tread input from the files specified by\x0A\t\t\tNULL-terminated names in file F;\x0A\t\t\t\tIf F is - then read names from standard input\x0A\t-L, --max-line-length\tprint the maximum display width\x0A\t-w, --words\t\tprint the word counts\x0A\t--help\t\t\tdisplay this help and exit\x0A\t-v, --version\t\toutput version and exit.\x0A\nAuthor: ProX - <https://www.github.com/Pr00x/>");
  return 0;
  }
	else if(*(argv + 1) && (strncmp(*(argv + 1), "--version", 10) == 0 || strncmp(*(argv + 1), "-v", 3) == 0)) {
    printf("%s\x0A\x0AWritten by Prox - <https://github.com/Pr00x/>\x0A", VERSION);
    return 0;
  }
	else if(argc == 2) {
    printf("%llu %u %u %s\x0A", lines(*(argv + 1)), words(*(argv + 1)), chars(*(argv + 1)), *(argv + 1));
    return 0;
  }
	
	struct option long_args[] = {
		{ "bytes", 0, 0, 'c' },
		{ "chars", 0, 0, 'm' },
		{ "lines", 0, 0, 'l' },
		{ "files0-from=F", 0, 0, 0 },
		{ "max-line-length", 0, 0, 'L' },
		{ "words", 0, 0, 'w' },
		{ NULL, 0, 0, 0 }
	};

	int opt;

	while((opt = getopt_long_only(argc, argv, "cmlLwv", long_args, NULL)) != -1) {
		switch(opt) {
			case 'c':
				printf("%llu ", chars(*(argv + 2)));
				break;
			case 'm':
				printf("%llu ", chars(*(argv + 2)));
				break;
			case 'l':
				printf("%u ", lines(*(argv + 2)));
				break;
			case 'w':
				printf("%u ", words(*(argv + 2)));
				break;
			case '?':
				return -1;
		}
	}

	puts(*(argv + 2));

	return 0;
}
