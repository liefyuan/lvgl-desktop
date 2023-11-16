MY_APP_DIR_NAME ?= my_app

override CFLAGS := -I$(LVGL_DIR) $(CFLAGS)

CSRCS += $(wildcard $(LVGL_DIR)/$(MY_APP_DIR_NAME)/*.c)
CSRCS += $(wildcard $(LVGL_DIR)/$(MY_APP_DIR_NAME)/my_about_app/*.c)
CSRCS += $(wildcard $(LVGL_DIR)/$(MY_APP_DIR_NAME)/my_calc_app/*.c)
CSRCS += $(wildcard $(LVGL_DIR)/$(MY_APP_DIR_NAME)/my_clock_app/*.c)
CSRCS += $(wildcard $(LVGL_DIR)/$(MY_APP_DIR_NAME)/my_clock_app/assets/*.c)

CSRCS += $(wildcard $(LVGL_DIR)/$(MY_APP_DIR_NAME)/my_desktop/*.c)
CSRCS += $(wildcard $(LVGL_DIR)/$(MY_APP_DIR_NAME)/my_desktop/assets/*.c)

CSRCS += $(wildcard $(LVGL_DIR)/$(MY_APP_DIR_NAME)/my_music_app/*.c)
CSRCS += $(wildcard $(LVGL_DIR)/$(MY_APP_DIR_NAME)/my_music_app/assets/*.c)

CSRCS += $(wildcard $(LVGL_DIR)/$(MY_APP_DIR_NAME)/my_QRcode_app/*.c)
CSRCS += $(wildcard $(LVGL_DIR)/$(MY_APP_DIR_NAME)/my_QRcode_app/assets/*.c)

CSRCS += $(wildcard $(LVGL_DIR)/$(MY_APP_DIR_NAME)/my_settings_app/*.c)
CSRCS += $(wildcard $(LVGL_DIR)/$(MY_APP_DIR_NAME)/my_settings_app/assets/*.c)

CSRCS += $(wildcard $(LVGL_DIR)/$(MY_APP_DIR_NAME)/my_temp_app/*.c)
CSRCS += $(wildcard $(LVGL_DIR)/$(MY_APP_DIR_NAME)/my_temp_app/assets/*.c)

CSRCS += $(wildcard $(LVGL_DIR)/$(MY_APP_DIR_NAME)/my_widget_app/*.c)
CSRCS += $(wildcard $(LVGL_DIR)/$(MY_APP_DIR_NAME)/my_widget_app/assets/*.c)

