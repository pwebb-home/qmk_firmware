// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "bootmagic.h"
#include "matrix.h"
#include "keyboard.h"
#include "wait.h"
#include "eeconfig.h"

void reset_keyboard(void);

#ifdef RGBLIGHT_ENABLE
#    include "rgblight.h"
#endif // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#endif // RGB_MATRIX_ENABLE
#ifdef LED_MATRIX_ENABLE
#    include "led_matrix.h"
#endif // LED_MATRIX_ENABLE
#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif // BACKLIGHT_ENABLE
#ifdef OLED_ENABLE
#    include "oled_driver.h"
#endif // OLED_ENABLE

#ifndef BOOTMAGIC_DEBOUNCE
#    if defined(DEBOUNCE) && DEBOUNCE > 0
#        define BOOTMAGIC_DEBOUNCE (DEBOUNCE * 2)
#    else
#        define BOOTMAGIC_DEBOUNCE 30
#    endif
#endif

void bootmagic_scan(void) {
    bool perform_reset = false;
    // We need multiple scans because debouncing can't be turned off.
    matrix_scan();
    wait_ms(BOOTMAGIC_DEBOUNCE);
    matrix_scan();

    // If the configured key (commonly Esc) is held down on power up,
    // reset the EEPROM valid state and jump to bootloader.
    // This isn't very generalized, but we need something that doesn't
    // rely on user's keymaps in firmware or EEPROM.
    uint8_t row = BOOTMAGIC_ROW, col = BOOTMAGIC_COLUMN;
#if defined(BOOTMAGIC_EEPROM_ROW) && defined(BOOTMAGIC_EEPROM_COLUMN)
    uint8_t row_e = BOOTMAGIC_EEPROM_ROW, col_e = BOOTMAGIC_EEPROM_COLUMN;
#endif

#if defined(SPLIT_KEYBOARD) && defined(BOOTMAGIC_ROW_RIGHT) && defined(BOOTMAGIC_COLUMN_RIGHT)
    if (!is_keyboard_left()) {
        row = BOOTMAGIC_ROW_RIGHT;
        col = BOOTMAGIC_COLUMN_RIGHT;
#    if defined(BOOTMAGIC_EEPROM_ROW) && defined(BOOTMAGIC_EEPROM_COLUMN) && defined(BOOTMAGIC_EEPROM_ROW_RIGHT) && \
        defined(BOOTMAGIC_EEPROM_COLUMN_RIGHT)
        row_e = BOOTMAGIC_EEPROM_ROW_RIGHT;
        col_e = BOOTMAGIC_EEPROM_COLUMN_RIGHT;
#    endif
    }
#endif

#if defined(BOOTMAGIC_EEPROM_ROW) && defined(BOOTMAGIC_EEPROM_COLUMN)
    if (matrix_get_row(row_e) & (1 << col_e)) {
        eeconfig_disable();
        perform_reset = true;
    }
#endif
    if (matrix_get_row(row) & (1 << col)) {
        perform_reset = true;
    }
#ifdef BOOTLOADER_RESET_PIN
    if (!gpio_read_pin(BOOTLOADER_RESET_PIN)) {
        perform_reset = true;
    }
#endif

    if (perform_reset) {
#ifdef RGBLIGHT_ENABLE
        rgblight_init();
#endif
#ifdef RGB_MATRIX_ENABLE
        rgb_matrix_init();
#endif
#ifdef LED_MATRIX_ENABLE
        led_matrix_init();
#endif
#ifdef BACKLIGHT_ENABLE
        backlight_init_ports();
#endif
#ifdef OLED_ENABLE
        oled_init(OLED_ROTATION_0);
#endif
        reset_keyboard();
    }
}
