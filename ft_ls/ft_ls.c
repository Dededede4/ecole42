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
}

void	ll_file_hr_user(int uid)
{
	struct passwd *pwd;

	pwd = getpwuid(uid);
	ft_printf(pwd->pw_name);
}

void	ll_file_hr_group(int gid)
{
	struct group *pwd;

	pwd = getgrgid(gid);
	ft_printf(pwd->gr_name);
}

void	ll_file_datetime(const time_t *clock)
{
	char	*str;
	char	**split;

	str = ctime(clock);
	split = ft_strsplit(str, ' ');
	ft_printf("%s %s %.5s", split[1], split[2], split[3]);
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
    		ft_err("Connot open file (2)");
		total += fileStat.st_blocks;
    }
    ft_printf("total %d\n", total);
	closedir(d);
}

void	ll_file(char *path)
{
	struct stat fileStat;

	if(stat(path,&fileStat) < 0)    
    	ft_err("Connot open file (1)");
    ll_file_hr_permissions(fileStat.st_mode);
    ft_printf("  %3d",fileStat.st_nlink); // TODO : remplace "3"
    ft_printf(" ");
    ll_file_hr_user(fileStat.st_uid); // Size ?
    ft_printf("  ");
    ll_file_hr_group(fileStat.st_gid); // Size ?
    ft_printf("  ");
    ft_printf("%7d", fileStat.st_size); // Size ?
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

	d = opendir(path);
	if (d == NULL)
		ft_err("Cannot open directory");
	ll_total(path);
	while ((pd = readdir(d)) != NULL) {
		if (FALSE) // TODO : long display ?
            ft_printf("%s\n", pd->d_name);
        else
        {
        	ll_file(pd->d_name);
        }
    }
	closedir(d);
}

// Todo : valgrind

int		main(int argc, char **argv)
{
	if (argc != 2)
		ft_err("Bad args");
	lstdir(argv[1]);

}
