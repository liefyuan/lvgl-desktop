
#include <stdio.h>
#include "../lv_100ask.h"

static lv_obj_t * meter;

static void set_value(void * indic, int32_t v)
{
    lv_meter_set_indicator_end_value(meter, indic, v);

}

/**
 * A clock from a meter
 */
void my_clock_app(lv_obj_t *obj)
{
    meter = lv_meter_create(obj);
    lv_obj_set_size(meter, 320, 320);
    lv_obj_center(meter);
    lv_obj_set_style_bg_color(meter, lv_color_hex(0xffff00),LV_PART_MAIN);
    lv_obj_set_style_bg_grad_color(meter, lv_color_hex(0xff00ff),LV_PART_MAIN);
    lv_obj_set_style_bg_grad_dir(meter, LV_GRAD_DIR_VER,LV_PART_MAIN);
    lv_obj_set_style_bg_color(meter, lv_color_hex(0x0000ff),LV_PART_INDICATOR);//中间圆的大小


    /*Create another scale for the hours. It's only visual and contains only major ticks*/
    lv_meter_scale_t * scale_hour = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale_hour, 12, 0, 0, lv_color_hex(0x2196F3));  //给仪表添加一个新的刻度。
    lv_meter_set_scale_major_ticks(meter, scale_hour, 1, 2, 20, lv_color_hex(0x2196F3), 10);
    lv_meter_set_scale_range(meter, scale_hour, 1, 12, 330, 300);

    lv_meter_scale_t * scale_min = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale_min, 61, 0, 0, lv_color_hex(0x2196F3));//给仪表添加一个新的刻度。
    lv_meter_set_scale_range(meter, scale_min, 0, 60, 360, 270);

    lv_meter_scale_t * scale_sec = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale_sec, 61, 1, 10, lv_color_hex(0x2196F3));//给仪表添加一个新的刻度。
    lv_meter_set_scale_range(meter, scale_sec, 0, 60, 360, 270);

    LV_IMG_DECLARE(my_img_hand)
    /*Add a the hands from images*/
    lv_meter_indicator_t * indic_hour = lv_meter_add_needle_img(meter, scale_min, &my_img_hand, 5, 5);
    lv_meter_indicator_t * indic_min =  lv_meter_add_needle_img(meter, scale_min, &my_img_hand, 5, 5);
    lv_meter_indicator_t * indic_sec =  lv_meter_add_needle_img(meter, scale_sec, &my_img_hand, 5, 5);
    /*Create an animation to set the value*/
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_values(&a, 0, 60);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_time(&a, 2000);     /*2 sec for 1 turn of the minute hand (1 hour)*/
    lv_anim_set_var(&a, indic_min);
    lv_anim_start(&a);

    lv_anim_set_var(&a, indic_hour);
    lv_anim_set_time(&a, 6000);    /*24 sec for 1 turn of the hour hand*/
    lv_anim_set_values(&a, 0, 60);
    lv_anim_start(&a);

    lv_anim_set_var(&a, indic_sec);
    lv_anim_set_time(&a, 1000);    /*24 sec for 1 turn of the hour hand*/
    lv_anim_set_values(&a, 0, 60);
    lv_anim_start(&a);
}
