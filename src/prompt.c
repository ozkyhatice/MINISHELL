/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkiraz <abkiraz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:13:49 by abkiraz           #+#    #+#             */
/*   Updated: 2024/06/28 10:13:50 by abkiraz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	printwelcome(void)
{
	printf("\033[32m/* ************************************************ */\n");
	printf("/*                                                  */\n");
	printf("/*          Welcome to our Miniroot Shell           */\n");
	printf("/*          hozkaya      <--->      relvan          */\n");
	printf("/*                                                  */\n");
	printf("/* ************************************************ */\n\n\033[0m");
}