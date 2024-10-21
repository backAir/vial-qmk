// Copyright 2024 Anthony (@bair)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */
#define VIAL_KEYBOARD_UID {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF1}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 3 }
#define VIAL_UNLOCK_COMBO_COLS { 3, 3 }



#define LED_CAPS_LOCK_PIN GP0

// #undef I2C1_SCL_PIN
// #undef I2C1_SDA_PIN

#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN GP15
#define I2C1_SDA_PIN GP14
#define OLED_BRIGHTNESS 128

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X32
// #    define OLED_FONT_H "./lib/glcdfont.c"
#    define OLED_TIMEOUT 30000
#endif // OLED_ENABLE

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

#define FLASH_SIZE 0x1000000

#define VIAL_MACRO_COUNT 64


// #define WEAR_LEVELING_BACKING_SIZE 2000000
// #define WEAR_LEVELING_LOGICAL_SIZE 1000000

// #undef WEAR_LEVELING_RP2040_FLASH_SIZE
// #define WEAR_LEVELING_RP2040_FLASH_SIZE 16000000

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
