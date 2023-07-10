#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float position_player_1, score_player_1;
float position_derivative_player_1;		//aka velocity
float position_player_2, score_player_2;
float position_derivative_player_2;		//aka velocity

float half_size_x_arena = 85, half_size_y_arena = 45;
float half_size_x_player = 2.5, half_size_y_player = 12;

float position_ball_x, position_ball_y;
float position_derivative_ball_x = 130, position_derivative_ball_y;
float half_size_ball = 1;


internal void
simulate_player(float *position, float *position_derivative, float position_derivative_derivative, float delta_time)
{
	position_derivative_derivative -= *position_derivative* 10.f;
	*position = *position + *position_derivative * delta_time + position_derivative_derivative* delta_time * delta_time / 2;
	*position_derivative = *position_derivative + position_derivative_derivative * delta_time;

	if ((*position + half_size_y_player) > half_size_y_arena)
	{
		*position = half_size_y_arena - half_size_y_player;
		*position_derivative = 0.f;
	}
	else if ((*position - half_size_y_player) < -half_size_y_arena)
	{
		*position = -half_size_y_arena + half_size_y_player;
		*position_derivative = 0.f;
	}
}

internal bool
aabb_vs_aabb(float p1x, float p1y, float hs1x, float hs1y,
	float p2x, float p2y, float hs2x, float hs2y)
{
	return (p1x + hs1x > p2x - hs2x &&
		p1x - hs1x < p2x + hs2x &&
		p1y + hs1y > p2y - hs2y &&
		p1y + hs1y < p2y + hs2y);
}

enum Gamemode
{
	GM_MENU,
	GM_GAMEPLAY,
};

Gamemode gamemode_current;
int hot_button;
bool enemy_is_ai;

internal void
game_simulate(Input* input, float delta_time)
{
	clear_screen(0xff5500);
	draw_rect(0, 0, half_size_x_arena, half_size_y_arena, 0xffaa33);
	 
	if (gamemode_current == GM_GAMEPLAY)
	{
		float position_derivative_derivative_player_1 = 0.f;		//aka acceleration
		float position_derivative_derivative_player_2 = 0.f;		//aka acceleration
		if (!enemy_is_ai)
		{
			if (is_down(BUTTON_DOWN)) position_derivative_derivative_player_1 -= 2000;
			if (is_down(BUTTON_UP)) position_derivative_derivative_player_1 += 2000;
		}
		else 
		{
			/*if (position_ball_y > position_player_1 + 2.f) position_derivative_derivative_player_1 += 1300;
			if (position_ball_y < position_player_1 + 2.f) position_derivative_derivative_player_1 -= 1300;*/
			position_derivative_derivative_player_1 = (position_ball_y - position_player_1) * 100;
			if (position_derivative_derivative_player_1 > 1300) position_derivative_derivative_player_1 = 1300;
			if (position_derivative_derivative_player_1 < -1300) position_derivative_derivative_player_1 = -1300;
		}
		if (is_down(BUTTON_S)) position_derivative_derivative_player_2 -= 2000;
		if (is_down(BUTTON_W)) position_derivative_derivative_player_2 += 2000;

		simulate_player(&position_player_1, &position_derivative_player_1, position_derivative_derivative_player_1, delta_time);
		simulate_player(&position_player_2, &position_derivative_player_2, position_derivative_derivative_player_2, delta_time);

		position_ball_x = position_ball_x + position_derivative_ball_x * delta_time;
		position_ball_y = position_ball_y + position_derivative_ball_y * delta_time;

		//simulate ball
		{
			if (aabb_vs_aabb(position_ball_x, position_ball_y, half_size_ball, half_size_ball, 80, position_player_1, half_size_x_player, half_size_y_player))
			{
				position_ball_x = 80 - half_size_x_player - half_size_ball;
				position_derivative_ball_x *= -1;

				position_derivative_ball_y = (position_ball_y - position_player_1) * 2 + position_derivative_player_1 * .75f;
			}
			else if (aabb_vs_aabb(position_ball_x, position_ball_y, half_size_ball, half_size_ball, -80, position_player_2, half_size_x_player, half_size_y_player))
			{
				position_ball_x = -80 + half_size_x_player + half_size_ball;
				position_derivative_ball_x *= -1;

				position_derivative_ball_y = (position_ball_y - position_player_2) * 2 + position_derivative_player_2 * .75f;
			}

			if (position_ball_y + half_size_ball > half_size_y_arena)
			{
				position_ball_y = half_size_y_arena - half_size_ball;
				position_derivative_ball_y *= -1;
			}
			else if (position_ball_y - half_size_ball < -half_size_y_arena)
			{
				position_ball_y = -half_size_y_arena + half_size_ball;
				position_derivative_ball_y *= -1;
			}

			if (position_ball_x + half_size_ball > half_size_x_arena)
			{
				position_derivative_ball_x *= -1;
				position_derivative_ball_y = 0;
				position_ball_x = 0;
				position_ball_y = 0;
				score_player_1++;
			}
			else if (position_ball_x - half_size_ball < -half_size_x_arena)
			{
				position_derivative_ball_x *= -1;
				position_derivative_ball_y = 0;
				position_ball_x = 0;
				position_ball_y = 0;
				score_player_2++;
			}
		}

		draw_number(score_player_1, -10, 40, 1.f, 0xbbffbb);
		draw_number(score_player_2, 10, 40, 1.f, 0xbbffbb);

		//Render
		draw_rect(position_ball_x, position_ball_y, half_size_ball, half_size_ball, 0xffffff);
		draw_rect(80, position_player_1, half_size_x_player, half_size_y_player, 0xff0000);
		draw_rect(-80, position_player_2, half_size_x_player, half_size_y_player, 0xff0000);
	}
	else
	{
		if (pressed(BUTTON_LEFT) || pressed(BUTTON_RIGHT))
		{
			hot_button = !hot_button;
		}
		
		if(pressed(BUTTON_ENTER))
		{
			gamemode_current = GM_GAMEPLAY;
			enemy_is_ai = hot_button ? 0 : 1;
		}

		if (hot_button == 0)
		{
			draw_rect(20, 0, 10, 10, 0xcccccc);
			draw_rect(-20, 0, 10, 10, 0xff0000);
		}
		else
		{
			draw_rect(-20, 0, 10, 10, 0xcccccc);
			draw_rect(20, 0, 10, 10, 0xff0000);
		}
	}
}