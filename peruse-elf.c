/* Copyright 2014
 * Author : Vasanth Raja Chittampally
 * Date of Creation : 22/12/2014
 *
 * This code is for reading the elf header from
 * the given elf binary file
 */

#include <stdio.h>
#include <stdlib.h>
#include "elf.h"

/* global variable to hold the elf trace level */
enum trace_level elf_trace_level;

/* elf function to filter level and print log/traces */
void elf_printf(enum trace_level level, char *format, ...)
{
	va_list args;

	if (level <= elf_trace_level) {
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
	}
}

/* function to print the elf type */
static void print_elf_type(Elf32_Half type)
{
	ELF_PRINT(ELF_INFORM, "ELF TYPE :-\n");

	/* print elf type */
	switch (type)
	{
		case ETNONE:
			ELF_PRINT(ELF_WARN, "NONE\n");
			break;
		case ETREL:
			ELF_PRINT(ELF_INFORM, "Relocatable file\n");
			break;
		case ETEXEC:
			ELF_PRINT(ELF_INFORM, "Executable file\n");
			break;
		case ETDYN:
			ELF_PRINT(ELF_INFORM, "Shared Object file\n");
			break;
		case ETCORE:
			ELF_PRINT(ELF_INFORM, "Core file\n");
			break;
		case ETLOPROC:
		case ETHIPROC:
			ELF_PRINT(ELF_INFORM, "Processor Specific file\n");
			break;
		default:
			ELF_PRINT(ELF_ERROR, "ERR: invalid elf file type\n");
			break;
	}

	ELF_PRINT(ELF_INFORM, "\n");
}

/* function to printf the elf ident details */
static void print_elf_ident(const Elf32_Char ident[])
{
	ELF_PRINT(ELF_INFORM, "\nELF IDENTIFICATION DETAILS :-\n");

	/* print elf class */
	ELF_PRINT(ELF_INFORM, "ELF CLASS: ");
	switch (ident[EI_CLASS])
	{
		case ELFCLASSNONE:
			ELF_PRINT(ELF_WARN, "NONE\n");
			break;
		case ELFCLASS32:
			ELF_PRINT(ELF_INFORM, "CLASS 32\n");
			break;
		case ELFCLASS64:
			ELF_PRINT(ELF_INFORM, "CLASS 64\n");
			break;
		default:
			ELF_PRINT(ELF_ERROR, "ERR: invalid elf class\n");
			break;
	}

	/* print elf data/endianess */
	ELF_PRINT(ELF_INFORM, "ELF DATA: ");
	switch (ident[EI_DATA])
	{
		case ELFDATANONE:
			ELF_PRINT(ELF_INFORM, "NONE! Invalid\n");
			break;
		case ELFDATA2LSB:
			ELF_PRINT(ELF_INFORM, "DATA2LSB (Little endian)\n");
			break;
		case ELFDATA2MSB:
			ELF_PRINT(ELF_INFORM, "DATA2MSB (Big endian)\n");
			break;
		default:
			ELF_PRINT(ELF_ERROR, "ERR: invalid elf data\n");
			break;
	}

	/* print elf version */
	ELF_PRINT(ELF_INFORM, "ELF VERSION: ");
	switch (ident[EI_VERSION])
	{
		case EV_NONE:
			ELF_PRINT(ELF_WARN, "NONE! Invalid\n");
			break;
		case EV_CURRENT:
			ELF_PRINT(ELF_INFORM, "CURRENT\n");
			break;
		default:
			ELF_PRINT(ELF_INFORM, "ERR: invalid elf version\n");
			break;
	}

	ELF_PRINT(ELF_INFORM, "\n");
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

	/* initiate the trace level */
	elf_trace_level = ELF_INFORM;

	ELF_PRINT(ELF_DBG, "DBG: Validating input file name\n");
	/* validae the input file name */
	if (argv[1] == NULL) {
		ELF_PRINT(ELF_ERROR, "You need to provide the elf file name\n");
		return EXIT_FAILURE;
	} else {
		ELF_PRINT(ELF_DBG, "DBG: Opening %s file\n", argv[1]);
		/* open the elf file provided in read binary mode */
		fp = fopen(argv[1], "rb");
		if (!fp) {
			/* file not found, return failure */
			ELF_PRINT(ELF_ERROR, "file not found !!! Please check the file\n");
			return EXIT_FAILURE;
		}
	}

	ELF_PRINT(ELF_DBG, "DBG: Allocating Elf32_Ehdr\n");
	/* allocate buffer to hold Elf32_Ehdr */
	buffer = (char *)malloc(sizeof(Elf32_Ehdr));
	if (!buffer) {
		/* No memory, return failure */
		ELF_PRINT(ELF_ERROR, "ERROR: Buffer allocation failed\n");
		return EXIT_FAILURE;
	}

	ELF_PRINT(ELF_DBG, "DBG: Reading elf hearder from file\n");
	/* read the elf file */
	len = fread(buffer, 1, sizeof(Elf32_Ehdr), fp);
	if (len != sizeof(Elf32_Ehdr)) {
		ELF_PRINT(ELF_ERROR, "Failed to read the file %s\n", argv[1]);
		ELF_PRINT(ELF_ERROR, "ERROR: bytes read: %d\n", len);
		/* failed to read, free up the buffer and return failure */
		free(buffer);
		return EXIT_FAILURE;
	}

	/* typecast buffer to Elf32_Ehdr */
	header = (Elf32_Ehdr *)buffer;

	ELF_PRINT(ELF_DBG, "DBG: Validating elf header\n");
	/* validate the elf identification */
	if(validate_elf_ident(header->e_ident) != 0) {
		ELF_PRINT(ELF_ERROR, "ELF: ERR: Invalid elf header found!\n");
		return EXIT_FAILURE;
	}
	ELF_PRINT(ELF_DBG, "DBG: Validation elf header success\n");

	/* print all the elf header details */
	print_elf_ident(header->e_ident);
	print_elf_type(header->e_type);
	ELF_PRINT(ELF_INFORM, "e_machine: 0x%x\n", header->e_machine);
	ELF_PRINT(ELF_INFORM, "e_version: 0x%x\n", header->e_version);
	ELF_PRINT(ELF_INFORM, "e_entry: 0x%x\n", header->e_entry);
	ELF_PRINT(ELF_INFORM, "e_phoff: 0x%x\n", header->e_phoff);
	ELF_PRINT(ELF_INFORM, "e_shoff: 0x%x\n", header->e_shoff);
	ELF_PRINT(ELF_INFORM, "e_flags: 0x%x\n", header->e_flags);
	ELF_PRINT(ELF_INFORM, "e_ehsize: 0x%x\n", header->e_ehsize);
	ELF_PRINT(ELF_INFORM, "e_phentsize: 0x%x\n", header->e_phentsize);
	ELF_PRINT(ELF_INFORM, "e_phnum: 0x%x\n", header->e_phnum);
	ELF_PRINT(ELF_INFORM, "e_shentsize: 0x%x\n", header->e_shentsize);
	ELF_PRINT(ELF_INFORM, "e_shnum: 0x%x\n", header->e_shnum);
	ELF_PRINT(ELF_INFORM, "e_shstrndx: 0x%x\n", header->e_shstrndx);

	ELF_PRINT(ELF_DBG, "DBG: Free up the allocated buffer\n");
	/* free up allocated buffer */
	free(buffer);

	/* return success */
	return EXIT_SUCCESS;
}

