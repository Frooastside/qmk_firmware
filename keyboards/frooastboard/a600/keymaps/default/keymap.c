// Copyright 2024 Simon Benezan (@Frooastside)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "raw_hid.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌────┐ ┌────┬────┬────┬────┬────┐ ┌────┬────┬────┬────┬────┐ ┌────┐
     * │ Esc│ │ F1 │ F2 │ F3 │ F4 │ F5 │ │ F6 │ F7 │ F8 │ F9 │F10 │ │Help│
     * └────┘ └────┴────┴────┴────┴────┘ └────┴────┴────┴────┴────┘ └────┘
     * ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │  `  │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ \ │Bsp│Del│
     * ├─────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┘
     * │  Tab  │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │     │
     * ├────┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐ Ent│
     * │Ctrl│Cap│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ # │    │
     * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┤
     * │Shift │ \ │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │Shift │ ↑ │
     * └──┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴───┴─┬─┴──┬┴───┼──┬───┼───┼───┐
     *    │LAlt│LGUI│                           │LGUI│LAlt│  │ ← │ ↓ │ → │
     *    └────┴────┴───────────────────────────┴────┴────┘  └───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_HELP,

        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_ENT,
        KC_LCTL, KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,
                 KC_LALT, KC_LGUI,                       KC_SPC,                         KC_RGUI, KC_RALT,          KC_LEFT, KC_DOWN, KC_RGHT
    )
};

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (data[0] == 0xA4) {
        uint8_t response[length];
        memset(response, 0, length);
        response[0] = 0xA4;

        gpio_set_pin_output(GP23);
        gpio_set_pin_output(GP24);
        gpio_set_pin_output(GP25);
        response[1] = 0x00;

        raw_hid_send(response, length);
    } else if (data[0] == 0xA6) {
        uint8_t response[length];
        memset(response, 0, length);
        response[0] = 0xA6;

        if((data[1] == 0x00 || data[1] == 0x01) && (data[2] == 0x00 || data[2] == 0x01) && (data[3] == 0x00 || data[3] == 0x01)) {
            gpio_write_pin(GP23, data[1] == 0x01);
            gpio_write_pin(GP24, data[2] == 0x01);
            gpio_write_pin(GP25, data[3] == 0x01);
            response[1] = 0x00;
        }else {
            response[1] = 0x01;
        }

        raw_hid_send(response, length);
    }
}
