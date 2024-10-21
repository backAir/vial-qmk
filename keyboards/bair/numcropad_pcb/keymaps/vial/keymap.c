// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdlib.h>
#include "keymap_definitions.h"
#include QMK_KEYBOARD_H
#include "quantum.h"
// #include "gpio.h"
// #include "i2c.h"

#include "timer.h"



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
        KC_MUTE,   FR_A,  FR_B,   FR_C,
        KC_NUM_LOCK,   KC_KP_SLASH,  KC_KP_ASTERISK,   KC_BACKSPACE,
        FR_D,   FR_E,  KC_KP_7,   KC_KP_8,  KC_KP_9,   KC_KP_MINUS,
        FR_F,   FR_G,  KC_KP_4,   KC_KP_5,  KC_KP_6,   KC_KP_PLUS,
        FR_H,   FR_I,  KC_KP_1,   KC_KP_2,  KC_KP_3,
        FR_J, FR_K,  QK_BOOTLOADER,  KC_KP_DOT,   KC_KP_ENTER

    )
    // [0] = LAYOUT_ortho_5x4(
    //     TG(1),   KC_PSLS, KC_PAST, KC_PeMNS,
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
// #define OLED_ENABLE
#if defined(OLED_ENABLE)
#include "oled.h"
static uint8_t oled_buffer[128 * 32 / 8] = {0};
static bool oled_update_required = false;


void matrix_init_user(void) {
    memset(oled_buffer, 0, sizeof(oled_buffer));
    // Set the pin as an output
    setPinOutput(GP1);
}

bool toggled = false;
bool blinking = false;
uint16_t blink_timer = 0;
const uint16_t BLINK_INTERVAL = 500; // Blink interval in milliseconds
int stupid_logo = false;
int x = 0;
int y = 0;


bool process_record_user(uint16_t keycode, keyrecord_t *record){
    if(!record->event.pressed){
        return false;
    }
    switch (keycode) {
        case FR_A:
            oled_buffer[0] = 0xFF;
            oled_buffer[10] = 0x00;
            oled_update_required = true;
        break;
        case FR_B:
            oled_buffer[0] = 0x00;
            oled_buffer[10] = 0xFF;
            oled_update_required = true;
        break;
        case FR_C:
            for (size_t i = 0; i < 10; i++)
            {
                bool in_bound = y < 128;
                if(in_bound){
                    write_to_oled_buffer(x,y,true);
                    oled_update_required = true;
                    x++;
                    if (x >= OLED_WIDTH) {
                        x = 0;
                        y++;
                    }
                }
            }
        break;
        case QK_BOOTLOADER:
            return true;
    }
    return false;
}

void matrix_scan_user(void) {
    if (blinking) {
        if (timer_elapsed(blink_timer) > BLINK_INTERVAL) {
            blink_timer = timer_read();
            if (readPin(GP1)) {
                writePinLow(GP1);
            } else {
                writePinHigh(GP1);
            }
        }
    }
}


static void write_to_oled_buffer(uint8_t x, uint8_t y, bool on){
    if (x >= OLED_WIDTH || y >= OLED_HEIGHT) {
        return; // Out of bounds
    }

    uint16_t index = (y / 8) * OLED_WIDTH + x;
    uint8_t bit = 1 << (y % 8);

    if (on) {
        oled_buffer[index] |= bit; // Set the bit to turn the pixel on
    } else {
        oled_buffer[index] &= ~bit; // Clear the bit to turn the pixel off
    }
}





oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}




bool oled_task_kb(void) {
    if (oled_update_required) {
        oled_write_raw((char*)oled_buffer, sizeof(oled_buffer));
        oled_update_required = false;
    }
    return false;
}

#endif
