/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_codes_config.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:59:22 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/23 13:51:44 by tschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

t_exit_codes	*get_exit_codes(void)
{
	static t_exit_codes	exit_code;

	return (&exit_code);
}

bool	init_exit_codes(int argc)
{
	t_exit_codes	*exit_code;

	exit_code = get_exit_codes();
	if (argc == 1)
	{
		exit_code->last_exit_code = ec_sucess;
	}
	return (true);
}

void	clean_exit_codes(void)
{
	t_exit_codes	*exit_code;

	exit_code = get_exit_codes();
	exit_code->last_exit_code = 0;
}

void	print_error_message(t_token **token_list, char *line)
{
	int		error;


	error = get_exit_codes()->last_exit_code;
	if (error == invalid_identifier)
		ft_putendl_fd("shell: not a valid indentifier", 2);
	if (error == syntax_failure)
		ft_putendl_fd("shell: syntax failure", 2);
	if (error == cmd_not_found)
		ft_putendl_fd("shell: command not found", 2);
	if (error == syntax_error_token)
		ft_putendl_fd("shell: syntax error near unexpected token", 2);
	clean_token_lst(*token_list);
	free(line);
}

void	print_lexer_error_message(char *line)
{
	int	error;

	(void)line;

	error = get_exit_codes()->last_exit_code;
	if (error == invalid_identifier)
		ft_putendl_fd("shell: not a valid identifier", 2);

	if (error == syntax_failure)
		ft_putendl_fd("shell: syntax failure", 2);
	if (error == cmd_not_found)
		ft_putendl_fd("shell: command not found", 2);
	if (error == syntax_error_token)
		ft_putendl_fd("shell: syntax error near unexpected token", 2);
}
