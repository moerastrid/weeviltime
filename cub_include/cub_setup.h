/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_setup.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 16:22:33 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/13 13:32:21 by ageels        ########   odam.nl         */
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
// FOV : field of view (in degrees)
# ifndef FOV
#  define FOV 72
# endif
// RPD : rays per degree (in degrees)
# ifndef RPD
#  define RPD 27
# endif
// SPEED : player movement speed
# ifndef SPEED
#  define SPEED 5
# endif
//// DOF : depth of field (?)
//# ifndef DOF
//#  define DOF 32
//# endif

// COP : colour of player
# ifndef COP
#  define COP 0xFFC000FF
# endif

#endif