/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_text_to_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:54:16 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/10 09:30:50 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**ft_cpy_array_str(char **arrays)
{
	char	**new_array;
	int		i;

	i = 0;
	if (!arrays)
		return (NULL);
	while (arrays[i] != NULL)
		i++;
	new_array = (char **)malloc((i + 1) * sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (arrays[i] != NULL)
	{
		new_array[i] = ft_strdup(arrays[i]);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}

void	ft_free_array(char **arrays)
{
	int	i;

	i = 0;
	while (arrays[i])
		i++;
	while (i >= 0)
	{
		free(arrays[i]);
		i--;
	}
	free(arrays);
}

char	**cpy_token_char(char *token)
{
	char	**cmd_array;
	int		i;

	i = 0;
	cmd_array = (char **)malloc(2 * sizeof(char *));
	cmd_array[i++] = ft_strdup(token);
	cmd_array[i] = NULL;
	return (cmd_array);
}

void	append_token_char(t_cmd_node *cmd_node, t_token *curr_token)
{
	char	**append_cmd_array;
	int		i;
	int		len;

	i = 0;
	while (cmd_node->cmd[i] != NULL)
		i++;
	len = i;
	append_cmd_array = (char **)malloc((len + 2) * sizeof(char *));
	if (!append_cmd_array)
		return ;
	i = 0;
	while (i < len)
	{
		append_cmd_array[i] = ft_strdup(cmd_node->cmd[i]);
		i++;
	}
	append_cmd_array[i] = ft_strdup(curr_token->token);
	append_cmd_array[i + 1] = NULL;
	ft_free_array(cmd_node->cmd);
	cmd_node->cmd = append_cmd_array;
}

void	handle_special_cases(t_token **curr_token, t_cmd_node *cmd_node)
{
	t_token	*passed_position;

	(void)cmd_node;
	passed_position = (*curr_token);
	while (curr_token && *curr_token)
	{
		if (curr_token && *curr_token && (*curr_token)->token_type == CALL_EXIT)
			(*curr_token)->token_type = TEXT;
		if (curr_token && *curr_token
			&& (*curr_token)->token_type == CALL_SAVED_VAR)
			(*curr_token)->token_type = TEXT;
		if (curr_token && *curr_token && (*curr_token)->token_type == EXPORT)
			(*curr_token)->token_type = TEXT;
		if (curr_token && *curr_token 
			&& (*curr_token)->token_type == Export_var)
		{
			(*curr_token)->token_type = TEXT;
		}
        (*curr_token) = (*curr_token)->next;
	}
	(*curr_token) = passed_position;
}

void	process_token_type_Text(t_token **curr_token,t_cmd_node *cmd_node)
{
	handle_special_cases(curr_token, cmd_node);
	while (curr_token && *curr_token && (*curr_token)->token_type == TEXT )
	{
		if (cmd_node->cmd_type == 0)
		{
			cmd_node->cmd_type = choose_cmd_type(*curr_token);
			cmd_node->cmd = cpy_token_char((*curr_token)->token);
		}
		else
		{
			append_token_char(cmd_node, *curr_token);
		}
		if ((*curr_token)->next)
			(*curr_token) = (*curr_token)->next;
		else
		{
			*curr_token = NULL;
			return ;
		}
	}
	process_redirect(curr_token, cmd_node);
	return ;
}

void	process_redirect(t_token **curr_token, t_cmd_node *cmd_node)
{
	if (cmd_node->cmd_type == 0)
	{
		if (redir_token(curr_token) == true)
		{
			cmd_node->cmd_type = choose_cmd_type(*curr_token);
			cmd_node->cmd = malloc(sizeof(char *));
			if (cmd_node->cmd)
				cmd_node->cmd[0] = NULL;
		}
	}
	return ;
}

void	check_cmd_builtin(t_cmd_node **cmd_node)
{
	if ((*cmd_node)->cmd_type == EXECUTE)
	{
		(*cmd_node)->cmd_type = correct_cmd_type(cmd_node);
	}
}

int	correct_cmd_type(t_cmd_node **cmd_node)
{
	int		cmd_type;
	char	*lower;

	cmd_type = 0;
	lower = ft_strtolower((*cmd_node)->cmd[0]);
    (*cmd_node)->cmd[0] = lower;
	cmd_type = (check_for_builtin(lower));
    if (cmd_type != 0)
		return (cmd_type);
	return (cmd_type = EXECUTE);
}
