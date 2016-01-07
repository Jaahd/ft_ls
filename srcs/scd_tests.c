#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h> /* -> getpwduid */
#include <pwd.h> /* -> getpwduid */
#include <grp.h> /* -> get grgid */
#include <uuid/uuid.h> /* -> getpwduid & getgrgid */
#include <sys/errno.h>
#include <sys/stat.h>
#include "libft.h"
#include <time.h> /* for ctime -> pour modif format de time */
/*
   int     stat(const char *restrict path, struct stat *restrict buf);

   struct stat { * when _DARWIN_FEATURE_64_BIT_INODE is defined *
   dev_t           st_dev;           * ID of device containing file *
   mode_t          st_mode;          * Mode of file (see below) *
   nlink_t         st_nlink;         * Number of hard links *
   ino_t           st_ino;           * File serial number *
   uid_t           st_uid;           * User ID of the file *
   gid_t           st_gid;           * Group ID of the file *
   dev_t           st_rdev;          * Device ID *
   struct timespec st_atimespec;     * time of last access *
   struct timespec st_mtimespec;     * time of last data modification *
   struct timespec st_ctimespec;     * time of last status change *
   struct timespec st_birthtimespec; * time of file creation(birth) *
   off_t           st_size;          * file size, in bytes *
   blkcnt_t        st_blocks;        * blocks allocated for file *
   blksize_t       st_blksize;       * optimal blocksize for I/O *
   uint32_t        st_flags;         * user defined flags for file *
   uint32_t        st_gen;           * file generation number *
   int32_t         st_lspare;        * RESERVED: DO NOT USE! *
   int64_t         st_qspare[2];     * RESERVED: DO NOT USE! *
   };

   struct stat { * when _DARWIN_FEATURE_64_BIT_INODE is NOT defined *
   dev_t				st_dev;			* device inode resides on *
   ino_t				st_ino;			* inode's number *
   mode_t				st_mode;		* inode protection mode *
   nlink_t				st_nlink;		* number of hard links to the file *
   uid_t				st_uid;			* user-id of owner *
   gid_t				st_gid;			* group-id of owner *
   dev_t				st_rdev;		* device type, for special file inode *
   struct timespec		st_atimespec;	* time of last access *
   struct timespec		st_mtimespec;	* time of last data modification *
   struct timespec		st_ctimespec;	* time of last file status change *
   off_t				st_size;		* file size, in bytes *
   quad_t				st_blocks;		* blocks allocated for file *
   u_long				st_blksize;		* optimal file sys I/O ops blocksize *
   u_long				st_flags;		* user defined flags for file *
   u_long				st_gen;			* file generation number *
   };

   struct passwd			*getpwuid(uid_t uid);

   struct passwd {
   char    *pw_name;			* user name *
   char    *pw_passwd;			* encrypted password *
   uid_t   pw_uid;				* user uid *
   gid_t   pw_gid;				* user gid *
   time_t  pw_change;			* password change time *
   char    *pw_class;			* user access class *
   char    *pw_gecos;			* Honeywell login info *
   char    *pw_dir;				* home directory *
   char    *pw_shell;			* default shell *
   time_t  pw_expire;			* account expiration *
   int     pw_fields;			* internal: fields filled in *
   };

   struct group				*getgrgid(gid_t gid);	   

   struct group {
   char					*gr_name;       * group name *
   char					*gr_passwd;     * group password *
   gid_t				gr_gid;			* group id *
   char					**gr_mem;       * group members *
   };

   time_t	time(time_t *tloc);					--> permet de recuperer le temps en sec depuis 01/01/70
   char		*ctime(const time_t *clock);		--> format la valeur donnee par time 

   struct timespec
{
	time_t			tv_sec;
	long				tv_nsec;
};

*/

int				main (int ac, char **av) 
{
	struct dirent	*pDirent;
	struct stat		buff_stat;
	struct passwd	*given_pw;
	struct group	*given_gr;
	DIR				*pDir;
	char			*time_tmp;
	char			perm[11];

	if (ac < 2) 
		av[1] = ".";
	pDir = opendir (av[1]);
	if (pDir == NULL)
	{
		perror(av[1]);
		return 1;
	}
	while ((pDirent = readdir(pDir)) != NULL) 
	{
		lstat(ft_strjoin("./libft/", pDirent->d_name), &buff_stat);
		given_pw = getpwuid(buff_stat.st_uid);
		given_gr = getgrgid(buff_stat.st_gid);
		time_tmp = ctime(&buff_stat.st_mtime);
		if(S_ISBLK(buff_stat.st_mode))
			perm[0] = 'b';
		else if(S_ISREG(buff_stat.st_mode))
			perm[0] = '-';
		else if(S_ISCHR(buff_stat.st_mode))
			perm[0] = 'c';
		else if(S_ISDIR(buff_stat.st_mode))
			perm[0] = 'd';
		else if(S_ISFIFO(buff_stat.st_mode))
			perm[0] = 'p';
		else if(S_ISLNK(buff_stat.st_mode))
			perm[0] = 'l';
		else if(S_ISSOCK(buff_stat.st_mode))
			perm[0] = 's';
		else
			perm[0] = '?';
	//	perm[0] = (S_ISDIR(buff_stat.st_mode)) ? 'd' : '-';
		perm[1] = (buff_stat.st_mode & S_IRUSR) ? 'r' : '-';
		perm[2] = (buff_stat.st_mode & S_IWUSR) ? 'w' : '-';
		perm[3] = (buff_stat.st_mode & S_IXUSR) ? 'x' : '-';
		perm[4] = (buff_stat.st_mode & S_IRGRP) ? 'r' : '-'; 
		perm[5] = (buff_stat.st_mode & S_IWGRP) ? 'w' : '-'; 
		perm[6] = (buff_stat.st_mode & S_IXGRP) ? 'x' : '-';
		perm[7] = (buff_stat.st_mode & S_IROTH) ? 'r' : '-';
		perm[8] = (buff_stat.st_mode & S_IWOTH) ? 'w' : '-';
		perm[9] = (buff_stat.st_mode & S_IXOTH) ? 'x' : '-';
		perm[10] = '\0';
		ft_putstr("nom du fichier :\t");
		ft_putendl(pDirent->d_name);
		printf("user id :\t%s\n", given_pw->pw_name);
		printf("nb of links :\t%d\n", buff_stat.st_nlink);
		printf("file mode :\t%s\n", perm);
		printf("group id :\t%s\n", given_gr->gr_name);
		printf("last modifs :\t%s\n", ft_strsub(time_tmp, 4, 12));
		ft_putchar('\n');
		buff_stat.st_mode = 0;
	}
	closedir (pDir);
	return 0;
}
