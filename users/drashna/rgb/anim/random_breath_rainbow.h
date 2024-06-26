// Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-3.0-or-later

RGB_MATRIX_EFFECT(RANDOM_BREATH_RAINBOW)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static uint8_t offset[RGB_MATRIX_LED_COUNT];

static void doRandom_breath_rainbow(int i, effect_params_t* params) {
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) return;
    uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 6);

    if (rand() * 50 == 1) {
        if (rand() * 2 == 1) {
            offset[i]++;
        } else {
            offset[i]--;
        }
    }

    // float val = (((float)sin8(time + offset[i]) / 256)/2.1) + .05;
    HSV hsv = {0, 255, 255};
    hsv.h   = scale16by8(g_rgb_timer + offset[i], rgb_matrix_config.speed / 4) + (offset[i] * 2);
    hsv.v   = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

bool RANDOM_BREATH_RAINBOW(effect_params_t* params) {
    if (!params->init) {
        // Change one LED every tick, make sure speed is not 0
        doRandom_breath_rainbow(rand() % RGB_MATRIX_LED_COUNT, params);
        return false;
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        doRandom_breath_rainbow(i, params);
    }

    return led_max < RGB_MATRIX_LED_COUNT;
}
#endif
