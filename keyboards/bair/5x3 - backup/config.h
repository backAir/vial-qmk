// Copyright 2023 Anthony (@backAir)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */
#define VIAL_KEYBOARD_UID {0xE1, 0x6B, 0x7F, 0xD8, 0x1D, 0xA0, 0x3E, 0x6A}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 1 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 2 }



//1 Encoder
#define ENCODERS_PAD { encoderA, encoderB }

//2 or more encoders
// #define ENCODERS_PAD_A { encoder1a, encoder2a }
// #define ENCODERS_PAD_B { encoder1b, encoder2b }


/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
