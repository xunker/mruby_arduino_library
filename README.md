Arduino function library for mruby
==================================

Bridge Arduino function in to mruby. Intended for Arduino Due but may work for
others.
Based on https://github.com/kyab/mruby-arduino, turned in to Arduino library and
updated to get around memory limitations with mruby 1.3.0.
Working with Arduino IDE v1.8.3.

---

Use in sketch:

cd <sketch_dir>
mkdir src
<copy mruby-arduino directory to new 'directory'>

At top of sketch add
`#include "src/mruby-arduino/mruby-arduino.h"`

In setup() of sketch add
`add_arduino_to_mruby(mrb);`

Be sure to edit config.h to enable the functions you want!

---

Use as library:

cd <Arduino sketch dir>
<copy mruby-arduino directory to 'libraries' directory>

At top of sketch add
`#include <mruby-arduino.h>`

In setup() of sketch add
`add_arduino_to_mruby(mrb);`

You will still need to edit config.h to enable the functions you want, even
though it's in the libraries directory.
