#include <stdint.h>

typedef uint16_t Elf32_Half;    // Unsigned half int
typedef uint32_t Elf32_Off;     // Unsigned offset
typedef uint32_t Elf32_Addr;    // Unsigned address
typedef uint32_t Elf32_Word;    // Unsigned int
typedef int32_t  Elf32_Sword;   // Signed int
typedef uint8_t  Elf32_Char;	// Signed char

#define ELF_NIDENT 0x10
typedef struct {
    Elf32_Char  e_ident[ELF_NIDENT];
    Elf32_Half  e_type;
    Elf32_Half  e_machine;
    Elf32_Word  e_version;
    Elf32_Addr  e_entry;
    Elf32_Off   e_phoff;
    Elf32_Off   e_shoff;
    Elf32_Word  e_flags;
    Elf32_Half  e_ehsize;
    Elf32_Half  e_phentsize;
    Elf32_Half  e_phnum;
    Elf32_Half  e_shentsize;
    Elf32_Half  e_shnum;
    Elf32_Half  e_shstrndx;
}Elf32_Ehdr;

enum elf_ident {
	EI_MAG0,
	EI_MAG1,
	EI_MAG2,
	EI_MAG3,
	EI_CLASS,
	EI_DATA,
	EI_VERSION,
	EI_PAD,
	EI_NIDENT = ELF_NIDENT
};

#define IS_ELF(i) ((i[EI_MAG1] == 'E') && \
			(i[EI_MAG2] == 'L') && \
			(i[EI_MAG3] == 'F'))

typedef enum {
	ELF_SUCCESS,
	ELF_FAILURE,
	ELF_BADARG,
	ELF_OUTRANGE
} elf_status;

enum elf_class {
	ELFCLASSNONE,
	ELFCLASS32,
	ELFCLASS64
};

enum elf_data {
	ELFDATANONE,
	ELFDATA2LSB,
	ELFDATA2MSB
};

enum elf_version {
	EV_NONE,
	EV_CURRENT
};

enum elf_type {
	ETNONE,
	ETREL,
	ETEXEC,
	ETDYN,
	ETCORE,
	ETLOPROC = 0xff00,
	ETHIPROC = 0xffff
};
