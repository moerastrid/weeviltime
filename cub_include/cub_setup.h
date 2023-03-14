/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_setup.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 16:22:33 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/14 15:38:43 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_SETUP_H
# define CUB_SETUP_H

# include "cub.h"
# include "line.h"

// WIDTH of window
# ifndef WIDTH
#  define WIDTH 1920
# endif
// HEIGHT of window
# ifndef HEIGHT
#  define HEIGHT 1080
# endif
// FOV : field of view (in degrees)
# ifndef FOV
#  define FOV 72
# endif
// SPEED : player movement speed
# ifndef SPEED
#  define SPEED 0.05
# endif
// TURN_SPEED : player turn speed
# ifndef TURN_SPEED
#  define TURN_SPEED 3
# endif
// COP : colour of player
# ifndef COP
#  define COP 0xFFC000FF
# endif

#endif