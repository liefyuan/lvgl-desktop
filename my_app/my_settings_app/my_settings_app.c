
#include <stdio.h>
#include "../lv_100ask.h"

lv_obj_t * main_page;
lv_obj_t *Play_SW_OBJ,*Volume_adjust_OBJ,*Sidebar_SW_OBJ;

enum {
    LV_MENU_ITEM_BUILDER_VARIANT_1,//ͼ��λ���������
    LV_MENU_ITEM_BUILDER_VARIANT_2 //ͼ��λ���������±�
};
typedef uint8_t lv_menu_builder_variant_t;

static lv_obj_t * create_text(lv_obj_t * parent, const char * icon, const char * txt,
                                        lv_menu_builder_variant_t builder_variant,
                                        bool Whether_SYMBOL_RIGHT,   //����ʾ�ұߵķ��� ��>��
                                        bool Whether_Draw_Border_line//�Ƿ���Ʒָ���
                             )
{
    lv_obj_t * obj = lv_menu_cont_create(parent);//����һ���˵�����

    lv_obj_t * img = NULL;
    lv_obj_t * label = NULL;

    if(icon) {
        img = lv_img_create(obj);
        lv_img_set_src(img, icon);
    }

    if(txt) {
        label = lv_label_create(obj);
        lv_label_set_text(label, txt);
        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
        lv_obj_set_flex_grow(label, 1);

        if(Whether_SYMBOL_RIGHT){
            img = lv_img_create(obj);
            lv_img_set_src(img, LV_SYMBOL_RIGHT);
            lv_obj_align(img,LV_ALIGN_LEFT_MID,LV_PCT(90),0);
        }
    }

    if(builder_variant == LV_MENU_ITEM_BUILDER_VARIANT_2 && icon && txt) {
        lv_obj_add_flag(img, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
        lv_obj_swap(img, label);
    }
    if(Whether_Draw_Border_line){
        static lv_point_t line_points[2];
        line_points[0].x = lv_obj_get_x(parent);      line_points[0].y = lv_obj_get_y(parent);
        line_points[1].x = lv_obj_get_style_width(parent,0); line_points[1].y = line_points[0].y;
        static bool frist=0;
        static lv_style_t style_line;
        if(!frist)//ֻ��ʼ��һ��
        {
             frist=1;
             lv_style_init(&style_line);
        }
        lv_style_set_line_width(&style_line, 1);
        lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_GREY));//��ɫ
        lv_style_set_line_rounded(&style_line, true);

        lv_obj_t * line1;
        line1 = lv_line_create(parent);
        lv_line_set_points(line1, line_points, 2);     /*Set the points*/
        lv_obj_add_style(line1, &style_line, 0);
        lv_obj_align(line1,LV_ALIGN_BOTTOM_LEFT,0,0);
    }
    return obj;
}
static void back_event_handler(lv_event_t * e)
{
    lv_obj_t *parent = lv_obj_get_parent(e->user_data); //��ȡ����
    if(lv_menu_back_btn_is_root(e->user_data,e->target))//�������ˣ���ʱ��Ҫ���ص�����
    {
      LV_LOG_USER("btn_is_root\r\n");
      lv_event_send(lv_obj_get_child(parent,0), LV_EVENT_CLICKED, NULL);
    }

}
static lv_obj_t * create_slider(lv_obj_t * parent, const char * icon, const char * txt, int32_t min, int32_t max, int32_t val,bool draw_line)
{
    lv_obj_t * obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_2,!true,draw_line);

    lv_obj_t * slider = lv_slider_create(obj);
    lv_obj_set_flex_grow(slider, 1);
    lv_slider_set_range(slider, min, max);
    lv_slider_set_value(slider, val, LV_ANIM_ON);

    if(icon == NULL) {
        lv_obj_add_flag(slider, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    }

    return obj;
}

static lv_obj_t * create_switch(lv_obj_t * parent, const char * icon, const char * txt, bool chk,bool draw_line)
{
    lv_obj_t * obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_1,!true,draw_line);

    lv_obj_t * sw = lv_switch_create(obj);
    lv_obj_add_state(sw, chk ? LV_STATE_CHECKED : 0);

    return obj;
}
/*****************************************************************************************************************/

static void switch_handler(lv_event_t * e)//�л��˵���ʽ
{
    lv_obj_t * obj = lv_event_get_target(e);           //��ȡĿ������  ��ȡ�¼������ԵĶ���
    lv_obj_t * obj2 = lv_event_get_current_target(obj);//��ȡ�����¼�����ĸ�����

    LV_LOG_USER("EVENT CNT = %d\r\n",lv_obj_get_child_cnt(obj2));//��ȡ�ܶ������
    LV_LOG_USER("EVENT ID = %d\r\n",lv_obj_get_index(obj));//��ȡ��ǰ�¼���������

    if(obj2 == Sidebar_SW_OBJ&&e->code == LV_EVENT_VALUE_CHANGED)
    {
        //lv_obj_add_event_cb(lv_obj_get_child(Sidebar_SW_OBJ, 2), switch_handler, LV_EVENT_VALUE_CHANGED, menu);
        if(lv_obj_has_state(obj, LV_STATE_CHECKED))
        {
            lv_menu_set_page(e->user_data, NULL);//�������˵�ҳ��
            lv_menu_set_sidebar_page(e->user_data, main_page);//���ò˵�ҳ����ʾ�ڲ���
            lv_event_send(lv_obj_get_child(lv_obj_get_child(lv_menu_get_cur_sidebar_page(e->user_data), 1), 0), LV_EVENT_CLICKED, NULL);
            //lv_menu_get_cur_sidebar_page  ��ȡ��ǰ��ʾ�ڲ�����еĲ˵�ҳ���ָ��
            //����¼��ص���������������
            lv_obj_add_event_cb(lv_menu_get_sidebar_header_back_btn(e->user_data), back_event_handler, LV_EVENT_CLICKED, e->user_data);
            /*�޸ı���*/
            lv_obj_t * sidebar_back_btn = lv_menu_get_sidebar_header_back_btn(e->user_data);
            lv_obj_set_style_bg_opa(sidebar_back_btn, LV_OPA_50, 0);
            lv_obj_set_style_bg_color(sidebar_back_btn, lv_color_hex(0xf00fff), 0);
            lv_obj_t * sidebar_back_btn_label = lv_label_create(sidebar_back_btn);
            lv_label_set_text(sidebar_back_btn_label, "      ");//������Ϊ�����󷵻ؼ��ĽӴ���
        }
        else
        {
            lv_menu_clear_history(e->user_data); /* �����ʷ��¼����Ϊ�����Ժ���ʾ��ҳ�� */
            lv_menu_set_sidebar_page(e->user_data, NULL);
            lv_menu_set_page(e->user_data, main_page);//�������˵�ҳ��
        }
    }
    else if(obj2 == Play_SW_OBJ&&e->code == LV_EVENT_VALUE_CHANGED)
    {

           if(lv_obj_has_state(obj, LV_STATE_CHECKED))
           {
             lv_led_on(e->user_data);
             LV_LOG_USER("LED ON\r\n");
           }
           else
           {
             LV_LOG_USER("LED OFF\r\n");
             lv_led_off(e->user_data);
           }
    }
    else if(obj2 == Volume_adjust_OBJ&&e->code == LV_EVENT_VALUE_CHANGED)
    {
          LV_LOG_USER("slider_is_dragged\r\n");
          if(lv_slider_is_dragged(obj))//������������϶�
          {
            lv_led_set_brightness(e->user_data, lv_slider_get_value(obj));
          }
    }

}


void my_settings_app(lv_obj_t *sobj)
{
    /*����һ���˵�����*/
    lv_obj_t * menu = lv_menu_create(sobj);

    lv_color_t bg_color = lv_obj_get_style_bg_color(menu, 0);
    if(lv_color_brightness(bg_color) > 127) {
        lv_obj_set_style_bg_color(menu, lv_color_darken(lv_obj_get_style_bg_color(menu, 0), 20), 0);
    }else{
        lv_obj_set_style_bg_color(menu, lv_color_darken(lv_obj_get_style_bg_color(menu, 0), 50), 0);
    }

    lv_obj_set_size(menu, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_clear_flag(sobj,LV_OBJ_FLAG_SCROLLABLE);
    lv_menu_set_mode_root_back_btn(menu, LV_MENU_ROOT_BACK_BTN_ENABLED);    //�ڵ�һ�����һ�����ؼ�
    lv_obj_add_event_cb(lv_menu_get_main_header_back_btn(menu), back_event_handler, LV_EVENT_CLICKED, menu);//����¼��ص���������������
    lv_obj_center(menu);

    /*�޸ı���*/
    lv_obj_t * back_btn = lv_menu_get_main_header_back_btn(menu);
    lv_obj_set_style_bg_opa(back_btn, LV_OPA_50, 0);
    lv_obj_set_style_bg_color(back_btn, lv_color_hex(0xf00fff), 0);
    lv_obj_t * back_btn_label = lv_label_create(back_btn);
    lv_label_set_text(back_btn_label, "      ");//������Ϊ�����󷵻ؼ��ĽӴ���



    /*������ҳ��*/
    lv_obj_t * sub_1_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_1_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);

    lv_menu_separator_create(sub_1_page);        //����һ���˵��ָ����� ����ķָ���Ϊ���붥���ֿ�һ�ξ���

    lv_obj_t * section = lv_menu_section_create(sub_1_page);//����һ���½ڵ�
    Play_SW_OBJ = create_switch(section, LV_SYMBOL_REFRESH, "Loop Playback", true,true);
    Volume_adjust_OBJ = create_slider(section, LV_SYMBOL_VOLUME_MAX, "Settings Volume", 0, 255, 100,!true);

    //ע�����ﷵ�� Volume_adjust_OBJ�Ǹ�������  ��������������ؼ���ͼ�꣬�ı��������������������淢���¼�ʱ�����͵ڣ�3-1�����Ӷ���Ҳ���ǻ�����
    create_text(sub_1_page, LV_SYMBOL_DIRECTORY, "File", LV_MENU_ITEM_BUILDER_VARIANT_1,!true,!true);

    section = lv_menu_section_create(sub_1_page);//����һ���½ڵ�
    create_text(section, LV_SYMBOL_AUDIO, "Music-1.mp3", LV_MENU_ITEM_BUILDER_VARIANT_1,true,true);
    create_text(section, LV_SYMBOL_AUDIO, "Music-2.mp3", LV_MENU_ITEM_BUILDER_VARIANT_1,true,true);
    create_text(section, LV_SYMBOL_AUDIO, "Music-3.mp3", LV_MENU_ITEM_BUILDER_VARIANT_1,true,!true);

///**************************************************************************************************/
///**************************************************************************************************/
///**************************************************************************************************/
    lv_menu_separator_create(sub_1_page);               //����һ���˵��ָ�����
    section = lv_menu_section_create(sub_1_page);       //����һ���½ڵ�
    lv_obj_t * obj= lv_obj_create(section);
    lv_obj_set_size(obj,LV_PCT(100),200);

    lv_obj_t * led1 = lv_led_create(obj);
    lv_led_set_color(led1, lv_color_hex(0xffff00));
    lv_obj_align(led1,LV_ALIGN_CENTER,0,0);
    lv_obj_t * led2 = lv_led_create(obj);
    lv_led_set_color(led2, lv_color_hex(0xff00ff));
    lv_led_set_brightness(led2, lv_slider_get_value(lv_obj_get_child(Volume_adjust_OBJ, 2)));
    lv_obj_align_to(led2,led1,LV_ALIGN_OUT_RIGHT_MID,0,0);
    lv_obj_add_event_cb(lv_obj_get_child(Play_SW_OBJ, 2), switch_handler, LV_EVENT_VALUE_CHANGED, led1);//�����¼��ص�����
    lv_obj_add_event_cb(lv_obj_get_child(Volume_adjust_OBJ, 2), switch_handler, LV_EVENT_VALUE_CHANGED, led2);//�����¼��ص�����


    lv_obj_set_style_bg_color(led1, lv_color_hex(0x0), LV_PART_INDICATOR);
    lv_obj_set_style_bg_grad_color(led1, lv_color_hex(0x0), LV_PART_INDICATOR);
    lv_obj_set_style_bg_grad_dir(led1, LV_GRAD_DIR_VER, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(led1, LV_OPA_100 ,LV_PART_MAIN);
    lv_obj_set_style_shadow_color(led1, lv_color_hex(0x111111),LV_PART_MAIN);
    lv_obj_set_style_shadow_width(led1, 5,LV_PART_MAIN);
    lv_obj_set_style_shadow_opa(led1, LV_OPA_50,LV_PART_MAIN);

    lv_obj_set_style_bg_color(led2, lv_color_hex(0x0), LV_PART_INDICATOR);
    lv_obj_set_style_bg_grad_color(led2, lv_color_hex(0x0), LV_PART_INDICATOR);
    lv_obj_set_style_bg_grad_dir(led2, LV_GRAD_DIR_VER, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(led2, LV_OPA_100 ,LV_PART_MAIN);
    lv_obj_set_style_shadow_color(led2, lv_color_hex(0x111111),LV_PART_MAIN);
    lv_obj_set_style_shadow_width(led2, 5,LV_PART_MAIN);
    lv_obj_set_style_shadow_opa(led2, LV_OPA_50,LV_PART_MAIN);
///**************************************************************************************************/
///**************************************************************************************************/
///**************************************************************************************************/

    lv_obj_t * sub_2_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_2_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_2_page);        //����һ���˵��ָ����� ����ķָ���Ϊ���붥���ֿ�һ�ξ���
    section = lv_menu_section_create(sub_2_page);//����һ���½ڵ�
    create_text(section, LV_SYMBOL_IMAGE, "Picture-1.png", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_IMAGE, "Picture-2.png", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_IMAGE, "Picture-3.png", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_IMAGE, "Picture-4.png", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_IMAGE, "Picture-5.png", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_IMAGE, "Picture-6.png", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_IMAGE, "Picture-7.png", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_IMAGE, "Picture-8.png", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_IMAGE, "Picture-9.png", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_IMAGE, "Picture-10.png", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_IMAGE, "Picture-11.png", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_IMAGE, "Picture-12.png", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_IMAGE, "Picture-13.png", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_IMAGE, "Picture-14.png", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_IMAGE, "Picture-15.png", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_IMAGE, "Picture-16.png", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_IMAGE, "Picture-17.png", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_IMAGE, "Picture-18.png", LV_MENU_ITEM_BUILDER_VARIANT_1,1,0);



    lv_obj_t * sub_3_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_3_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_3_page);        //����һ���˵��ָ����� ����ķָ���Ϊ���붥���ֿ�һ�ξ���
    section = lv_menu_section_create(sub_3_page);//����һ���½ڵ�
    create_text(section, LV_SYMBOL_VIDEO, "Video-1.mp4", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_VIDEO, "Video-2.mp4", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_VIDEO, "Video-3.mp4", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_VIDEO, "Video-4.mp4", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_VIDEO, "Video-5.mp4", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_VIDEO, "Video-6.mp4", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_VIDEO, "Video-7.mp4", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_VIDEO, "Video-8.mp4", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_VIDEO, "Video-9.mp4", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_VIDEO, "Video-10.mp4", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_VIDEO, "Video-11.mp4", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_VIDEO, "Video-12.mp4", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_VIDEO, "Video-13.mp4", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_VIDEO, "Video-14.mp4", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_VIDEO, "Video-15.mp4", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_VIDEO, "Video-16.mp4", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_VIDEO, "Video-17.mp4", LV_MENU_ITEM_BUILDER_VARIANT_1,1,1);
    create_text(section, LV_SYMBOL_VIDEO, "Video-18.mp4", LV_MENU_ITEM_BUILDER_VARIANT_1,1,0);



    lv_obj_t * sub_4_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_4_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_4_page);        //����һ���˵��ָ�����  ����ķָ���Ϊ���붥���ֿ�һ�ξ���
    section = lv_menu_section_create(sub_4_page);//����һ���½ڵ�
    Sidebar_SW_OBJ = create_switch(section, LV_SYMBOL_SETTINGS, "Sidebar enable", true,!true);
    lv_obj_add_event_cb(lv_obj_get_child(Sidebar_SW_OBJ, 2), switch_handler, LV_EVENT_VALUE_CHANGED, menu);
    /**< ������ͼ�꣬�ı�����SW���أ�������������Ҫ��ȡSW����״̬�����Դ���ڣ�3-1�����Ӷ��� */





    /*����һ����ҳ*/
    main_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(main_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);

    create_text(main_page, NULL, "General", LV_MENU_ITEM_BUILDER_VARIANT_1,!true,!true);
    section = lv_menu_section_create(main_page);//����һ���½ڵ�

    lv_obj_t * cont_1 = create_text(section, LV_SYMBOL_AUDIO, "Music", LV_MENU_ITEM_BUILDER_VARIANT_1,true,true);
    lv_menu_set_load_page_event(menu, cont_1, sub_1_page);//��˵�����Ӳ˵�

    lv_obj_t * cont_2 = create_text(section, LV_SYMBOL_IMAGE, "Image", LV_MENU_ITEM_BUILDER_VARIANT_1,true,true);
    lv_menu_set_load_page_event(menu, cont_2, sub_2_page);//��˵�����Ӳ˵�

    lv_obj_t * cont_3 = create_text(section, LV_SYMBOL_VIDEO, "Video", LV_MENU_ITEM_BUILDER_VARIANT_1,true,!true);
    lv_menu_set_load_page_event(menu, cont_3, sub_3_page);//��˵�����Ӳ˵�


    create_text(main_page, NULL, "Others", LV_MENU_ITEM_BUILDER_VARIANT_1,!true,!true);
    section = lv_menu_section_create(main_page);//����һ���½ڵ�  ������ķֿ�

    lv_obj_t * cont_4 = create_text(section, LV_SYMBOL_SETTINGS, "Mode Set", LV_MENU_ITEM_BUILDER_VARIANT_1,true,!true);
    lv_menu_set_load_page_event(menu, cont_4, sub_4_page);//��˵�����Ӳ˵�


#if  1
    lv_menu_set_sidebar_page(menu, main_page);//���ò˵�ҳ����ʾ�ڲ���
    lv_event_send(lv_obj_get_child(lv_obj_get_child(lv_menu_get_cur_sidebar_page(menu), 1), 0), LV_EVENT_CLICKED, NULL);
    /*����һ������¼�*/
#else
    lv_menu_set_page(menu, main_page);
#endif

    //����¼��ص���������������
    lv_obj_add_event_cb(lv_menu_get_sidebar_header_back_btn(menu), back_event_handler, LV_EVENT_CLICKED, menu);
    /*�޸ı���*/
    lv_obj_t * sidebar_back_btn = lv_menu_get_sidebar_header_back_btn(menu);
    lv_obj_set_style_bg_opa(sidebar_back_btn, LV_OPA_50, 0);
    lv_obj_set_style_bg_color(sidebar_back_btn, lv_color_hex(0xf00fff), 0);
    lv_obj_t * sidebar_back_btn_label = lv_label_create(sidebar_back_btn);
    lv_label_set_text(sidebar_back_btn_label, "      ");//������Ϊ�����󷵻ؼ��ĽӴ���
}





