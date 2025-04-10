/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:41:44 by poverbec          #+#    #+#             */
/*   Updated: 2025/04/10 16:29:17 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>


// get input 
void	interactive_shell_tty(int argc, char **argv, char **envp, char *line);
void	non_interactive_shell(int argc, char **argv, char **envp, char *line);

// lexer
bool	lexer(char *line);
bool	wrong_use_pipe_and_redirection(char *line);


bool 	tokeniser (char *line);




// laxxer ==> lexical analyser
typedef struct s_tokens
{
	
}	t_tokens;

#endif