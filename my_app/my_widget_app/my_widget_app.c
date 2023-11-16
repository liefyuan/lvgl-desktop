
#include <stdio.h>
#include "../lv_100ask.h"


lv_obj_t * cw,* sw;
static void delete_event_cb(lv_event_t * e);     //父对象被删除回调函数

// #define RGB888_RED      0x00ff0000
// #define RGB888_GREEN    0x0000ff00
// #define RGB888_BLUE     0x000000ff

 
// unsigned short RGB888ToRGB565(const  unsigned int n888Color)
// {
// 	unsigned short n565Color = 0;
 
// 	// 获取RGB单色，并截取高位
// 	unsigned char cRed   = (n888Color & RGB888_RED)   >> 19;
// 	unsigned char cGreen = (n888Color & RGB888_GREEN) >> 10;
// 	unsigned char cBlue  = (n888Color & RGB888_BLUE)  >> 3;
 
// 	// 连接
// 	n565Color = (cRed << 11) + (cGreen << 5) + (cBlue << 0);
// 	return n565Color;
// }

#define RGB565_RED      0xf800		//1111 1000 0000 0000 | 0000 0000 1111 1000
#define RGB565_GREEN    0x07e0		//0000 0111 1110 0000 | 0000 0000 1111 1100
#define RGB565_BLUE     0x001f 		//0000 0000 0001 1111 | 0000 0000 1111 1000
unsigned int RGB565ToRGB888(const unsigned short n565Color)
{
	uint32_t n888Color = 0;
 
	uint32_t cRed   = (n565Color & RGB565_RED)    << 8;
	uint32_t cGreen = (n565Color & RGB565_GREEN)  << 5;
	uint32_t cBlue  = (n565Color & RGB565_BLUE)   << 3;
 
	n888Color = cRed | cGreen  | cBlue ;
	return n888Color;	
}


/**********************************************************************
 * 函数名称： event_handler_app
 * 功能描述： app事件回调
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_app(lv_event_t *e)
{
    uint32_t color_full=0;
    //lv_obj_get_child(e->target, 2);//色环
    //lv_obj_get_child(e->target, 3);//开关
    if(e->target == sw&&e->code == LV_EVENT_VALUE_CHANGED)
    {
           if(lv_obj_has_state(sw, LV_STATE_CHECKED))
          {
              LV_LOG_USER("SW ON\r\n");
              lv_color_t color = lv_colorwheel_get_rgb(cw);
              LV_LOG_USER("colorwheel = 0x%08x\r\n",color.full&0x00ffffff);
              color_full =  RGB565ToRGB888(color.full&0xffff);
              //SetLed((uint8_t)(color_full>>16), (uint8_t)(color_full>>8), (uint8_t)color_full);
          }
          else
          {
              LV_LOG_USER("SW OFF\r\n");
              //SetLed(0, 0, 0);
          }

    }
    if(e->target == cw&&e->code == LV_EVENT_VALUE_CHANGED)
    {
          if(lv_obj_has_state(sw, LV_STATE_CHECKED))
          {
              lv_color_t color = lv_colorwheel_get_rgb(cw);
              LV_LOG_USER("colorwheel = 0x%08x\r\n",color.full&0x00ffffff);
              //SetLed(color.ch.red, color.ch.green, color.ch.blue);
              color_full =  RGB565ToRGB888(color.full&0xffff);
              //SetLed((uint8_t)(color_full>>16), (uint8_t)(color_full>>8), (uint8_t)color_full);
          }
    }
}

void lv_colorwheel(lv_obj_t *obj)
{
    cw = lv_colorwheel_create(obj, true);//色环开裂问题，请到.c文件改变响应宏的大小
    lv_obj_set_size(cw, 350, 350);
//    lv_colorwheel_set_mode(cw, LV_COLORWHEEL_MODE_HUE);//调色板模式
//    lv_colorwheel_set_mode_fixed(cw, true);
    lv_colorwheel_set_rgb(cw, lv_color_hex(0x00f0f0));//设置默认颜色
    lv_obj_center(cw);
    lv_obj_set_style_arc_width(cw, 75, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(cw, 10, LV_PART_KNOB);
    lv_obj_add_event_cb(cw, event_handler_app, LV_EVENT_VALUE_CHANGED, NULL);


    /* 创建一个 switch 部件(对象) */
    sw = lv_switch_create(obj);
    lv_obj_align(sw, LV_ALIGN_CENTER, 0, 0);       // 对象居中
    lv_obj_set_size(sw, 100, 50);
    // 修改开关状态指示器部分，关闭状态时的背景颜色
    lv_obj_set_style_bg_opa(sw, 100, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(sw, lv_color_hex(0x111111), LV_PART_INDICATOR);
    // 修改开关状态指示器部分，打开状态时的背景颜色
    lv_obj_set_style_bg_color(sw, lv_color_hex(0x11ff22), LV_PART_INDICATOR | LV_STATE_CHECKED);
    // 修改开关旋钮部分的颜色
    //lv_obj_set_style_bg_color(sw, lv_color_hex(0xc43e1c), LV_PART_KNOB);

    // 开操作
    //lv_obj_add_state(sw, LV_STATE_CHECKED);                       // 开关默认处于关闭状态，这里设置为打开状态
    //lv_obj_add_state(sw, LV_STATE_CHECKED | LV_STATE_DISABLED);   // 当前状态是开，并且不可更改

    // 关操作
    //lv_obj_clear_state(sw, LV_STATE_CHECKED);	        //  关
    //lv_obj_add_state(sw, LV_STATE_DISABLED); 		    //  当前状态是关，并且不可更改

    // 清除禁用状态，一般由其他部件(外部)清除
    //lv_obj_clear_state(sw, LV_STATE_ DISABLED);       // 清除禁用状态，按钮可正常使用
    lv_obj_add_event_cb(sw, event_handler_app, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_add_event_cb(obj, delete_event_cb, LV_EVENT_DELETE,NULL);//添加一个删除事件，检测父对象是否被删除
}

static void delete_event_cb(lv_event_t * e)
{
    if(e->code==LV_EVENT_DELETE)
    {
        //SetLed(0, 0, 0);
    }
}