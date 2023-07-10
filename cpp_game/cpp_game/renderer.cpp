
internal void
renderer_background()
{
	u32* pixel_pointer = (u32*)render_state.memory;

	for (int y = 0; y < render_state.height; y++)
	{
		for (int x = 0; x < render_state.width; x++)
		{
			*pixel_pointer++ = x + y;
		}
	}
}

internal void
clear_screen(unsigned int color)
{
	u32* pixel_pointer = (u32*)render_state.memory;

	for (int y = 0; y < render_state.height; y++)
	{
		for (int x = 0; x < render_state.width; x++)
		{
			*pixel_pointer++ = color;
		}
	}
}

internal void
draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color)
{
	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);


	for (int y = y0; y < y1; y++)
	{
		u32* pixel_pointer = (u32*)render_state.memory + x0 + y * render_state.width;

		for (int x = x0; x < x1; x++)
		{
			*pixel_pointer++ = color;
		}
	}
}

global_variable float render_scale = 0.01f;

internal void
draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color)
{
	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	half_size_x *= render_state.height * render_scale;
	half_size_y *= render_state.height * render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f; 
	//Change to pixels
	int x0 = x - half_size_x;
	int y0 = y - half_size_y;
	int x1 = x + half_size_x;
	int y1 = y + half_size_y;


	draw_rect_in_pixels(x0, y0, x1, y1, color);
}

const char* letters[][7] =
{
	" 00",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",
}

internal void
draw_letter(float x, float y, float size, u32 color)
{
	float half_size = size / 2;
	const char** a_letter = letters[0];
}

internal void
draw_number(int number, float x, float y, float size, u32 color)
{
	float half_size = size / 2;
	bool drew_number = false;

	while (number || !drew_number)
	{
		drew_number = true;
		int digit = number % 10;
		number = number / 10;
		switch (digit)
		{
		case 0:
		{
			draw_rect(x - size, y, half_size, 2.5f * size, color);
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x, y + 2.f * size, half_size, half_size, color);
			draw_rect(x, y - 2.f * size, half_size, half_size, color);
			x -= 4.f * size;
		}break;
		case 1:
		{
			draw_rect(x, y, half_size, 2.5f * size, color);
			x -= 3.f * size;
		}break;
		case 2:
		{
			draw_rect(x + size, y + size, half_size, 1.5f * size, color);
			draw_rect(x - size, y - size, half_size, 1.5f * size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - 2.f * size, 1.5f * size, half_size, color);
			draw_rect(x, y + 2.f * size, 1.5f * size, half_size, color);
			x -= 4.f * size;
		}break;
		case 3:
		{
			draw_rect(x + size, y + size, half_size, 1.5f * size, color);
			draw_rect(x + size, y - size, half_size, 1.5f * size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - 2.f * size, 1.5f * size, half_size, color);
			draw_rect(x, y + 2.f * size, 1.5f * size, half_size, color);
			x -= 4.f * size;
		}break;
		case 4:
		{
			draw_rect(x - size, y + size, half_size, 1.5f * size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			x -= 4.f * size;
		}break;
		case 5:
		{
			draw_rect(x - size, y + size, half_size, 1.5f * size, color);
			draw_rect(x + size, y - size, half_size, 1.5f * size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - 2.f * size, 1.5f * size, half_size, color);
			draw_rect(x, y + 2.f * size, 1.5f * size, half_size, color);
			x -= 4.f * size;
		}break;
		case 6:
		{
			draw_rect(x + size, y - size, half_size, 1.5f * size, color);
			draw_rect(x - size, y, half_size, 2.5f * size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - 2.f * size, 1.5f * size, half_size, color);
			draw_rect(x, y + 2.f * size, 1.5f * size, half_size, color);
			x -= 4.f * size;
		}break;
		case 7:
		{
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x, y + 2.f * size, 1.5f * size, half_size, color);
			x -= 4.f * size;
		}break;
		case 8:
		{
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x - size, y, half_size, 2.5f * size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - 2.f * size, 1.5f * size, half_size, color);
			draw_rect(x, y + 2.f * size, 1.5f * size, half_size, color);
			x -= 4.f * size;
		}break;
		case 9:
		{
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x - size, y + size, half_size, 1.5f * size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - 2.f * size, 1.5f * size, half_size, color);
			draw_rect(x, y + 2.f * size, 1.5f * size, half_size, color);
			x -= 4.f * size;
		}break;
		}
	}
}