/*This code for reading the elf header from
 * the given elf binary file
 * */

#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    char *buffer = NULL;
    Elf32_Ehdr *header = NULL;
    int len;
    if (argv[1] == NULL) {
        printf("You need to provide the file name\n");
        return EXIT_FAILURE;
    } else {
        fp = fopen(argv[1], "rb");
        if (!fp) {
            printf("Invalid file name\n");
            printf("Cannot open the given file name");
            return EXIT_FAILURE;
        }
    }
    buffer = (char *)malloc(sizeof(Elf32_Ehdr));
    if (!buffer) {
        printf("ERROR: Buffer allocation failed\n");
        return EXIT_FAILURE;
    }
    len = fread(buffer, 1, sizeof(Elf32_Ehdr), fp);
    if (len <= 0)
    {
        printf("Failed to read the file %s\n", argv[1]);
        printf("ERROR: bytes read: %d\n", len);
        free(buffer);
        return EXIT_FAILURE;
    }
    header = (Elf32_Ehdr *)buffer;
    printf("e_ident: %s\n", header->e_ident);
	printf("e_type: 0x%x\n", header->e_type);
	printf("e_machine: 0x%x\n", header->e_machine);
	printf("e_version: 0x%x\n", header->e_version);
	printf("e_entry: 0x%x\n", header->e_entry);
	printf("e_phoff: 0x%x\n", header->e_phoff);
	printf("e_shoff: 0x%x\n", header->e_shoff);
	printf("e_flags: 0x%x\n", header->e_flags);
	printf("e_ehsize: 0x%x\n", header->e_ehsize);
	printf("e_phentsize: 0x%x\n", header->e_phentsize);
	printf("e_phnum: 0x%x\n", header->e_phnum);
	printf("e_shentsize: 0x%x\n", header->e_shentsize);
	printf("e_shnum: 0x%x\n", header->e_shnum);
	printf("e_shstrndx: 0x%x\n", header->e_shstrndx);
    return 0;
}

