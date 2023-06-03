/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylemrab <aylemrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 06:31:04 by aylemrab          #+#    #+#             */
/*   Updated: 2023/06/03 02:07:24 by aylemrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <signal.h>
# include <stddef.h>
# include <ctype.h>
# include <stdbool.h>
# include "libft/libft.h"

typedef struct s_vars
{
	int			fd[2];
	int			infile;
	int			outfile;
	int			pid1;
	int			pid;
	char		*c_path;
	char		**env;
}	t_vars;

char	**getpath(char **env);
int		check_access(char *join3);
char	*get_command_path(char *cmd, char **env_paths);

#endif