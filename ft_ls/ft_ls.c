/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 19:33:47 by mprevot           #+#    #+#             */
/*   Updated: 2017/06/27 19:37:18 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>
#include <sys/stat.h>

// Pour getpwuid
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>

// Pour getgrgid
 #include <grp.h>
 #include <uuid/uuid.h>

// Pour ctime
#include <time.h>


// Pour errno
#include <errno.h>

#include <string.h>

void	ft_putstr_right(char const *s, size_t place)
{
	size_t	spaces;

	spaces = place - ft_strlen(s);
	while (place && spaces--)
		ft_putchar(' ');
	while (*s)
		ft_putchar(*(s++));
}

void	ft_putnbr_right(int nbr, size_t place)
{
	size_t	spaces;

	spaces = place - ft_intlen(nbr);
	while (place && spaces--)
		ft_putchar(' ');
	ft_putnbr(nbr);
}

void	ft_putstr_left(char const *s, size_t place)
{
	size_t	spaces;

	spaces = place - ft_strlen(s);
	while (*s)
		ft_putchar(*(s++));
	while (place && spaces--)
		ft_putchar(' ');
}


t_inputsize	get_col_size(char *path)
{
	t_inputsize		size;
	DIR				*d;
	struct dirent	*pd;
	struct stat		fileStat;
	struct passwd *pwd;
	struct group *gwd;

	size.col1 = 0;
	size.col2 = 0;
	size.col3 = 0;
	size.col4 = 0;
	size.col5 = 0;

	size.col1 = 10;
	d = opendir(path);
	while ((pd = readdir(d)) != NULL) {
		if(stat(pd->d_name,&fileStat) < 0)   
			ft_err("err\n");
		if (ft_intlen(fileStat.st_nlink) > size.col2)
			size.col2 = ft_intlen(fileStat.st_nlink);

		pwd = getpwuid(fileStat.st_uid);
		if (ft_strlen(pwd->pw_name) > size.col3)
			size.col3 = ft_strlen(pwd->pw_name);

		gwd = getgrgid(fileStat.st_gid);
		if (ft_strlen(gwd->gr_name) > size.col4)
			size.col4 = ft_strlen(gwd->gr_name);

		
		if (ft_intlen(fileStat.st_size) > size.col5)
			size.col5 = ft_intlen(fileStat.st_size);
    }
	closedir(d);
	return (size);
}

void	ll_file_hr_permissions(int chmod)
{
	ft_printf( (S_ISDIR(chmod)) ? "d" : "-");
    ft_printf( (chmod & S_IRUSR) ? "r" : "-");
    ft_printf( (chmod & S_IWUSR) ? "w" : "-");
    ft_printf( (chmod & S_IXUSR) ? "x" : "-");
    ft_printf( (chmod & S_IRGRP) ? "r" : "-");
    ft_printf( (chmod & S_IWGRP) ? "w" : "-");
    ft_printf( (chmod & S_IXGRP) ? "x" : "-");
    ft_printf( (chmod & S_IROTH) ? "r" : "-");
    ft_printf( (chmod & S_IWOTH) ? "w" : "-");
    ft_printf( (chmod & S_IXOTH) ? "x" : "-");
    // TODO : + @
}

void	ll_file_hr_user(int uid, t_inputsize inputsize)
{
	struct passwd *pwd;

	pwd = getpwuid(uid);
	ft_putstr_left(pwd->pw_name, inputsize.col3);
}

void	ll_file_hr_group(int gid, t_inputsize inputsize)
{
	struct group *pwd;

	pwd = getgrgid(gid);
	ft_putstr_left(pwd->gr_name, inputsize.col4);
}

void	ll_file_datetime(const time_t *clock)
{
	char	*str;
	char	**split;

	str = ctime(clock);
	split = ft_strsplit(str, ' ');
	ft_printf("%3s %2s %.5s", split[1], split[2], split[3]);
}

void	ll_total(char *path)
{
	DIR *d;
	struct dirent *pd;
	struct stat fileStat;
	int total;

	total = 0;
	d = opendir(path);
	if (d == NULL)
		ft_err("Cannot open directory"); 
	while ((pd = readdir(d)) != NULL) {
		
		if(stat(pd->d_name,&fileStat) < 0)   
		{
			ft_printf("%s%s\n",path, pd->d_name);
			ft_printf(strerror(errno));
    		ft_err("Connot open file (2)");
		}
		total += fileStat.st_blocks;
    }
    ft_printf("total %d\n", total);
	closedir(d);
}

void	ll_file(char *path, t_inputsize	inputsize)
{
	struct stat fileStat;

	if(stat(path,&fileStat) < 0)    
    	ft_err("Connot open file (1)");
    ll_file_hr_permissions(fileStat.st_mode);
    ft_printf(" ");
    ft_putnbr_right(fileStat.st_nlink, inputsize.col2);
    ft_printf(" ");
    ll_file_hr_user(fileStat.st_uid, inputsize);
    ft_printf("  ");
    ll_file_hr_group(fileStat.st_gid, inputsize);
    ft_printf("  ");
    ft_putnbr_right(fileStat.st_size, inputsize.col5);
    ft_printf(" ");
    ll_file_datetime(&fileStat.st_mtime);
    ft_printf(" ");
    ft_printf("%s", path);
    ft_printf("\n");
    /*
    ft_printf("Information for %s\n",path);
    ft_printf("---------------------------\n");
    ft_printf("File Size: \t\t%d bytes\n",fileStat.st_size);
    ft_printf("Number of Links: \t%d\n",fileStat.st_nlink);
    ft_printf("File inode: \t\t%d\n",fileStat.st_ino);
 
    ft_printf("File Permissions: \t");
    
 
    ft_printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");*/
}

void	lstdir(char *path)
{
	DIR *d;
	struct dirent *pd;
	t_inputsize	inputsize;

	d = opendir(path);
	if (d == NULL)
		ft_err("Cannot open directory");
	ll_total(path);
	inputsize = get_col_size(path);
	while ((pd = readdir(d)) != NULL) {
		// Todo : add path to the name
		if (FALSE) // TODO : long display ?
            ft_printf("%s\n", pd->d_name);
        else
        {
        	ll_file(pd->d_name, inputsize);
        }
    }
	closedir(d);
}

// Todo : valgrind

int		main(int argc, char **argv)
{
	errno = 0;
	if (argc != 2)
		ft_err("Bad args");
	lstdir(argv[1]);

}
