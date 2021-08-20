// lcd header //


/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *           View this license at http://creativecommons.org/about/licenses/
 */



/*
#define CTRL_PORT	PORTA
#define CTRL_DDR	DDRA
#define CTRL_PIN	PINA
#define DATA_PORT	PORTC
#define DATA_DDR	DDRC
#define DATA_PIN	PINC
*/

#define CTRL_PORT	PORTB
#define CTRL_DDR	DDRB
#define CTRL_PIN	PINB
#define DATA_PORT	PORTD
#define DATA_DDR	DDRD
#define DATA_PIN	PIND


#define CS			0	/* Active low chip select enable */
#define BLC			1	/* Active High back light control */
#define RESET		2
#define WR			3
#define RS			4
#define RD			5
#define VSYNC		6
#define FMARK		7

#define CS_lo()		CTRL_PORT &= ~_BV(CS)
#define CS_hi()		CTRL_PORT |= _BV(CS)
#define BLC_lo()	CTRL_PORT &= ~_BV(BLC)
#define BLC_hi()	CTRL_PORT |= _BV(BLC)
#define RESET_lo()	CTRL_PORT &= ~_BV(RESET)
#define RESET_hi()	CTRL_PORT |= _BV(RESET)
#define WR_lo()		CTRL_PORT &= ~_BV(WR)
#define WR_hi()		CTRL_PORT |= _BV(WR)
#define RS_lo()		CTRL_PORT &= ~_BV(RS)
#define RS_hi()		CTRL_PORT |= _BV(RS)
#define RD_lo()		CTRL_PORT &= ~_BV(RD)
#define RD_hi()		CTRL_PORT |= _BV(RD)
#define VSYNC_lo()	CTRL_PORT &= ~_BV(VSYNC)
#define VSYNC_hi()	CTRL_PORT |= _BV(VSYNC)
#define WRITE(x)	DATA_PORT = (x)









/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *           View this license at http://creativecommons.org/about/licenses/
 */
  


/* Basic Commands */
#define NO_OPERATION								0x00
#define SOFTWARE_RESET								0x01
#define READ_DISPLAY_IDENTIFICATION_INFORMATION		0x04
#define READ_DISPLAY_STATUS							0x09
#define READ_DISPLAY_POWER_MODE						0x0A
#define READ_DISPLAY_MADCTL							0x0B
#define READ_DISPLAY_PIXEL_FORMAT					0x0C
#define READ_DISPLAY_IMAGE_FORMAT					0x0D
#define READ_DISPLAY_SIGNAL_MODE					0x0E
#define READ_DISPLAY_SELF_DIAGNOSTIC_RESULT			0x0F
#define ENTER_SLEEP_MODE							0x10
#define SLEEP_OUT									0x11	
#define PARTIAL_MODE_ON								0x12
#define NORMAL_DISPLAY_MODE_ON						0x13
#define DISPLAY_INVERSION_OFF						0x20
#define DISPLAY_INVERSION_ON						0x21
#define GAMMA_SET									0x26
#define DISPLAY_OFF									0x28
#define DISPLAY_ON									0x29
#define COLUMN_ADDRESS_SET							0x2A
#define PAGE_ADDRESS_SET							0x2B
#define MEMORY_WRITE								0x2C
#define COLOR_SET									0x2D
#define MEMORY_READ									0x2E
#define PARTIAL_AREA								0x30
#define VERTICAL_SCROLLING_DEFINITION				0x33
#define TEARING_EFFECT_LINE_OFF						0x34
#define TEARING_EFFECT_LINE_ON						0x35
#define MEMORY_ACCESS_CONTROL						0x36	
#define VERTICAL_SCROLLING_START_ADDRESS			0x37
#define IDLE_MODE_OFF								0x38
#define IDLE_MODE_ON								0x39
#define PIXEL_FORMAT_SET							0x3A
#define WRITE_MEMORY_CONTINUE						0x3C
#define READ_MEMORY_CONTINUE						0x3E
#define SET_TEAR_SCANLINE							0x44
#define GET_SCANLINE								0x45
#define WRITE_DISPLAY_BRIGHTNESS					0x51
#define READ_DISPLAY_BRIGHTNESS						0x52
#define WRITE_CTRL_DISPLAY							0x53
#define READ_CTRL_DISPLAY							0x54
#define WRITE_CONTENT_ADAPTIVE_BRIGHTNESS_CONTROL	0x55
#define READ_CONTENT_ADAPTIVE_BRIGHTNESS_CONTROL	0x56
#define WRITE_CABC_MINIMUM_BRIGHTNESS				0x5E
#define READ_CABC_MINIMUM_BRIGHTNESS				0x5F
#define READ_ID1									0xDA
#define READ_ID2									0xDB
#define READ_ID3									0xDC

/* Extended Commands */
#define RGB_INTERFACE_SIGNAL_CONTROL				0xB0
#define FRAME_CONTROL_IN_NORMAL_MODE				0xB1
#define FRAME_CONTROL_IN_IDLE_MODE					0xB2
#define FRAME_CONTROL_IN_PARTIAL_MODE				0xB3
#define DISPLAY_INVERSION_CONTROL					0xB4
#define BLANKING_PORCH_CONTROL						0xB5
#define DISPLAY_FUNCTION_CONTROL					0xB6
#define ENTRY_MODE_SET								0xB7
#define BACKLIGHT_CONTROL_1							0xB8
#define BACKLIGHT_CONTROL_2							0xB9
#define BACKLIGHT_CONTROL_3							0xBA
#define BACKLIGHT_CONTROL_4							0xBB
#define BACKLIGHT_CONTROL_5							0xBC
#define BACKLIGHT_CONTROL_7							0xBE
#define BACKLIGHT_CONTROL_8							0xBF
#define POWER_CONTROL_1								0xC0
#define POWER_CONTROL_2								0xC1
#define POWER_CONTROL3_(FOR_NORMAL_MODE)			0xC2
#define POWER_CONTROL4_(FOR_IDLE_MODE)				0xC3
#define POWER_CONTROL5_(FOR_PARTIAL_MODE)			0xC4
#define VCOM_CONTROL_1								0xC5
#define VCOM_CONTROL_2								0xC7
#define NV_MEMORY_WRITE								0xD0
#define NV_MEMORY_PROTECTION_KEY					0xD1
#define NV_MEMORY_STATUS_READ						0xD2
#define READ_ID4									0xD3
#define POSITIVE_GAMMA_CORRECTION					0xE0
#define NEGATIVE_GAMMA_CORRECTION					0xE1
#define DIGITAL_GAMMA_CONTROL						0xE2
#define DIGITAL_GAMMA_CONTROL2						0xE3
#define INTERFACE_CONTROL							0xF6

/* Undocumented commands */
#define INTERNAL_IC_SETTING							0xCB
#define GAMMA_DISABLE								0xF2

#define write_cmd(cmd) \
{ \
	RS_lo(); \
	WRITE(cmd); \
	WR_lo(); \
	WR_hi(); \
	RS_hi(); \
}

#define write_data(data) \
{ \
   	WRITE(data); \
	WR_lo(); \
	WR_hi(); \
}

#define write_data16(data) \
{ \
	write_data((data) >> 8); \
	write_data((data) & 0xFF); \
}

#define write_cmd_data(cmd, ndata, data) \
{ \
	uint8_t i; \
	char *d = data; \
	write_cmd(cmd); \
	for(i=0; i<ndata; i++) \
		write_data(*d++); \
}

void init_display_controller();








/*
 *  
 *  
 *
 *  Created by Steve Gunn on 23/09/2012.
 *  Copyright 2012 University of Southampton. All rights reserved.
 *
 */


const char font5x7[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, // SPACE
    0x00, 0x00, 0x5F, 0x00, 0x00, // !
    0x00, 0x03, 0x00, 0x03, 0x00, // "
    0x14, 0x3E, 0x14, 0x3E, 0x14, // #
    0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
    0x43, 0x33, 0x08, 0x66, 0x61, // %
    0x36, 0x49, 0x55, 0x22, 0x50, // &
    0x00, 0x05, 0x03, 0x00, 0x00, // '
    0x00, 0x1C, 0x22, 0x41, 0x00, // (
    0x00, 0x41, 0x22, 0x1C, 0x00, // )
    0x14, 0x08, 0x3E, 0x08, 0x14, // *
    0x08, 0x08, 0x3E, 0x08, 0x08, // +
    0x00, 0x50, 0x30, 0x00, 0x00, // ,
    0x08, 0x08, 0x08, 0x08, 0x08, // -
    0x00, 0x60, 0x60, 0x00, 0x00, // .
    0x20, 0x10, 0x08, 0x04, 0x02, // /
    0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
    0x00, 0x04, 0x02, 0x7F, 0x00, // 1
    0x42, 0x61, 0x51, 0x49, 0x46, // 2
    0x22, 0x41, 0x49, 0x49, 0x36, // 3
    0x18, 0x14, 0x12, 0x7F, 0x10, // 4
    0x27, 0x45, 0x45, 0x45, 0x39, // 5
    0x3E, 0x49, 0x49, 0x49, 0x32, // 6
    0x01, 0x01, 0x71, 0x09, 0x07, // 7
    0x36, 0x49, 0x49, 0x49, 0x36, // 8
    0x26, 0x49, 0x49, 0x49, 0x3E, // 9
    0x00, 0x36, 0x36, 0x00, 0x00, // :
    0x00, 0x56, 0x36, 0x00, 0x00, // ;
    0x08, 0x14, 0x22, 0x41, 0x00, // <
    0x14, 0x14, 0x14, 0x14, 0x14, // =
    0x00, 0x41, 0x22, 0x14, 0x08, // >
    0x02, 0x01, 0x51, 0x09, 0x06, // ?
    0x3E, 0x41, 0x59, 0x55, 0x5E, // @
    0x7E, 0x09, 0x09, 0x09, 0x7E, // A
    0x7F, 0x49, 0x49, 0x49, 0x36, // B
    0x3E, 0x41, 0x41, 0x41, 0x22, // C
    0x7F, 0x41, 0x41, 0x41, 0x3E, // D
    0x7F, 0x49, 0x49, 0x49, 0x41, // E
    0x7F, 0x09, 0x09, 0x09, 0x01, // F
    0x3E, 0x41, 0x41, 0x49, 0x3A, // G
    0x7F, 0x08, 0x08, 0x08, 0x7F, // H
    0x00, 0x41, 0x7F, 0x41, 0x00, // I
    0x30, 0x40, 0x40, 0x40, 0x3F, // J
    0x7F, 0x08, 0x14, 0x22, 0x41, // K
    0x7F, 0x40, 0x40, 0x40, 0x40, // L
    0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
    0x7F, 0x02, 0x04, 0x08, 0x7F, // N
    0x3E, 0x41, 0x41, 0x41, 0x3E, // O
    0x7F, 0x09, 0x09, 0x09, 0x06, // P
    0x1E, 0x21, 0x21, 0x21, 0x5E, // Q
    0x7F, 0x09, 0x09, 0x09, 0x76, // R
    0x26, 0x49, 0x49, 0x49, 0x32, // S
    0x01, 0x01, 0x7F, 0x01, 0x01, // T
    0x3F, 0x40, 0x40, 0x40, 0x3F, // U
    0x1F, 0x20, 0x40, 0x20, 0x1F, // V
    0x7F, 0x20, 0x10, 0x20, 0x7F, // W
    0x41, 0x22, 0x1C, 0x22, 0x41, // X
    0x07, 0x08, 0x70, 0x08, 0x07, // Y
    0x61, 0x51, 0x49, 0x45, 0x43, // Z
    0x00, 0x7F, 0x41, 0x00, 0x00, // [
    0x02, 0x04, 0x08, 0x10, 0x20, // slash
    0x00, 0x00, 0x41, 0x7F, 0x00, // ]
    0x04, 0x02, 0x01, 0x02, 0x04, // ^
    0x40, 0x40, 0x40, 0x40, 0x40, // _
    0x00, 0x01, 0x02, 0x04, 0x00, // `
    0x20, 0x54, 0x54, 0x54, 0x78, // a
    0x7F, 0x44, 0x44, 0x44, 0x38, // b
    0x38, 0x44, 0x44, 0x44, 0x44, // c
    0x38, 0x44, 0x44, 0x44, 0x7F, // d
    0x38, 0x54, 0x54, 0x54, 0x18, // e
    0x04, 0x04, 0x7E, 0x05, 0x05, // f
    0x08, 0x54, 0x54, 0x54, 0x3C, // g
    0x7F, 0x08, 0x04, 0x04, 0x78, // h
    0x00, 0x44, 0x7D, 0x40, 0x00, // i
    0x20, 0x40, 0x44, 0x3D, 0x00, // j
    0x7F, 0x10, 0x28, 0x44, 0x00, // k
    0x00, 0x41, 0x7F, 0x40, 0x00, // l
    0x7C, 0x04, 0x78, 0x04, 0x78, // m
    0x7C, 0x08, 0x04, 0x04, 0x78, // n
    0x38, 0x44, 0x44, 0x44, 0x38, // o
    0x7C, 0x14, 0x14, 0x14, 0x08, // p
    0x08, 0x14, 0x14, 0x14, 0x7C, // q
    0x00, 0x7C, 0x08, 0x04, 0x04, // r
    0x48, 0x54, 0x54, 0x54, 0x20, // s
    0x04, 0x04, 0x3F, 0x44, 0x44, // t
    0x3C, 0x40, 0x40, 0x20, 0x7C, // u
    0x1C, 0x20, 0x40, 0x20, 0x1C, // v
    0x3C, 0x40, 0x30, 0x40, 0x3C, // w
    0x44, 0x28, 0x10, 0x28, 0x44, // x
    0x0C, 0x50, 0x50, 0x50, 0x3C, // y
    0x44, 0x64, 0x54, 0x4C, 0x44, // z
    0x00, 0x08, 0x36, 0x41, 0x41, // {
    0x00, 0x00, 0x7F, 0x00, 0x00, // |
    0x41, 0x41, 0x36, 0x08, 0x00, // }
    0x02, 0x01, 0x02, 0x04, 0x02};// ~








/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *           View this license at http://creativecommons.org/about/licenses/
 */
 


#define LCDWIDTH	240
#define LCDHEIGHT	320

/* Colour definitions RGB565 */
#define WHITE       0xFFFF
#define BLACK       0x0000
#define BLUE        0x001F      
#define GREEN       0x07E0      
#define CYAN        0x07FF      
#define RED         0xF800      
#define MAGENTA     0xF81F      
#define YELLOW      0xFFE0      

typedef enum {North, West, South, East} orientation;

typedef struct {
	uint16_t width, height;
	orientation orient;
	uint16_t x, y;
	uint16_t foreground, background;
} lcd;

extern lcd display;

typedef struct {
	uint16_t left, right;
	uint16_t top, bottom;
} rectangle;	

void init_lcd();
void set_orientation(orientation o);
void clear_screen();
void fill_rectangle(rectangle r, uint16_t col);
void fill_rectangle_indexed(rectangle r, uint16_t* col);
void display_char(char c);
void display_string(char *str);










/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *           View this license at http://creativecommons.org/about/licenses/
 */
 



void init_display_controller()
{
	uint16_t x, y;
	RESET_lo();
	_delay_ms(100);
	RESET_hi();
	_delay_ms(100);
	RS_hi();
	WR_hi();
	RD_hi(); 
	CS_lo();
	BLC_lo();
	VSYNC_hi();
	write_cmd(DISPLAY_OFF);
	write_cmd(SLEEP_OUT);
	_delay_ms(60);
	write_cmd_data(INTERNAL_IC_SETTING,			 1, "\x01");
	write_cmd_data(POWER_CONTROL_1,				 2, "\x26\x08");
    write_cmd_data(POWER_CONTROL_2,				 1, "\x10");
    write_cmd_data(VCOM_CONTROL_1,				 2, "\x35\x3E");
    write_cmd_data(MEMORY_ACCESS_CONTROL,		 1, "\x48");
    write_cmd_data(RGB_INTERFACE_SIGNAL_CONTROL, 1, "\x4A");  // Set the DE/Hsync/Vsync/Dotclk polarity
    write_cmd_data(FRAME_CONTROL_IN_NORMAL_MODE, 2, "\x00\x1B"); // 70Hz
    write_cmd_data(DISPLAY_FUNCTION_CONTROL,	 4, "\x0A\x82\x27\x00");
    write_cmd_data(VCOM_CONTROL_2,			     1, "\xB5");
    write_cmd_data(INTERFACE_CONTROL,			 3, "\x01\x00\x00"); // System interface
    write_cmd_data(GAMMA_DISABLE,				 1, "\x00"); 
    write_cmd_data(GAMMA_SET,					 1, "\x01"); // Select Gamma curve 1
    write_cmd_data(PIXEL_FORMAT_SET,			 1, "\x55"); // 0x66 - 18bit /pixel,  0x55 - 16bit/pixel
    write_cmd_data(POSITIVE_GAMMA_CORRECTION,	15, "\x1F\x1A\x18\x0A\x0F\x06\x45\x87\x32\x0A\x07\x02\x07\x05\x00");
    write_cmd_data(NEGATIVE_GAMMA_CORRECTION,	15, "\x00\x25\x27\x05\x10\x09\x3A\x78\x4D\x05\x18\x0D\x38\x3A\x1F");
    write_cmd_data(COLUMN_ADDRESS_SET,			 4, "\x00\x00\x00\xEF");
    write_cmd_data(PAGE_ADDRESS_SET,			 4, "\x00\x00\x01\x3F");
    write_cmd(TEARING_EFFECT_LINE_OFF);
    write_cmd_data(DISPLAY_INVERSION_CONTROL,	 1, "\x00");
    write_cmd_data(ENTRY_MODE_SET,				 1, "\x07");
    /* Clear display */
	write_cmd(MEMORY_WRITE);
	for(x=0; x<240; x++)
		for(y=0; y<320; y++)
			write_data16(0x0000);
	write_cmd(DISPLAY_ON);
	_delay_ms(50);
	BLC_hi();
};









/*
 *  font5x7.c
 *  
 *
 *  Created by Steve Gunn on 23/09/2012.
 *  Copyright 2012 University of Southampton. All rights reserved.
 *
 */







/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *           View this license at http://creativecommons.org/about/licenses/
 */
 


lcd display = {LCDWIDTH, LCDHEIGHT, South, 0, 0, WHITE, BLACK};

void init_lcd()
{
	/* Disable JTAG in software, so that it does not interfere with Port C  */
	/* It will be re-enabled after a power cycle if the JTAGEN fuse is set. */
	MCUCR |= (1<<JTD);
	MCUCR |= (1<<JTD);
	
	/* Configure ports */
	CTRL_DDR = 0x7F;
	DATA_DDR = 0xFF;
	
	init_display_controller();
}

void set_orientation(orientation o)
{
	display.orient = o;
	write_cmd(MEMORY_ACCESS_CONTROL);
	if (o==North) { 
		display.width = LCDWIDTH;
		display.height = LCDHEIGHT;
		write_data(0x48);
	}
	else if (o==West) {
		display.width = LCDHEIGHT;
		display.height = LCDWIDTH;
		write_data(0xE8);
	}
	else if (o==South) {
		display.width = LCDWIDTH;
		display.height = LCDHEIGHT;
		write_data(0x88);
	}
	else if (o==East) {
		display.width = LCDHEIGHT;
		display.height = LCDWIDTH;
		write_data(0x28);
	}
	write_cmd(COLUMN_ADDRESS_SET);
	write_data16(0);
	write_data16(display.width-1);
	write_cmd(PAGE_ADDRESS_SET);
	write_data16(0);
	write_data16(display.height-1);
}

void fill_rectangle(rectangle r, uint16_t col)
{
	uint16_t x, y;
	write_cmd(COLUMN_ADDRESS_SET);
	write_data16(r.left);
	write_data16(r.right);
	write_cmd(PAGE_ADDRESS_SET);
	write_data16(r.top);
	write_data16(r.bottom);
	write_cmd(MEMORY_WRITE);
	for(x=r.left; x<=r.right; x++)
		for(y=r.top; y<=r.bottom; y++)
			write_data16(col);
}

void fill_rectangle_indexed(rectangle r, uint16_t* col)
{
	uint16_t x, y;
	write_cmd(COLUMN_ADDRESS_SET);
	write_data16(r.left);
	write_data16(r.right);
	write_cmd(PAGE_ADDRESS_SET);
	write_data16(r.top);
	write_data16(r.bottom);
	write_cmd(MEMORY_WRITE);
	for(x=r.left; x<=r.right; x++)
		for(y=r.top; y<=r.bottom; y++)
			write_data16(*col++);
}

void clear_screen()
{
	display.x = 0;
	display.y = 0;
	rectangle r = {0, display.width-1, 0, display.height-1};
	fill_rectangle(r, display.background);
}

void display_char(char c)
{
	uint16_t x, y;
	PGM_P fdata; 
	uint8_t bits, mask;
	uint16_t sc=display.x, ec=display.x + 4, sp=display.y, ep=display.y + 7;
	if (c < 32 || c > 126) return;
	fdata = (c - ' ') * 5 + font5x7;
	write_cmd(PAGE_ADDRESS_SET);
	write_data16(sp);
	write_data16(ep);
	for(x=sc; x<=ec; x++) {
		write_cmd(COLUMN_ADDRESS_SET);
		write_data16(x);
		write_data16(x);
		write_cmd(MEMORY_WRITE);
		bits = pgm_read_byte(fdata++);
		for(y=sp, mask=0x01; y<=ep; y++, mask<<=1)
			write_data16((bits & mask) ? display.foreground : display.background);
	}
	write_cmd(COLUMN_ADDRESS_SET);
	write_data16(x);
	write_data16(x);
	write_cmd(MEMORY_WRITE);
	for(y=sp; y<=ep; y++)
		write_data16(display.background);

	display.x += 6;
	if (display.x >= display.width) { display.x=0; display.y+=8; }
}

void display_string(char *str)
{
	uint8_t i;
	for(i=0; str[i]; i++) 
		display_char(str[i]);
} 

