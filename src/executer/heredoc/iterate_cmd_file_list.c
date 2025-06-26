



#include "executer.h"
#include "signal_tp.h"


int find_here_doc_file_node(t_file_node **file_node)
{
	t_file_node *cur_file_node = *file_node;
    
	while(cur_file_node)
	{
		if(cur_file_node->redir_type == HERE_DOC)
		{
			if(save_here_doc_in_tmp(&cur_file_node) != 0)
				return (1);
		}
		if(cur_file_node->next)
			cur_file_node= cur_file_node->next;
		else
			return 0;
	}
	return (0);
}



// head uebergeben // muss doppelpointer sein um die nodes zu veraendern
void save_heredoc_files(t_cmd_node **cmd_node)
{	
	t_cmd_node *cur_cmd_node = *cmd_node;
	
	while(cur_cmd_node)
    {
        if(cur_cmd_node->file_list && cur_cmd_node->file_list->head)
        {
            if(find_here_doc_file_node(&cur_cmd_node->file_list->head) != 0)
                return;
        }
        cur_cmd_node= cur_cmd_node->next;
    }
}

