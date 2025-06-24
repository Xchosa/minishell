/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:09:11 by poverbec          #+#    #+#             */
/*   Updated: 2025/06/24 14:11:38 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void clean_token_lst(t_token *token_lst)
{
	t_token *tmp;

	while(token_lst)
	{
		tmp = token_lst->next;
		free(token_lst->token);
		free(token_lst);
		token_lst = tmp;
	}
	
}

void free_single_token(t_token **token)
{
	if (*token)
	{
		free((*token)->token);
		free(*token);
		*token = NULL;
	}
}


/* delete all tmp files , where all here_docs are saved /*
/* struct dirent {
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

bool tokeniser_successful(t_token *token_lst, char *line)
{
	if (!token_lst)
	{
		free(line);
		return (false);
	}	
	return(true);
}

bool check_lexer_token_and_free(t_token *token, char *line)
{
	if (lexer_token(token) == false)
	{
		print_error_message(line);
		free(line);
		free(token);
		return(false);
	}
	return(true);
}

bool check_lexer_and_free(char *line)
{
	if (line == NULL)
        return(false);
	if (lexer(line) == false)
	{
		get_exit_codes()->last_exit_code = syntax_failure;
		print_error_message(line);
		free(line);
		return(false);
    }
	return(true);
}
