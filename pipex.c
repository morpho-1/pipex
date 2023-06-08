/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylemrab <aylemrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:19:38 by aylemrab          #+#    #+#             */
/*   Updated: 2023/06/08 10:35:02 by aylemrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	open_inout(t_vars *vars, char *av[])
{
	vars->outfile = open(av[4], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (vars->outfile == -1)
		perror("failed outfile");
	vars->infile = open(av[1], O_RDONLY);
	if (vars->infile < 0)
	{
		perror("Invalid file name");
		exit(1);
	}
}

static void	exec_cmd_one(t_vars *vars, char **av, char **env)
{
	close(vars->fd[0]);
	vars->c_path = get_command_path(*ft_split(av[2], ' '), getpath(env));
	if (!vars->c_path)
	{
		write(1, "path not found\n", 15);
		exit(1);
	}
	dup2(vars->infile, STDIN_FILENO);
	close(vars->infile);
	dup2(vars->fd[1], STDOUT_FILENO);
	close(vars->fd[1]);
	execve(vars->c_path, ft_split(av[2], ' '), env);
	perror("execve");
}

static void	exec_cmd_two(t_vars *vars, char **av, char **env)
{
	close(vars->fd[1]);
	vars->c_path = get_command_path(*ft_split(av[3], ' '), getpath(env));
	if (!vars->c_path)
	{
		write(1, "path not found\n", 15);
		exit(1);
	}
	dup2(vars->fd[0], STDIN_FILENO);
	close(vars->fd[0]);
	dup2(vars->outfile, STDOUT_FILENO);
	close(vars->outfile);
	execve(vars->c_path, ft_split(av[3], ' '), env);
	perror("execve");
}

int	main(int ac, char **av, char **env)
{
	t_vars	vars;

	ft_memset(&vars, 0, sizeof(t_vars));
	if (ac == 5)
	{
		open_inout(&vars, av);
		if (pipe(vars.fd) == -1)
			return (perror("pipe"), 1);
		vars.pid = fork();
		if (vars.pid == -1)
			return (perror("fork : cannot create child process"), 1);
		if (vars.pid == 0)
			exec_cmd_one(&vars, av, env);
		vars.pid1 = fork();
		if (vars.pid1 == -1)
			return (perror("fork : cannot create child process"), 1);
		if (vars.pid1 == 0)
			exec_cmd_two(&vars, av, env);
	}
	else
		perror("invalid args");
	close(vars.fd[0]);
	close(vars.fd[1]);
	while (waitpid(-1, 0, 0) != -1)
		;
}
