#include <avr/pgmspace.h>
#include "actionmap.h"
#include "actionmap_common.h"
#include "action_util.h"
#include "action_code.h"
#include "action_layer.h"
#include "wait.h"

#include <avr/wdt.h>

/* id for user defined functions */
enum function_id {
    RESET_LAYER_STATE,
    PROMICRO_RESET,
    PROMICRO_PROGRAM,
};

#define AC_FN0            AC_TRNS
#define AC_FN1            ACTION_LAYER_MOMENTARY(1)
#define AC_FN2            ACTION_LAYER_MOMENTARY(2)
#define AC_FN3            ACTION_LAYER_SET_CLEAR(0)

#define AC_W_CAP          ACTION_MODS_TAP_KEY(MOD_LGUI, KC_CAPS)
#define AC_S_SFT          ACTION_MODS_TAP_KEY(MOD_LSFT, ACTION_MODS_ONESHOT(MOD_LSFT))
#define AC_SFCTL          ACTION_MODS(MOD_LCTL | MOD_LSFT)
#define AC_F1_F           ACTION_LAYER_TAP_KEY(1, KC_F)
#define AC_F1_J           ACTION_LAYER_TAP_KEY(1, KC_J)
#define AC_F2_K           ACTION_LAYER_TAP_KEY(2, KC_K)
#define AC_F2_D           ACTION_LAYER_TAP_KEY(2, KC_D)
#define AC_F3_S           ACTION_LAYER_TAP_KEY(3, KC_S)
#define AC_F3_L           ACTION_LAYER_TAP_KEY(3, KC_L)
#define AC_LRBR           ACTION_MODS_KEY(MOD_LSFT, KC_9)
#define AC_RRBR           ACTION_MODS_KEY(MOD_LSFT, KC_0)
#define AC_DQUOT          ACTION_MODS_KEY(MOD_LSFT, KC_QUOTE)

/* for layer 2 */
#define AC_EXCL             ACTION_MODS_KEY(MOD_LSFT, KC_1)
#define AC_QUES             ACTION_MODS_KEY(MOD_LSFT, KC_SLSH)
#define AC_AMPS             ACTION_MODS_KEY(MOD_LSFT, KC_7)
#define AC_DOLA             ACTION_MODS_KEY(MOD_LSFT, KC_4)
#define AC_AT               ACTION_MODS_KEY(MOD_LSFT, KC_2)
#define AC_STAR             ACTION_MODS_KEY(MOD_LSFT, KC_8)
#define AC_HASH             ACTION_MODS_KEY(MOD_LSFT, KC_3)
#define AC_VBAR             ACTION_MODS_KEY(MOD_LSFT, KC_BSLS)
#define AC_CARE             ACTION_MODS_KEY(MOD_LSFT, KC_6)
#define AC_PERC             ACTION_MODS_KEY(MOD_LSFT, KC_5)
#define AC_CAPB             ACTION_MODS_KEY(MOD_LSFT, KC_B)
#define AC_CAPY             ACTION_MODS_KEY(MOD_LSFT, KC_Y)
#define AC_CAPO             ACTION_MODS_KEY(MOD_LSFT, KC_O)
#define AC_CAPU             ACTION_MODS_KEY(MOD_LSFT, KC_U)
#define AC_LANG             ACTION_MODS_KEY(MOD_LSFT, KC_COMM)
#define AC_RANG             ACTION_MODS_KEY(MOD_LSFT, KC_DOT)
#define AC_CAPL             ACTION_MODS_KEY(MOD_LSFT, KC_L)
#define AC_CAPD             ACTION_MODS_KEY(MOD_LSFT, KC_D)
#define AC_CAPW             ACTION_MODS_KEY(MOD_LSFT, KC_W)
#define AC_CAPV             ACTION_MODS_KEY(MOD_LSFT, KC_V)
#define AC_CAPC             ACTION_MODS_KEY(MOD_LSFT, KC_C)
#define AC_CAPI             ACTION_MODS_KEY(MOD_LSFT, KC_I)
#define AC_CAPE             ACTION_MODS_KEY(MOD_LSFT, KC_E)
#define AC_CAPA             ACTION_MODS_KEY(MOD_LSFT, KC_A)
#define AC_COLN             ACTION_MODS_KEY(MOD_LSFT, KC_SCLN)
#define AC_CAPH             ACTION_MODS_KEY(MOD_LSFT, KC_H)
#define AC_CAPT             ACTION_MODS_KEY(MOD_LSFT, KC_T)
#define AC_CAPS             ACTION_MODS_KEY(MOD_LSFT, KC_S)
#define AC_CAPN             ACTION_MODS_KEY(MOD_LSFT, KC_N)
#define AC_TILD             ACTION_MODS_KEY(MOD_LSFT, KC_GRV)
#define AC_CAPG             ACTION_MODS_KEY(MOD_LSFT, KC_G)
#define AC_CAPX             ACTION_MODS_KEY(MOD_LSFT, KC_X)
#define AC_CAPJ             ACTION_MODS_KEY(MOD_LSFT, KC_J)
#define AC_CAPK             ACTION_MODS_KEY(MOD_LSFT, KC_K)
#define AC_UNDS             ACTION_MODS_KEY(MOD_LSFT, KC_MINS)
#define AC_PLUS             ACTION_MODS_KEY(MOD_LSFT, KC_EQL)
#define AC_CAPR             ACTION_MODS_KEY(MOD_LSFT, KC_R)
#define AC_CAPM             ACTION_MODS_KEY(MOD_LSFT, KC_M)
#define AC_CAPF             ACTION_MODS_KEY(MOD_LSFT, KC_F)
#define AC_CAPP             ACTION_MODS_KEY(MOD_LSFT, KC_P)
#define AC_CAPQ             ACTION_MODS_KEY(MOD_LSFT, KC_Q)
#define AC_CAPZ             ACTION_MODS_KEY(MOD_LSFT, KC_Z)

#define AC_PROMICRO_PROGRAM  ACTION_FUNCTION_TAP(PROMICRO_PROGRAM)
#define AC_PROMICRO_RESET    ACTION_FUNCTION_TAP(PROMICRO_RESET)

// TODO ctrl space
// TODO arrow keys in layer 1 to be shifted one key to the right
const uint16_t PROGMEM actionmaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* engram */
    [0] = ACTIONMAP(
        /* left hand */
            ESC  , 1    , 2    , 3    , 4    , 5    ,
            TAB  , B    , Y    , O    , U    , QUOT ,
            FN2  , C    , I    , E    , A    , COMM ,
            GRV  , G    , X    , J    , K    , MINS ,
            FN1  , LGUI , LALT  , LCTL, LRBR , SPC  ,
        /* right hand */
            6    , 7    , 8    , 9    , 0    , PSCR ,
            DQUOT, L    , D    , W    , V    , SLSH ,
            DOT  , H    , T    , S    , N    , FN2 ,
            EQUAL, R    , M    , F    , P    , Q    ,
            BSPC , RRBR , RCTL , ENT  , Z    , FN1
    ),
    /* fn */
    [1] = ACTIONMAP(
        /* left hand */
            F1   , F2   , F3   , F4   , F5   , F6   ,
            TRNS , MUTE , VOLU , UP   , HOME , TRNS ,
            TRNS , CAPS , LEFT , DOWN , RIGHT, TRNS ,
            TRNS , TRNS , VOLD , TRNS , END  , TRNS ,
            TRNS , TRNS , TRNS , TRNS , LSFT , TRNS ,
        /* right hand */
			F7   , F8   , F9   , F10  , F11  , F12  ,
			INS  , HOME , UP   , PGUP , PAUS , TRNS ,
			DEL  , LEFT , DOWN , RIGHT, TRNS , TRNS ,
            SLCK , END  , MENU , PGDN , TRNS , TRNS ,
            TRNS , RSFT , TRNS , RALT , TRNS , TRNS
        ),
    /* fn + shift */
    [2] = ACTIONMAP(
        /* left hand */
            TRNS , EXCL , QUES , AMPS , DOLA , AT   ,
            TRNS , CAPB , CAPY , CAPO , CAPU , LANG ,
            TRNS , CAPC , CAPI , CAPE , CAPA , SCLN ,
            TILD , CAPG , CAPX , CAPJ , CAPK , UNDS ,
            LSFT , TRNS , TRNS , TRNS , LBRC , TRNS ,
        /* right hand */
			STAR , HASH , VBAR , CARE , PERC , TRNS ,
            RANG , CAPL , CAPD , CAPW , CAPV , BSLS ,
            COLN , CAPH , CAPT , CAPS , CAPN , TRNS ,
            PLUS , CAPR , CAPM , CAPF , CAPP , CAPQ ,
            TRNS , RBRC , TRNS , TRNS , CAPZ , RSFT
        ),
}; 
