/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <null>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 23:57:55 by valentin          #+#    #+#             */
/*   Updated: 2017/12/07 02:17:20 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

void	ft_checker_error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

int		ft_is_valid_operation(char *str)
{
	if (ft_strcmp(str, "sa") == 0)
		return (1);
	else if (ft_strcmp(str, "sb") == 0)
		return (1);
	else if (ft_strcmp(str, "ss") == 0)
		return (1);
	else if (ft_strcmp(str, "pa") == 0)
		return (1);
	else if (ft_strcmp(str, "pb") == 0)
		return (1);
	else if (ft_strcmp(str, "ra") == 0)
		return (1);
	else if (ft_strcmp(str, "rb") == 0)
		return (1);
	else if (ft_strcmp(str, "rr") == 0)
		return (1);
	else if (ft_strcmp(str, "rra") == 0)
		return (1);
	else if (ft_strcmp(str, "rrb") == 0)
		return (1);
	else if (ft_strcmp(str, "rrr") == 0)
		return (1);
	return (0);
}

void	ft_del_operation(void *name, size_t size)
{
	(void)size;
	free(name);
}

void	ft_checker_handle_stack(int argc, char *argv[], t_env *env)
{
	int		count;
	int		nb;
	int		i;
	int		*tmp;

	count = 0;
	i = 0;
	while (++count < argc)
	{
		if ((nb = ft_getnbr(argv[count])) == 0 && ft_strcmp(argv[count], "0") != 0)
			ft_checker_error();
		tmp = env->stack_a;
		ft_free_tab((void*)(&env->stack_a));
		if (!(env->stack_a = malloc(sizeof(int) * (i + 1))))
			ft_checker_error();
		ft_memcpy(&tmp, &env->stack_a, (size_t)i + 1);
		env->stack_a[i++] = nb;
	}
}

void	ft_checker_handle_operations(t_env *env)
{
	char	*line;

	env->operations = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (!ft_is_valid_operation(line))
			return (ft_checker_error());
		else
			ft_lstaddend(&env->operations, ft_lstnew(line, ft_strlen(line)));
	}
	free(line);
}

int		main(int argc, char *argv[])
{
	t_env	env;

	if (argc < 2)
		ft_checker_error();
	if (!(env.stack_a = malloc(sizeof(int))) || !(env.stack_b = malloc(sizeof(int))))
		ft_checker_error();
	ft_memset(&env, 0, sizeof(env));
	ft_checker_handle_stack(argc, argv, &env);
	ft_checker_handle_operations(&env);
	ft_free_tab((void*)(&env.stack_b));
	ft_free_tab((void*)(&env.stack_a));
	ft_lstdel(&env.operations, &ft_del_operation);
	return (EXIT_SUCCESS);
}