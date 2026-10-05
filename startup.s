.global _resethandler
.section .lol

_resethandler:
	
	la x2, _stack_top
	call main
	

1:
	j 1b
