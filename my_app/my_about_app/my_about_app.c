
#include "../lv_100ask.h"


static lv_style_t freetype_style;

void my_about_app (lv_obj_t *obj)
{

#if LV_USE_FREETYPE
    static lv_ft_info_t info;
    info.name = "D:/STKAITI.ttf";
    info.weight = 40;
    info.style = FT_FONT_STYLE_NORMAL;
    info.mem = NULL;

    static bool freetype_frist=0;
    if(!freetype_frist)
    {
        if(!lv_ft_font_init(&info))
        {
          LV_LOG_ERROR("create failed.");
        }
        freetype_frist=1;
        lv_style_init(&freetype_style);
        lv_style_set_text_font(&freetype_style, info.font);
        lv_style_set_text_align(&freetype_style, LV_TEXT_ALIGN_CENTER);
    }
#endif
    lv_obj_t *label_tile = lv_label_create(obj);
#if LV_USE_FREETYPE
    lv_obj_add_style(label_tile, &freetype_style, 0);//设置FreeType字体
#else
    lv_obj_set_style_text_font(label_tile, &lv_font_montserrat_28, 0);
#endif
    lv_label_set_text(label_tile,"ESP32-S3-N8R2\n4.3inch 800x480pixel\nTouch: GT911\nlvgl version:\"8.3.4\"");
    lv_obj_align(label_tile,LV_ALIGN_CENTER,0,0);

}
