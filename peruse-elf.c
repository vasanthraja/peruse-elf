/* This code is for reading the elf header from
 * the given elf binary file
 */

#include <stdio.h>
#include <stdlib.h>
#include "elf.h"

/* function to printf the elf type */
static void print_elf_type(Elf32_Half type)
{
	printf ("ELF TYPE :-\n");

	/* print elf type */
	switch (type)
	{
		case ETNONE:
			printf ("NONE\n");
			break;
		case ETREL:
			printf ("Relocatable file\n");
			break;
		case ETEXEC:
			printf ("Executable file\n");
			break;
		case ETDYN:
			printf ("Shared Object file\n");
			break;
		case ETCORE:
			printf ("Core file\n");
			break;
		case ETLOPROC:
		case ETHIPROC:
			printf ("Processor Specific file\n");
			break;
		default:
			printf ("ERR: invalid elf file type\n");
			break;
	}

	printf ("\n");
}

/* function to printf the elf ident details */
static void print_elf_ident(const Elf32_Char ident[])
{
	printf ("\nELF IDENTIFICATION DETAILS :-\n");

	/* print elf class */
	printf ("ELF CLASS: ");
	switch (ident[EI_CLASS])
	{
		case ELFCLASSNONE:
			printf ("NONE\n");
			break;
		case ELFCLASS32:
			printf ("CLASS 32\n");
			break;
		case ELFCLASS64:
			printf ("CLASS 64\n");
			break;
		default:
			printf ("ERR: invalid elf class\n");
			break;
	}

	/* print elf data/endianess */
	printf ("ELF DATA: ");
	switch (ident[EI_DATA])
	{
		case ELFDATANONE:
			printf ("NONE! Invalid\n");
			break;
		case ELFDATA2LSB:
			printf ("DATA2LSB (Little endian)\n");
			break;
		case ELFDATA2MSB:
			printf ("DATA2MSB (Big endian)\n");
			break;
		default:
			printf ("ERR: invalid elf data\n");
			break;
	}

	/* print elf version */
	printf ("ELF VERSION: ");
	switch (ident[EI_VERSION])
	{
		case EV_NONE:
			printf ("NONE! Invalid\n");
			break;
		case EV_CURRENT:
			printf ("CURRENT\n");
			break;
		default:
			printf ("ERR: invalid elf version\n");
			break;
	}

	printf ("\n");
}

/* function to validate the elf ident */
static elf_status validate_elf_ident(const Elf32_Char ident[])
{
	/* check magic number 0x7f and 'E' 'L' 'F' in ident */
	if (ident[EI_MAG0] != 0x7f || !IS_ELF(ident)) {
		/* if signature not found, return failure */
		return ELF_FAILURE;
	}

	/* return success */
	return ELF_SUCCESS;
}

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

	/* validate the elf identification */
	if(validate_elf_ident(header->e_ident) != 0) {
		printf ("ELF: ERR: Invalid elf header found!\n");
		return EXIT_FAILURE;
	}

	/* print all the elf header details */
	print_elf_ident(header->e_ident);
	print_elf_type(header->e_type);
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

