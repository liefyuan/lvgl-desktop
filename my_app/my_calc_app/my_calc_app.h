#ifndef MY_CALC_APP_H
#define MY_CALC_APP_H

#ifdef __cplusplus
extern "C" {
#endif


/*********************
 *      INCLUDES
 *********************/
#include "../lv_100ask.h"


/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
// Calculation expression
#define LV_100ASK_CALC_EXPR_LEN                            (128) // 允许表达式的最大长度
#define LV_100ASK_CALC_MAX_NUM_LEN                         (32)   // 允许运算数的最大长度

#define LV_100ASK_CALC_HISTORY_MAX_LINE     (128)

/*********************
 *      TYPEDEF
 *********************/
// 标记符
typedef enum {
    TOKENIZER_ERROR,        // Error
    TOKENIZER_ENDOFINPUT,   // End of input
    TOKENIZER_NUMBER,       // number
    TOKENIZER_PLUS,         // +
    TOKENIZER_MINUS,        // -
    TOKENIZER_ASTR,         // *
    TOKENIZER_SLASH,        // /
    TOKENIZER_LPAREN,       // (
    TOKENIZER_RPAREN,       // )
} token_t;

//  错误代码
typedef enum {
    no_error = 0,           // no error
    syntax_error,           // syntax error
} error_t;

// 错误代码与对应的消息
typedef struct {
    error_t error_code;
    char *message;
} error_table_t;


/**********************
 * GLOBAL PROTOTYPES
 **********************/
void my_calc_app(lv_obj_t *obj);





/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_100ASK_STM32_TOOL_CALC_H */





