/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:56:23 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/23 10:23:34 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// #include "mini.h"

int	main(int argc, char **argv, char **envp)
{
	t_data		*data;
	t_command	commands;
	char		*path;
	char		*args[3];
	int			ret;

	int i = 0;
	args[i++] = "cd";
	args[i++] = "..";
	// args[i++] = "";
	// args[i++] = "";
	args[i++] = NULL;

	(void)argc;
	(void)argv;
	ret = 0;
	data = (t_data *)malloc(sizeof(t_data));
	alloc_env(&data->env, envp);
	data->exit_code = 0;
	data->cmmds = &commands;
	char *en[2] = {"env", NULL};
	commands.args = args;
	// env(data->env, en);
	ret = builtin_commands(args, data);
	printf("ret: %d\n", ret);
	env(data->env, en);
	path = getcwd(NULL, 0);
	printf("path: %s\n", path);
	free(path);
	// free_env (&data->env);
	free (data);
	// system("leaks minishell");
	return (ret);
}
