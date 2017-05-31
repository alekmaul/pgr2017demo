/*---------------------------------------------------------------------------------


	template for main c file
	-- alekmaul


---------------------------------------------------------------------------------*/
#include <snes.h>

#include "pgr2017intro.h"

// From my friend Stef and his SGDK for Megadrive :)
typedef s16 fix16;

const fix16 sintab16[1024] =
{
    0, 0, 1, 1, 2, 2, 2, 3,
    3, 4, 4, 4, 5, 5, 5, 6,
    6, 7, 7, 7, 8, 8, 9, 9,
    9, 10, 10, 11, 11, 11, 12, 12,
    12, 13, 13, 14, 14, 14, 15, 15,
    16, 16, 16, 17, 17, 17, 18, 18,
    19, 19, 19, 20, 20, 20, 21, 21,
    22, 22, 22, 23, 23, 23, 24, 24,
    24, 25, 25, 26, 26, 26, 27, 27,
    27, 28, 28, 28, 29, 29, 29, 30,
    30, 31, 31, 31, 32, 32, 32, 33,
    33, 33, 34, 34, 34, 35, 35, 35,
    36, 36, 36, 37, 37, 37, 37, 38,
    38, 38, 39, 39, 39, 40, 40, 40,
    41, 41, 41, 42, 42, 42, 42, 43,
    43, 43, 44, 44, 44, 44, 45, 45,
    45, 46, 46, 46, 46, 47, 47, 47,
    47, 48, 48, 48, 48, 49, 49, 49,
    49, 50, 50, 50, 50, 51, 51, 51,
    51, 52, 52, 52, 52, 53, 53, 53,
    53, 53, 54, 54, 54, 54, 54, 55,
    55, 55, 55, 55, 56, 56, 56, 56,
    56, 57, 57, 57, 57, 57, 58, 58,
    58, 58, 58, 58, 59, 59, 59, 59,
    59, 59, 59, 60, 60, 60, 60, 60,
    60, 60, 61, 61, 61, 61, 61, 61,
    61, 61, 61, 62, 62, 62, 62, 62,
    62, 62, 62, 62, 62, 63, 63, 63,
    63, 63, 63, 63, 63, 63, 63, 63,
    63, 63, 63, 63, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 63, 63, 63,
    63, 63, 63, 63, 63, 63, 63, 63,
    63, 63, 63, 63, 62, 62, 62, 62,
    62, 62, 62, 62, 62, 62, 61, 61,
    61, 61, 61, 61, 61, 61, 61, 60,
    60, 60, 60, 60, 60, 60, 59, 59,
    59, 59, 59, 59, 59, 58, 58, 58,
    58, 58, 58, 57, 57, 57, 57, 57,
    56, 56, 56, 56, 56, 55, 55, 55,
    55, 55, 54, 54, 54, 54, 54, 53,
    53, 53, 53, 53, 52, 52, 52, 52,
    51, 51, 51, 51, 50, 50, 50, 50,
    49, 49, 49, 49, 48, 48, 48, 48,
    47, 47, 47, 47, 46, 46, 46, 46,
    45, 45, 45, 44, 44, 44, 44, 43,
    43, 43, 42, 42, 42, 42, 41, 41,
    41, 40, 40, 40, 39, 39, 39, 38,
    38, 38, 37, 37, 37, 37, 36, 36,
    36, 35, 35, 35, 34, 34, 34, 33,
    33, 33, 32, 32, 32, 31, 31, 31,
    30, 30, 29, 29, 29, 28, 28, 28,
    27, 27, 27, 26, 26, 26, 25, 25,
    24, 24, 24, 23, 23, 23, 22, 22,
    22, 21, 21, 20, 20, 20, 19, 19,
    19, 18, 18, 17, 17, 17, 16, 16,
    16, 15, 15, 14, 14, 14, 13, 13,
    12, 12, 12, 11, 11, 11, 10, 10,
    9, 9, 9, 8, 8, 7, 7, 7,
    6, 6, 5, 5, 5, 4, 4, 4,
    3, 3, 2, 2, 2, 1, 1, 0,
    0, 0, -1, -1, -2, -2, -2, -3,
    -3, -4, -4, -4, -5, -5, -5, -6,
    -6, -7, -7, -7, -8, -8, -9, -9,
    -9, -10, -10, -11, -11, -11, -12, -12,
    -12, -13, -13, -14, -14, -14, -15, -15,
    -16, -16, -16, -17, -17, -17, -18, -18,
    -19, -19, -19, -20, -20, -20, -21, -21,
    -22, -22, -22, -23, -23, -23, -24, -24,
    -24, -25, -25, -26, -26, -26, -27, -27,
    -27, -28, -28, -28, -29, -29, -29, -30,
    -30, -31, -31, -31, -32, -32, -32, -33,
    -33, -33, -34, -34, -34, -35, -35, -35,
    -36, -36, -36, -37, -37, -37, -37, -38,
    -38, -38, -39, -39, -39, -40, -40, -40,
    -41, -41, -41, -42, -42, -42, -42, -43,
    -43, -43, -44, -44, -44, -44, -45, -45,
    -45, -46, -46, -46, -46, -47, -47, -47,
    -47, -48, -48, -48, -48, -49, -49, -49,
    -49, -50, -50, -50, -50, -51, -51, -51,
    -51, -52, -52, -52, -52, -53, -53, -53,
    -53, -53, -54, -54, -54, -54, -54, -55,
    -55, -55, -55, -55, -56, -56, -56, -56,
    -56, -57, -57, -57, -57, -57, -58, -58,
    -58, -58, -58, -58, -59, -59, -59, -59,
    -59, -59, -59, -60, -60, -60, -60, -60,
    -60, -60, -61, -61, -61, -61, -61, -61,
    -61, -61, -61, -62, -62, -62, -62, -62,
    -62, -62, -62, -62, -62, -63, -63, -63,
    -63, -63, -63, -63, -63, -63, -63, -63,
    -63, -63, -63, -63, -64, -64, -64, -64,
    -64, -64, -64, -64, -64, -64, -64, -64,
    -64, -64, -64, -64, -64, -64, -64, -64,
    -64, -64, -64, -64, -64, -64, -64, -64,
    -64, -64, -64, -64, -64, -64, -64, -64,
    -64, -64, -64, -64, -64, -63, -63, -63,
    -63, -63, -63, -63, -63, -63, -63, -63,
    -63, -63, -63, -63, -62, -62, -62, -62,
    -62, -62, -62, -62, -62, -62, -61, -61,
    -61, -61, -61, -61, -61, -61, -61, -60,
    -60, -60, -60, -60, -60, -60, -59, -59,
    -59, -59, -59, -59, -59, -58, -58, -58,
    -58, -58, -58, -57, -57, -57, -57, -57,
    -56, -56, -56, -56, -56, -55, -55, -55,
    -55, -55, -54, -54, -54, -54, -54, -53,
    -53, -53, -53, -53, -52, -52, -52, -52,
    -51, -51, -51, -51, -50, -50, -50, -50,
    -49, -49, -49, -49, -48, -48, -48, -48,
    -47, -47, -47, -47, -46, -46, -46, -46,
    -45, -45, -45, -44, -44, -44, -44, -43,
    -43, -43, -42, -42, -42, -42, -41, -41,
    -41, -40, -40, -40, -39, -39, -39, -38,
    -38, -38, -37, -37, -37, -37, -36, -36,
    -36, -35, -35, -35, -34, -34, -34, -33,
    -33, -33, -32, -32, -32, -31, -31, -31,
    -30, -30, -29, -29, -29, -28, -28, -28,
    -27, -27, -27, -26, -26, -26, -25, -25,
    -24, -24, -24, -23, -23, -23, -22, -22,
    -22, -21, -21, -20, -20, -20, -19, -19,
    -19, -18, -18, -17, -17, -17, -16, -16,
    -16, -15, -15, -14, -14, -14, -13, -13,
    -12, -12, -12, -11, -11, -11, -10, -10,
    -9, -9, -9, -8, -8, -7, -7, -7,
    -6, -6, -5, -5, -5, -4, -4, -4,
    -3, -3, -2, -2, -2, -1, -1, 0
};

#define sinFix16(value)             sintab16[(value) & 1023]
#define cosFix16(value) sintab16[((value) + 256) & 1023]

const char *demo_strings[] = 
{
	/*
	"<------- MAX HEADROOM --------->\0"
	*/
	"CHERS AMIS PASTGAMERS\0",
	"LES RETROGAMERS VOUS PARLENT\0",
	"10EME EDITION DE LA PGR !!!\0",

	"NOUS SOMMES CONTENT DE VENIR A\0",
	"CET EVENEMENT TRES IMPORTANT\0",
	"EN FRANCE!\0",
	"MERCI ENCORE A L'ORGANISATION\0",
	"HTTP://PASTGAME.FR/\0",

	"CET EVENEMENT A LIEU A PINON\0",
	"PAS TRES LOIN DE SOISSONS\0",
	"ELLE COMMENCE LE 03/06/2017\0",	
	"JUSQU'AU 04/06/2017\0",	

	"PAS MAL DE MICROS ET CONSOLES\0",
	"DES JEUX, DES COMPETITIONS\0",
	"ET BIEN ENTENDU,\0",
	"CETTE DEMO OLDSCHOOL, YEAAAH !!\0",

	"LA PGR A ETE LANCEE EN PICARDIE\0",
	"EN 2008 PAR CINQ PASSIONNES\0",
	"DONT DARKCHRIS & GENIUS60\0",

	"CETTE FETE EST BIEN ENTENDU\0",
	"ACCOMPAGNEE DU BARBEUK DE TITI !\0",

	"EN INVITES VIP CETTE ANNEE\0",
	"OLIVIER WAHWAH RA, YOUTUBER\0",
	"ALEXANDRE SEREL DE PIX'N LOVE\0",

	"REMERCIEMENTS POUR CETTE INTRO:\0",
	"LOGOS DU SITE PASTGAME\0",
	"MUSIQUE DE RETRO (MATILDA)\0",
	"CODE D'ALEKMAUL EN 6 HEURES :)\0",

	"BASE SUR LA DEMO VIP2017\0",
	"DE RESISTANCEVAULT\0",
	"GITHUB.COM/RESISTANCEVAULT\0",

	"--- REMERCIEMENTS POUR ---\0",
	"LES MEMBRES DU STAFF : ANGEL,\0",
	"TITI (CUISTO), SYNOPSYS-51\0",
	"MARCOLUDO, MAGICFIRMUSIC,\0",
	"KRAAGAN & DARKCHRIS\0",
	"MAIS AUSSI\0",
	"ALEX: JEAN-CLAUDE CROFT\0",
	"MARIO-ZELDA: COSPLAY TOMB RAIDER\0",
	"ET ENFIN\0",
	"L'ASSO SPORTS ET LOISIRS PINON\0",
	"SANS OUBLIER ...\0",
	"LA MAIRIE DE PINON :) !\0",
	
	"LE TEXTE VA RECOMMENCER ...\0",
	" \0",
	/*	Do not remove the next line */
	"\0"
};

const u8 sprIdx[16] =
{
	0x00, 0x04, 0x08, 0x0C, 0x40, 0x44, 0x48, 0x4C, 0x80, 0x84, 0x88, 0x8C, 0xC0, 0xC4, 0xC8, 0xCC,
};

extern u8 fontg,fontg_end,fontp;														// graphic for font
extern u8 starsg,starsg_end,starsp,starsm;									// graphic for starfield
extern u8 logog,logog_end,logop,logom;											// graphic for logo
extern u8 spriteg, spriteg_end, spritep;										// graphic for sprites

extern u8 firstonesg,firstonesg_end,firstonesp,firstonesm;	// 1st PGR in 2008
extern u8 lastonesg,lastonesg_end,lastonesp,lastonesm;			// last PGR in 2016

extern u8 __SOUNDBANK__0, __SOUNDBANK__1;										// music

//---------------------------------------------------------------------------------
u16 i, ns, s;
char c;
u16 fade, faded_idx;

u16 figure_counter;
u8 figure_mode;
u8 demo_phase;
u8 vblrefresh;
u16 phase_counter;

u8 scroll_bg2[(3*TABLE_LEN)+1];
u8 scroll_speed[TABLE_LEN];
u8 *ptscr,*ptspd;
dmaMemory  data_to_transfert;

u16 txtLine[32];

u16 writer_state;
u16 writer_switch;
u16 current_string_idx;
u16 current_string_len;
u16 current_char_idx;
u16 current_char_x;
u16 writer_timer;

//---------------------------------------------------------------------------------
u16 charToTileIndex(char c) {
	if (c >= 'A' && c <= 'Z')
		return (u16) (c - 'A' + FONT_OFFSET); 

	if (c >= '0' && c <= '9')
		return (u16)(c - '0') + 26 + FONT_OFFSET;

	switch(c)	{
		case '!':
			return FONT_PUNCT_OFFSET;
		case '\"':
			return FONT_PUNCT_OFFSET + 1;
		case '#':
			return FONT_PUNCT_OFFSET + 2;
		case '$':
			return FONT_PUNCT_OFFSET + 3;
		case '%':
			return FONT_PUNCT_OFFSET + 4;
		case '&':
			return FONT_PUNCT_OFFSET + 5;
		case '\'':
			return FONT_PUNCT_OFFSET + 6;
		case '(':
			return FONT_PUNCT_OFFSET + 7;
		case ')':
			return FONT_PUNCT_OFFSET + 8;
		case '*':
			return FONT_PUNCT_OFFSET + 9;
		case '+':
			return FONT_PUNCT_OFFSET + 10;
		case ',':
			return FONT_PUNCT_OFFSET + 11;
		case '-':
			return FONT_PUNCT_OFFSET + 12;
		case '.':
			return FONT_PUNCT_OFFSET + 13;
		case '/':
			return FONT_PUNCT_OFFSET + 14;
		case ':':
			return FONT_PUNCT_OFFSET + 15;
		case ';':
			return FONT_PUNCT_OFFSET + 16;
		case '<':
			return FONT_PUNCT_OFFSET + 17;
		case '=':
			return FONT_PUNCT_OFFSET + 18;
		case '>':
			return FONT_PUNCT_OFFSET + 19;
		case '?':
			return FONT_PUNCT_OFFSET + 20;
		case '[':
			return FONT_PUNCT_OFFSET + 21;
		case '\\':
			return FONT_PUNCT_OFFSET + 22;
		case ']':
			return FONT_PUNCT_OFFSET + 23;
		case '^':
			return FONT_PUNCT_OFFSET + 24;									
		case '_':
			return FONT_PUNCT_OFFSET + 25;									
	};

	/* if no character was found,
		we return a special code */
	return 0xFF;
}

//---------------------------------------------------------------------------------
u8 drawString(const char *str) {
	for (fade = 0; fade < 3; fade++) {
		faded_idx = current_char_idx + fade;
		c = str[faded_idx];

		if (fade == 0 && c == 0)
			return 0;

		if (c != ' ') {
			i = charToTileIndex(c);
			if ( (faded_idx < current_string_len) && (i != 0xFF) ) {
				txtLine[current_char_x + fade]=i+ (FONT_LINE_OFFSET * fade) + (1<<13); // priority high
			}
			vblrefresh=1;
		}
	}

	current_char_x++;
	current_char_idx++;

	return 1;
}

//---------------------------------------------------------------------------------
void updateLineWriter(void) {
	switch(writer_state) {
		case WRT_CENTER_CUR_LINE:
			current_string_len = strlen(demo_strings[current_string_idx]);
			current_char_x = ((256 / 8) - current_string_len) >> 1;
			writer_state = WRT_WRITE_CUR_LINE;
			break;

		case WRT_WRITE_CUR_LINE:
			if (drawString(demo_strings[current_string_idx])==0)  {
				writer_timer = 0;
				writer_state = WRT_WAIT;
			}
			break;

		case WRT_WAIT:
			if (writer_timer++ > 50) {
				writer_state = WRT_CLEAR_LINE;
				current_char_x = 0;
			}
			break;

		case WRT_CLEAR_LINE:
			txtLine[current_char_x]=0x0000;
			vblrefresh=1;
			current_char_x++;
			if (current_char_x > (256 >> 3) ) {
				current_char_x = 0;
				current_char_idx = 0;
				current_string_idx++;
				if (demo_strings[current_string_idx][0] == '\0')
					current_string_idx = 0;

				writer_state = WRT_CENTER_CUR_LINE;
			}
			break;
	}		
}

//---------------------------------------------------------------------------------
void hdmaScroll(void) {
	REG_HDMAEN = 0; // Disable HDMA

	REG_DMAP6 = 0x02; // Meaning write twice 010
	REG_BBAD6 = 0x0F; // BG2 horizontal scrolling
	data_to_transfert.mem.p = (u8 *) scroll_bg2;
	REG_A1T6LH = data_to_transfert.mem.c.addr; // DMA channel x source address offset low $4712 and high $4717 optimisation)
	REG_A1B6 = data_to_transfert.mem.c.bank; // DMA channel x source address bank

	REG_HDMAEN = 0x40; // Enable DMA channel 6
}

//---------------------------------------------------------------------------------
void myconsoleVblank(void) {
	// Refresh pad values
	scanPads();

	// Put screen regarding how to put it
	if (vblrefresh ==1) {
		dmaCopyVram((u8 *) (txtLine), MAP0ADR+32*24,32*2);
		vblrefresh=0;
	}
 
	// Put oam to screen if needed
	oamUpdate();
}

//---------------------------------------------------------------------------------
// Main init of sound
void soundInit(void) {
	// Set give soundbank
	//spcSetBank(&__SOUNDBANK__1);
	spcSetBank(&__SOUNDBANK__0);
	
	// allocate around 10K of sound ram (39 256-byte blocks)
	spcAllocateSoundRegion(0);
	spcStop(); 
}

//---------------------------------------------------------------------------------
// Main init of snes graphics
void gfxInit(void) {
	// init sprites 
	oamInit();
	vblrefresh=0;
	
	__nmi_handler=myconsoleVblank; 

	spcProcess();
	setBrightness(0); // Force VBlank
}

//---------------------------------------------------------------------------------
int main(void) {
	// Initialize SNES 
	consoleInit();

	// Initialize sound engine (take some time)
	spcBoot();
	
	// Init sound & graphic mode for SNES
	soundInit();
	gfxInit();
	
	// Load the tiles & font
	bgInitTileSet(0, (u8 *) &logog, (u8 *) &logop, 2, ((u8 *) &logog_end - (u8 *) &logog), 16*2*2, BG_16COLORS, GFXMAP0ADR);
	bgInitTileSet(1, (u8 *) &starsg, (u8 *) &starsp, 1, ((u8 *) &starsg_end - (u8 *) &starsg), 16*2*1, BG_16COLORS, GFXMAP1ADR);
	setBrightness(0x0); 
	dmaCopyVram(&fontg, GFXMAP0ADR+FONTADR/2, (&fontg_end-&fontg));
	dmaCopyCGram(&fontp, 0 * 16, 16*2);

	// Copy Map to VRAM
	bgInitMapSet(0, &logom, 32*32*2,SC_32x32, MAP0ADR);
	bgInitMapSet(1, &starsm, 64*32*2,SC_64x32, MAP1ADR);

	// Init sprites
	oamInitGfxSet(&spriteg, (&spriteg_end-&spriteg), &spritep, 16*2*2, 0, GFXADRSPR, OBJ_SIZE32);
	for(i = 0; i < MAX_SPRITES; i++) {
		oamSetAttr(i<<2,  0, 0, 0, 2<<4); 
		oamSetVisible(i<<2, OBJ_SHOW);
	}
	
	// Now Put in 16 color mode and disable other BGs except 1st one
	setMode(BG_MODE1,0);  bgSetEnable(1); bgSetDisable(2);
	
	//	Create the scrolling offset table 
	s = 1;
	for(i = 0; i < TABLE_LEN; i++) {
		scroll_bg2[i*3] = 3;
		do
		{
			ns = ((rand() % 3) + 1);
		} while (ns == s);
		scroll_speed[i] = ns;
		s = ns;
	}
	scroll_bg2[TABLE_LEN]=0x00;// init end of hdma table
	
	for (i=0;i<32;i++)
		txtLine[i]=0x0000;
	
	// Init vars
	figure_counter = 0;
	figure_mode=8; // 0;
	demo_phase = 0;
	phase_counter = 0;
	writer_switch = 0;
	writer_state = WRT_CENTER_CUR_LINE;		

	// play music now
	spcLoad(0); spcPlay(0);
	
	// Infinite loop to keep the program running
	s = 0;
	while(1) {
		switch(demo_phase) {
			case 0:
				setFadeEffect(FADE_IN);
				phase_counter = 0;
				demo_phase++;
				break;

			case 1:
				phase_counter++;
				if (phase_counter > 32 + 16) {
					phase_counter = 0;
					demo_phase++;
					//VDP_fadePalTo(PAL2, donut.palette->data, 32, TRUE);
				}
				break;
			case 2:
				phase_counter++;
				if (phase_counter > 32 + 16) {
					phase_counter = 0;
					demo_phase++;
					//VDP_fadePalTo(PAL0, vip_logo.palette->data, 32, TRUE);					
				}
				break;
		}

		// do starfiled and sprites only for some cases
		if (figure_mode<9) {
			// update text if possible
			if (demo_phase > 2) {
				if ( (writer_switch!=0) || (writer_state == WRT_CLEAR_LINE) )
					updateLineWriter();
				writer_switch = 1-writer_switch;					
			}

			// 	Scroll the starfield 
			hdmaScroll();
			ptscr=(u8 *) &(scroll_bg2+1);
			ptspd=(u8 *) &scroll_speed;
			for(i = 0; i < TABLE_LEN; i++) {
				//scroll_bg2[i*3+1] = (scroll_bg2[i*3+1] + scroll_speed[i]) & 0xFF;
				*ptscr=(*ptscr+*ptspd) & 0xFF;
				ptspd++;
				ptscr=ptscr+3;
			}

			//	Animate the sprites
			for(i = 0; i < MAX_SPRITES; i++) {
				switch(figure_mode) {
					case 0:
						oamSetAttr(i<<2, (cosFix16(s + (i << 5)) << 1) + 128 - 16, sinFix16(s + (i << 5)) + 112 - 16, sprIdx[(( i) & 7)], 2<<4);
						//oamSetXY(i<<2, (cosFix16(s + (i << 5)) << 1) + 128 - 16, sinFix16(s + (i << 5)) + 112 - 16);
						break;
					case 1:
						oamSetAttr(i<<2, (cosFix16(s + (i << 6)) << 1) + 128 - 16, (sinFix16(s + (i << 5))) + 112 - 16, sprIdx[((( i) & 7))+8], (1<<1) | (2<<4));
						//oamSetXY(i<<2, (cosFix16(s + (i << 6)) << 1) + 128 - 16, (sinFix16(s + (i << 5))) + 112 - 16);
						break;
					case 2:
						oamSetAttr(i<<2, ((sinFix16((s << 1) + (i << 6))) << 1) + 128 - 16, (cosFix16(s + (i << 5)) << 1) + 112 - 16, sprIdx[(( i) & 7)], 2<<4);
						//oamSetXY(i<<2, ((sinFix16((s << 1) + (i << 6))) << 1) + 128 - 16, (cosFix16(s + (i << 5)) << 1) + 112 - 16);
						break;
					case 3:
						oamSetAttr(i<<2, (sinFix16(s + (i << 7))) + 128 - 16, (cosFix16((s >> 1) + (i << 4)) << 1) + 112 - 16, sprIdx[((( i) & 7))+8], (1<<1) | (2<<4));
						//oamSetXY(i<<2, (sinFix16(s + (i << 7))) + 128 - 16, (cosFix16((s >> 1) + (i << 4)) << 1) + 112 - 16);
						break;
					case 4:
						oamSetAttr(i<<2, (cosFix16((s << 1) + (i << 5)) << 1) + 128 - 16, (sinFix16((s >> 1) + (i << 5)) << 1) + 112 - 16, sprIdx[(( i) & 7)], 2<<4);
						//oamSetXY(i<<2, (cosFix16((s << 1) + (i << 5)) << 1) + 128 - 16, (sinFix16((s >> 1) + (i << 5)) << 1) + 112 - 16);
						break;
					case 5:
						oamSetAttr(i<<2, (cosFix16((s << 1) + (i << 5)) << 1) + 128 - 16, (sinFix16((s >> 1) + (i << 5)) << 1) + 112 - 16, sprIdx[((( i) & 7))+8], (1<<1) | (2<<4));
						//oamSetXY(i<<2, (cosFix16((s << 1) + (i << 5)) << 1) + 128 - 16, (sinFix16((s >> 1) + (i << 5)) << 1) + 112 - 16);
						break;
					case 6:
						oamSetAttr(i<<2, (cosFix16((s << 1) + (i << 5)) << 1) + 128 - 16, (sinFix16((s >> 1) + (i << 5)) << 1) + 112 - 16, sprIdx[(( i) & 7)], 2<<4);
						//oamSetXY(i<<2, (cosFix16((s << 1) + (i << 5)) << 1) + 128 - 16, (sinFix16((s >> 1) + (i << 5)) << 1) + 112 - 16);
						break;
					case 7:
						oamSetAttr(i<<2, ((sinFix16((s << 1) + (i << 6))) << 1) + 128 - 16, (cosFix16(s + (i << 5)) << 1) + 112 - 16, sprIdx[((( i) & 7))+8], (1<<1) | (2<<4));
						//oamSetXY(i<<2, ((sinFix16((s << 1) + (i << 6))) << 1) + 128 - 16, (cosFix16(s + (i << 5)) << 1) + 112 - 16);
						break;
					case 8:
						oamSetAttr(i<<2, (cosFix16(s + (i << 6)) << 1) + 128 - 16, (sinFix16(s + (i << 5))) + 112 - 16, sprIdx[(( i) & 7)], 2<<4);
						//oamSetXY(i<<2, (cosFix16(s + (i << 6)) << 1) + 128 - 16, (sinFix16(s + (i << 5))) + 112 - 16);
						break;
				}
			}
		}
		if (figure_mode==9) {
			setFadeEffect(FADE_OUT);
			spcProcess();	setBrightness(0); // Force VBlank
			for(i = 0; i < MAX_SPRITES; i++) {
				oamSetXY(i<<2,  256, 240); 
			}
			dmaCopyVram(&firstonesg, GFXMAP0ADR, (&firstonesg_end-&firstonesg));
			dmaCopyCGram(&firstonesp, 2 * 16, 16*2);
			dmaCopyVram(&firstonesm, MAP0ADR, 32*32*2);
			figure_counter=640; // to go quickly to next step
		}
		else if (figure_mode==10) {
			// display 1st event with a mosaic effect
			setFadeEffect(FADE_IN);
			figure_counter=640; // to go quickly to next step
		}
		else if (figure_mode==12) {
			// display last event with a mosaic effect
			setFadeEffect(FADE_OUT);
			spcProcess();	setBrightness(0); // Force VBlank
			dmaCopyVram(&lastonesg, GFXMAP0ADR, (&lastonesg_end-&lastonesg));
			dmaCopyCGram(&lastonesp, 2 * 16, 16*2);
			dmaCopyVram(&lastonesm, MAP0ADR, 32*32*2);
			figure_counter=640; // to go quickly to next step
		}
		else if (figure_mode==13) {
			// display last event with a mosaic effect
			setFadeEffect(FADE_IN);
			figure_counter=640; // to go quickly to next step
		}
		else if (figure_mode==15) {
			// display last event with a mosaic effect
			setFadeEffect(FADE_OUT);
			spcProcess();	setBrightness(0); // Force VBlank
			dmaCopyVram(&logog, GFXMAP0ADR, (&logog_end-&logog));
			dmaCopyCGram(&logop, 2 * 16, 16*2*2);
			dmaCopyVram(&logom, MAP0ADR, 32*32*2);
			dmaCopyVram(&fontg, GFXMAP0ADR+FONTADR/2, (&fontg_end-&fontg));
			figure_counter=640; // to go quickly to next step
		}
		
		// update counters for sprites
		s += 4;
		figure_counter++;
		if (figure_counter > 640) {
			figure_mode++;
			if (figure_mode > 15) figure_mode = 0;
			figure_counter = 0;
		}	
		
		// Wait refresh
		spcProcess();WaitForVBlank();
	}
	return 0;
}
