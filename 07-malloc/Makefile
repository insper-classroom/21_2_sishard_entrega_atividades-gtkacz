all: copia_string concatena_string

%: %.c 
	gcc -Og -fno-stack-protector $< -o $@ -lsystemd
	./$@

.PHONY = all
