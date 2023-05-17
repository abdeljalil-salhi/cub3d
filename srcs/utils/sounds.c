/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 07:43:28 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/17 09:06:28 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_sounds(t_game *g)
{
	g->sound[SOUND_THEME].path = " assets/sounds/theme.wav";
	g->sound[SOUND_THEME].volume = "0.7";
	g->sound[SOUND_NPC_ATTACK].path = " assets/sounds/effects/npc_attack.wav";
	g->sound[SOUND_NPC_ATTACK].volume = "1";
	g->sound[SOUND_NPC_DEATH].path = " assets/sounds/effects/npc_death.wav";
	g->sound[SOUND_NPC_DEATH].volume = "1";
	g->sound[SOUND_NPC_DAMAGED].path = " assets/sounds/effects/npc_pain.wav";
	g->sound[SOUND_NPC_DAMAGED].volume = "1";
	g->sound[SOUND_PLAYER_DAMAGED].path = " assets/sounds/effects/player_pain.wav";
	g->sound[SOUND_PLAYER_DAMAGED].volume = "2";
	g->sound[SOUND_SHOTGUN].path = " assets/sounds/effects/shotgun.wav";
	g->sound[SOUND_SHOTGUN].volume = "1";
	return (RETURN_SUCCESS);
}

int	afplay(t_game *g, int sound)
{
	char	*command;
	char	*tmp;
	char	**afplays;

	afplays = (char *[]){"afplay -v ", g->sound[sound].volume,
			g->sound[sound].path, NULL};
	command = ft_strjoin(afplays[0], afplays[1]);
	if (!command)
		return (cub_errors_setter(g, ERR_MALLOC));
	tmp = command;
	command = ft_strjoin(command, afplays[2]);
	if (!command)
		return (cub_errors_setter(g, ERR_MALLOC));
	free(tmp);
	system(command);
	free(command);
	return (RETURN_SUCCESS);
}

void	play_sound_track(t_game *g)
{
	g->pid.soundtrack = fork();
	if (g->pid.soundtrack == -1)
		cub_errors_exit(g, ERR_FORK);
	if (g->pid.soundtrack == 0)
	{
		while (access(TMP, F_OK) == -1)
			if (afplay(g, SOUND_THEME))
				cub_errors_exit(g, g->error.message);
		exit(EXIT_SUCCESS);
	}
}

void	play_sound_effect(t_game *g, int sound)
{
	int	i;

	i = -1;
	while (g->pid.playing_soundeffect[++i] && i < 5)
		;
	if (i == 5)
		return ;
	g->pid.soundeffect[i] = fork();
	if (g->pid.soundeffect[i] == -1)
		cub_errors_exit(g, ERR_FORK);
	if (g->pid.soundeffect[i] == 0)
	{
		g->pid.playing_soundeffect[i] = getpid();
		if (afplay(g, sound))
			cub_errors_exit(g, g->error.message);
		g->pid.playing_soundeffect[i] = 0;
		exit(EXIT_SUCCESS);
	}
}

void	stop_sound_track(t_game *g)
{
	if (!g->allocated.soundtrack)
		return ;
	system("killall afplay");
	g->allocated.soundtrack = false;
	kill(g->pid.soundtrack, SIGKILL);
}
