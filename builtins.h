/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahae <bahae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:00:15 by bahae             #+#    #+#             */
/*   Updated: 2023/12/13 10:40:38 by bahae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H

# define BUILTINS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_env
{	
	char			*key;
	char			*value;
	struct s_env	*next;
	
}			t_env;


#endif
