/*
		Example Arduino IDE file to show how to use mruby-arduino library in a
		sketch using mruby 1.3.0 and Arduino IDE v1.8.3. October 2017.

		Please see more detailed demo at
		https://github.com/xunker/mruby_arduino_due_example

		Compiled by Matthew Nielsen (xunker@pyxidis.org), based on extensive work
		by kyab:
		https://github.com/kyab/mruby-arduino/blob/master/samples/blink/blink.pde
*/
#include "src/mruby-arduino/mruby-arduino.h"
#include "mruby/irep.h"

mrb_state *mrb;
int ai;
size_t total_allocated;

#include "skeleton.h"

/* Custom allocator to check heap shortage. Originally created by kyab, copied
   from github.com/kyab/mruby-arduino/blob/master/samples/blink/blink.pde */
void *myallocf(mrb_state *mrb, void *p, size_t size, void *ud){
	if (size == 0){
		free(p);
		return NULL;
	}

	void *ret = realloc(p, size);
	if (!ret){
		/*
			Reaches here means mruby failed to allocate memory.
			Sometimes it is not critical because mruby core will retry allocation
			after GC.
		*/

		Serial.print("memory allocation error. requested size:");
		Serial.println(size, DEC);

		Serial.flush();

		//Ensure serial output received by host before proceeding.
		delay(200);
		return NULL;
	}
	total_allocated += size;
	return ret;
}

void setup() {
  Serial.begin(9600);

  total_allocated = 0;

	/* Init mruby. Block originally by kyab and copied from
	   github.com/kyab/mruby-arduino/blob/master/samples/blink/blink.pde */
	Serial.println("mrb_open()...");
	delay(100);
	mrb = mrb_open_allocf(myallocf, NULL);
	if (mrb){
		Serial.print("Success: mrb_open() total allocated : ");
		Serial.println(total_allocated,DEC);
	}else{
		Serial.print("Failure: mrb_open() total allocated : ");
		Serial.println(total_allocated,DEC);
		return;
	}

	/* This adds the Arduino.* and Serial.* methods to mruby, but ONLY THOSE that
	   have been enabled in config.h. */
  add_arduino_to_mruby(mrb);

	ai = mrb_gc_arena_save(mrb); // see https://github.com/mruby/mruby/blob/master/doc/guides/gc-arena-howto.md
}

void loop() {
	mrb_load_irep(mrb, bytecode);
	mrb_close(mrb);
	mrb_gc_arena_restore(mrb,ai); // see https://github.com/mruby/mruby/blob/master/doc/guides/gc-arena-howto.md
  delay(1000);
}
