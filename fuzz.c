void do_fuzz_on_one_glyph_goto (Glyph_t * p_glyph)
{
	unsigned char i, j, a, b, mi, mj;
	for (i = 0; i < xl_glyph; ++i)
	{
		mi = i + xyl_fuzz;
		mi = mi > xl_glyph ? xl_glyph : mi;
		for (j = 0; j < yl_glyph; ++j)
		{
			mj = j + xyl_fuzz;
			mj = mj > yl_glyph ? yl_glyph : mj;
			for (a = i; a < mi; ++a)
			{
				for (b = j; b < mj; ++b)
				{
					if ( p_glyph->tryd [a] [b] == 1)
					{
						p_glyph->fuzz [i] [j] = 1;
						goto next_pixel;
					}
				}
			}
			p_glyph->fuzz [i] [j] = 0;
		next_pixel:;
		}
	}
}

void do_fuzz_on_one_glyph (Glyph_t * p_glyph)
{
	unsigned char i, j, a, b, mi, mj;
	// unimplemented: clear fuzz on glyph
	for (i = 0; i < xl_glyph; ++i)
	{
		mi = i + xyl_fuzz;
		mi = mi > xl_glyph ? xl_glyph : mi;
		for (j = 0; j < yl_glyph; ++j)
		{
			mj = j + xyl_fuzz;
			mj = mj > yl_glyph ? yl_glyph : mj;
			if ( p_glyph->tryd [i] [j] == 1)
			{
				for (a = i; a < mi; ++a)
				{
					for (b = j; b < mj; ++b)
					{
						p_glyph->fuzz [i] [j] = 1;
					}
				}
			}
		}
	}
}

void do_fuzz_on_all_glyphs
(
	const int c_glyph,
	Glyph_t * a_glyph
)
{
	unsigned int g;
	for (g = 0; g < c_glyph; ++g)
	{
		do_fuzz_on_one_glyph_goto ( &a_glyph[g] );
	}
}
