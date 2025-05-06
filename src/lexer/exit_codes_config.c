


#include "parser.h"
#include "minishell.h"



t_bash	*get_exit_codes(void)
{
	static t_exit_codes	exit_code;

	return (&exit_code);
}

bool	init_exit_codes(int argc)
{
	t_exit_codes *exit_code;
	
	exit_code = get_exit_codes();
	if (argc == 1)
	{
		exit_code->ec_sucess = 0;
		exit_code->ec_abort_z = 146;
		exit_code->ec_failure = 127; // command not found
		exit_code->syntax_failure = 258;
		exit_code->last_exit_code = 0;
	}
	return (true);
}