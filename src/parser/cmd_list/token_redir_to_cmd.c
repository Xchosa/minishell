#include "parser.h"
#include "minishell.h"

t_file_node* create_redirect_output_file_node(t_token **curr_token)
{
	t_file_node *new_file_node;
    new_file_node = malloc(sizeof(t_cmd_node));
	if (!new_file_node)
		return (NULL);
    (*curr_token) =(*curr_token)->next;
	new_file_node->redir_type = REDIRECT_OUTPUT;
	new_file_node->filename = ft_strdup((*curr_token)->token);
	(*curr_token) =(*curr_token)->next;
    return(new_file_node);
}


t_file_node* create_redirect_input_file_node(t_token **curr_token)
{
    t_file_node *new_file_node;
	new_file_node = malloc(sizeof(t_cmd_node));
	if (!new_file_node)
		return (NULL);
    (*curr_token) =(*curr_token)->next;
	new_file_node->redir_type = REDIRECT_INPUT;
	new_file_node->filename = ft_strdup((*curr_token)->token);
	(*curr_token) =(*curr_token)->next;
    return(new_file_node);
}
t_file_node* create_heredoc_file_node(t_token **curr_token)
{
    t_file_node *new_file_node;
	new_file_node = malloc(sizeof(t_cmd_node));
	if (!new_file_node)
		return (NULL);
    (*curr_token) =(*curr_token)->next;
	new_file_node->redir_type = HERE_DOC;
	new_file_node->filename = ft_strdup((*curr_token)->token);
	(*curr_token) =(*curr_token)->next;
    return(new_file_node);
}
t_file_node* create_append_file_node(t_token **curr_token)
{
    t_file_node *new_file_node;
	new_file_node = malloc(sizeof(t_cmd_node));
	if (!new_file_node)
		return (NULL);
    (*curr_token) =(*curr_token)->next;
	new_file_node->redir_type = APPEND;
	new_file_node->filename = ft_strdup((*curr_token)->token);
	(*curr_token) =(*curr_token)->next;
	return(new_file_node);
}

t_file_node*	process_token_type_redir(t_token **curr_token)
{
	t_file_node  *new_file_node;
	new_file_node = NULL;

	if((*curr_token)->token_type == Redirect_input)
		new_file_node = create_redirect_input_file_node(curr_token);
    else if ((*curr_token)->token_type == Redirect_output)
        new_file_node = create_redirect_output_file_node(curr_token);
	// if here
    else if ((*curr_token)->token_type == here_doc)
        new_file_node = create_heredoc_file_node(curr_token);
    else if ((*curr_token)->token_type == Append)
        new_file_node = create_append_file_node(curr_token);
    return (new_file_node);
}