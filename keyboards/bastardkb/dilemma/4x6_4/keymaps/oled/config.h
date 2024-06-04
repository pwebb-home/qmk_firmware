/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
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
#pragma once
#ifndef OLED_UPDATE_INTERVAL
#    ifdef SPLIT_KEYBOARD
#        define OLED_UPDATE_INTERVAL 60
#    elif defined(OLED_DISPLAY_128X128)
#        define OLED_UPDATE_INTERVAL 30
#    else
#        define OLED_UPDATE_INTERVAL 15
#    endif
#endif

#define DYNAMIC_KEYMAP_LAYER_COUNT 8
#define OLED_DISPLAY_128X128
#define OLED_UPDATE_PROCESS_LIMIT 2

#define I2C_DRIVER       I2CD1
#define I2C1_SDA_PIN     GP2
#define I2C1_SCL_PIN     GP3
#define I2C1_CLOCK_SPEED 400000