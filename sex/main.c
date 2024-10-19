/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 05:32:33 by aogbi             #+#    #+#             */
/*   Updated: 2024/10/19 06:58:12y aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sex.h"

extern char **environ;

void ft_cd(t_micro *node)
{
	if (node && node->size != 2)
	{
		write(STDERR_FILENO, "error: cd: bad arguments\n", strlen("error: cd: bad arguments\n"));
		return ;
	}

	if (chdir(node->cmd[1]) == -1)
	{
		write(STDERR_FILENO, "error: cd: cannot change directory to ", strlen("error: cd: cannot change directory to "));
		write(STDERR_FILENO, node->cmd[1], strlen(node->cmd[1]));
		write(STDERR_FILENO, "\n", 1);
	}
}

void syscall_error()
{
	write(STDERR_FILENO, "error: fatal\n", strlen("error: fatal\n"));
	exit(EXIT_FAILURE);
}

void execve_error(char *cmd)
{
	write(STDERR_FILENO, "error: cannot execute ", strlen("error: cannot execute "));
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void add_to_list(t_micro **head, t_micro *node)
{
	if (!(*head))
		*head = node;
	else
	{
		t_micro *tmp = *head;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void spawn_process(t_micro *node, int input, int fds[2])
{
	int output = fds[1];
	int zayd = fds[0];

	if (node && !strcmp(node->cmd[0], "cd"))
		return ft_cd(node);
	int ret = fork();
	if (ret == -1)
		syscall_error();
	else if (ret != 0)
		return ;
	
	if (zayd != 0 && zayd != 1)
	{
		if (close(zayd) == -1)
			syscall_error();
	}
	if (input != STDIN_FILENO)
	{
		if (dup2(input, STDIN_FILENO) == -1)
			syscall_error();
		if (close(input) == -1)
			syscall_error();
	}
	if (output != STDOUT_FILENO)
	{
		if (dup2(output, STDOUT_FILENO) == -1)
			syscall_error();
		if (close(output) == -1)
			syscall_error();
	}
	if (execve(node->cmd[0], node->cmd, environ) == -1)
		execve_error(node->cmd[0]);
}

void lunch_pipes(t_micro *head)
{
	int fds[2];
	int input = 0;

	int count = 0;
	while (head && head->next)
	{
		if (pipe(fds) == -1)
			syscall_error();
		spawn_process(head, input, fds);
		if (close(fds[1]) == -1)
			syscall_error();
		if (input != STDIN_FILENO)
		{
			if (close(input) == -1)
				syscall_error();
		}
		input = fds[0];
		head = head->next;
		count++;
	}
	fds[0] = 0;
	fds[1] = 1;
	spawn_process(head, input, fds);
	if (input != STDIN_FILENO)
	{
		if (close(input) == -1)
			syscall_error();
	}
	count++;
	int status = 0;
		// printf("===> wait for %d\n", count);
	for (int i = 0; i < count; i++)
	{
		waitpid(-1, &status, 0);
		// printf("===> wait for %d\n", i);
	}
	// printf("\n\n");
}

int exec_pipe(int ac, char **av, int i)
{
    t_micro *head = NULL;

    while (i < ac)
    {
		if (!strcmp(av[i], ";"))
		{
			i++;
			break ;
		}
		else if (!strcmp(av[i], "|"))
		{
			if (i == 0 || i == ac - 1)
				exit(EXIT_FAILURE);
			i++;
		}
		else
		{
        	t_micro *tmp = malloc(sizeof(t_micro));
			if (!tmp)
				syscall_error();

			int j = i;
			int size = 0;
			while (j < ac && strcmp(av[j], "|") && strcmp(av[j], ";"))
				j++, size++;

			tmp->cmd = malloc(sizeof(char *) * (size + 1));
			if (!tmp->cmd)
				syscall_error();
			
			j = i;
			size = 0;
			while (j < ac && strcmp(av[j], "|") && strcmp(av[j], ";"))
				tmp->cmd[size++] = av[j++];
			tmp->cmd[size] = NULL;
			tmp->size = size;
			// printf("size is %d\n", size);

			// for (int i = 0; i < size; i++)
			// 	printf("(%s)\n", tmp->cmd[i]);
			// printf("\n");
			
			add_to_list(&head, tmp);
			i = j;
		}
    }
	int c = 0;
	for (t_micro *tmp = head; tmp; tmp = tmp->next)
		c++;
	// printf("c %d\n", c);
	// printf("salina\n");
	lunch_pipes(head);
	return (i);
}

void microshell(int ac, char **av)
{
    int i = 0;
    while (i < ac)
        i = exec_pipe(ac, av, i);
}

int main(int ac, char **av)
{
	// printf("%d\n", getpid());
    microshell(ac - 1, av + 1);
	// sleep(100);
    return 0;
}