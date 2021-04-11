TTF_Font *font = NULL;
SDL_Texture *text;
SDL_Rect text_rect;
SDL_Color color = {0, 0, 0, 255};


void render_cursor()
{
	point_t point;
	sprite_t sprite;
	sprite_init(&sprite, cursor_spritesheet.texture);

	int offset_x = camera_pos.x % tile_size.x;
	int offset_y = camera_pos.y % tile_size.y;

	vec2d mouse_pos_adjusted = {mouse_pos.x, mouse_pos.y};

	mouse_pos_adjusted.x -= offset_x;
	mouse_pos_adjusted.y -= offset_y;

	int cell_x = (mouse_pos_adjusted.x / tile_size.x);
	int cell_y = (mouse_pos_adjusted.y / tile_size.y);

	int snap_x = (mouse_pos_adjusted.x / tile_size.x) * tile_size.x;
	int snap_y = (mouse_pos_adjusted.y / tile_size.y) * tile_size.y;

	selected_x = (cell_y - (camera_pos.y / tile_size.y)) + ((cell_x - camera_pos.x / tile_size.x));
	selected_y = (cell_y - (camera_pos.y / tile_size.y)) - ((cell_x - camera_pos.x / tile_size.x));

	/*
	printf("MOUSE: %d - %d\n", mouse_pos.x, mouse_pos.y);
	printf("CELL: %d - %d\n", cell_x, cell_y);
	printf("SELECTED: %d - %d\n", selected_x, selected_y);
	printf("SNAP: %d - %d\n", snap_x, snap_y);
	printf("OFFSET: %d - %d\n", offset_x, offset_y);
	*/

	//load_text();
	load_text(0, 0, "SELECTED CELL:");
	SDL_RenderCopy(renderer, text, NULL, &text_rect);

	char str[10];
	sprintf(str, "%d", selected_x);
	load_text(200, 0, str);
	SDL_RenderCopy(renderer, text, NULL, &text_rect);

	sprintf(str, "%d", selected_y);
	load_text(250, 0, str);
	SDL_RenderCopy(renderer, text, NULL, &text_rect);

	SDL_Rect rect;
	rect.x = snap_x + offset_x;
	rect.y = snap_y + offset_y;
	rect.w = tile_size.x;
	rect.h = tile_size.y;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &rect);
			
	
	sprite.src_rect.x = 0;
	sprite.src_rect.y = 0;
	point.x = selected_x;
	point.y = selected_y;

	//iso_map_to_screen(&point);

	sprite.dst_rect.x = point.x;
	sprite.dst_rect.y = point.y;
	sprite.dst_rect.w = tile_size.x;
	sprite.dst_rect.h = tile_size.y;

	SDL_RenderCopy(renderer, sprite.texture, &sprite.src_rect, &sprite.dst_rect);
}

void render_player()
{
	point_t point;

	point.x = cloud.dst_rect.x;
	point.y = cloud.dst_rect.y;

	//iso_map_to_screen(&point);

	SDL_Rect tmp_dst_rect;
	tmp_dst_rect.x = point.x;
	tmp_dst_rect.y = point.y - (tile_size.y) - (tile_size.y / 4);
	tmp_dst_rect.w = tile_size.x;
	tmp_dst_rect.h = tile_size.y * 2;

	SDL_RenderCopy(renderer, cloud.texture, &cloud.src_rect, &tmp_dst_rect);
}


void iso_map_to_screen(point_t *point)
{
	int tmp_x = camera_pos.x + (point->x - point->y) * (tile_size.x / 2);
	int tmp_y = camera_pos.y + (point->x + point->y) * (tile_size.y / 2);
	point->x = tmp_x;
	point->y = tmp_y;
}


void render_map()
{
	point_t point;
	sprite_t sprite;
	sprite_init(&sprite, tileset.texture);

	for(int y = 0; y < MAP_HEIGHT; y++)
		for(int x = 0; x < MAP_WIDTH; x++)
		{
			sprite.src_rect.x = (map[y][x] % 3) * 32;
			sprite.src_rect.y = (map[y][x] / 3) * 16;
			sprite.src_rect.h = 16;
			point.x = x;
			point.y = y;

			iso_map_to_screen(&point);

			sprite.dst_rect.x = point.x;
			sprite.dst_rect.y = point.y;
			sprite.dst_rect.w = tile_size.x;
			sprite.dst_rect.h = tile_size.y;

			if(map[y][x] >= 6)
			{
				printf("%d %d\n", sprite.dst_rect.y, sprite.dst_rect.h);
				sprite.src_rect.h = 32;
				sprite.dst_rect.h *= 2;
				sprite.dst_rect.y -= 16 * scale;
			}
			if(map[y][x] >= 9)
			{
				
				sprite.src_rect.y += 16;
			}
			

			SDL_RenderCopy(renderer, sprite.texture, &sprite.src_rect, &sprite.dst_rect);
		}
}


int load_font()
{
	font = TTF_OpenFont("./assets/roboto.ttf", 24);
	if(font == NULL)
	{
		printf("failed to load font");
		return 0;
	}
	
	return 1;
}


int load_text(int x, int y, char *content)
{
	SDL_Surface *tmp_surface = TTF_RenderText_Solid(font, content, color);
	if(tmp_surface == NULL)
	{
		printf("cant load font");
		return 0;
	}

	text = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	if(text == NULL)
	{
		printf("cant convert font to texture");
		return 0;
	}

	text_rect.x = x;
	text_rect.y = y;
	text_rect.w = tmp_surface->w;
	text_rect.h = tmp_surface->h;

	SDL_FreeSurface(tmp_surface);
	
	return 1;
}

