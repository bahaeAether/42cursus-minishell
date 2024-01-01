/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 10:57:47 by baboulou          #+#    #+#             */
/*   Updated: 2023/12/29 14:10:52 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"

int	print_amb_msg(t_node *node)
{
	ft_putstr_fd("bash: $", 2);
	ft_putstr_fd(node->amb_msg, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	return (1);
}

int	print_file_not_found_msg(t_node *node)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(node->file_msg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	if (ft_strcmp(node->cmd, node->file_msg) == 0)
		return (127);
	return (1);
}

int	print_permission_msg(t_node *node)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(node->file_msg, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	if (ft_strcmp(node->cmd, node->file_msg) == 0)
		return (126);
	return (1);
}

int	print_cmd_not_found_msg(t_node *node)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(&node->cmd[1], 2);
	ft_putstr_fd(": command not found\n", 2);
	return (127);
}

int	print_isd_msg(t_node *node)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(node->file_msg, 2);
	ft_putstr_fd(": is a directory\n", 2);
	if (ft_strcmp(node->cmd, node->file_msg) == 0)
		return (126);
	return (1);
}
