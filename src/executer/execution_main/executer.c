/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:13:15 by tschulle          #+#    #+#             */
/*   Updated: 2025/07/01 11:50:52 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"



void	ft_execute_command(t_cmd_node *cmd_node, char **envp)
{
	char	*path;

	path = ft_getpath(cmd_node->cmd[0], envp); // ft_getpath und alles was folgt ist einfach aus pipex kopiert. 
	//in pipex.c ist eine funktion ft_freearray2 weil du auch eine hattest und mich der compiler dafuer angekackt hat. 
	//kann man aber auf eine reduzieren
	if (path == NULL)
	{
		return ; //errorhandling, free, exit
	}
	execve(path, cmd_node->cmd, envp); // eventuell errorcheck also != 0 ? und ausgabe error sollte hier mit perror funktionieren
	// path ist malloced und muesste eigentlich von der execute main am ende einmal gefreet werden.
}


// functioniert nur fuer Outfile
// void	ft_execute_node(
// 	t_cmd_list *cmd_list, t_cmd_node *cmd_node, int fd[][2], char **envp)
// { 
// 	int backupStdout = dup(STDOUT_FILENO);
// 	int backupStdin = dup(STDIN_FILENO);

	
// 	if (cmd_list->size > 1)
// 		ft_manage_pipes(cmd_list, cmd_node, fd);
// 	// muss verallgemeinert sein 
// 	// int backupSTDOUT = dup(STDOUT_FILENO);// immer standout speichern, nur einmal davor. nie exist danach machen. // mu
// 	ft_manage_redirections_multi(cmd_node, fd, backupStdin, backupStdout);
	
// 	if (cmd_node->cmd_type == EXECUTE)
// 		ft_execute_command(cmd_node, envp);
// 	else if (cmd_node->cmd_type == BUILTIN)
// 	{
		
// 		ft_execute_builtin(cmd_node, envp);
// 		if(cmd_list->size > 1)
// 		{
// 			dup2(backupStdout, STDOUT_FILENO);
// 			exit(0); // auf keinen Fall 
// 		}
// 			// exit damit child prozesse von builtins keine zombie prozesse werden.
// 			// ob der wert hier wichtig is weiss ich nicht, haengt glaub ich davon ab wie man in ft_execute damit umgeht
// 	}
// 	dup2(backupStdout, STDOUT_FILENO);
// }

// dafor die fd speichern wie in outfile 
// 



bool manage_single_cmd_node(t_cmd_list *cmd_list, t_cmd_node *cmd_node, int fd[][2], char **envp)
{
	int backupStdout;
	int backupStdin;
	
	backupStdout = dup(STDOUT_FILENO);
	backupStdin = dup(STDIN_FILENO);

	(void) cmd_list;
	// printf("\n do i entere\n");
	ft_manage_redirections_multi(cmd_node->file_list, fd, backupStdin, backupStdout );
	if (cmd_node->cmd_type == BUILTIN)
		ft_execute_builtin(cmd_node, envp);
	
	
	reset_redir(&backupStdin, &backupStdout);
	return (true);
	// redirecte Stdout_filien, zuruck auf backupSTDout

}

// <<hello <<now funcitioniert
// echo hallo <<now 		->printed nicht hallo nach heredoc
// cat <<now 				haegt sich auf 
// modifizierte ft_execute_node
bool execution_loop (t_cmd_list *cmd_list, t_cmd_node *cmd_node, int fd[][2], char **envp)
{
	int backupStdout;
	int backupStdin;
	// printf("do I enter executon ");
	backupStdout = dup(STDOUT_FILENO);
    backupStdin = dup(STDIN_FILENO);
	while(cmd_node != NULL)
	{
		if (cmd_list->size > 1)
			ft_manage_pipes(cmd_list, cmd_node, fd);
		// printf("entered ft_manage_redirection");
		if (ft_manage_redirections_multi(cmd_node->file_list, fd, backupStdin, backupStdout) != 0);
			return false;
		// printf("exited ft_manage_redirection");
		if(cmd_node->cmd_type == EXECUTE)
			ft_execute_command(cmd_node, envp);
		else if (cmd_node->cmd_type == BUILTIN)
			ft_execute_builtin(cmd_node, envp);
		reset_redir(&backupStdin,&backupStdout);
		cmd_node = cmd_node->next;
	}
	reset_redir(&backupStdin,&backupStdout);
	return true;
}


void	ft_execute(t_cmd_list *cmd_list, char **envp)
{
	t_cmd_node	*cur_cmd_node;
	int			pid;
	int			i;

	i = 0;
	save_heredoc_files(&cmd_list->head);
	// iter_cmd_lst(cmd_list, &print_cmd_lst);
	
	int			fd[(int)cmd_list->size][2]; // am anfang werden alle pipes erstellt. ich glaube norminette mochte die schreibweise nicht, also vllt mit * ?
	
	cur_cmd_node = cmd_list->head;
	if (cmd_list->size == 1 && cmd_list->head->cmd_type == BUILTIN) // das ist der sonderfall von dem gabrijel geredet hat. Das muss sein damit man im selben prozess bleibt.
	{ 
		if (manage_single_cmd_node(cmd_list, cur_cmd_node, fd, envp ) == true) // works
			return ; 
	}
	else
	{
		if (cmd_list->size > 1) // pipes nur wenn mehr als eine node
			ft_open_pipes(fd, cmd_list); // die funktionen zu pipes sind alle irgendwie kompliziert, aber ich glaube sie funktionieren. 
			//Es geht darum dass die child prozesse offene fd erben und am ende des child prozesses alle fd geschlossen sind
		
		while (cur_cmd_node != NULL)
		{
			// printf("before forking ");
			pid = fork();
			if (pid == 0)
			{
				// ft_execute_node(cmd_list, cur_cmd_node, fd, envp);
				if (execution_loop (cmd_list, cur_cmd_node, fd, envp) == false)
					break;
			}
			wait(0); // hier mit wait oder waitpid, kann der exit code von execve abgefangen werden. der exit code builtins kommt aus zeile 55. ist aber vielleicht gar nicht noetig weil es ja eh darum geht die variable zu setzen und nicht so sehr darum dass das child mit dem richtigen code exitet
			cur_cmd_node = cur_cmd_node->next;
			if (i < cmd_list->size - 1)
				close(fd[i][1]);
			if (i > 0 && i < cmd_list->size - 1)
			{
				// if (i > 0)
				close(fd[i - 1][0]);
			}
			i++;
		}
		if (cmd_list->size > 1)
			close(fd[i - 1][0]);
	}
}

// echo ?! -> should return a new line 
// cmd list => uebergibt 'echo' '' -> besser NULL?




//test fuer export
// int	main(int argc, char **argv, char **envp)
// {
// 	t_cmd_list	cmd_list;
// 	t_cmd_node	cmd_node1;
// 	t_file_list	file_list1;

// 	(void)argc;
// 	(void)argv;
// 	if (init_bash(envp, argc)== false || (init_exit_codes(argc) == false))
//  		return(1);
// 	cmd_list.head = &cmd_node1;
// 	cmd_list.tail = NULL;
// 	cmd_list.size = 1;
// 	cmd_node1.cmd_type = BUILTIN;
// 	cmd_node1.cmd = ft_split("export thilo=hi", ' ');
// 	//cmd_node1.cmd = {"export", "thilo=hi", "paul=kruecke", "test=cat makefile", NULL};
// 	cmd_node1.file_list = &file_list1;
// 	cmd_node1.next = NULL;
// 	file_list1.head = NULL;
// 	file_list1.tail = NULL;
// 	file_list1.size = 0;
// 	ft_execute(&cmd_list, get_bash()->env);
// }

//test fuer cd
// int	main(int argc, char **argv, char **envp)
// {
// 	t_cmd_list	cmd_list;
// 	t_cmd_node	cmd_node1;
// 	t_file_list	file_list1;

// 	(void)argc;
// 	(void)argv;
// 	cmd_list.head = &cmd_node1;
// 	cmd_list.tail = NULL;
// 	cmd_list.size = 1;
// 	cmd_node1.cmd_type = BUILTIN;
// 	cmd_node1.cmd = ft_split("cd /home/thilo/projects/philo", ' ');
// 	cmd_node1.file_list = &file_list1;
// 	cmd_node1.next = NULL;
// 	file_list1.head = NULL;
// 	file_list1.tail = NULL;
// 	file_list1.size = 0;
// ft_execute(&cmd_list, envp);
// }





//main fuer builtin pwd
// int	main(int argc, char **argv, char **envp)
// {
// 	t_cmd_list	cmd_list;
// 	t_cmd_node	cmd_node1;
// 	t_file_list	file_list1;

// 	(void)argc;
// 	(void)argv;
// 	cmd_list.head = &cmd_node1;
// 	cmd_list.tail = NULL;
// 	cmd_list.size = 1;
// 	cmd_node1.cmd_type = BUILTIN;
// 	cmd_node1.cmd = ft_split("pwd", ' ');
// 	cmd_node1.file_list = &file_list1;
// 	cmd_node1.next = NULL;
// 	file_list1.head = NULL;
// 	file_list1.tail = NULL;
// 	file_list1.size = 0;
// ft_execute(&cmd_list, envp);
// }

//test fuer builtin echo
// int	main(int argc, char **argv, char **envp)
// {
// 	t_cmd_list	cmd_list;
// 	t_cmd_node	cmd_node1;
// 	t_file_list	file_list1;

// 	(void)argc;
// 	(void)argv;
// 	if (init_bash(envp, argc)== false || (init_exit_codes(argc) == false))
// 		return(1);
// 	cmd_list.head = &cmd_node1;
// 	cmd_list.tail = NULL;
// 	cmd_list.size = 1;
// 	cmd_node1.cmd_type = BUILTIN;
// 	// export test=tschulle;
// 	// char *buf[] = {"$test"};
// 	// char *buf[] = {"echo", "", NULL "halo", "$welt", "ein langer string in einer zeile", NULL};
// 	// char *buf1[] = {"echo", "-n", "halo", "'$welt'", "ein langer string in einer zeile", NULL};
// 	// char *buf2[] = {"echo", "-n", "halo", "welt", "ein langer string in     einer zeile", NULL};
// 	// cmd_node1.cmd = buf;
// 	//cmd_node1.cmd = ft_split("echo hello $?    test $USER", ' ');
// 	cmd_node1.file_list = &file_list1;
// 	cmd_node1.next = NULL;
// 	file_list1.head = NULL;
// 	file_list1.tail = NULL;
// 	file_list1.size = 0;
// ft_execute(&cmd_list, envp);
// }


//test fuer append
// int	main(int argc, char **argv, char **envp)
// {
// 	t_cmd_list	cmd_list;
// 	t_cmd_node	cmd_node1;
// 	t_file_list	file_list1;
// 	t_file_node file_node1;
// 	t_file_node file_node2;
// 	t_file_node	file_node3;

// 	(void)argc;
// 	(void)argv;
// 	cmd_list.head = &cmd_node1;
// 	cmd_list.tail = NULL;
// 	cmd_list.size = 1;
// 	cmd_node1.cmd_type = 2;
// 	cmd_node1.cmd = ft_split("head -n 5", ' ');
// 	cmd_node1.file_list = &file_list1;
// 	cmd_node1.next = NULL;
// 	file_list1.head = &file_node1;
// 	file_list1.tail = NULL;
// 	file_list1.size = 3;
// 	file_node1.filename = "eingabe";
// 	file_node1.next = &file_node2;
// 	file_node1.redir_type = 1;
// 	file_node2.filename = "ausgabe";
// 	file_node2.next = &file_node3;
// 	file_node2.redir_type = 2;
// 	file_node3.filename = "ausgabe2";
// 	file_node3.redir_type = 3;
// 	file_node3.next = NULL;
// ft_execute(&cmd_list, envp);
// }


//test for priority of pipes vs redirects;
// int	main(int argc, char **argv, char **envp)
// {
// 	t_cmd_list	cmd_list;
// 	t_cmd_node	cmd_node1;
// 	t_cmd_node	cmd_node2;
// 	t_file_list	file_list1;
// 	t_file_list file_list2;
// 	t_file_node file_node1;
// 	t_file_node file_node2;
// 	t_file_node	file_node3;

// 	(void)argc;
// 	(void)argv;
// 	cmd_list.head = &cmd_node1;
// 	cmd_list.tail = &cmd_node2;
// 	cmd_list.size = 2;
// 	cmd_node1.cmd_type = 2;
// 	cmd_node1.cmd = ft_split("tail -n 3", ' ');
// 	cmd_node1.file_list = &file_list1;
// 	cmd_node1.next = &cmd_node2;
// 	file_list1.head = &file_node1;
// 	file_list1.tail = NULL;
// 	file_list1.size = 2;
// 	file_node1.filename = "ausgabe";
// 	file_node1.next = &file_node2;
// 	file_node1.redir_type = 2;
// 	file_node2.filename = "eingabe";
// 	file_node2.next = NULL;
// 	file_node2.redir_type = 1;
// 	cmd_node2.cmd_type = 2;
// 	cmd_node2.cmd = ft_split("head -n 2", ' ');
// 	cmd_node2.file_list= &file_list2;
// 	file_list2.head = &file_node3;
// 	file_list2.size = 1;
// 	file_list2.tail = NULL;
// 	file_node3.filename = "test";
// 	file_node3.next = NULL;
// 	file_node3.redir_type = 1;
// 	cmd_node2.next = NULL;
// 	ft_execute(&cmd_list, envp);
// }

//test for multiple pipes
// int	main(int argc, char **argv, char **envp)
// {
// 	t_cmd_list	cmd_list;
// 	t_cmd_node	cmd_node1;
// 	t_cmd_node	cmd_node2;
// 	t_cmd_node	cmd_node3;
// 	t_cmd_node	cmd_node4;
// 	t_cmd_node	cmd_node5;
// 	t_file_list	file_list1;
// 	t_file_list file_list2;
// 	t_file_list file_list3;
// 	t_file_list file_list4;
// 	t_file_list	file_list5;
// 	t_file_node file_node1;
// 	(void)argc;
// 	(void)argv;
// 	cmd_list.head = &cmd_node1;
// 	cmd_list.tail = &cmd_node5;
// 	cmd_list.size = 5;
// 	cmd_node1.cmd_type = 2;
// 	cmd_node1.cmd = ft_split("tail -n 8", ' ');
// 	cmd_node1.file_list = &file_list1;
// 	cmd_node1.next = &cmd_node2;
// 	file_list1.head = &file_node1;
// 	file_list1.tail = NULL;
// 	file_list1.size = 1;
// 	file_node1.filename = "eingabe";
// 	file_node1.next = NULL;
// 	file_node1.redir_type = 1;
// 	cmd_node2.cmd_type = 2;
// 	cmd_node2.cmd = ft_split("head -n 7", ' ');
// 	cmd_node2.file_list= &file_list2;
// 	cmd_node2.next = &cmd_node3;
// 	file_list2.head = NULL; //&file_node5;
// 	file_list2.size = 0;
// 	file_list2.tail = NULL;
// 	cmd_node3.cmd_type = 2;
// 	cmd_node3.cmd = ft_split("tail -n 3", ' ');
// 	cmd_node3.file_list = &file_list3;
// 	cmd_node3.next = &cmd_node4;
// 	file_list3.head = NULL;
// 	file_list3.tail = NULL;
// 	file_list3.size = 0;
// 	cmd_node4.cmd_type = 2;
// 	cmd_node4.cmd = ft_split("head -n 2", ' ');
// 	cmd_node4.next = &cmd_node5;
// 	cmd_node4.file_list = &file_list4;
// 	file_list4.head = NULL;
// 	file_list4.tail = NULL;
// 	file_list4.size = 0;
// 	cmd_node5.cmd_type = 2;
// 	cmd_node5.cmd = ft_split("tail -n 1", ' ');
// 	cmd_node5.next = NULL;
// 	cmd_node5.file_list = &file_list5;
// 	file_list5.head = NULL;
// 	file_list5.tail = NULL;
// 	file_list5.size = 0;
// 	ft_execute(&cmd_list, envp);
// 	return (0);
// }

// //test for multiple in and out
// int	main(int argc, char **argv, char **envp)
// {
// 	t_cmd_list	cmd_list;
// 	t_cmd_node	cmd_node1;
// 	t_cmd_node	cmd_node2;
// 	t_file_list	file_list1;
// 	t_file_list file_list2;
// 	t_file_node	file_node1;
// 	t_file_node file_node2;
// 	t_file_node file_node3;
// 	t_file_node file_node4;
// 	t_file_node	file_node5;
// 	(void)argc;
// 	(void)argv;
// 	cmd_list.head = &cmd_node1;
// 	cmd_list.tail = &cmd_node2;
// 	cmd_list.size = 2;
// 	cmd_node1.cmd_type = 2;
// 	cmd_node1.cmd = ft_split("tail -n 1", ' ');
// 	cmd_node1.file_list = &file_list1;
// 	cmd_node1.next = &cmd_node2;
// 	file_list1.head = &file_node1;
// 	file_list1.tail = NULL;
// 	file_list1.size = 4;
// 	file_node1.redir_type = 1;
// 	file_node1.filename = "test";
// 	file_node1.next = &file_node2;
// 	file_node2.filename = "ausgabe";
// 	file_node2.redir_type = 2;
// 	file_node2.next = &file_node3;
// 	file_node3.filename = "eingabe";
// 	file_node3.redir_type = 1;
// 	file_node3.next = &file_node4;
// 	file_node4.filename = "ausgabe2";
// 	file_node4.redir_type = 2;
// 	file_node4.next = NULL;
// 	cmd_node2.cmd_type = 2;
// 	cmd_node2.cmd = ft_split("wc", ' ');
// 	cmd_node2.file_list= &file_list2;
// 	cmd_node2.next = NULL;
// 	file_list2.head = NULL; //&file_node5;
// 	file_list2.size = 0;
// 	file_list2.tail = NULL;
// 	ft_execute(&cmd_list, envp);
// 	return (0);
// }