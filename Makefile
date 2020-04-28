all: xdtldt output.txt
	@rm -rf *o xdtldt

xdtldt: main.c sbox.c sbox.h
	@rm -rf *.o xdtldt output.txt
	@gcc -o xdtldt main.c sbox.c sbox.h

output.txt:
	@./xdtldt

clean:
	@rm -rf *.o xdtldt output.txt
