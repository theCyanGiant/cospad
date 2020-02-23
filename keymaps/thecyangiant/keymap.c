// Next Steps:
//- Make code lighter with function definition for if(record->event.pressed) and tap timer.
//- Hold behavior is triggering on release, would be nicer if it triggered when timer greater than defined time.
//- Hold behavior on backspace: would be nice to have hold behavior continue to backspace until released.
//- Figure out how to send the shifted event as a keypress and not a string.
// ISSUES:
// - Rapid tap typing on 0 & 1 sometimes do not register, this is likely an artifact of tapping-term (set to 175 in config). How can this be resolved?  Moving from 250 to 175 reduced the lag a little, but going much lower will likely manifest in the same issue.  

#include QMK_KEYBOARD_H

enum custom_keycodes { SVN_OBRKT = SAFE_RANGE, EGT_COLN, NIN_CBRKT, DEL_BSPC };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t tap_timer;
    /*if(record->event.pressed) {*/  // is there a way to make this universal for each of the below cases?
    /*tap_timer = timer_read(); */   // is there a way to make this universal for each of the below cases?
    switch (keycode) {
        case SVN_OBRKT:
            if (record->event.pressed) {
                tap_timer = timer_read();
            } else {
                if (timer_elapsed(tap_timer) < 250) {
                    tap_code(KC_P7);  // if button tapped select 7
                } else {
                    SEND_STRING("(");       // if button held select left paren string
                    /*tap_code(KC_LPRN);*/  // can't send shifted codes, maybe do a shift+9 to use keycode instead of string?
                    return false;
                }
            }
            break;
        case EGT_COLN:
            if (record->event.pressed) {
                tap_timer = timer_read();
            } else {
                if (timer_elapsed(tap_timer) < 250) {
                    tap_code(KC_P8);  // if button tapped select 8
                } else {
                    SEND_STRING(":");  // if button held select colon
                    return false;
                }
            }
            break;
        case NIN_CBRKT:
            if (record->event.pressed) {
                tap_timer = timer_read();
            } else {
                if (timer_elapsed(tap_timer) < 250) {
                    tap_code(KC_P9);  // if button tapped select 9
                } else {
                    SEND_STRING(")");  // if button held right paren
                    return false;
                }
            }
            break;
        case DEL_BSPC:
            if (record->event.pressed) {
                tap_timer = timer_read();
            } else {
                if (timer_elapsed(tap_timer) > 250) {  // changed to greater than and inverted press/hold to see if register/unregister of backspace will allow hold behavior of multiple backspaces.  This does NOT work to do multiple presses on hold.  need to research.
                    register_code(KC_BSPC);
                    unregister_code(KC_BSPC);
                } else {
                    tap_code(KC_DEL);
                    return false;
                }
                break;
            }
    }
    return true;  // We didn't handle other keypresses                                

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
/* Keymap _0: (Base Layer) Default Layer x/y means x on tap, y on hold
 * ,----------------------.
 * |Esc  |NL/LT2| CAL | DEL|
 * |-----|------|-----|----|
 * | TAB | /    | *   | -  |
 * |-----|------|-----|----|
 * | 7/( | 8/:  | 9/) |    |
 * |-----|------|-----| +  |
 * | 4   | 5    | 6   |    |
 * |-----|------|-----|----|      
 * |1/SFT| 2    | 3   |    |
 * |-----|------|-----| En |
 * |   0/LCTL   |./LT1|    |
 * `-----------------------'
 */
	[0] = LAYOUT_numpad_6x4(
        KC_ESC,         LT(2,KC_NLCK),  LT(2,KC_CALC),  DEL_BSPC,\
        KC_TAB,         KC_PSLS,        KC_PAST,        KC_PMNS, \
        SVN_OBRKT,      EGT_COLN,       NIN_CBRKT,               \
        KC_P4,          KC_P5,          KC_P6,          KC_PPLS, \
        LSFT_T(KC_P1),  KC_P2,          KC_P3,                   \
        LCTL_T(KC_P0),                  LT(1,KC_PDOT),  KC_PENT
    ),

	
/* Keymap _1: (ALT Layer) Layer Accessed by holding dot
 * ,----------------------.
 * |Esc  |      |     |BSPC|
 * |-----|------|-----|----|
 * | PSCR|SCRLCK|Pause|CUT |
 * |-----|------|-----|----|
 * | HOME|  UP  | PGUP|    |
 * |-----|------|-----|COPY|
 * | LEFT|PLY/PS|RIGHT|    |
 * |-----|------|-----|----|
 * | END | DOWN | PGDN|    |
 * |-----|------|-----|PAST|
 * |  INS       |     |    |
 * `-----------------------'
 */
	[1] = LAYOUT_numpad_6x4(
        KC_ESC,         KC_NO,          KC_NO,      KC_BSPC, \
        KC_PSCR,        KC_SLCK,        KC_PAUS,    KC_CUT,  \
        KC_HOME,        KC_UP,          KC_PGUP,             \
        KC_LEFT,        KC_MPLY,        KC_RGHT,    KC_COPY, \
        KC_END,         KC_DOWN,        KC_PGDN,             \
        KC_INS,                         KC_NO,      KC_PSTE
    ),

	
/* Keymap _2: (RGB Layer) Layer Accessed by holding Numlock
 * ,------------------------.
 * |RESET|      |speed|speed
 * |     |      | inc | dec |
 * |-----|------|-----|-----|
 * | RGB |RGB F |RGB R| RGB |
 * | TOG | cycle|cycle| Brth|
 * |-----|------|-----|-----|
 * |HueIn| SatIn|BrtIn|     |
 * |-----|------|-----| RGB |
 * |HueDc| SatDc|BrdDc|plain|
 * |-----|------|-----|-----|
 * |Snake|Knight|Swirl|     |
 * |-----|------|-----| TEST|
 * |RGB Gradient|Rainb|     |
 * `------------------------'
 */
	[2] = LAYOUT_numpad_6x4(
        RESET,          KC_NO,          RGB_SPI,    RGB_SPD,\
        RGB_TOG,        RGB_MOD,        RGB_RMOD,   RGB_M_B,\
        RGB_HUI,        RGB_SAI,        RGB_VAI,            \
        RGB_HUD,        RGB_SAD,        RGB_VAD,    RGB_M_P,\
        RGB_M_SN,       RGB_M_K,        RGB_M_SW,           \
        RGB_M_G,                        RGB_M_R,    RGB_M_T
    )
};
