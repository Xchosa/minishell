/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:06:28 by poverbec          #+#    #+#             */
/*   Updated: 2025/06/24 14:27:07 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"


// saved all heredocs in /tmp directory 
// first alle redirection machen 
// dann bei multiple nodes, wenn klar ist, das 1 weitere node.
// pipes setzten mit set_up pipes 
// danach schliessen. 
void execute_loop(t_cmd_list **cmd_list)
{
	t_cmd_node *cur_cmd_node;
	cur_cmd_node = (*cmd_list)->head;
	//get_bash()->env;// env 
	
	save_heredoc_files(&cur_cmd_node);
	
	if ((*cmd_list)->size == 1 && (*cmd_list)->head->cmd_type == BUILTIN)
		if(handle_single_cmd_node((*cmd_list)->head) == false)
			return;
	// else
	// 	handle_multiple_cmd_node(curr_cmd_node)
}






