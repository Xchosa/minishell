/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_special.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:58:14 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/07 11:31:03 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*create_first_token(char **line)
{
	if (ft_strncmp("\"", *line, 1) == 0)
		return (d_quote_case(line));
	if ((ft_strncmp("\'", *line, 1) == 0))
		return (s_quote_case(line));
	if ((ft_strncmp("$?", *line, 2) == 0))
		return (call_exit_token(line));
	if ((ft_strncmp("$", *line, 1) == 0))
		return (call_saved_export_var(line));
	if ((ft_strncmp("=", *line, 1) == 0))
		return (equal_case(line));
	else
		return (create_token(line));
}

t_token	*create_token_with_quote_case(char **line, t_token *token)
{
	if (ft_strncmp("\"", *line, 1) == 0)
		return (d_quote_case(line));
	if ((ft_strncmp("\'", *line, 1) == 0))
		return (s_quote_case(line));
	if ((ft_strncmp("$?", *line, 2) == 0))
		return (call_exit_token(line));
	if ((ft_strncmp("$", *line, 1) == 0))
		return (call_saved_export_var(line));
	if (token->head->token_type == EXPORT)
		return (create_token_equal_as_div(line));
	else
		return (create_token(line));
}
