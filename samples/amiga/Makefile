
NAKEN_INCLUDE=../../../naken_asm/include

CLASSES= \
  Common.class \
  Display.class \
  Image3Billion.class \
  ImageAmigaLogo8.class \
  ImageAmigaLogo16.class \
  ImageCodedUsing.class \
  ImageCommodoreLogo.class \
  ImageJavaGrinder.class\
  ImageJavaGrinderText.class\
  Logo.class \
  Mandelbrot.class \
  SongAmigaGrind.class \
  SongBach.class \
  SpriteJava.class \
  Stars.class \
  AmigaDemo.class

default: $(CLASSES)

grind:
	../../java_grinder -v AmigaDemo.class amiga_demo.asm amiga
	../../../naken_asm/naken_asm -I $(NAKEN_INCLUDE) -l -amiga -o amiga_demo amiga_demo.asm

display:
	javac -classpath ../../build/JavaGrinder.jar:. TestDisplay.java
	../../java_grinder -v TestDisplay.class test_display.asm amiga
	../../../naken_asm/naken_asm -I $(NAKEN_INCLUDE) -l -amiga -o test_display test_display.asm

%.class: %.java
	javac -classpath ../../build/JavaGrinder.jar:. $*.java

song:
	../../../drumsplusplus/playdpp -o amiga_grind.mid amiga_grind.dpp

clean:
	@rm -f *.lst *.class amiga_demo.asm amiga_demo
	@rm -rf cfg nvram snap
	@echo "Clean!"

