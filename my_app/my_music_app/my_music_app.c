
#include <stdio.h>
#include "../lv_100ask.h"



//上一曲事件回调
static void music_event_btnleft(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED)
    {
       LV_LOG_USER("Previous song\r\n");
    }
}
//下一曲事件回调
static void music_event_btnright(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED)
    {
       LV_LOG_USER("Next song\r\n");
    }
}

//开始按钮事件回调
static void music_event_btnstart(lv_event_t *e)
{
    static bool Pause=0;
    if(e->code==LV_EVENT_CLICKED)
    {
           if(Pause)
           {
              Pause = 0;
              lv_label_set_text((lv_obj_t*)e->user_data, LV_SYMBOL_PAUSE);
              LV_LOG_USER("Playing\r\n");
              //音乐启动
           }
           else
           {
              Pause = 1;
              lv_label_set_text((lv_obj_t*)e->user_data, LV_SYMBOL_PLAY);
              LV_LOG_USER("Paused\r\n");
              //音乐暂停
           }

    }
}
//进度条事件回调
static void music_slider_event_cb(lv_event_t * e)
{
          lv_event_code_t code = lv_event_get_code(e);
          lv_obj_t * obj = lv_event_get_target(e);

          if(code == LV_EVENT_REFR_EXT_DRAW_SIZE)
          {
              lv_coord_t * s = lv_event_get_param(e);
              *s = LV_MAX(*s, 60);
          }
          else if(code == LV_EVENT_DRAW_PART_END) //整理绘制零件
          {
              lv_obj_draw_part_dsc_t * dsc = lv_event_get_param(e);
              if(dsc->part == LV_PART_KNOB && lv_obj_has_state(obj, LV_STATE_PRESSED))
              {
                  char buf[8];
                  lv_snprintf(buf, sizeof(buf), "%02d"":""%02d", (uint16_t)lv_slider_get_value(obj)/60,(uint16_t)lv_slider_get_value(obj)%60);
                  LV_LOG_USER("%s\r\n",buf);//获取数据
                  lv_point_t text_size;     //先获取文本的大小
                  lv_txt_get_size(&text_size, buf, &lv_font_montserrat_18, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);

                  lv_area_t txt_area;
                  txt_area.x1 = dsc->draw_area->x1 + lv_area_get_width(dsc->draw_area) / 2 - text_size.x / 2;
                  txt_area.x2 = txt_area.x1 + text_size.x;
                  txt_area.y2 = dsc->draw_area->y1 - 25;//显示区域距离手柄的高度
                  txt_area.y1 = txt_area.y2 - text_size.y;

                  lv_area_t bg_area;
                  bg_area.x1 = txt_area.x1 - LV_DPX(8);
                  bg_area.x2 = txt_area.x2 + LV_DPX(8);
                  bg_area.y1 = txt_area.y1 - LV_DPX(8);
                  bg_area.y2 = txt_area.y2 + LV_DPX(8);

                  lv_draw_rect_dsc_t rect_dsc;
                  lv_draw_rect_dsc_init(&rect_dsc);
                  rect_dsc.bg_color = lv_palette_darken(LV_PALETTE_GREY, 3);
                  rect_dsc.radius = LV_DPX(5);
                  lv_draw_rect(dsc->draw_ctx, &rect_dsc, &bg_area);//画一个矩形

                  lv_draw_label_dsc_t label_dsc;
                  lv_draw_label_dsc_init(&label_dsc);
                  label_dsc.color = lv_color_white();
                  label_dsc.font = &lv_font_montserrat_18;
                  lv_draw_label(dsc->draw_ctx, &label_dsc, &txt_area, buf, NULL);
              }
          }

}
//音量事件回调
static void music_vol_event_cb(lv_event_t * e)
{
        if(e->code == LV_EVENT_VALUE_CHANGED) //音量被改变
        {
          LV_LOG_USER("Vol = %d\r\n",lv_slider_get_value(e->target));
        }
}
///////////////////// SCREENS ////////////////////
void my_music_app(lv_obj_t *obj)
{

    // 设置一个背景图片
    lv_obj_t *ui_musicImg = lv_img_create(obj);
    LV_IMG_DECLARE(music_bg);
    lv_img_set_src(ui_musicImg, &music_bg);
    lv_obj_align(ui_musicImg, LV_ALIGN_CENTER,0,-25);


    // 创建开始按钮
    lv_obj_t *ui_btnstart = lv_btn_create(obj);
    lv_obj_set_size(ui_btnstart, 60,60);
	lv_obj_align(ui_btnstart,LV_ALIGN_BOTTOM_MID,0,-10);

    lv_obj_set_style_radius(ui_btnstart, 180, LV_PART_MAIN | LV_STATE_DEFAULT);//设置圆角为180
    lv_obj_set_style_radius(ui_btnstart, 180, LV_PART_MAIN | LV_STATE_PRESSED);//设置圆角为180
    lv_obj_set_style_bg_color(ui_btnstart, lv_color_hex(0x58CB35), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_btnstart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_btnstart, 100, LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui_btnstart,0,LV_PART_MAIN | LV_STATE_DEFAULT);
    // 创建开始按钮标签
    lv_obj_t *ui_Labbtnstart = lv_label_create(ui_btnstart);
    lv_obj_set_size(ui_Labbtnstart, LV_SIZE_CONTENT,LV_SIZE_CONTENT);
    lv_label_set_text(ui_Labbtnstart, LV_SYMBOL_PAUSE);
    lv_obj_align_to(ui_Labbtnstart,ui_btnstart, LV_ALIGN_CENTER,0,0);
    //为开始按钮添加事件，把标签obj当做用户数据传送过去
    lv_obj_add_event_cb(ui_btnstart, music_event_btnstart, LV_EVENT_ALL, ui_Labbtnstart);


    // 创建上一首按钮
    lv_obj_t *ui_btnleft = lv_btn_create(obj);
    lv_obj_set_size(ui_btnleft, 80,60);
	lv_obj_align(ui_btnleft,LV_ALIGN_BOTTOM_MID,-120,-11);
    lv_obj_add_event_cb(ui_btnleft, music_event_btnleft, LV_EVENT_ALL, NULL);
    lv_obj_set_style_radius(ui_btnleft, 180, LV_PART_MAIN | LV_STATE_DEFAULT);//设置圆角为180
    lv_obj_set_style_radius(ui_btnleft, 180, LV_PART_MAIN | LV_STATE_PRESSED);//设置圆角为180
    lv_obj_set_style_bg_color(ui_btnleft, lv_color_hex(0x58CB35), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_btnleft, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_btnleft, 100, LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui_btnleft,0,LV_PART_MAIN | LV_STATE_DEFAULT);
    // 创建上一首按钮标签
    lv_obj_t *ui_Labbtnleft = lv_label_create(ui_btnleft);
    lv_obj_set_size(ui_Labbtnleft, LV_SIZE_CONTENT,LV_SIZE_CONTENT);
    lv_label_set_text(ui_Labbtnleft, LV_SYMBOL_PREV);
    lv_obj_set_align(ui_Labbtnleft, LV_ALIGN_CENTER);


    // 创建下一首按钮
    lv_obj_t *ui_btnright = lv_btn_create(obj);
    lv_obj_set_size(ui_btnright, 80,60);
	lv_obj_align(ui_btnright,LV_ALIGN_BOTTOM_MID,120,-11);
    lv_obj_add_event_cb(ui_btnright, music_event_btnright, LV_EVENT_ALL,NULL);
    lv_obj_set_style_radius(ui_btnright, 180, LV_PART_MAIN | LV_STATE_DEFAULT);//设置圆角为180
    lv_obj_set_style_radius(ui_btnright, 180, LV_PART_MAIN | LV_STATE_PRESSED);//设置圆角为180
    lv_obj_set_style_bg_color(ui_btnright, lv_color_hex(0x58CB35), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_btnright, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_btnright, 100, LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui_btnright,0,LV_PART_MAIN | LV_STATE_DEFAULT);
    // 创建下一首按钮标签
    lv_obj_t *ui_Labbtnright = lv_label_create(ui_btnright);
    lv_obj_set_size(ui_Labbtnright, LV_SIZE_CONTENT,LV_SIZE_CONTENT);
    lv_label_set_text(ui_Labbtnright, LV_SYMBOL_NEXT);
    lv_obj_set_align(ui_Labbtnright, LV_ALIGN_CENTER);


    // 设置一个标签用来显示歌曲名字
    lv_obj_t *ui_Labmp3Name = lv_label_create(obj);
    lv_label_set_long_mode(ui_Labmp3Name, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_width(ui_Labmp3Name, 250);
    lv_obj_set_height(ui_Labmp3Name, LV_SIZE_CONTENT);
	lv_obj_align(ui_Labmp3Name,LV_ALIGN_TOP_MID,0,40);
    lv_label_set_text(ui_Labmp3Name, "mp3 name");
    lv_obj_set_style_text_color(ui_Labmp3Name, lv_color_hex(0xA01DF1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Labmp3Name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);


    // 设置一个标签用来显示总歌曲数量与当前播放的索引
    lv_obj_t *ui_Musicindex = lv_label_create(obj);
    lv_obj_set_width(ui_Musicindex, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Musicindex, LV_SIZE_CONTENT);
	lv_obj_align(ui_Musicindex,LV_ALIGN_TOP_MID,0,65);
    lv_label_set_text(ui_Musicindex, "34/255");
    lv_obj_set_style_text_color(ui_Musicindex, lv_color_hex(0x0082BE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Musicindex, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);


    // 创建一个进度条显示当前播放进度
    lv_obj_t *ui_MusicSlider = lv_slider_create(obj);
    lv_obj_set_size(ui_MusicSlider, 380,10);
    // 这个模式下只能通过拖动滑动条的旋钮(PART KNOB)来调整滑动条的数值
	//lv_obj_add_flag(ui_MusicSlider, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_align(ui_MusicSlider, LV_ALIGN_BOTTOM_MID, 0, -100);
    lv_obj_add_event_cb(ui_MusicSlider, music_slider_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_refresh_ext_draw_size(ui_MusicSlider);
    // 设置默认背景颜色
    lv_obj_set_style_bg_color(ui_MusicSlider, lv_color_hex(0xA7C0DC), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui_MusicSlider, LV_OPA_100, LV_PART_MAIN);
    // 设置默认状态下，指示器部分的背景颜色
    lv_obj_set_style_bg_color(ui_MusicSlider, lv_color_hex(0xFF4800), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MusicSlider, LV_OPA_100, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    // 设置中间手柄按下时的颜色
    //lv_obj_set_style_bg_color(ui_MusicSlider, lv_color_hex(0xbdddba), LV_PART_KNOB | LV_STATE_PRESSED);
    // 设置中间手柄默认时的颜色
    lv_obj_set_style_bg_color(ui_MusicSlider, lv_color_hex(0x007FFE), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_slider_set_range(ui_MusicSlider, 0, 100);		    // 如果不设置，默认是(0-100)
    lv_slider_set_value(ui_MusicSlider, 50, LV_ANIM_ON);	// 设置值


    // 创建标签用来显示歌曲总时间和已经播放的时间
    lv_obj_t *ui_MusicTime = lv_label_create(obj);
    lv_obj_set_width(ui_MusicTime, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_MusicTime, LV_SIZE_CONTENT);
    lv_obj_align_to(ui_MusicTime,ui_MusicSlider,LV_ALIGN_OUT_TOP_LEFT,0,-5);
    lv_label_set_text(ui_MusicTime, "00:21/3:01");
    lv_obj_set_style_text_color(ui_MusicTime, lv_color_hex(0xB848FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_MusicTime, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);\


    // 创建一个 slider 组件(对象)来设置音量大小
    lv_obj_t *ui_MusicVol = lv_slider_create(obj);
    /*调整大小，让 slider 垂直摆放  */
    lv_obj_set_size(ui_MusicVol, 60, 150);
    // 这个模式下只能通过拖动滑动条的旋钮(PART KNOB)来调整滑动条的数值
    lv_obj_add_flag(ui_MusicVol, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_add_event_cb(ui_MusicVol, music_vol_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_align(ui_MusicVol, LV_ALIGN_RIGHT_MID, -10, -200);
    lv_obj_set_style_radius(ui_MusicVol, 15, LV_PART_MAIN | LV_STATE_DEFAULT);//设置圆角为15
    lv_obj_set_style_bg_color(ui_MusicVol,lv_color_hex(0x2D2D2D),LV_PART_MAIN | LV_STATE_DEFAULT);		// 设置背景颜色
    lv_obj_set_style_pad_top(ui_MusicVol, -2,LV_PART_MAIN | LV_STATE_DEFAULT); 		    // 设置顶部(top)的填充(top)大小
    lv_obj_set_style_pad_bottom(ui_MusicVol, -2,LV_PART_MAIN | LV_STATE_DEFAULT);		// 设置底部部(bottom)的填充(top)大小
    lv_obj_set_style_bg_opa(ui_MusicVol, LV_OPA_80,LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MusicVol, LV_OPA_0,LV_PART_KNOB | LV_STATE_DEFAULT);      //去除旋钮
    lv_obj_set_style_radius(ui_MusicVol, 0,LV_PART_INDICATOR | LV_STATE_DEFAULT);		// 设置四个角的圆角
    lv_obj_set_style_bg_color(ui_MusicVol,lv_color_hex(0xFFFFFF),LV_PART_INDICATOR | LV_STATE_DEFAULT);		// 设置背景颜色
    lv_obj_t *ui_MusicVolLabel = lv_label_create(ui_MusicVol);
    lv_label_set_text(ui_MusicVolLabel, LV_SYMBOL_VOLUME_MAX);
    lv_obj_set_style_text_font(ui_MusicVolLabel, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(ui_MusicVolLabel, lv_color_hex(0x007ACC), 0);
    lv_obj_align(ui_MusicVolLabel, LV_ALIGN_BOTTOM_MID, 0, -20);
}






