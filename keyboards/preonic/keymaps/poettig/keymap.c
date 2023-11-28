/* Copyright 2015-2021 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.	If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "os_detection.h"
#include "musical_notes.h"

#define ___X___ KC_NO

#ifdef DEV_MODE
#include "print.h"
#endif

#ifdef AUDIO_ENABLE
#    define EASTEREGG Q__NOTE(_F4), Q__NOTE(_G4), Q__NOTE(_BF4), Q__NOTE(_G4), HD_NOTE(_D5), HD_NOTE(_D5), W__NOTE(_C5), H__NOTE(_REST), Q__NOTE(_F4), Q__NOTE(_G4), Q__NOTE(_BF4), Q__NOTE(_G4), HD_NOTE(_C5), HD_NOTE(_C5), W__NOTE(_BF4), H__NOTE(_REST), Q__NOTE(_F4), Q__NOTE(_G4), Q__NOTE(_BF4), Q__NOTE(_G4), W__NOTE(_BF4), H__NOTE(_C5), H__NOTE(_A4), H__NOTE(_A4), H__NOTE(_G4), H__NOTE(_F4), H__NOTE(_F4), W__NOTE(_C5), W__NOTE(_BF4),
static float easteregg[][2] = SONG(EASTEREGG);
#endif

enum unicode_names { ELLIPSIS, FQ_LEFT, FQ_RIGHT };

const uint32_t PROGMEM unicode_map[] = {
    [ELLIPSIS] = 0x2026, // …
    [FQ_LEFT]  = 0x00BB, // »
    [FQ_RIGHT] = 0x00AB, // «
};

enum preonic_layers { _BASE, _LOWER, _RAISE, _ADJUST, _LAYER3 };

enum preonic_keycodes { LOWER, RAISE, EEGG };

#ifdef DEV_MODE
static uint32_t key_hold_timer = 0;
#endif

const key_override_t shift_1_override = ko_make_basic(MOD_MASK_SHIFT, KC_1, LSFT(KC_GRV));
const key_override_t shift_2_override = ko_make_basic(MOD_MASK_SHIFT, KC_2, LSFT(KC_3));
const key_override_t shift_7_override = ko_make_basic(MOD_MASK_SHIFT, KC_7, RALT(KC_E));

const key_override_t **key_overrides = (const key_override_t *[]){&shift_1_override, &shift_2_override, &shift_7_override, NULL};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_preonic_grid(
        KC_ESC,              KC_1,    KC_2,    KC_3,    KC_4,  KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,              KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC,
        LT(_LAYER3, KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,             KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_DEL,
        KC_LCTL,             ___X___, KC_LGUI, KC_LALT, LOWER, KC_SPC, KC_ENT, RAISE, KC_LEFT,  KC_DOWN, KC_UP,   KC_RGHT
    ),

    [_LAYER3] = LAYOUT_preonic_grid(
        KC_GRV,  UM(FQ_LEFT),   UM(FQ_RIGHT),   _______,       _______,       _______,       _______,       _______,    _______,       _______,       _______,       _______,
        _______, UM(ELLIPSIS),  LSFT(KC_SLASH), RALT(KC_8),    RALT(KC_9),    KC_GRAVE,      LSFT(KC_1),    KC_NUBS,    LSFT(KC_NUBS), LSFT(KC_0),    LSFT(KC_6),    _______,
        _______, RALT(KC_MINS), LSFT(KC_7),     RALT(KC_7),    RALT(KC_0),    LSFT(KC_RBRC), LSFT(KC_MINS), LSFT(KC_8), LSFT(KC_9),    KC_SLSH,       LSFT(KC_DOT),  RALT(KC_Q),
        _______, KC_NUHS,       LSFT(KC_4),     RALT(KC_NUBS), RALT(KC_RBRC), LSFT(KC_EQL),  KC_RBRC,       LSFT(KC_5), LSFT(KC_2),    LSFT(KC_NUHS), LSFT(KC_COMM), KC_RSFT,
        _______, _______,       _______,        _______,       _______,       _______,       _______,       _______,    _______,       _______,       _______,       _______
    ),

    [_LOWER] = LAYOUT_preonic_grid(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___,  ___X___, KC_DEL,
        _______, ___X___, KC_MINS, KC_EQL,  ___X___, ___X___, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_BSPC, KC_PSCR,
        _______, ___X___, ___X___, ___X___, ___X___, ___X___, KC_HOME, KC_PGDN, KC_PGUP, KC_END,   ___X___, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD,  KC_VOLU, KC_MPLY
    ),

    [_RAISE] = LAYOUT_preonic_grid(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, KC_DEL,
        _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_U, KC_WH_D,
        _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, _______,
        _______, _______, _______, _______, _______, KC_BTN1, KC_BTN2, _______, _______, _______, _______, _______
    ),

    [_ADJUST] = LAYOUT_preonic_grid(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, QK_BOOT, DB_TOGG, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, KC_DEL,
        _______, ___X___, ___X___, ___X___, ___X___, AU_TOGG, MU_TOGG, EEGG,    ___X___, ___X___, ___X___, ___X___,
        _______, ___X___, ___X___, ___X___, ___X___, CK_TOGG, CK_UP,   CK_DOWN, CK_RST,  ___X___, ___X___, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )

};

uint32_t startup(uint32_t trigger_time, void *cb_arg) {
    switch (detected_host_os()) {
        case OS_LINUX:
            set_unicode_input_mode(UNICODE_MODE_LINUX);

#ifdef AUDIO_ENABLE
            static float linux[][2] = SONG(Q__NOTE(_D4), Q__NOTE(_D4), H__NOTE(_D5), HD_NOTE(_A4));
            PLAY_SONG(linux);
#endif

            break;

        case OS_WINDOWS:
            set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);

#ifdef AUDIO_ENABLE
            static float windows[][2] = SONG(H__NOTE(_E4), H__NOTE(_A4), H__NOTE(_REST), H__NOTE(_B4), B__NOTE(_E5));
            PLAY_SONG(windows);
#endif

            break;

        default:
            break;
    }

    return 0;
}

void keyboard_post_init_user(void) {
    defer_exec(2000, startup, NULL);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case EEGG:
            if (record->event.pressed) {
                PLAY_SONG(easteregg);
            }
            return false;
            break;
        default:
            break;
    }

#ifdef DEV_MODE
    if (record->event.pressed) {
        // Key is pressed, initialize the hold time counter
        key_hold_timer = timer_read32();
        uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    } else {
        // Key is released, calculate hold time
        uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u, hold time: %lu\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count, timer_elapsed32(key_hold_timer));
    }
#endif

    return true;
};
