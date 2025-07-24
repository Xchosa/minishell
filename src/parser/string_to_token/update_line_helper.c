/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_line_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:09:01 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/03 14:23:10 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// char	*update_line_unitl_d_quotes(char *line)
// {
// 	line++;
// 	while (ft_strncmp("\"", line, 1) != 0)
// 		line++;
// 	line++;
// 	return (line);
// }

// char	*update_line_unitl_s_quotes(char *line)
// {
// 	line++;
// 	while (ft_strncmp("\'", line, 1) != 0)
// 		line++;
// 	line++;
// 	return (line);
// }

// char	*update_line_until_space(char *line)
// {
// 	line++;
// 	while (*line && ft_strncmp(" ", line, 1) != 0)
// 		line++;
// 	return (line);
// }

// char	*skip_dollar_parameter(char *line)
// {
// 	line++;
// 	line++;
// 	return (line);
// }

// char	*handle_special_characters(char *line)
// {
// 	if (ft_strncmp("\"", line, 1) == 0)
// 		return (update_line_unitl_d_quotes(line));
// 	if (ft_strncmp("\'", line, 1) == 0)
// 		return (update_line_unitl_s_quotes(line));
// 	if (ft_strncmp("=", line, 1) == 0)
// 		return (++line);
// 	if (ft_strncmp("$?", line, 2) == 0)
// 		return (skip_dollar_parameter(line));
// 	if (ft_strncmp("$", line, 1) == 0)
// 		return (update_line_until_space(line));
// 	return (NULL);
// }
