

void abandoned_update_pixels ( Uint32 * a_pixel, const char c_glyph, const Glyph_t * a_glyph )
{
	unsigned int gx, gy, gi, px, py, pi, gpx, gpy;
	for (gi = 0, gx = 0; gx < cx_glyph; ++gx)
	{
		px = xl_glyph * gx;
		for (gy = 0; gy < cy_glyph; ++gy, ++gi)
		{
			py = yl_glyph * gy;
			for (gpx = 0; gpx < xl_glyph; ++gpx)
			{
				for (gpy = 0; gpy < yl_glyph; ++gpy)
				{
					a_pixel [ (gpy + py)] = 0; // new idea, don't use this function
				}
			}
		}
	}
}

void update_pixels ( const int xl_win, const int yl_win, Uint32 * a_pixel, const char c_glyph, const Glyph_t * a_glyph )
{
	unsigned int pi, px, py, gx, gy, gpx, gpy;
	unsigned char val;
	a_pixel [0] = 5;
	px = 0;
	py = 0;
	gx = 0;
	gy = 0;
	for (pi = 0; pi < xl_win * yl_win; ++pi)
	{
		gpx = px - gx * xl_glyphbox;
		gpy = py - gy * yl_glyphbox;
		if (gpx >= display_padding && gpx < xl_glyph + display_padding
		 && gpy >= display_padding && gpy < yl_glyph + display_padding)
			val = a_glyph [gx + gy * cx_glyph].data [gpx - display_padding] [gpy - display_padding];
		else
			val = 0;
		a_pixel [pi] = val ? 0xffffffff : 0xff000000;
		++px;
		if (px % (xl_glyph + (display_padding << 1)) == 0)
			++gx;
		if (px == xl_win)
		{
			px = 0;
			gx = 0;
			++py;
			if (py % (yl_glyph + (display_padding << 1)) == 0)
				++gy;
		}
		else if (px > xl_win)
			printf ( "display-stuff.c/abandoned_update_pixels: ???" );
	}
}

void draw_pixels ( Uint32 * a_pixel, SDL_Renderer * renderp, SDL_Texture * texturep, const int xl_win )
{
	SDL_UpdateTexture ( texturep, NULL, a_pixel, xl_win * sizeof ( Uint32 ) );
	SDL_RenderClear ( renderp );
	SDL_RenderCopy ( renderp, texturep, NULL, NULL );
	SDL_RenderPresent ( renderp );
}
