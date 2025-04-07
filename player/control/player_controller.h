#ifndef ST_PLAYER_CONTROLLER_H
#define ST_PLAYER_CONTROLLER_H

void player_controller_new(void);

void player_controller_free(void);

void player_controller_update(double dt);

// Tells the player to ignore input and enable the mouse for this frame. Mostly for UI
void player_controller_ignore_input(void);

#endif // ST_PLAYER_CONTROLLER_H
