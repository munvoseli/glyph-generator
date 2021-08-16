#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>


#define xl_glyph 6
#define yl_glyph 6
#define cx_glyph 4
#define cy_glyph 4
#define xyl_fuzz 2
#define display_padding 6
#define xl_glyphbox (xl_glyph + (display_padding << 1))
#define yl_glyphbox (yl_glyph + (display_padding << 1))

typedef struct Glyph
{
	Uint8 data [ xl_glyph            ] [ yl_glyph            ];
	Uint8 tryd [ xl_glyph            ] [ yl_glyph            ];
	Uint8 fuzz [ xl_glyph + xyl_fuzz ] [ yl_glyph + xyl_fuzz ];
} Glyph_t;


#include "glyph-data-utils.c"
#include "fuzz.c"
#include "display-stuff.c"


// experiment in style
unsigned long
calculate_total_difference
(
	const int c_glyph ,
	const Glyph_t const * a_glyph
)
{
	unsigned char i , j ;
	unsigned int g0 , g1 ;
	unsigned long result = 0 ;
	for ( g0 = 0 ; g0 < c_glyph ; ++g0 )
		for ( g1 = g0 + 1 ; g1 < c_glyph ; ++g1 )
			for ( i = 0 ; i < xl_glyph + xyl_fuzz ; ++i )
				for ( j = 0 ; j < yl_glyph + xyl_fuzz ; ++j )
					if ( a_glyph [ g0 ] . fuzz [ i ] [ j ] != a_glyph [ g1 ] . fuzz [ i ] [ j ] )
						++result ;
	return result ;
}


void init_glyphs ( const int c_glyph, Glyph_t * a_glyph )
{
	zero_data_all_glyphs ( c_glyph, a_glyph );
	copy_data_to_tryd ( c_glyph, a_glyph );
}



int main ( int argc, char ** argv )
{
	static const int c_glyph = cx_glyph * cy_glyph;
	static const int xl_win = cx_glyph * (xl_glyph + (display_padding << 1)), yl_win = cy_glyph * (yl_glyph + (display_padding << 1));
	char keep_going = 1;
	long prev_total_difference = 0, next_total_difference;
	SDL_Window * windowp;
	SDL_Renderer * renderp;
	SDL_Texture * texturep;
	Uint32 a_pixel [ xl_win * yl_win ];
	SDL_Event event;
	Glyph_t a_glyph [ c_glyph ];
	time_t time_thing;
	SDL_Init ( SDL_INIT_EVERYTHING );
	windowp = SDL_CreateWindow ( "h", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, xl_win, yl_win, 0 );
	renderp = SDL_CreateRenderer ( windowp, -1, 0 );
	texturep = SDL_CreateTexture ( renderp, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, xl_win, yl_win );
	
	srand ( (unsigned) time ( &time_thing ) );
	
	init_glyphs ( c_glyph, a_glyph );
	
	while (keep_going)
	{
		SDL_WaitEvent ( &event );
		if ( event.type == SDL_QUIT || ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE ) )
		{
			SDL_Quit ();
			keep_going = 0;
		}
		else if ( event.type == SDL_KEYDOWN )
		{
			if ( event.key.keysym.sym == SDLK_f )
			{
				randomize_glyphs                                   (c_glyph,a_glyph);
				do_fuzz_on_all_glyphs                              (c_glyph,a_glyph);
				next_total_difference = calculate_total_difference (c_glyph,a_glyph);
				if ( prev_total_difference > next_total_difference )
					copy_data_to_tryd                          (c_glyph,a_glyph);
				else
				{
					copy_tryd_to_data                          (c_glyph,a_glyph);
					prev_total_difference = next_total_difference;
				}
				update_pixels ( xl_win, yl_win, a_pixel, c_glyph, a_glyph );
				draw_pixels ( a_pixel, renderp, texturep, xl_win );
			}
		}
	}
	return 0;
}
