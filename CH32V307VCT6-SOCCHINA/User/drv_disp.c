#include <drv_disp.h>
#include "lcd.h"
#include "lvgl.h"

static void disp_init(void);
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area,
		lv_color_t * color_p);

void lv_port_disp_init(void)
{
	disp_init();

	static lv_disp_draw_buf_t draw_buf_dsc_1;
	static lv_color_t buf_1[LCD_H * 10];
	lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, LCD_H * 10);

	static lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	disp_drv.hor_res = LCD_H;
	disp_drv.ver_res = LCD_W;
	disp_drv.flush_cb = disp_flush;
	disp_drv.draw_buf = &draw_buf_dsc_1;
	lv_disp_drv_register(&disp_drv);
}

static void disp_init(void)
{
	lcd_init();
	LCD_SetBrightness(10);
}

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area,
		lv_color_t * color_p)
{
	int32_t x;
	int32_t y;
	for (y = area->y1; y <= area->y2; y++)
	{
		for (x = area->x1; x <= area->x2; x++)
		{
			lcd_draw_point_color(x, y, color_p->full);
			color_p++;
		}
	}
	lv_disp_flush_ready(disp_drv);
}

