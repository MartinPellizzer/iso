#include "../inc/game.h"


map_t map;
moving_area_t moving_area;

player_t player1;
player_t player2;
player_t enemy1;
player_t enemy2;

vec2_t tile_size;

int player_num = 0;
int player_index = 0;

void init()
{
	sdl_init();
	is_running = 1;
	scale = 1;
	tile_size.x = 32 * scale;
	tile_size.y = 16 * scale;
		
	FPS = 60;
	frame_delay = 1000 / FPS;

	texture_t texture;
	texture_init(&texture);
	texture_load_from_file(&texture, "./assets/tileset_32x16.png");

	// init map
	vec2_t map_tiles_num = {16, 16};
	map_init(&texture, tile_size, map_tiles_num);

	// init players
	vec2_t player1_pos = {3, 10};
	int player1_dir = 0;
	player_init(&player1, sdl_load_texture("./assets/cloud.png"), player1_pos, player1_dir);
	player1.mov = 4;

	vec2_t player2_pos = {5, 10};
	int player2_dir = 0;
	player_init(&player2, sdl_load_texture("./assets/cloud.png"), player2_pos, player2_dir);
	player2.mov = 4;

	vec2_t enemy1_pos = {10, 3};
	int enemy1_dir = 2;
	player_init(&enemy1, sdl_load_texture("./assets/dragoon.png"), enemy1_pos, enemy1_dir);
	enemy1.mov = 3;

	vec2_t enemy2_pos = {12, 3};
	int enemy2_dir = 2;
	player_init(&enemy2, sdl_load_texture("./assets/dragoon.png"), enemy2_pos, enemy2_dir);
	enemy2.mov = 3;

	player_manager_init(4);
	player_manager.players[0] = player1;
	player_manager.players[1] = player2;
	player_manager.players[2] = enemy1;
	player_manager.players[3] = enemy2;

	player_manager.current_player = &player_manager.players[0];

	// init cursor
	vec2_t cursor_pos = {player_manager.current_player->pos.x, player_manager.current_player->pos.y}; 
	cursor_init(sdl_load_texture("./assets/cursor.png"), cursor_pos, map_tiles_num);
	
	// init moving area
	moving_area_init(&moving_area, sdl_load_texture("./assets/cursor.png"), tile_size, map_tiles_num);
	
	// init camera
	camera_init();

	path = NULL;

	astar_init(&map);
	
}



void update()
{
	player_manager_update();

	player_move(player_manager.current_player, 1, 0);

	mouse_update();
	camera_update(&tile_size);

	cursor_update();
}




void move_to_tile()
{
	selected_tile.x = cursor.pos.x;
	selected_tile.y = cursor.pos.y;

	node_start = &nodes[(player_manager.current_player->pos.y * map.tile_num.x + player_manager.current_player->pos.x)];
	node_end = &nodes[(selected_tile.y * map.tile_num.x + selected_tile.x)];

	solve_astar(&map);
}



void render()
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	SDL_RenderClear(renderer);
	
	map_render();
	moving_area_render(&moving_area, player_manager.current_player);
	cursor_render();
	player_manager_render();

	SDL_RenderPresent(renderer);

	delay_fps();
}

void delay_fps()
{
	frame_time = SDL_GetTicks() - frame_start;
	if(frame_delay > frame_time)
		SDL_Delay(frame_delay - frame_time);
	frame_start = SDL_GetTicks();
}

void change_player()
{
	player_index++;
	player_index %= player_manager.num;
	player_manager.current_player = &player_manager.players[player_index];
	cursor.pos = player_manager.current_player->pos;	
	camera_center_to_player(player_manager.current_player);
}

void handle_inputs()
{
	//const Uint8 *keystate = SDL_GetKeyboardState(NULL);
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				is_running = 0;
				break;

			case SDL_MOUSEWHEEL:
				mouse_scroll(event.wheel.x, event.wheel.y);
				break;

			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					map_get_tile_pos(&map);
				}

				if(event.button.button == SDL_BUTTON_MIDDLE)
				{
					mouse_pan_start();
				}
				break;

			case SDL_MOUSEBUTTONUP:
				if(event.button.button == SDL_BUTTON_MIDDLE)
				{
					mouse_pan_end();
				}
				break;

			
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_UP:
						cursor_move(0, -1, player_manager.current_player);
						break;
					case SDLK_RIGHT:
						cursor_move(1, 0, player_manager.current_player);
						break;
					case SDLK_DOWN:
						cursor_move(0, 1, player_manager.current_player);
						break;
					case SDLK_LEFT:
						cursor_move(-1, 0, player_manager.current_player);
						break;
					case SDLK_x:
						change_player();
						break;
					case SDLK_z:
						move_to_tile();
						break;
					default:
						break;
				}
				break;
			

			default:
				break;
		}
	}
	/*

	if(keystate[SDL_SCANCODE_UP])
	{
		//llist_vec2_insert(&path, pos);
		player_move(current_player, 0, -1);
	}
	else if(keystate[SDL_SCANCODE_RIGHT])
	{
		player_move(current_player, 1, 0);
	}
	else if(keystate[SDL_SCANCODE_DOWN])
	{
		player_move(current_player, 0, 1);
	}
	else if(keystate[SDL_SCANCODE_LEFT])
	{
		player_move(current_player, -1, 0);
	}
*/
}

void quit()
{
	sdl_quit();
}


