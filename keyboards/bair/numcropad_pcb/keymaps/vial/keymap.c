// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdlib.h>
#include <string.h>
#include "keymap_definitions.h"
#include QMK_KEYBOARD_H
#include "quantum.h"
// #include "gpio.h"
// #include "i2c.h"

#include "timer.h"

// enum layer_names
// {
//     Base,
//     Two,
//     Three,
//     RGB
// };

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
        0x5203,   FR_E, KC_NUM_LOCK,   KC_KP_SLASH,  KC_KP_ASTERISK,   KC_BACKSPACE,
        FR_F,   FR_G,  KC_KP_7,   KC_KP_8,  KC_KP_9,   KC_KP_MINUS,
        FR_H,   FR_I,  KC_KP_4,   KC_KP_5,  KC_KP_6,   KC_KP_PLUS,
        FR_J,   FR_K,  KC_KP_1,   KC_KP_2,  KC_KP_3,
        FR_L,   FR_M,  KC_KP_0,  KC_KP_DOT,   KC_KP_ENTER
    ),
    [3] = LAYOUT_ortho_5x4(
        QK_UNDERGLOW_TOGGLE,   RGB_MODE_PLAIN,  QK_UNDERGLOW_MODE_PREVIOUS,   QK_UNDERGLOW_MODE_NEXT,
        0x5200,   0, QK_UNDERGLOW_SATURATION_DOWN,   QK_UNDERGLOW_SATURATION_UP,  QK_UNDERGLOW_VALUE_DOWN,   QK_UNDERGLOW_VALUE_UP,
        0,   0,  0,   0,  QK_UNDERGLOW_SPEED_DOWN,   QK_UNDERGLOW_SPEED_UP,
        0,   0,  0,   0,  0,   0,
        0,   0,  0,   0,  0,
        0,   0,  0,  0,   QK_BOOTLOADER
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





led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {   NO_LED, 4, 10,   16 },
  { NO_LED,NO_LED, 0,5,11,17 },
  { NO_LED,NO_LED, 1,6,12,18 },
  { NO_LED,NO_LED, 2,7,13,19 },
  { NO_LED,NO_LED, 3,8,14 },
  { NO_LED,NO_LED, 9,15,20 }
}, {
  // LED Index to Physical Position
  { 188,  16 }, { 187,  48 }, { 149,  64 }, { 112,  64 }, {  37,  48 }, {  38,  16 },
  { 188,  16 }, { 187,  48 }, { 149,  64 }, { 112,  64 }, {  37,  48 }, {  38,  16 },
  { 188,  16 }, { 187,  48 }, { 149,  64 }, { 112,  64 }, {  37,  48 }, {  38,  16 },
  { 188,  16 }, { 187,  48 }, { 149,  64 }
}, {
  // LED Index to Flag
  1, 4, 4, 4, 4, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
} };

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), // Encoder 0
            },
    [3] =   { ENCODER_CCW_CW(QK_UNDERGLOW_HUE_DOWN, QK_UNDERGLOW_HUE_UP), // Encoder 0
            },
};
#endif

#define RGB_WHITE       0xFF, 0xFF, 0xFF

// #define OLED_ENABLE
#if defined(OLED_ENABLE)
#include "oled.h"
static uint8_t oled_buffer[128 * 32 / 8] = {0};
static bool oled_update_required = false;


#define ACH_LOGO { \
        0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0x20, \
        0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0x20, \
        0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0x20, \
        0x00 \
}


void matrix_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_GRADIENT_UP_DOWN);
    // static const char PROGMEM atreus_logo[] = ACH_LOGO;

    memset(oled_buffer, 0, sizeof(oled_buffer));
    memcpy(oled_buffer, PUFF,sizeof(char)*128);
    // memset(ACH_LOGO, 0, sizeof(oled_buffer));
    oled_update_required = true;
    rgblight_enable_noeeprom(); // enables Rgb, without saving settings
    rgblight_sethsv_noeeprom(HSV_WHITE);
    // Set the pin as an output
    // setPinOutput(GP1);
}

bool toggled = false;
bool blinking = false;
uint16_t blink_timer = 0;
const uint16_t BLINK_INTERVAL = 500; // Blink interval in milliseconds
int stupid_logo = false;
int x = 0;
int y = 0;


bool process_record_user(uint16_t keycode, keyrecord_t *record){

    // if(!record->event.pressed){
    //     return true;
    // }
    // switch (keycode) {
    //     case FR_A:
    //         oled_buffer[0] = 0xFF;
    //         oled_buffer[10] = 0x00;
    //         oled_update_required = true;
    //     break;
    //     case FR_B:
    //         oled_buffer[0] = 0x00;
    //         oled_buffer[10] = 0xFF;
    //         oled_update_required = true;
    //     break;
    //     case FR_C:
    //         for (size_t i = 0; i < 10; i++)
    //         {
    //             bool in_bound = y < 128;
    //             if(in_bound){
    //                 write_to_oled_buffer(x,y,true);
    //                 oled_update_required = true;
    //                 x++;
    //                 if (x >= OLED_WIDTH) {
    //                     x = 0;
    //                     y++;
    //                 }
    //             }
    //         }
    //     break;
    //     case QK_BOOTLOADER:
    //         return true;
    // }
    return true;
}


// Custom code to run on layer change
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 0:
            // memset(oled_buffer, 0, sizeof(oled_buffer));
            memcpy(oled_buffer, PUFF,sizeof(char)*128);
            break;
        case 3:
            memset(oled_buffer, 0, sizeof(char)*32);
            memcpy(oled_buffer+32, RGB_LOGO,sizeof(char)*(64));
            memset(oled_buffer+32+64, 0, sizeof(char)*32);
            break;
        // Add cases for other layers as needed
        default:
            break;
    }
    oled_update_required = true;
    return state;
}

void matrix_scan_user(void) {
    if (blinking) {
        if (timer_elapsed(blink_timer) > BLINK_INTERVAL) {
            blink_timer = timer_read();
            // if (readPin(GP1)) {
            //     writePinLow(GP1);
            // } else {
            //     writePinHigh(GP1);
            // }
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
    write_to_oled_buffer(0,0,0);
    return OLED_ROTATION_270;
}




// bool oled_task_user(void) {
// // bool oled_task_kb(void) {

//     if (oled_update_required) {
//         oled_write_raw((char*)oled_buffer, sizeof(oled_buffer));
//         // oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
//         oled_update_required = false;
//     }
//     return false;
// }
bool oled_task_user(void) {
    // Set cursor position
    if (oled_update_required) {
        oled_write_raw((char*)oled_buffer, sizeof(oled_buffer));
        oled_update_required = false;
    }
    oled_set_cursor(32, 1);
    // Caps lock status
    led_t led_state = host_keyboard_led_state();
    // oled_write_P(led_state.num_lock ? PSTR("Num On ") : PSTR("Num Off"), false);
    // if (led_state.num_lock){

    // }else
    // {

    // }

    uint8_t num_lock_led_index = 0;
    //turns off numlock led when off
    if (!led_state.num_lock) {
        rgb_matrix_set_color(num_lock_led_index, RGB_OFF);
    }

    return false;
}

#endif
