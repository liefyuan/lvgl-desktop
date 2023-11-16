
#include <stdio.h>
#include "../lv_100ask.h"


/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t * bg_top;			// 背景
static lv_obj_t *desktop;	        // 页签
static uint16_t tabview_desktop_id;	// 记录页签当前展示的页面

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void event_handler_demo_about(lv_event_t * e);					    // 打开关于我们应用事件处理函数
static void event_handler_demo_game_2048(lv_event_t * e);				    // 打开2048游戏应用事件处理函数事件处理函数
static void event_handler_demo_tools_calc(lv_event_t * e);      		    // 打开计算器应用事件处理函数
static void event_handler_demo_game_snake(lv_event_t * e);			        // 打开贪吃蛇游戏应用事件处理函数
static void event_handler_demo_tools_clock(lv_event_t * e);			        // 打开时钟应用事件处理函数
static void event_handler_demo_tools_regbit(lv_event_t * e);   			    // 打开寄存器位查看计算工具应用事件处理函数
static void event_handler_demo_tools_qrcode(lv_event_t * e);   			    // 打开创建二维码应用事件处理函数
static void event_handler_demo_music_player(lv_event_t * e); 			    // 打开音乐播放器应用事件处理函数
static void event_handler_demo_tools_humiture(lv_event_t * e);			    // 打开温湿度应用事件处理函数
static void event_handler_demo_tools_settings(lv_event_t * e);			    // 打开系统设置应用事件处理函数
static void event_handler_demo_tools_widget_test(lv_event_t * e);		    // 打开ADC、LED、BEEP测试应用事件处理函数
static void event_handler_demo_tools_file_browser(lv_event_t * e); 		    // 打开文件浏览器应用事件处理函数

static void event_handler_demo_tools_camera(lv_event_t * e);		       //  打开相机应用事件处理函数
static void event_handler_demo_tools_tetris(lv_event_t * e); 		       //  打开tetris应用事件处理函数

static void event_handler_bottom_round(lv_event_t *e);//底部小圆事件回调


/* 桌标图标声明 */
LV_IMG_DECLARE(img_lv_100ask_icon_2048);		// 00 LV_100ASK_MENU_ITEM_COUNT
LV_IMG_DECLARE(img_lv_100ask_icon_about_us);	// 01
LV_IMG_DECLARE(img_lv_100ask_icon_setting);	    // 02
LV_IMG_DECLARE(img_lv_100ask_icon_data);		// 03
LV_IMG_DECLARE(img_lv_100ask_icon_floder);		// 04
LV_IMG_DECLARE(img_lv_100ask_icon_music);		// 05
LV_IMG_DECLARE(img_lv_100ask_icon_QRcode);  	// 06
LV_IMG_DECLARE(img_lv_100ask_icon_snake);		// 07
LV_IMG_DECLARE(img_lv_100ask_icon_humiture);	// 08
LV_IMG_DECLARE(img_lv_100ask_icon_regbit);		// 09
LV_IMG_DECLARE(img_lv_100ask_icon_calc);		// 10
LV_IMG_DECLARE(img_lv_100ask_icon_widgets);   	// 11

LV_IMG_DECLARE(img_lv_100ask_icon_camera);     	// 12
LV_IMG_DECLARE(img_lv_100ask_icon_tetris);   	// 13
/* 桌标图标数组 */
static const lv_img_dsc_t *app_icon[] = \
	{ \
	  &img_lv_100ask_icon_floder,	 &img_lv_100ask_icon_data, 	   &img_lv_100ask_icon_QRcode,	  &img_lv_100ask_icon_about_us, \
	  &img_lv_100ask_icon_humiture,  &img_lv_100ask_icon_2048,	   &img_lv_100ask_icon_music,	  &img_lv_100ask_icon_snake, \
	  &img_lv_100ask_icon_calc,      &img_lv_100ask_icon_regbit,   \
	  &img_lv_100ask_icon_setting,  \
	  &img_lv_100ask_icon_widgets,  \
      &img_lv_100ask_icon_camera,     \
      &img_lv_100ask_icon_tetris
	};


/* 回调函数指针数组*/
static void (*lv_event_cb[])(lv_event_t *e) = \
	{ \
	  event_handler_demo_tools_file_browser, event_handler_demo_tools_clock, event_handler_demo_tools_qrcode,  event_handler_demo_about, \
	  event_handler_demo_tools_humiture,     event_handler_demo_game_2048,   event_handler_demo_music_player,  event_handler_demo_game_snake, \
	  event_handler_demo_tools_calc,         event_handler_demo_tools_regbit, \
	  event_handler_demo_tools_settings,    \
	  event_handler_demo_tools_widget_test, \
      event_handler_demo_tools_camera,        \
      event_handler_demo_tools_tetris
	};

/* 应用图标名称 */
static const char * app_name[] = \
	{ \
	  "file",     "time",    "QRcode",  "aboutus", \
	  "humiture", "2048",    "music",  "snake", \
	  "calc",     "regbit", \
	  "settings",  \
	  "widget",      \
	  "camera",    \
	  "tetris"
	};

void lv_start_demo(uint32_t delay)
{
    lv_obj_clean(lv_scr_act()); 					// 确保屏幕无残留
    lv_obj_t * scr = lv_obj_create(NULL);
    lv_scr_load(scr);
    bg_top=lv_scr_act();
    //lv_obj_fade_in(bg_top,delay, delay);//延时进入
    lv_demo_home(delay);
}
void lv_demo_home(uint32_t delay)
{
    lv_obj_t *obj = lv_obj_create(bg_top);
    lv_font_t * font = lv_obj_get_style_text_font(obj, LV_PART_MAIN);//获取字体样式，进而求得高度
    lv_obj_set_size(obj,LV_PCT(100),font->line_height*2);
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_border_opa(obj, LV_OPA_0, LV_PART_MAIN);//边框设置成透明，进而隐藏边框
    lv_obj_set_style_bg_color(obj, lv_color_darken(lv_obj_get_style_bg_color(bg_top, 0), 0), LV_PART_MAIN);
    lv_obj_clear_flag(obj,LV_OBJ_FLAG_SCROLLABLE);//清除滑动效果，是为了隐藏滚动条

    lv_obj_t *label_tile = lv_label_create(obj);
    lv_label_set_long_mode(label_tile, LV_LABEL_LONG_CLIP);
    lv_label_set_text(label_tile,LV_SYMBOL_WIFI " "LV_SYMBOL_BLUETOOTH);
    lv_obj_add_flag(label_tile,LV_OBJ_FLAG_FLOATING);
    lv_obj_align(label_tile,LV_ALIGN_LEFT_MID,0,0);


    label_tile = lv_label_create(obj);
    lv_label_set_long_mode(label_tile, LV_LABEL_LONG_CLIP);
    lv_label_set_text(label_tile,LV_SYMBOL_GPS" "LV_SYMBOL_VOLUME_MAX" "LV_SYMBOL_BATTERY_3);
    lv_obj_add_flag(label_tile,LV_OBJ_FLAG_FLOATING);
    lv_obj_align(label_tile,LV_ALIGN_RIGHT_MID,0,0);

    label_tile = lv_label_create(obj);
    lv_label_set_long_mode(label_tile, LV_LABEL_LONG_CLIP);
    lv_label_set_text(label_tile,"14:23");
    lv_obj_add_flag(label_tile,LV_OBJ_FLAG_FLOATING);
    lv_obj_align(label_tile,LV_ALIGN_CENTER,0,0);

    desktop = lv_tileview_create(bg_top);//创建桌面  E:\百韦网\my_project\codeblocks_plus\pic_test
    lv_obj_set_style_bg_color(desktop, lv_color_hex(0x33D4FF), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_color(desktop, lv_color_hex(0xff00ff), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_dir(desktop, LV_GRAD_DIR_VER, LV_PART_MAIN);
    //lv_obj_set_style_bg_img_src(desktop,"D:/system/desktop/my_jpg1.jpg", LV_PART_MAIN);
    //lv_obj_set_style_bg_img_opa(desktop, LV_OPA_100, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(desktop, LV_OPA_0, LV_PART_SCROLLBAR);//隐藏滚动条
    lv_obj_set_style_bg_opa(desktop, LV_OPA_0, LV_PART_SCROLLBAR|LV_STATE_SCROLLED);//隐藏滚动条
    lv_obj_set_size(desktop,LV_PCT(100),lv_obj_get_height(lv_scr_act())-font->line_height*2);
    lv_obj_align(desktop,LV_ALIGN_DEFAULT,0,font->line_height*2);
    /*创建界面1*/
    lv_obj_t * tile1 = lv_tileview_add_tile(desktop, 0, 0, LV_DIR_LEFT | LV_DIR_RIGHT|LV_DIR_HOR|LV_DIR_VER);
    lv_obj_set_tile(desktop, tile1, true);

    /*创建界面2*/
    lv_obj_t * tile2 = lv_tileview_add_tile(desktop, 1, 0, LV_DIR_LEFT | LV_DIR_RIGHT|LV_DIR_HOR|LV_DIR_VER);
    lv_obj_set_tile(desktop, tile2, true);

    lv_obj_t * round = lv_obj_create(bg_top);//创建底部小圆1
    lv_obj_set_size(round,8,8);
    lv_obj_align(round,LV_ALIGN_BOTTOM_MID,-10,-160);
    lv_obj_set_style_radius(round, 180, 0);
    lv_obj_set_style_border_opa(round, LV_OPA_0, 0);
    lv_obj_set_style_bg_opa(round, LV_OPA_90, 0);

    round = lv_obj_create(bg_top);//创建底部小圆2
    lv_obj_set_size(round,8,8);
    lv_obj_align(round,LV_ALIGN_BOTTOM_MID,14,-160);
    lv_obj_set_style_radius(round, 180, 0);
    lv_obj_set_style_border_opa(round, LV_OPA_0, 0);
    lv_obj_set_style_bg_opa(round, LV_OPA_30, 0);
    lv_obj_add_event_cb(desktop, event_handler_bottom_round, LV_EVENT_SCROLL_END, round);//创建事件回调函数

    static bool frist=0; static lv_style_t style_pr;  //只初始化一次，不然会造成内存泄漏
    if(frist==0)
    {   frist=1;
        lv_style_reset(&style_pr);
        lv_style_init(&style_pr);
        lv_style_set_img_recolor_opa(&style_pr, LV_OPA_30);
        lv_style_set_img_recolor(&style_pr, lv_color_black());
    }
    #define icon_width    52  //图标宽度
    #define icon_height   52  //图标高度
    #define row_num       6   //每行放图标个数 //不要大于6
    #define interval      26  //图标与图标间隔   一般是图标宽度的一半
    for(int i=0;i<14;i++){
         if(i<row_num){
            lv_obj_t * imgbtn1 = lv_imgbtn_create(tile1);
            lv_obj_set_size(imgbtn1,icon_width,icon_height);
            lv_imgbtn_set_src(imgbtn1, LV_IMGBTN_STATE_RELEASED, NULL, app_icon[i], NULL);
            lv_obj_add_style(imgbtn1, &style_pr, LV_STATE_PRESSED);/**< 按下时样式 */
            lv_obj_align(imgbtn1, LV_ALIGN_TOP_LEFT,(lv_obj_get_content_width(tile1)-(icon_width*row_num+(interval*(row_num-1))))/2+(i*(icon_width+interval)), 30);

            lv_obj_t *label = lv_label_create(tile1);
            lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), 0);
            lv_label_set_text(label, app_name[i]);
            lv_obj_align_to(label,imgbtn1, LV_ALIGN_OUT_BOTTOM_MID, 0, 6);
            lv_obj_add_event_cb(imgbtn1, lv_event_cb[i], LV_EVENT_CLICKED, NULL);//创建事件回调函数
         }
         else{  //换页
            lv_obj_t * imgbtn1 = lv_imgbtn_create(tile2);
            lv_obj_set_size(imgbtn1,icon_width,icon_height);
            lv_imgbtn_set_src(imgbtn1, LV_IMGBTN_STATE_RELEASED, NULL, app_icon[i], NULL);
            lv_obj_add_style(imgbtn1, &style_pr, LV_STATE_PRESSED);/**< 按下时样式 */
            if(i<12)
            {
              lv_obj_align(imgbtn1, LV_ALIGN_TOP_LEFT,(lv_obj_get_content_width(tile2)-(icon_width*row_num+(interval*(row_num-1))))/2+((i-row_num)*(icon_width+interval)), 30);
            }
            else
            {
              lv_obj_align(imgbtn1, LV_ALIGN_TOP_LEFT,(lv_obj_get_content_width(tile2)-(icon_width*row_num+(interval*(row_num-1))))/2+((i-12)*(icon_width+interval)), 125);
            }
            lv_obj_t *label = lv_label_create(tile2);
            lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), 0);
            lv_label_set_text(label, app_name[i]);
            lv_obj_align_to(label,imgbtn1, LV_ALIGN_OUT_BOTTOM_MID, 0, 6);
            lv_obj_add_event_cb(imgbtn1, lv_event_cb[i], LV_EVENT_CLICKED, NULL);//创建事件回调函数
         }
    }

    lv_obj_t * bottom_cont = lv_obj_create(bg_top);
    lv_obj_set_size(bottom_cont,450,120);
    lv_obj_align(bottom_cont,LV_ALIGN_BOTTOM_MID,0,-30);
    lv_obj_set_style_radius(bottom_cont, 45, 0);
    lv_obj_set_style_border_opa(bottom_cont, LV_OPA_0, 0);
    lv_obj_set_style_bg_opa(bottom_cont, LV_OPA_30, 0);
    for(int i=0;i<4;i++){  //底部按钮栏

            lv_obj_t * imgbtn1 = lv_imgbtn_create(bottom_cont);
            lv_obj_set_size(imgbtn1,icon_width,icon_height);
            lv_obj_add_flag(imgbtn1,LV_OBJ_FLAG_FLOATING);//不随父对象滚动
            lv_imgbtn_set_src(imgbtn1, LV_IMGBTN_STATE_RELEASED, NULL, app_icon[i], NULL);
            lv_obj_add_style(imgbtn1, &style_pr, LV_STATE_PRESSED);/**< 按下时样式 */
            lv_obj_align(imgbtn1, LV_ALIGN_TOP_LEFT,28+(i*(icon_width+52)),10);

            lv_obj_t *label = lv_label_create(bottom_cont);
            lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), 0);
            lv_obj_add_flag(label,LV_OBJ_FLAG_FLOATING);
            lv_label_set_text(label, app_name[i]);
            lv_obj_align_to(label,imgbtn1, LV_ALIGN_OUT_BOTTOM_MID, 0, 6);
            lv_obj_add_event_cb(imgbtn1, lv_event_cb[i], LV_EVENT_CLICKED, NULL);//创建事件回调函数
    }
}
static void event_handler_bottom_round(lv_event_t *e)
{
    if(e->code==LV_EVENT_SCROLL_END) {//滚动停止事件
        LV_LOG_USER("SCROLL_END\r\n");
        lv_obj_t *obj = e->target;
        lv_obj_t *user_data = lv_obj_get_parent(e->user_data);//这里获取到的父对象，其实是  bg_top
        int child_index = lv_obj_get_index(lv_tileview_get_tile_act(obj));
        LV_LOG_USER("tileview index = %d\r\n",child_index);
        if(child_index==0){
             lv_obj_set_style_bg_opa(lv_obj_get_child(user_data, 2), LV_OPA_90, 0);
             lv_obj_set_style_bg_opa(lv_obj_get_child(user_data, 3), LV_OPA_30, 0);
             LV_LOG_USER("bottom round child_cnt = %d\r\n",lv_obj_get_child_cnt(user_data));
        }
        else if(child_index==1){
             lv_obj_set_style_bg_opa(lv_obj_get_child(user_data, 2), LV_OPA_30, 0);
             lv_obj_set_style_bg_opa(lv_obj_get_child(user_data, 3), LV_OPA_90, 0);
             LV_LOG_USER("bottom round child_cnt = %d\r\n",lv_obj_get_child_cnt(user_data));
        }
    }
}

/**********************************************************************
 * 函数名称： event_handler_demo_tools_camera
 * 功能描述： 打开相机应用
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_demo_tools_camera(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED)
    {
      LV_LOG_USER("camera APP\r\n");
      //lv_obj_del(desktop);
      lv_obj_clean(bg_top);//清除背景层上的所有对象
      LV_LOG_USER("residue...%d\r\n",lv_obj_get_child_cnt(bg_top)); //如果等于0 ，说明清除完成
      lv_obj_t *app_obj = lv_create_back_btn("camera");
    }

}
/**********************************************************************
 * 函数名称： event_handler_demo_tools_tetris
 * 功能描述： 打开tetris应用
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_demo_tools_tetris(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED)
    {
      LV_LOG_USER("tetris APP\r\n");
      //lv_obj_del(desktop);
      lv_obj_clean(bg_top);//清除背景层上的所有对象
      LV_LOG_USER("residue...%d\r\n",lv_obj_get_child_cnt(bg_top)); //如果等于0 ，说明清除完成
      lv_obj_t *app_obj = lv_create_back_btn("tetris");
    }

}
/**********************************************************************
 * 函数名称： event_handler_demo_about
 * 功能描述： 打开关于应用
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_demo_about(lv_event_t *e)
{
    if(e->code == LV_EVENT_CLICKED)
    {
      LV_LOG_USER("about APP\r\n");
      //lv_obj_del(desktop);
      lv_obj_clean(bg_top);//清除背景层上的所有对象
      LV_LOG_USER("residue...%d\r\n",lv_obj_get_child_cnt(bg_top)); //如果等于0 ，说明清除完成
      lv_obj_t *app_obj = lv_create_back_btn("about");
      my_about_app(app_obj);
    }
}


/**********************************************************************
 * 函数名称： event_handler_demo_music_player
 * 功能描述： 打开音乐播放器应用
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_demo_music_player(lv_event_t *e)
{
    if(e->code == LV_EVENT_CLICKED)
    {
       LV_LOG_USER("music APP\r\n");
       //lv_obj_del(desktop);
       lv_obj_clean(bg_top);//清除背景层上的所有对象
       LV_LOG_USER("residue...%d\r\n",lv_obj_get_child_cnt(bg_top)); //如果等于0 ，说明清除完成
       lv_obj_t *app_obj = lv_create_back_btn("music player");
       my_music_app(app_obj);
    }
}



/**********************************************************************
 * 函数名称： event_handler_demo_game_2048
 * 功能描述： 打开2048游戏
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_demo_game_2048(lv_event_t *e)
{
    if(e->code == LV_EVENT_CLICKED)
    {
      LV_LOG_USER("2048 APP\r\n");
      //lv_obj_del(desktop);
      lv_obj_clean(bg_top);//清除背景层上的所有对象
      LV_LOG_USER("residue...%d\r\n",lv_obj_get_child_cnt(bg_top)); //如果等于0 ，说明清除完成
      lv_obj_t *app_obj = lv_create_back_btn("game 2048");
    }
}


/**********************************************************************
 * 函数名称： event_handler_demo_tools_regbit
 * 功能描述： 打开寄存器位查看计算工具
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_demo_tools_regbit(lv_event_t *e)
{
    if(e->code == LV_EVENT_CLICKED)
    {
       LV_LOG_USER("regbit APP\r\n");
       //lv_obj_del(desktop);
       lv_obj_clean(bg_top);//清除背景层上的所有对象
       LV_LOG_USER("residue...%d\r\n",lv_obj_get_child_cnt(bg_top)); //如果等于0 ，说明清除完成
       lv_obj_t *app_obj = lv_create_back_btn("regbit");
    }
}


/**********************************************************************
 * 函数名称： event_handler_demo_tools_qrcode
 * 功能描述： 打开二维码创建工具
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_demo_tools_qrcode(lv_event_t *e)
{
    if(e->code == LV_EVENT_CLICKED)
    {
        LV_LOG_USER("qrcode APP\r\n");
        //lv_obj_del(desktop);
        lv_obj_clean(bg_top);//清除背景层上的所有对象
        LV_LOG_USER("residue...%d\r\n",lv_obj_get_child_cnt(bg_top)); //如果等于0 ，说明清除完成
        lv_obj_t *app_obj = lv_create_back_btn("qrcode");
        lv_QRcode_demo(app_obj);
    }
}

/**********************************************************************
 * 函数名称： event_handler_demo_tools_calc
 * 功能描述： 打开计算器
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_demo_tools_calc(lv_event_t *e)
{
    if(e->code == LV_EVENT_CLICKED)
    {
       LV_LOG_USER("calc APP\r\n");
       //lv_obj_del(desktop);
       lv_obj_clean(bg_top);//清除背景层上的所有对象
       LV_LOG_USER("residue...%d\r\n",lv_obj_get_child_cnt(bg_top)); //如果等于0 ，说明清除完成
       lv_obj_t *app_obj = lv_create_back_btn("calc");
       my_calc_app(app_obj);
    }
}


/**********************************************************************
 * 函数名称： event_handler_demo_tools_file_browser
 * 功能描述： 打开文件浏览器
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_demo_tools_file_browser(lv_event_t *e)
{
    if(e->code == LV_EVENT_CLICKED)
    {
       LV_LOG_USER("file_browser APP\r\n");
       //lv_obj_del(desktop);
       lv_obj_clean(bg_top);//清除背景层上的所有对象
       LV_LOG_USER("residue...%d\r\n",lv_obj_get_child_cnt(bg_top)); //如果等于0 ，说明清除完成
       lv_obj_t *app_obj = lv_create_back_btn("file browser");
    }
}



/**********************************************************************
 * 函数名称： event_handler_demo_tools_snake
 * 功能描述： 打开贪吃蛇游戏
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_demo_game_snake(lv_event_t *e)
{
    if(e->code == LV_EVENT_CLICKED)
    {
       LV_LOG_USER("snake APP\r\n");
       //lv_obj_del(desktop);
       lv_obj_clean(bg_top);//清除背景层上的所有对象
       LV_LOG_USER("residue...%d\r\n",lv_obj_get_child_cnt(bg_top)); //如果等于0 ，说明清除完成
       lv_obj_t *app_obj = lv_create_back_btn("snake");
    }
}


/**********************************************************************
 * 函数名称： event_handler_demo_tools_clock
 * 功能描述： 打开时钟
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_demo_tools_clock(lv_event_t *e)
{
    if(e->code == LV_EVENT_CLICKED)
    {
        LV_LOG_USER("clock APP\r\n");
        //lv_obj_del(desktop);
        lv_obj_clean(bg_top);//清除背景层上的所有对象
        LV_LOG_USER("residue...%d\r\n",lv_obj_get_child_cnt(bg_top)); //如果等于0 ，说明清除完成
        lv_obj_t *app_obj = lv_create_back_btn("clock");
        my_clock_app(app_obj);
    }
}


/**********************************************************************
 * 函数名称： event_handler_demo_tools_humiture
 * 功能描述： 打开温湿度检测应用
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_demo_tools_humiture(lv_event_t *e)
{
    if(e->code == LV_EVENT_CLICKED)
    {
       LV_LOG_USER("humiture APP\r\n");
       //lv_obj_del(desktop);
       lv_obj_clean(bg_top);//清除背景层上的所有对象
       LV_LOG_USER("residue...%d\r\n",lv_obj_get_child_cnt(bg_top)); //如果等于0 ，说明清除完成
       lv_obj_t *app_obj = lv_create_back_btn("humiture");
       my_temp_app(app_obj);
    }
}
/**********************************************************************
 * 函数名称： event_handler_demo_tools_widget_test
 * 功能描述： 打开板载部件测试应用
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_demo_tools_widget_test(lv_event_t *e)
{
    if(e->code == LV_EVENT_CLICKED)
    {
       LV_LOG_USER("test APP\r\n");
       //lv_obj_del(desktop);
       lv_obj_clean(bg_top);//清除背景层上的所有对象
       LV_LOG_USER("residue...%d\r\n",lv_obj_get_child_cnt(bg_top)); //如果等于0 ，说明清除完成
       lv_obj_t *app_obj = lv_create_back_btn("widget test");
       lv_colorwheel(app_obj);
    }
}


/**********************************************************************
 * 函数名称： event_handler_demo_tools_settings
 * 功能描述： 打开系统设置
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_handler_demo_tools_settings(lv_event_t *e)
{
    if(e->code == LV_EVENT_CLICKED){
      LV_LOG_USER("settings APP\r\n");
      //lv_obj_del(desktop);
      lv_obj_clean(bg_top);//清除背景层上的所有对象
      LV_LOG_USER("residue...%d\r\n",lv_obj_get_child_cnt(bg_top)); //如果等于0 ，说明清除完成
      lv_obj_t *app_obj = lv_create_back_btn("settings");
      my_settings_app(app_obj);
      
    }
}
/**********************************************************************
 * 函数名称： event_cb  back_event_handler
 * 功能描述： 退出当前界面系统回调函数
 * 输入参数： 无
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_current_target(e);
    uint16_t  btn_id = lv_msgbox_get_active_btn(obj);
    LV_LOG_USER("Button %s clicked  btn_id = %d\r\n", lv_msgbox_get_active_btn_text(obj),btn_id);
    if(e->code==LV_EVENT_CLICKED)
    {
        if(btn_id==1)
        {
          lv_msgbox_close_async(obj);
          lv_anim_del_all();//如果有动画，记得删除动画
          lv_obj_del(e->user_data);
          //lv_obj_fade_in(bg_top,500, 0);//延时进入
          lv_demo_home(0);
        }
        else if(btn_id==0)
        {
          lv_msgbox_close_async(obj);
        }
    }
}
static void back_event_handler(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED) {
        static const char * btns[] ={"#0f0fff Cancel#", "#03f030 Enter#", ""};
        static lv_btnmatrix_ctrl_t ctrl_map[] = {LV_BTNMATRIX_CTRL_RECOLOR,LV_BTNMATRIX_CTRL_RECOLOR};
        lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Hello", "Are you sure you want out?", btns, true);
        lv_btnmatrix_set_ctrl_map(lv_msgbox_get_btns(mbox1), ctrl_map);
        lv_obj_set_style_text_color(lv_msgbox_get_title(mbox1),lv_color_hex(0xff0000), LV_PART_MAIN);
        lv_obj_set_style_bg_color(lv_msgbox_get_btns(mbox1),lv_color_hex(0x555555), LV_PART_ITEMS);//设置矩阵按钮背景
        lv_obj_set_style_bg_color(lv_msgbox_get_btns(mbox1), lv_color_hex(0x78c146) , LV_STATE_PRESSED | LV_PART_ITEMS);//设置矩阵按钮按下背景
        lv_obj_set_style_bg_color(lv_msgbox_get_close_btn(mbox1), lv_color_hex(0xff00ff), LV_PART_MAIN);
        lv_obj_set_style_shadow_width(mbox1, 5, LV_PART_MAIN);
        lv_obj_add_event_cb(mbox1, event_cb, LV_EVENT_CLICKED, e->user_data);
        lv_obj_center(mbox1);
    }
}
/**********************************************************************
 * 函数名称： lv_create_back_btn
 * 功能描述： 创建一个返回按钮
 * 输入参数： 无
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 返回创建对象
 ***********************************************************************/
lv_obj_t * lv_create_back_btn(char *title)
{
    lv_obj_t * obj= lv_obj_create(lv_scr_act());
    lv_obj_set_style_radius(obj, 0, 0);
    // lv_obj_set_style_bg_color(obj, lv_color_darken(lv_obj_get_style_bg_color(obj, 0), 0), 0);
    lv_obj_set_size(obj, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    //lv_obj_set_style_bg_img_src(obj,"D:/system/desktop/my_jpg4.jpg", LV_PART_MAIN);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x23A8F2), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xA4E233), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN);
    lv_obj_center(obj);
    // lv_obj_fade_in(obj,500, 0);//延时进入
    lv_obj_t * back_btn = lv_btn_create(obj);
    lv_obj_set_size(back_btn,60,30);
    lv_obj_set_style_bg_opa(back_btn, LV_OPA_50, 0);
    lv_obj_align(back_btn,LV_ALIGN_DEFAULT,-10,-5);
    lv_obj_t * back_btn_label = lv_label_create(back_btn);
    lv_obj_set_style_text_color(back_btn_label, lv_color_hex(0xffffff), 0);
    lv_label_set_text(back_btn_label, LV_SYMBOL_LEFT" back");//这里是为了增大返回键的接触面
    lv_obj_center(back_btn_label);
    lv_obj_add_event_cb(back_btn, back_event_handler, LV_EVENT_CLICKED, obj);

    lv_obj_t * title_label = lv_label_create(obj);
    lv_obj_set_style_text_font(title_label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(title_label,lv_color_hex(0xffffff), 0);
    lv_obj_add_flag(title_label,LV_OBJ_FLAG_FLOATING);
    lv_label_set_recolor(title_label, true);
    lv_label_set_text(title_label,title);
    lv_obj_align(title_label,LV_ALIGN_TOP_MID,0,5);

    return obj;
}
