void zero_data_all_glyphs ( const int c_glyph, Glyph_t * a_glyph )
{
	unsigned char g, i, j;
	for ( g = 0; g < c_glyph; ++g)
		for ( i = 0; i < xl_glyph; ++i)
			for ( j = 0; j < yl_glyph; ++j )
				a_glyph[g].data[i][j] = 0;
}

void copy_tryd_to_data ( const int c_glyph, Glyph_t * a_glyph )
{
	unsigned char g, i, j;
	for ( g = 0; g < c_glyph; ++g)
		for ( i = 0; i < xl_glyph; ++i)
			for ( j = 0; j < yl_glyph; ++j )
				a_glyph[g].data[i][j] = a_glyph[g].tryd[i][j];
}

void copy_data_to_tryd ( const int c_glyph, Glyph_t * a_glyph )
{
	unsigned char g, i, j;
	for ( g = 0; g < c_glyph; ++g)
		for ( i = 0; i < xl_glyph; ++i)
			for ( j = 0; j < yl_glyph; ++j )
				a_glyph[g].tryd[i][j] = a_glyph[g].data[i][j];
}

void randomize_glyphs ( const int c_glyph, Glyph_t * a_glyph )
{
	unsigned int n;
	unsigned char g, i, j;
	for (n = 0; n < 10; ++n)
	{
		g = rand () % c_glyph;
		i = rand () % xl_glyph;
		j = rand () % yl_glyph;
		a_glyph[g].tryd[i][j] ^= 1;
	}
}
