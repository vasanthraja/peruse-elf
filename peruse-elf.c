/* This code is for reading the elf header from
 * the given elf binary file
 */

#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	char *buffer = NULL;
	Elf32_Ehdr *header = NULL;
	int len;

	/* validae the input file name */
	if (argv[1] == NULL) {
		printf("You need to provide the elf file name\n");
		return EXIT_FAILURE;
	} else {
		/* open the elf file provided in read binary mode */
		fp = fopen(argv[1], "rb");
		if (!fp) {
			/* file not found, return failure */
			printf("file not found !!! Please check the file\n");
			return EXIT_FAILURE;
		}
	}

	/* allocate buffer to hold Elf32_Ehdr */
	buffer = (char *)malloc(sizeof(Elf32_Ehdr));
	if (!buffer) {
		/* No memory, return failure */
		printf("ERROR: Buffer allocation failed\n");
		return EXIT_FAILURE;
	}

	/* read the elf file */
	len = fread(buffer, 1, sizeof(Elf32_Ehdr), fp);
	if (len != sizeof(Elf32_Ehdr)) {
		printf("Failed to read the file %s\n", argv[1]);
		printf("ERROR: bytes read: %d\n", len);
		/* failed to read, free up the buffer and return failure */
		free(buffer);
		return EXIT_FAILURE;
	}

	/* typecast buffer to Elf32_Ehdr */
	header = (Elf32_Ehdr *)buffer;

	/* print all the elf header values */
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

	/* free up allocated buffer */
	free(buffer);

	/* return success */
	return EXIT_SUCCESS;
}

