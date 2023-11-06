// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keymap_definitions.h"



#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┐
     * │ A │ B │ C │ D │ E │
     * ├───┼───┼───┼───┼───┤
     * │ F │ G │ H │ I │ J │
     * ├───┼───┼───┼───┼───┤
     * │ K │ L │ M │ N │ O │
     * └───┴───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_5x3(
        FR_A,   FR_B,   FR_C,   FR_D, FR_E,
        FR_F,   FR_G,   FR_H,   FR_I, FR_J,
        FR_K,   FR_L,   FR_M,   FR_N, FR_O
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP)}
    // [1] =   { ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    // [2] =   { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    // [3] =   { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)},
    //                  Encoder 1                                     Encoder 2
};
#endif

