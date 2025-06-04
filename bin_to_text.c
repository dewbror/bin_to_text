#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void print_info(void)

{   
    /* Print info */
    printf("Welcome to bin_to_text v1.0.0\n");
    printf("bin_to_text is a simple CLI program for converting text written as binary to human readable text assuming the binary is ascii encoded.\n");
    printf("This program assumes each character is encoded as 8 bits.\n");
}

static void print_help(void)
{   
    /* Print help */
    printf("Options:\n");
    printf("  -f=\"path/to/file\"    Read in binary from a text file and print it as text to stdout.\n");
    printf("  -b=\"binary-code\"     Read in binary from terminal argument and print it as text to stdout.\n");
}

static void parse_bin(const char* bin)
{
    int code = 0;
    int j = 0;
    int i = 0;
    
    /* Loop through the string of binary */
    for(; bin[i] != '\0'; ++i) {
        /* We only care about ones and zeroes */
        if(bin[i] != '1' && bin[i] != '0')
            continue;
        
        /* If the char '1' then add 2^(j%8) to code, after 8 bits we will have the ascii character in decimal form */
        if(bin[i] == '1')
            code += 1 << (7 - (j % 8));

        /* After 8 bits we print the character and start over */
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
    
    /* Open file and handle potential error */
    FILE* f = fopen(path_to_file, "r");
    if(f == NULL) {
        printf("Error opening file %s: %s\n", path_to_file, strerror(errno));
        return 1;
    }
    
    /* Loop through the file contents */
    while(1) {
        c = fgetc(f);
        
        if(c == EOF)
            break;
        
        /* We only care about ones and zeroes */
        if(c != '1' && c != '0')
            continue;
        
        /* If the char is '1' then add 2^(j%8) to code, after 8 bits we will have the ascii character in decimal form */
        if(c == '1')
            code += 1 << (7 - (j % 8));
        
        /* After 8 bits we print the character and start over */
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
    /* If the first char is not - return error */
    if(*arg != '-')
        return 1;
    
    if(*++arg == 'f') {
        if(*++arg != '='){
            printf("Error: Unrecognized option(s)\n");
            return 1;
        }
        /* If arguemtn begins with -f= then call parse_file */
        return parse_file(++arg);
    }
    else if(*arg == 'b') {
        if(*++arg != '=') {
            printf("Error: Unrecognized option(s)\n");
            return 1;
        }
        /* If arguemnt begins with -b= then interpret then call parse_bin */
        parse_bin(++arg);
    }

    return 0;
}

int main(int argc, char **argv)
{
    int i = 0;
    /* If there are less than 2 arguments print help/info */
    if(argc < 2) {
        print_info();
        print_help();
    }
    else {
        /* else parse the first arguemnt */
        i = parse_arg(argv[1]);
    }
    
    /* if parse_arg failed return EXIT_FAILRUE */
    if(i == 1) {
        print_help();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
