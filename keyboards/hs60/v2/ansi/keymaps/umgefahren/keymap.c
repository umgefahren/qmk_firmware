/* Copyright 2018 Yiancar
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
#include "action_util.h"
#include "keyboard.h"
#include "modifiers.h"
#include QMK_KEYBOARD_H
#include "send_string.h"

enum custom_keycodes {
    Q_EXIT_TERMINAL = SAFE_RANGE,
    Q_LOVE_YOU,
    Q_SMILEY,
    Q_DESSS,
    Q_DEAE,
    Q_DEOE,
    Q_DEUE,
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case Q_EXIT_TERMINAL:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("\\"));
                SEND_STRING(SS_LCTL("n"));
            }
            break;
        case Q_LOVE_YOU:
            if (record->event.pressed) {
                SEND_STRING("i love you");
            }
            break;
        case Q_SMILEY:
            if (record->event.pressed) {
                SEND_STRING(":)");
            }
            break;
        case Q_DESSS:
            if (get_mods() & MOD_MASK_SHIFT) {
                SEND_STRING(SS_UP(X_LSFT));
            }
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("s"));
            }
            break;
        case Q_DEAE ... Q_DEUE:
            if (record->event.pressed) {
                bool is_shifted_oneshot = get_oneshot_mods() & MOD_MASK_SHIFT;
                if (is_shifted_oneshot) {
                    del_oneshot_mods(MOD_MASK_SHIFT);
                }
                SEND_STRING(SS_LALT("u"));

                if (is_shifted_oneshot) {
                    add_oneshot_mods(MOD_MASK_SHIFT);
                }

                switch (keycode) {
                    case Q_DEAE:
                        SEND_STRING("a");
                        break;
                    case Q_DEOE:
                        SEND_STRING("o");
                        break;
                    case Q_DEUE:
                        SEND_STRING("u");
                        break;
                }
            }
            break;
    }
    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_ansi(/* Base */
                         KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
                         KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
                         KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
                         KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                         KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, MO(1), KC_RALT, OSL(2), Q_EXIT_TERMINAL
                        ),

    [1] = LAYOUT_60_ansi(/* FN */
                         TO(0), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS,
                            KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, KC_TRNS,
                         TO(0), KC_LEFT, KC_DOWN, KC_RGHT, S1_DEC, S1_INC, S2_DEC, S2_INC, ES_DEC, ES_DEC, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS, EF_DEC, EF_INC, H1_DEC, H1_INC, H2_DEC, H2_INC, BR_DEC, BR_INC, KC_TRNS, UC_MAC, KC_UP,
                         KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT),

    [2] = LAYOUT_60_ansi(/* Empty for dynamic keymaps */
                         TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), Q_DESSS, TO(0), TO(0),
                         TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), Q_DEUE, Q_LOVE_YOU, Q_DEOE, TO(0), TO(0), TO(0), TO(0),
                         TO(0), Q_DEAE, Q_SMILEY, TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0),
                         OSM(MOD_RSFT), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), OSM(MOD_RSFT),
                         TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0)),

    [3] = LAYOUT_60_ansi(/* Empty for dynamic keymaps */
                         TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), OSL(2), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0), TO(0)),
};
