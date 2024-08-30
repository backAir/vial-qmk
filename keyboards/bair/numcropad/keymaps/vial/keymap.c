// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keymap_definitions.h"
#include QMK_KEYBOARD_H
#include "quantum.h"
// #include "gpio.h"
// #include "i2c.h"


// #include "config.h"

enum custom_keycodes {
    KC_P00 = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │TG1│ / │ * │ - │
     * ├───┼───┼───┼───┤
     * │ 7 │ 8 │ 9 │ + │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ % │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ = │
     * ├───┼───┼───┼───┤
     * │ 0 │00 │ . │Ent│
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_5x4(
        FR_A,   FR_B,  FR_C,   FR_D,
        FR_E,   FR_F,  FR_G,   FR_H,
        FR_I,   FR_J,  FR_K,   FR_L,
        FR_M,   FR_N,  FR_O,   FR_P,
        FR_Q,   FR_R,  FR_S,   FR_T
    ),
    // [0] = LAYOUT_ortho_5x4(
    //     TG(1),   KC_PSLS, KC_PAST, KC_PMNS,
    //     KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    //     KC_P4,   KC_P5,   KC_P6,   KC_PERC,
    //     KC_P1,   KC_P2,   KC_P3,   KC_EQL,
    //     KC_P0,   KC_P00,  KC_PDOT, KC_PENT
    // ),

    /*
     * ┌───┬───┬───┬───┐
     * │TG1│ / │ * │ - │
     * ┌───┬───┬───┐───┤
     * │Hom│ ↑ │PgU│ + │
     * ├───┼───┼───┤───┤
     * │ ← │   │ → │ % │
     * ├───┼───┼───┤───┤
     * │End│ ↓ │PgD│ = │
     * ├───┼───┼───┤───┤
     * │Ins│   │Del│Ent│
     * └───┴───┴───┘───┘
     */
    // [1] = LAYOUT_ortho_5x4(
    //     _______, _______, _______, _______,
    //     KC_HOME, KC_UP,   KC_PGUP, _______,
    //     KC_LEFT, XXXXXXX, KC_RGHT, _______,
    //     KC_END,  KC_DOWN, KC_PGDN, _______,
    //     KC_INS,  XXXXXXX, KC_DEL,  _______
    // )
};




#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), // Encoder 0
            },
};
#endif



void matrix_init_user(void) {
    // Set the pin as an output
    setPinOutput(GP13);
}

bool toggled = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    switch (keycode) {
        case FR_A:
            if (record->event.pressed) {
                if(toggled){
                    writePinLow(GP13);
                    toggled = false;
                }else{
                    writePinHigh(GP13);
                    toggled = true;
                }
                return false;
            }

            break;
    }
    return true;
}


#ifdef OLED_ENABLE

    oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        return OLED_ROTATION_270;
    }
    // bool oled_task_user() {

    //     oled_set_cursor(0, 1);

    //     oled_write("Hello, world!", false);

    //     return false;
    // }


    bool oled_task_user(void) {
        // Host Keyboard Layer Status
        oled_write_P(PSTR("elooo: "), false);
        oled_write_ln_P(PSTR("Undefined"), false);


        // Host Keyboard LED Status
        // led_t led_state = host_keyboard_led_state();
        // oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
        // oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
        // oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

        return false;
    }
#endif
