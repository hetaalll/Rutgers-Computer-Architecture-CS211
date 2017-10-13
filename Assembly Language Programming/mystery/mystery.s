	.file	"mystery.c"
	.comm	_a, 800, 5
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
	.align 4
LC0:
	.ascii "ERROR: Invalid Number of Arguments\0"
LC1:
	.ascii "%s\12\0"
LC2:
	.ascii "ERROR: Not a Number\0"
LC3:
	.ascii "ERROR: Overflow\0"
LC4:
	.ascii "Value: %d\12\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB15:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$32, %esp
	call	___main
	cmpl	$2, 8(%ebp)
	jg	L2
	cmpl	$1, 8(%ebp)
	jg	L3
L2:
	movl	$LC0, 8(%esp)
	movl	$LC1, 4(%esp)
	movl	__imp___iob, %eax
	addl	$64, %eax
	movl	%eax, (%esp)
	call	_fprintf
	movl	$0, (%esp)
	call	_exit
L3:
	movl	12(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	subl	$48, %eax
	cmpl	$9, %eax
	ja	L4
	movl	12(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	_atoi
	movl	%eax, 24(%esp)
	movl	$0, 28(%esp)
	jmp	L6
L4:
	movl	$LC2, 8(%esp)
	movl	$LC1, 4(%esp)
	movl	__imp___iob, %eax
	addl	$64, %eax
	movl	%eax, (%esp)
	call	_fprintf
	movl	$0, (%esp)
	call	_exit
L7:
	movl	28(%esp), %eax
	movl	$-1, _a(,%eax,4)
	addl	$1, 28(%esp)
L6:
	cmpl	$199, 28(%esp)
	jle	L7
	cmpl	$46, 24(%esp)
	jle	L8
	movl	$LC3, 8(%esp)
	movl	$LC1, 4(%esp)
	movl	__imp___iob, %eax
	addl	$64, %eax
	movl	%eax, (%esp)
	call	_fprintf
	movl	$0, (%esp)
	call	_exit
L8:
	movl	24(%esp), %eax
	movl	%eax, (%esp)
	call	_fibonacci
	movl	%eax, 20(%esp)
	movl	20(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$LC4, (%esp)
	call	_printf
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE15:
	.globl	_add
	.def	_add;	.scl	2;	.type	32;	.endef
_add:
LFB16:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE16:
	.globl	_fibonacci
	.def	_fibonacci;	.scl	2;	.type	32;	.endef
_fibonacci:
LFB17:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	8(%ebp), %eax
	movl	_a(,%eax,4), %eax
	cmpl	$-1, %eax
	jne	L13
	cmpl	$0, 8(%ebp)
	jne	L14
	movl	8(%ebp), %eax
	movl	$0, _a(,%eax,4)
	jmp	L13
L14:
	cmpl	$1, 8(%ebp)
	jne	L15
	movl	8(%ebp), %eax
	movl	$1, _a(,%eax,4)
	jmp	L13
L15:
	movl	8(%ebp), %eax
	subl	$1, %eax
	movl	%eax, (%esp)
	call	_fibonacci
	movl	%eax, %ebx
	movl	8(%ebp), %eax
	subl	$2, %eax
	movl	%eax, (%esp)
	call	_fibonacci
	movl	%ebx, 4(%esp)
	movl	%eax, (%esp)
	call	_add
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, _a(,%eax,4)
L13:
	movl	8(%ebp), %eax
	movl	_a(,%eax,4), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE17:
	.ident	"GCC: (GNU) 5.3.0"
	.def	_fprintf;	.scl	2;	.type	32;	.endef
	.def	_exit;	.scl	2;	.type	32;	.endef
	.def	_atoi;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
