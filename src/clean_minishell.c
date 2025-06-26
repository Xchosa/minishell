
#include "parser.h"




/* delete all tmp files , where all here_docs are saved /
	struct dirent {
    ino_t          d_ino;       inode number
    off_t          d_off;       offset to the next dirent 
    unsigned short d_reclen;    length of this record 
    unsigned char  d_type;      type of file; not supported
                                   by all file system types 
    char           d_name[256]; filename 
};
/tmp -> /tmp/ + 
"/tmp/.here_doc123")
*/


void delete_tmp_files(const char *foldername)
{
	DIR 			*directory;
	struct dirent	*fileName;
	char 			*full_path;
	char			*tmp_str;

	directory = opendir(foldername);
	if(!directory)
		return;
	fileName = readdir(directory);
	while(fileName != NULL)
	{
		if(ft_strncmp(fileName->d_name, ".here_doc", 9) == 0)
		{
			tmp_str = ft_strjoin(foldername, "/");
			full_path = ft_strjoin(tmp_str, fileName->d_name);
			unlink(full_path);
			free(tmp_str);
			free(full_path);
			unlink(fileName->d_name);
		}
		fileName = readdir(directory);
	}
	closedir(directory);
}


void clean_up(char *line, t_token *token_lst)
{
	if (token_lst)
        free_token(&token_lst);
	if (!line)
		free(line);
	// free(env)
	// free(cmdlist)

	
	delete_tmp_files("/tmp");
	
}