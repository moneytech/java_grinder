
default: JavaPropellerDemo.class

grind: JavaPropellerDemo.class
	../../java_grinder -v JavaPropellerDemo.class java_propeller_demo.asm propeller
	naken_asm -l -b -o java_propeller_demo.bin java_propeller_demo.asm

mandel: Mandelbrot.class
	../../java_grinder -v Mandelbrot.class mandelbrot_code.asm propeller
	naken_asm -l -b -o mandelbrot_code.bin mandelbrot_code.asm
	openspin ../../../naken_asm/samples/propeller/mandelbrot.spin -o mandelbrot.binary
	propeller-load -r -p /dev/ttyUSB0 mandelbrot.binary

flip_blink: FlipBlink.class
	../../java_grinder -v FlipBlink.class flip_blink_code.asm propeller
	naken_asm -l -b -o flip_blink_code.bin flip_blink_code.asm
	openspin ../../../naken_asm/samples/propeller/flip_blink.spin -o flip_blink.binary
	propeller-load -r -p /dev/ttyUSB0 flip_blink.binary

%.class: %.java
	javac -classpath ../../build/JavaGrinder.jar:. $*.java

program:
	openspin run_demo.spin
	propeller-load -r -p /dev/ttyUSB0 run_demo.binary

clean:
	@rm -f *.hex *.lst *.class *.asm *.bin *.spin *.binary
	@echo "Clean!"

