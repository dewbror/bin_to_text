#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void print_help(void)
{
    printf("Welcome to bin_to_text v1.0.0\n");
    printf("bin_to_text is a simple CLI program for converting text written as binary to human readable text assuming the binary is ascii encoded.\n");
    printf("This program assumes each character is encoded as 8 bits.\n");
    printf("Options:\n");
    printf("  -f=\"path/to/file\"    Read in binary from a text file and print it as text to stdout.\n");
    printf("  -b=\"binary-code\"     Read in binary from terminal argument and print it as text to stdout.\n");
}

static void parse_bin(const char* bin)
{
    int code = 0;
    int j = 0;
    int i = 0;

    for(; bin[i] != '\0'; ++i) {
        if(bin[i] != '1' && bin[i] != '0')
            continue;

        if(bin[i] == '1')
            code += 1 << (7 - (j % 8));

        if((7 - (j++ % 8)) == 0) {
            printf("%c", (char)code);
            code = 0;
        }
    }

    printf("\n");
}

static int parse_file(const char* path_to_file)
{       
    char c = '\0';
    int code = 0;
    int j = 0;

    FILE* f = fopen(path_to_file, "r");
    if(f == NULL) {
        printf("Error opening file %s: %s\n", path_to_file, strerror(errno));
        return 1;
    }
    
    while(1) {
        c = fgetc(f);

        if(c == EOF)
            break;

        if(c != '1' && c != '0')
            continue;

        if(c == '1')
            code += 1 << (7 - (j % 8));

        if((7 - (j++ % 8)) == 0) {
            printf("%c", (char)code);
            code = 0;
        }
    }

    printf("\n");

    fclose(f);

    return 0;
}

static int parse_arg(const char* arg)
{   
    if(*arg != '-')
        return 1;

    if(*++arg == 'f') {
        if(*++arg != '=')
            return 1;
        return parse_file(++arg);
    }
    else if(*arg == 'b') {
        if(*++arg != '=')
            return 1;
        parse_bin(++arg);
    }

    return 0;
}

int main(int argc, char **argv)
{
    int i = 0;
    if(argc != 2) {
        print_help();
    }
    else {
        i = parse_arg(argv[1]);
    }

    if(i == 1)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
