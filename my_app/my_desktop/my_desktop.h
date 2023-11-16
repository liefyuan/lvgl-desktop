/**
 * @file 
 *
 */

#ifndef MY_DESKTOP_H
#define MY_DESKTOP_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lv_100ask.h"



/**********************
 *      TYPEDEFS
 **********************/


/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lv_start_demo(uint32_t delay);
void lv_demo_home(uint32_t delay);

lv_obj_t * lv_create_back_btn(char *title);
/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
