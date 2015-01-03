/* Copyright 2015
 * Author : Prasanna Navaratna
 * Date of Creation : 03/01/2015
 *
 * The file contains macros for facilitating trace
 * in peruse-elf with various debug levels of prints.
 */

#ifndef __ELF_TRACE_H__
#define __ELF_TRACE_H__

/* various log trace levels */
enum trace_level
{
	ELF_ERROR,
	ELF_WARN,
	ELF_INFORM,
	ELF_DBG,
	ELF_MAX_LEVEL
};

extern void elf_printf(enum trace_level level, char *format, ...);

#define ELF_PRINT elf_printf

#endif /* __ELF_TRACE_H__ */
