

#include "../lv_100ask.h"
#include <stdio.h>

static lv_meter_indicator_t * indic;
static int anim=-20;static int speed_count=-20;

static void my_refresh_timer(lv_timer_t * timer);//定时器回调函数
static void delete_event_cb(lv_event_t * e);     //父对象被删除回调函数

static lv_style_t freetype_style;

void my_temp_app(lv_obj_t *obj)
{
    speed_count=-20;anim=-20;
    lv_obj_t * meter = lv_meter_create(obj);
    lv_obj_center(meter);
    lv_obj_set_size(meter, 430, 430);

    /*Remove the circle from the middle 去掉中间圆 */
    lv_obj_remove_style(meter, NULL, LV_PART_INDICATOR);
    lv_obj_set_style_border_color(meter, lv_color_hex(0x6432BE), LV_PART_MAIN);
    lv_obj_set_style_border_width(meter, 5, LV_PART_MAIN);
    lv_obj_set_style_border_opa(meter, LV_OPA_50, LV_PART_MAIN);
    lv_obj_set_style_bg_color(meter, lv_color_hex(0xFBFDE3), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_color(meter, lv_color_hex(0xFBFDE3), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_dir(meter, LV_GRAD_DIR_HOR, LV_PART_MAIN);

    /*先添加一个刻度*/
    lv_meter_scale_t * scale = lv_meter_add_scale(meter);  //给仪表添加一个新的刻度。
    lv_meter_set_scale_range(meter,scale, -20, 60, 280,130);
    lv_meter_set_scale_ticks(meter, scale, 81, 1, 12, lv_palette_main(LV_PALETTE_GREY));//总81个刻度线，小刻度线宽度为2，长度为10
    lv_meter_set_scale_major_ticks(meter, scale, 5, 4, 20, lv_color_black(), 20);   //每隔5个小刻度线绘制一个大刻度线，宽度4，长度20

    /*添加一个蓝色的开始弧线*/
    indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_BLUE), 0);//在刻度上增加一个圆弧指示器
    lv_meter_set_indicator_start_value(meter, indic, -20);
    lv_meter_set_indicator_end_value(meter, indic, 20);

    /*刻度开始处的勾线为蓝色*/
    indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE), false, 0);
    lv_meter_set_indicator_start_value(meter, indic, -20);
    lv_meter_set_indicator_end_value(meter, indic, 20);

    /*在添加一个绿色的弧线*/
    indic = lv_meter_add_arc(meter, scale, 3, lv_color_hex(0x43CB29), 0);
    lv_meter_set_indicator_start_value(meter, indic, 20);
    lv_meter_set_indicator_end_value(meter, indic, 28);

    /*刻度末端的勾线为绿色*/
    indic = lv_meter_add_scale_lines(meter, scale, lv_color_hex(0x43CB29), lv_color_hex(0x43CB29), false, 0);
    lv_meter_set_indicator_start_value(meter, indic, 20);
    lv_meter_set_indicator_end_value(meter, indic, 28);


    /*在结尾添加一个红色的弧线*/
    indic = lv_meter_add_arc(meter, scale, 3, lv_color_hex(0xFF2525), 0);
    lv_meter_set_indicator_start_value(meter, indic, 28);
    lv_meter_set_indicator_end_value(meter, indic, 60);
    /*刻度末端的勾线为红色*/
    indic = lv_meter_add_scale_lines(meter, scale, lv_color_hex(0xFF2525), lv_color_hex(0xFF2525), false, 0);
    lv_meter_set_indicator_start_value(meter, indic, 28);
    lv_meter_set_indicator_end_value(meter, indic, 60);

    /*添加针线指示器*/
    LV_IMG_DECLARE(temp_indicator);
    indic = lv_meter_add_needle_img(meter, scale, &temp_indicator,26, 26);
    lv_meter_set_indicator_value(meter, indic, anim);//设置初始值

    lv_obj_t *label_tile = lv_label_create(meter);
    lv_label_set_long_mode(label_tile, LV_LABEL_LONG_CLIP);
	
#if LV_USE_FREETYPE
    lv_obj_add_style(label_tile, &freetype_style, 0);//设置FreeType字体
#else
    lv_obj_set_style_text_font(label_tile, &lv_font_montserrat_40, 0);
#endif
	
    lv_label_set_text(label_tile,"-20");
    lv_obj_align_to(label_tile,meter,LV_ALIGN_CENTER,0,140);

    lv_timer_t *timer = lv_timer_create(my_refresh_timer, 50,  obj);//创建定时器50ms调用一次
    lv_timer_reset(timer);

    lv_obj_add_event_cb(obj, delete_event_cb, LV_EVENT_DELETE,timer);//添加一个删除事件，检测父对象是否被删除
}
static void my_refresh_timer(lv_timer_t * timer)
{
   lv_obj_t *cont_child_2 = lv_obj_get_child(timer->user_data,2);  //对象的第2个孩子
   lv_obj_t *cont_child_child_0 = lv_obj_get_child(cont_child_2,0);//对象孩子的孩子

   if(speed_count>=anim)anim=speed_count;
   if(speed_count<anim&&anim>0) anim--;

   char str_buf[100];
   sprintf(str_buf,"%02d",anim);
   lv_label_set_text(cont_child_child_0,str_buf);
   lv_obj_align_to(cont_child_child_0,cont_child_2,LV_ALIGN_CENTER,0,140);


   lv_meter_set_indicator_value(cont_child_2, indic, anim);    //关联指针

/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
   static uint8_t temp=0;//模拟动画
   temp++;if(temp>2)
   {
       temp=0;
       speed_count++;if(speed_count>60){speed_count=-20;}
   }

}
static void delete_event_cb(lv_event_t * e)
{
    if(e->code==LV_EVENT_DELETE)
    {
        if(e->user_data!=NULL)
        {
            LV_LOG_USER("LV_EVENT_DELETE\r\n");
            lv_timer_del(e->user_data);
        }
    }
}