/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include QMK_KEYBOARD_H


#define TAPPING_TERM_INCREMENT 10

enum layers {
    BASE,
    SYMBOLS
};

enum custom_dynamic_tapping_term_keys {
    DT_PRNT = SAFE_RANGE,
    DT_UP,
    DT_DOWN,
};

uint16_t g_tapping_term = TAPPING_TERM;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/* Base layer
 *
 *    ,-----------------------------------------.         .-----------------------------------------.
 *    |   `  |   1  |   2  |   3  |   4  |   5  |         |   6  |   7  |   8  |   9  |  10  |  -   |
 *    |------+------+------+------+------+------|         |------+------+------+------+------+------|
 *    |  Tab |   Q  |   W  |   E  |   R  |   T  |         |   Y  |   U  |   I  |   O  |   P  |  \   |
 *    |------+------+------+------+------+------|         |------+------+------+------+------+------|
 *    |L1/Esc|   A  |   S  |   D  |   F  |   G  |         |   H  |   J  |   K  |   L  |   ;  | L1/' |
 *    |------+------+------+------+------+------|         |------+------+------+------+------+------|
 *    | Shift|   Z  |   X  |   C  |   V  |   B  |         |   N  |   M  |   ,  |   ,  |   /  |Shift |
 *    `------+------+------+------+------+------'         '------+------+------+------+-------------'
 *
 *                         ,--------------------.         .--------------------.
 *                         | Space| Ctrl | Space|         |  L2  | Enter | Bspc|
 *                         '------+------+------|         |------+------+------'
 *                                |  Alt | Super|         |   ?  | Ctrl |
 *                                '------+------'         '------+------'
 */
  [0] = LAYOUT_split_4x6_5(
    KC_GRV,                            KC_1, KC_2, KC_3, KC_4, KC_5,	      KC_6, KC_7, KC_8,    KC_9,   KC_0,                  KC_MINS,
    KC_TAB,                            KC_Q, KC_W, KC_E, KC_R, KC_T,	      KC_Y, KC_U, KC_I,    KC_O,   KC_P,                  KC_BSLS,
    KC_ESC,                            KC_A, KC_S, KC_D, KC_F, KC_G,	      KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,               KC_QUOT,
    KC_LSFT,              MT(MOD_LSFT,KC_Z), KC_X, KC_C, KC_V, KC_B,          KC_N, KC_M, KC_COMM, KC_DOT, MT(MOD_RSFT,KC_SLSH),  KC_RSFT,

                                    KC_SPC, LCTL_T(KC_SPC), KC_LALT,          KC_RALT, LT(1, KC_ENT), KC_BSPC,
                                                   KC_LCTL, KC_LGUI,          KC_LGUI, KC_RCTL
  ),

/* Symbol layer
 *
 * ,-----------------------------------------.  .-----------------------------------------.
 * |      |      |      |      |  End |      |  | Home |      |      |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Pause|      |   {  |   [  |   (  |   +  |  |  =   |  )   |  ]   |  }   |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  | Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |      |      |      |      |      |      |
 * `------+------+------+------+------+------'  '------+------+------+------+-------------'
 *
 *                      ,--------------------.  .--------------------.
 *                      |      |      |      |  |      |      | Del  |
 *                      '------+------+------|  |------+------+------'
 *                             |      |      |  |      |      |
 *                             '------+------'  '------+------'
 */
  [1] = LAYOUT_split_4x6_5(
    _______, _______, _______, _______, KC_END,  _______,	    KC_HOME, _______, _______, _______, _______,  _______,
    KC_PAUS, _______, KC_LCBR, KC_LBRC, KC_LPRN, KC_PLUS,		KC_EQL,  KC_RPRN, KC_RBRC, KC_RCBR, _______,  _______,
    _______, _______, _______, _______, _______, _______,	    KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______,  _______,
    _______, _______, _______, DT_PRNT, DT_DOWN, DT_UP,       _______, _______, _______, _______, _______,  _______,

                               _______, _______, _______,		_______, _______, _______,
                                        _______, _______,       _______, _______
  ),
};



static void tapping_term_report(void) {
    char display[8];
    snprintf(display, sizeof(display), "%d", g_tapping_term);
    send_string((const char *)display);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case DT_PRNT:
        if (record->event.pressed) {
            tapping_term_report();
        }
        break;
    case DT_DOWN:
        if (record->event.pressed) {
            g_tapping_term -= TAPPING_TERM_INCREMENT;
        }
        break;
    case DT_UP:
        if (record->event.pressed) {
            g_tapping_term += TAPPING_TERM_INCREMENT;
        }
        break;
    }
    return true;
};



/* uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) { */
/*     switch (keycode) { */
/*         default: */
/*            return g_tapping_term; */
/*     } */
/* } */
