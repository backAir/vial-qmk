# This file intentionally left blank
# RGBLIGHT_ENABLE = yes


OLED_DRIVER = ssd1306
OLED_DRIVER_ENABLE= yes
OLED_TRANSPORT = i2c

OPT_DEFS += -DHAL_USE_I2C=TRUE
