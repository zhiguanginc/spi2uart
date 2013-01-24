# spi2uart for HT45B0F
# Michael Li
# QQ: 13458499
# Mail: zhiguang@outlook.com

objs = spi2uart.o
target = spi2uart

$(target): $(objs) 
	arm-linux-gcc -o $(target) $(objs)
	cp $(target) /home/tftproot/

spi2uart.o: spi2uart.c
	arm-linux-gcc -c spi2uart.c

clean:
	rm -rf $(objs)
	rm -rf $(target)
