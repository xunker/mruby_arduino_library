# Simple test, loop. There will be no output and this will go on forever.
loop do
  1 + 1
end


# ----------


# # Will blink the LED on the DUE labeled "L" on and off in 1 second intervals.
# # Needs the following enabled in config.h:
# #   MRUBY_ARDUINO_DIGITAL_WRITE
# #   MRUBY_ARDUINO_DELAY
# loop do
#   Arduino.digitalWrite(13, 1)
#   Arduino.delay(1000)
#   Arduino.digitalWrite(13, 0)
#   Arduino.delay(1000)
# end


# ----------


# # Using the Arduino methods as a module. Blinks the LED at 1 second interval
# # as well as printing text along the serial link.
# # Needs the following enabled in config.h:
# #   MRUBY_ARDUINO_DIGITAL_IO
# #   MRUBY_ARDUINO_DELAY
# #   MRUBY_ARDUINO_SERIAL_PRINTLN
# class Blinky
#   include Arduino
#
#   def initialize
#     Serial.println("Blinker initialized")
#     pinMode(13, OUTPUT)
#   end
#
#   def run
#     Serial.println("#run")
#     loop do
#       Serial.println("blink!")
#       digitalWrite(13, 1)
#       delay(1000)
#       digitalWrite(13, 0)
#       delay(1000)
#     end
#   end
# end
# blinky = Blinky.new
# blinky.run
