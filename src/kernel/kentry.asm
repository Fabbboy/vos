global start

section .text
global kentry
bits 32
kentry:
	; print `OK`
	mov dword [0xb8000], 0x2f4b2f4f
	hlt