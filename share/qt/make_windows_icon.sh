#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/vcc.ico

convert ../../src/qt/res/icons/vcc-16.png ../../src/qt/res/icons/vcc-32.png ../../src/qt/res/icons/vcc-48.png ${ICON_DST}
