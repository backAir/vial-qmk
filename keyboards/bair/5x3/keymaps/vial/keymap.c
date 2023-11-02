// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

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
        KC_A,   KC_B,   KC_C,   KC_D, KC_E,
        KC_F,   KC_G,   KC_H,   KC_I, KC_J,
        KC_K,   KC_L,   KC_M,   KC_N, KC_O
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)}
    // [1] =   { ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    // [2] =   { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    // [3] =   { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)},
    //                  Encoder 1                                     Encoder 2
};
#endif

