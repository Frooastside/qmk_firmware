// Copyright 2023 Simon Benezan (@Frooastside)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define I2C_DRIVER I2CD0
#define I2C0_SDA_PIN GP28
#define I2C0_SCL_PIN GP29

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
