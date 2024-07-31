/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:04:41 by amecani           #+#    #+#             */
/*   Updated: 2024/07/31 21:16:11 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminal_setup(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	setup_pwd(char ***env)
{
	char	*pwd;
	char 	*tmp;

	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin("=", pwd);
	update_env("PWD", tmp, env);
	free(tmp);
	free(pwd);
}

int	main(int argc, char **av, char **environ)
{
	t_data	*data;

	(void)av;
	if (argc != 1)
		return (printf("Type only : './minishell' \n"));
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (printf("m_error\n"), 1);
	alloc_env(&data->env, environ);
	setup_pwd(&data->env);
	terminal_setup();
	while (command_center(data) != CTRL_D)
		free(data->input);
	free_arr(data->env);
	system("leaks minishell");
	return (0);
}
