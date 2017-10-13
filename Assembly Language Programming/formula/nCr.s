	.file	"nCr.c"
	.section .rdata,"dr"
LC0:
	.ascii "ERROR: Integer overflow\0"
LC1:
	.ascii "%s\12\0"
	.text
	.globl	_Factorial
	.def	_Factorial;	.scl	2;	.type	32;	.endef
_Factorial:
LFB17:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	cmpl	$12, 8(%ebp)
	jle	L2
	movl	$LC0, 8(%esp)
	movl	$LC1, 4(%esp)
	movl	__imp___iob, %eax
	addl	$64, %eax
	movl	%eax, (%esp)
	call	_fprintf
	movl	$0, (%esp)
	call	_exit
L2:
	cmpl	$0, 8(%ebp)
	je	L3
	cmpl	$1, 8(%ebp)
	jne	L4
L3:
	movl	$1, %eax
	jmp	L5
L4:
	movl	8(%ebp), %eax
	subl	$1, %eax
	movl	%eax, (%esp)
	call	_Factorial
	imull	8(%ebp), %eax
L5:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE17:
	.section .rdata,"dr"
LC2:
	.ascii "Integer overflow\0"
LC3:
	.ascii "ERROR: n < r\0"
	.text
	.globl	_nCr
	.def	_nCr;	.scl	2;	.type	32;	.endef
_nCr:
LFB18:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	.cfi_offset 6, -12
	.cfi_offset 3, -16
	cmpl	$12, 8(%ebp)
	jle	L7
	movl	$LC2, 8(%esp)
	movl	$LC1, 4(%esp)
	movl	__imp___iob, %eax
	addl	$64, %eax
	movl	%eax, (%esp)
	call	_fprintf
	movl	$0, (%esp)
	call	_exit
L7:
	movl	8(%ebp), %eax
	cmpl	12(%ebp), %eax
	jge	L8
	movl	$LC3, (%esp)
	call	_puts
	movl	$0, (%esp)
	call	_exit
L8:
	movl	$0, -12(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_Factorial
	movl	%eax, %ebx
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_Factorial
	movl	%eax, %esi
	movl	8(%ebp), %eax
	subl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_Factorial
	movl	%esi, %edx
	imull	%eax, %edx
	movl	%edx, %ecx
	movl	%ebx, %eax
	cltd
	idivl	%ecx
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	addl	$32, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE18:
	.ident	"GCC: (GNU) 5.3.0"
	.def	_fprintf;	.scl	2;	.type	32;	.endef
	.def	_exit;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef
