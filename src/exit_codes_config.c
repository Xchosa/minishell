/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_codes_config.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschulle <tschulle@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:59:22 by poverbec          #+#    #+#             */
/*   Updated: 2025/07/23 13:31:21 by tschulle         ###   ########.fr       */
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

// free exit codes
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
		//(printf("shell: '%s': not a valid identifier \n", line));
	if (error == syntax_failure)
		ft_putendl_fd("shell: syntax failure", 2);
		//(printf("shell: '%s': syntax failure \n", line));
	if (error == cmd_not_found)
		ft_putendl_fd("shell: command not found", 2);
		//(printf("shell: '%s': command not found \n", line));
	if (error == syntax_error_token)
		ft_putendl_fd("shell: syntax error near unexpected token", 2);
		//(printf("shell: syntax error near unexpected token '%s' \n", line));
	clean_token_lst(*token_list);
	free(line);
}

void	print_lexer_error_message(char *line)
{
	int	error;

	error = get_exit_codes()->last_exit_code;
	if (error == invalid_identifier)
		(printf("minishell: '%s': not a valid identifier \n", line));
	if (error == syntax_failure)
		(printf("minishell: '%s': syntax failure \n", line));
	if (error == cmd_not_found)
		(printf("minishell: '%s': command not found \n", line));
	if (error == syntax_error_token)
		(printf("minishell: syntax error near unexpected token '%s' \n", line));
}
