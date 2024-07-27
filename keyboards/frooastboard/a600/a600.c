// Copyright 2022 Simon Benezan (@Frooastside)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(GP23);
    gpio_set_pin_output(GP24);
    gpio_set_pin_output(GP25);

    keyboard_pre_init_user();
}
