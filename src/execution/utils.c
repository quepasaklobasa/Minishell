/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcouto <jcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:34:39 by jcouto            #+#    #+#             */
/*   Updated: 2025/05/26 19:34:56 by jcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Setup file descriptors for command
void setup_fds(Command *cmd)
{
    if (cmd->in_fd == -1)
        cmd->in_fd = STDIN_FILENO;
    if (cmd->out_fd == -1)
        cmd->out_fd = STDOUT_FILENO;
}