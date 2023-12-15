global start
section .text
global kentry
extern main
bits 32
kentry: 
	call main