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


// #ifdef OLED_ENABLE

//     oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//         return OLED_ROTATION_270;
//     }
//     // bool oled_task_user() {

//     //     oled_set_cursor(0, 1);

//     //     oled_write("Hello, world!", false);

//     //     return false;
//     // }


//     bool oled_task_user(void) {
//         // Host Keyboard Layer Status
//         // Host Keyboard Layer Status
//         oled_write_ln_P(PSTR("ANAVI Knob 1"), false);
//         oled_write_ln_P(PSTR("Keymap: Default"), false);

//         return false;
//     }
// #endif



// logo
#define ACH_LOGO { \
        0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0x20, \
        0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0x20, \
        0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0x20, \
        0x00 \
}


#ifdef OLED_ENABLE

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    // if (is_keyboard_master()) {
    //     return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    // }

    return rotation;
}


bool render_status(void) {
    static const char PROGMEM atreus_logo[] = ACH_LOGO;
    oled_write_P(atreus_logo, false);
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("QWERTY\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("MEDIA\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("NAV\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("SYM\n"), false);
            break;
        case 4:
            oled_write_P(PSTR("NUM \n"), false);
            break;
        case 5:
            oled_write_P(PSTR("FUN\n"), false);
            break;
        case 6:
            oled_write_P(PSTR("BUTTON\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.caps_lock ? PSTR("\rCaps: ON  ") : PSTR("\rCaps: OFF  "), false);


    return false;
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    // if (is_keyboard_master()) {
    render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    // }
    return false;
}

#endif
