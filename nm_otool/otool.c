#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct			s_command
{
	char				*path;
	int					fd;
	char				*ptr;
	struct stat			buf;
	int					magic_number;
	int ncmds;
	struct mach_header_64 * header;
	struct load_command *lc;
	struct symtab_command *sym;
	struct segment_command_64 *seg;
	struct section_64		*sec;
	struct  nlist_64 *el;
}						t_command;


void print_data(void *start, uint64_t size, uint32_t offset)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (i  % 16 == 0)
		{
			ft_printf("00000001%08x\t", offset + i);
		}
		ft_printf("%02x", ((unsigned char*)start)[i]);
		if ((i + 1)  % 16 == 0 || i + 1 == size)
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

void handle_64(t_command command)
{

	int i = 0;
	int y = 0;

	(command.header) = (struct mach_header_64 *)(command.ptr);
	(command.ncmds)  = (command.header)->ncmds;
	(command.lc) = (void *)(command.ptr) + sizeof(*(command.header));
	while (i < (command.ncmds))
	{
		if ((command.lc)->cmd == LC_SYMTAB)
		{
			//ft_printf("LC_SYMTAB\n");
			//sym = (struct symtab_command *)lc;
			//ft_printf("nb symboles : %d\n", sym->nsyms);
			//                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 print_output(sym->nsyms, sym->symoff, sym->stroff, (command.ptr));
			//break;
		}
		else if ((command.lc)->cmd == LC_SEGMENT_64)
		{
			(command.seg) = (struct segment_command_64 *)(command.lc);

			// Attention aux trolls du \0
			//sqeg->segname[15] = 0; // On n'a pas le droit u___ù
			if (ft_strequ((command.seg)->segname, "__TEXT"))
			{
				//ft_printf("Position : %d == %x\n", ((void *)seg - (void*)(command.ptr)), ((void *)seg - (void*)(command.ptr)));
				//ft_printf("cmd : %x\n", seg->cmd);
				//ft_printf("cmdsize : %x\n", seg->cmdsize);
				//ft_printf("vmaddr : %x\n", seg->vmaddr);
				//ft_printf("vmsize : %d\n", seg->vmsize);
				//ft_printf("fileoff : %x\n", seg->fileoff);
				//ft_printf("filesize : %x\n", seg->filesize);
				//ft_printf("nsects : %x\n", seg->nsects);
				//ft_printf("flags : %x\n", seg->flags);

				(command.sec) = (((void*)(command.seg)) + sizeof(struct segment_command_64));
				while (y < (command.seg)->nsects) // todo troll
				{
					if (ft_strequ((command.sec)->sectname, "__text")) // todo troll
					{
						//ft_printf("Nom : %x %x\n", *((int*)text), sec->offset); // y'a plus qu'à afficher 
						ft_printf("%s:\nContents of (__TEXT,__text) section\n", command.path);
						print_data((command.ptr) + (command.sec)->offset, (command.sec)->size, (command.sec)->offset);
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
					
					(command.sec) = (((void*)(command.sec)) + sizeof(struct section_64));
					y++;
				}
				//sec = (struct section_64 *)((command.ptr) + seg->filesize);
				//while (sec < ) 
				//print_output(seg->nsects, seg->fileoff, seg->fileoff)
				/*el = (void*) ((command.ptr) + seg->fileoff);
				while((void *)sec < ((void*)(command.ptr) + (seg->fileoff + seg->filesize))) // troll de vmsize
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
		}
		else
		{
			//ft_printf("Connais pas : %x\n", (command.lc)->cmd);
		}
			
			/*print_output(seg->nsects, sym->symoff, sym->stroff, (command.ptr));
			ft_printf("-->%d<--\n", lc->cmd);*/
		
		(command.lc) = (void*) (command.lc) + (command.lc) ->cmdsize;
		i++;
	}
	//write(1, lc, 13896 - (((void*)lc) - ((void*)(command.ptr))));
}

void nm(t_command command)
{
	command.magic_number = *(int*) (command.ptr);
	if (command.magic_number == MH_MAGIC_64)
	{
		handle_64(command);
	}
	else
	{
		ft_printf("This magic number « %x » is unknow.\n", command.magic_number);
	}

}



int main(int ac, char **av)
{

	t_command	command;
	int			i;

	i = 1;
	if (ac <= 1)
	{
		ft_printf("Please give me an arg\n");
		return (0);
	}
	while ( i < ac )
	{
		command.path = av[i];
		if ((command.fd = open(av[i], O_RDONLY)) < 0)
		{
			ft_printf("Error in open\n");
			return (0);
		}
		if (fstat(command.fd, &(command.buf)) < 0)
		{
			ft_printf("Error in fstat\n");
			return (0);
		}
		if ((command.ptr = mmap(0, command.buf.st_size, PROT_READ, MAP_PRIVATE, command.fd, 0)) == MAP_FAILED)
		{
			ft_printf("Error in mmap\n");
			return (0);
		}
		nm(command);
		ft_bzero(&command, sizeof(command));
		i++;
	}
	return (0);
}
