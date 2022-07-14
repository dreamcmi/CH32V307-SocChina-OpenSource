/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef ZHFONT
#define ZHFONT 1
#endif

#if ZHFONT

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+5173 "关" */
    0x33, 0xc, 0xc7, 0xf8, 0x30, 0xc, 0x3f, 0xf0,
    0xc0, 0x78, 0x73, 0xb8, 0x78, 0x0,

    /* U+5EA6 "度" */
    0x4, 0x1, 0x7, 0xfd, 0x24, 0x7f, 0xd3, 0xc4,
    0xf1, 0xfe, 0x59, 0xb1, 0x8b, 0xfc, 0x0,

    /* U+5F00 "开" */
    0x7f, 0xc2, 0x30, 0x46, 0x8, 0xcf, 0xfe, 0x23,
    0xc, 0x61, 0x8c, 0x61, 0x88, 0x30,

    /* U+6E29 "温" */
    0xdf, 0x9c, 0x29, 0xfb, 0x7e, 0x5f, 0x97, 0xe5,
    0x79, 0x5e, 0xd7, 0xbf, 0xf0,

    /* U+6E7F "湿" */
    0x6f, 0xc5, 0x8, 0x3f, 0x24, 0x26, 0xfc, 0xf,
    0xf, 0xfb, 0x7e, 0x6f, 0xcb, 0xfc,

    /* U+7A97 "窗" */
    0xc, 0x3f, 0xef, 0x3b, 0xb7, 0x7f, 0x92, 0x25,
    0xf9, 0xea, 0x4e, 0x94, 0x27, 0xf8,

    /* U+95E8 "门" */
    0x40, 0x1f, 0xf2, 0xf, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xf0, 0x3c, 0x1c
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 189, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 14, .adv_w = 189, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 29, .adv_w = 189, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 43, .adv_w = 189, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 56, .adv_w = 189, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 70, .adv_w = 189, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 84, .adv_w = 189, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xd33, 0xd8d, 0x1cb6, 0x1d0c, 0x2924, 0x4475
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 20851, .range_length = 17526, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 7, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t zhFont = {
#else
lv_font_t zhFont = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 12,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if ZHFONT*/

