#/*************************************************************************
#	工程名：Matrix_Calculator
#	作者: 王召东
#	联系方式：yuanliudongdong@163.com
#	当前文件: Makefile
#	当前文件描述：包含编译指令和文件整理指令的文件
#**************************************************************************/
all:test_1.hex

test_1.hex:test_1.ihx
	packihx test_1.ihx > test_1.hex
	mv test_1.hex bin/
	mv test_1.rel lcd_function.rel lcd_code.rel core_function.rel keyboard_function.rel lib/
	mv test_1.* lcd_function.* lcd_code.* core_function.* keyboard_function.* build/

test_1.ihx:test_1.rel lcd_function.rel lcd_code.rel core_function.rel keyboard_function.rel
	sdcc test_1.rel lcd_function.rel lcd_code.rel core_function.rel keyboard_function.rel

test_1.rel:test/test_1.c include/common_include.h
	sdcc -c test/test_1.c

lcd_function.rel:src/lcd_function.c include/lcd_function.h include/pin_define.h
	sdcc -c src/lcd_function.c

lcd_code.rel:src/lcd_code.c include/lcd_code.h
	sdcc -c src/lcd_code.c

core_function.rel:src/core_function.c include/core_function.h
	sdcc -c src/core_function.c
	
keyboard_function.rel:src/keyboard_function.c include/keyboard_function.h
	sdcc -c src/keyboard_function.c

clean:
	rm -fr bin/* lib/* build/*  