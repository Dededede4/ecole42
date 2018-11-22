#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft/libft.h"

void	print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int i;
	char *stringtable;
	struct  nlist_64 *el;

	el = (void*)ptr + symoff;
	stringtable =  ptr + stroff;

	while (i < nsyms)
	{
		ft_printf("%s\n", stringtable + el[i].n_un.n_strx);
		i++;
	}
}

void print_data(void *start, uint64_t size, uint32_t offset)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (i  % 16 == 0)
		{
			ft_printf("%016x\t", offset + i);
		}
		ft_printf("%02X", ((unsigned char*)start)[i]);
		if ((i + 1)  % 16 == 0)
		{
			ft_printf("\n");
		}
		else
		{
			ft_printf(" ");
		}
		i++;
	}
}

void handle_64(char * ptr)
{
	int ncmds;
	struct mach_header_64 * header;
	struct load_command *lc;
	struct symtab_command *sym;
	struct segment_command_64 *seg;
	struct section_64		*sec;
	struct  nlist_64 *el;

	void	*text;

	int i = 0;

	int y = 0;

	header = (struct mach_header_64 *)ptr;
	ncmds  = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			ft_printf("LC_SYMTAB\n");
			//sym = (struct symtab_command *)lc;
			//ft_printf("nb symboles : %d\n", sym->nsyms);
			//                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			//break;
		}
		else if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;

			// Attention aux trolls du \0
			//seg->segname[15] = 0; // On n'a pas le droit u___ù
			if (ft_strequ(seg->segname, "__TEXT"))
			{
				//ft_printf("Position : %d == %x\n", ((void *)seg - (void*)ptr), ((void *)seg - (void*)ptr));
				//ft_printf("cmd : %x\n", seg->cmd);
				//ft_printf("cmdsize : %x\n", seg->cmdsize);
				//ft_printf("vmaddr : %x\n", seg->vmaddr);
				//ft_printf("vmsize : %d\n", seg->vmsize);
				//ft_printf("fileoff : %x\n", seg->fileoff);
				//ft_printf("filesize : %x\n", seg->filesize);
				//ft_printf("nsects : %x\n", seg->nsects);
				//ft_printf("flags : %x\n", seg->flags);

				sec = (((void*)seg) + sizeof(struct segment_command_64));
				while (y < seg->nsects) // todo troll
				{
					if (ft_strequ(sec->sectname, "__text")) // todo troll
					{
						text = ptr + sec->offset;
						//ft_printf("Nom : %x %x\n", *((int*)text), sec->offset); // y'a plus qu'à afficher 
						print_data(text, sec->size, sec->offset);
//						struct section_64 { /* for 64-bit architectures */
//						char		sectname[16];	/* name of this section */
//						char		segname[16];	/* segment this section goes in */
//						uint64_t	addr;		/* memory address of this section */
//						uint64_t	size;		/* size in bytes of this section */
//						uint32_t	offset;		/* file offset of this section */
//						uint32_t	align;		/* section alignment (power of 2) */
//						uint32_t	reloff;		/* file offset of relocation entries */
//						uint32_t	nreloc;		/* number of relocation entries */
//						uint32_t	flags;		/* flags (section type and attributes)*/
//						uint32_t	reserved1;	/* reserved (for offset or index) */
//						uint32_t	reserved2;	/* reserved (for count or sizeof) */
//						uint32_t	reserved3;	/* reserved */
					}
					
					sec = (((void*)sec) + sizeof(struct section_64));
					y++;
				}
				//sec = (struct section_64 *)(ptr + seg->filesize);
				//while (sec < ) 
				//print_output(seg->nsects, seg->fileoff, seg->fileoff)
				/*el = (void*) (ptr + seg->fileoff);
				while((void *)sec < ((void*)ptr + (seg->fileoff + seg->filesize))) // troll de vmsize
				{
					ft_printf("%p\n", sec);
					ft_printf("Size : %s\n", sec->sectname); // troll de \0
					sec++;
				}*/

				/*cmd : 19
cmdsize : 1d8
vmaddr : 0
vmsize : 8192
fileoff : 0
filesize : 2000
nsects : 5
flags : 0*/
			}
			else
			{
				ft_printf("Connais pas : %x\n", lc->cmd);
			}
			
			/*print_output(seg->nsects, sym->symoff, sym->stroff, ptr);
			ft_printf("-->%d<--\n", lc->cmd);*/
		}
		lc = (void*) lc + lc ->cmdsize;
		i++;
	}
	//write(1, lc, 13896 - (((void*)lc) - ((void*)ptr)));
}

void nm(char *ptr)
{
	int magic_number;

	magic_number = *(int*) ptr;
	if (magic_number == MH_MAGIC_64)
	{
		handle_64(ptr);
	}
	else
	{
		ft_printf("Ce n'est pas MH_MAGIC_64 : %x\n", magic_number);
	}

}

int main(int ac, char **av)
{
	int		fd;
	char	*ptr;
	struct stat	buf;

	if (ac != 2)
	{
		ft_printf("Please give me an arg\n");
		return (0);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		ft_printf("Erreur dans open");
		return (0);
	}
	if (fstat(fd, &buf) < 0)
	{
		ft_printf("fstat");
		return (0);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_printf("mmap");
		return (0);
	}
	nm(ptr);
	/*if (munmap(ptr, buf.st_size < 0))
	{
		ft_printf("munmap");
		return (0);
	}*/
	return (EXIT_SUCCESS);
}
