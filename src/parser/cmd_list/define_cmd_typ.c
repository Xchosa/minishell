/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_cmd_typ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:54:56 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/02 14:46:19 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int check_for_builtin(char *token_str)
{
    if (ft_strcmp("echo" , token_str) == true)
		return (BUILTIN);
	if( ft_strcmp("env" , token_str) == true)
		return (BUILTIN);
	if (ft_strcmp("export" , token_str) == true)
		return (BUILTIN);
	if (ft_strcmp("cd" , token_str) == true)
		return (BUILTIN);
	if (ft_strcmp("pwd" , token_str) == true)
		return (BUILTIN);
	if (ft_strcmp("unset" , token_str) == true)
		return (BUILTIN);
	if (ft_strcmp("$?" , token_str) == true)
		return (BUILTIN);
	if (ft_strcmp("exit" , token_str) == true)
		return (BUILTIN);
	return (0);
}

int choose_cmd_type(t_token *curr_token)
{
    int		cmd_type;
	char	*lower;

    cmd_type = 0;
	lower = ft_strtolower(curr_token->token);
	curr_token->token = lower; // token is empty now -> lass ihn auf lower zeigen. 
	cmd_type = (check_for_builtin(lower));
    if (cmd_type != 0)
        return (cmd_type);
    return (cmd_type = EXECUTE);
}
