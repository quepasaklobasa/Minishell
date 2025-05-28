/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcouto <jcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:28:32 by jcouto            #+#    #+#             */
/*   Updated: 2025/05/04 21:27:28 by jcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int ac, char **av, char **env)
{
    char *line;
    (void)ac;
    (void)av;
    while (1)
    {
        line = readline("minishell> ");
        if (!line) // Ctrl+D
            exit(EXIT_SUCCESS);
        if (*line)
            add_history(line);
        printf("You typed: %s\n", line);
        free(line);
    }
    return (0);
}
