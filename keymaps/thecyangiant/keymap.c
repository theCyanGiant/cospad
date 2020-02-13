#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_numpad_6x4(KC_ESC, LT(2,KC_NLCK), KC_CALC, KC_DEL, KC_TAB, KC_PSLS, KC_PAST, KC_PMNS, KC_P7, KC_P8, KC_P9, KC_P4, KC_P5, KC_P6, KC_PPLS, KC_P1, KC_P2, KC_P3, KC_P0, LT(1,KC_PDOT), KC_PENT),
	[1] = LAYOUT_numpad_6x4(KC_ESC, KC_NO, KC_NO, KC_BSPC, KC_PSCR, KC_SLCK, KC_PAUS, KC_CUT, KC_HOME, KC_UP, KC_PGUP, KC_LEFT, KC_MPLY, KC_RGHT, KC_COPY, KC_END, KC_DOWN, KC_PGDN, KC_INS, KC_NO, KC_PSTE),
	[2] = LAYOUT_numpad_6x4(RESET, KC_NO, RGB_SPI, RGB_SPD, RGB_TOG, RGB_MOD, RGB_RMOD, RGB_M_B, RGB_HUI, RGB_SAI, RGB_VAI, RGB_HUD, RGB_SAD, RGB_VAD, RGB_M_P, RGB_M_SN, RGB_M_K, RGB_SPI, RGB_M_G, KC_NO, RGB_M_SW)
};