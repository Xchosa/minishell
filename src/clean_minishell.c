
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

void clean_cmd_list_objects_tmp_files(t_cmd_list *cmd_list)
{
	clean_cmd_lst(cmd_list);
	clean_bash_env();
	clean_exit_codes();
	delete_tmp_files("/tmp");

}
// cmd_list, token_list, line, bash_env und exit_codes




void clean_file_lst(t_file_list *file_list)
{
	t_file_node *file_node;
	t_file_node *tmp;

	file_node = file_list->head;
	while(file_node)
	{
		tmp = file_node->next;
		free(file_node->filename);
		free(file_node);
		file_node = tmp;
	}
	free(file_list);
}


void clean_cmd_lst(t_cmd_list *cmd_list)
{
	t_cmd_node *cmd_node;
	t_cmd_node *tmp;

	
	if(cmd_list->head != NULL)
		cmd_node = cmd_list->head;

	if (!cmd_node)
        return;
	while(cmd_node)
	{
		if(cmd_node->next == NULL)
		{
			if(cmd_node->file_list != NULL)
				clean_file_lst(cmd_node->file_list);
		}
		tmp = cmd_node->next;
		ft_free_array(cmd_node->cmd);
		free(cmd_node);
		cmd_node = tmp;

	}
	free(cmd_list);
}

