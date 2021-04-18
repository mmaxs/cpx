	.file	"cpx-test-tail-recursion.c"
	.text
	.section .rdata,"dr"
	.align 8
.LC0:
	.ascii "%s: *** throw an exception: '%i'\12\0"
.LC1:
	.ascii "cpx-test-tail-recursion.c:11\0"
	.text
	.globl	bar
	.def	bar;	.scl	2;	.type	32;	.endef
	.seh_proc	bar
bar:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	cmpl	$4, 16(%rbp)
	jne	.L4
	movl	16(%rbp), %r8d
	leaq	__func__.3041(%rip), %rdx
	leaq	.LC0(%rip), %rcx
	call	printf
	movl	16(%rbp), %ecx
	call	_px_obj_set
	leaq	.LC1(%rip), %rcx
	call	_px_srcline_set
	leaq	__func__.3041(%rip), %rcx
	call	_px_srcfunc_set
	call	_px_ctx_getLast
	testq	%rax, %rax
	je	.L3
	call	_px_ctx_getLast
	movl	$1, %edx
	movq	%rax, %rcx
	movq	__imp_longjmp(%rip), %rax
	call	*%rax
.L3:
	call	_px_terminate_func_get
	call	*%rax
.L4:
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC2:
	.ascii "%s: *** exception caught: '%i' from <%s(),%s>\12\0"
.LC3:
	.ascii "%s: level %i\12\0"
	.align 8
.LC4:
	.ascii "%s: | set PX_CATCH and invoke bar()\12\0"
	.align 8
.LC5:
	.ascii "%s: | go to the next level...\12\0"
	.text
	.globl	foo_tail_recursion
	.def	foo_tail_recursion;	.scl	2;	.type	32;	.endef
	.seh_proc	foo_tail_recursion
foo_tail_recursion:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$304, %rsp
	.seh_stackalloc	304
	.seh_endprologue
	movl	%ecx, 32(%rbp)
	cmpl	$4, 32(%rbp)
	jle	.L14
	jmp	.L5
.L9:
	call	_px_srcline_get
	movq	%rax, %rbx
	call	_px_srcfunc_get
	movq	%rax, %rsi
	call	_px_get
	movl	(%rax), %eax
	movq	%rbx, 32(%rsp)
	movq	%rsi, %r9
	movl	%eax, %r8d
	leaq	__func__.3047(%rip), %rdx
	leaq	.LC2(%rip), %rcx
	call	printf
	jmp	.L5
.L14:
	nop
.L8:
	movl	32(%rbp), %r8d
	leaq	__func__.3047(%rip), %rdx
	leaq	.LC3(%rip), %rcx
	call	printf
	leaq	__func__.3047(%rip), %rdx
	leaq	.LC4(%rip), %rcx
	call	printf
	leaq	-256(%rbp), %rax
	movq	%rax, %rcx
	call	_px_ctx_onBegin
	testq	%rax, %rax
	je	.L10
	movq	%rbp, %rax
	movq	%rax, %rdx
	leaq	-256(%rbp), %rax
	movq	%rax, %rcx
	call	_setjmp
	testl	%eax, %eax
	je	.L10
	leaq	-256(%rbp), %rax
	movq	%rax, %rcx
	call	_px_ctx_onLongjmp
	movl	$0, %ebx
	jmp	.L12
.L10:
	movl	32(%rbp), %ecx
	call	bar
	leaq	__func__.3047(%rip), %rdx
	leaq	.LC5(%rip), %rcx
	call	printf
	movl	32(%rbp), %eax
	addl	$1, %eax
	movl	%eax, %ecx
	call	foo_tail_recursion
	movl	$1, %ebx
.L12:
	leaq	-256(%rbp), %rax
	movq	%rax, %rcx
	call	_px_ctx_onEnd
	cmpl	$1, %ebx
	jne	.L9
.L5:
	addq	$304, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	call	__main
	movl	$1, %ecx
	movq	__imp___acrt_iob_func(%rip), %rax
	call	*%rax
	movl	$0, %r9d
	movl	$4, %r8d
	movl	$0, %edx
	movq	%rax, %rcx
	call	setvbuf
	movl	$0, %ecx
	call	foo_tail_recursion
	movl	$0, %eax
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
__func__.3041:
	.ascii "bar\0"
	.align 16
__func__.3047:
	.ascii "foo_tail_recursion\0"
	.ident	"GCC: (Rev2, Built by MSYS2 project) 9.3.0"
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	_px_obj_set;	.scl	2;	.type	32;	.endef
	.def	_px_srcline_set;	.scl	2;	.type	32;	.endef
	.def	_px_srcfunc_set;	.scl	2;	.type	32;	.endef
	.def	_px_ctx_getLast;	.scl	2;	.type	32;	.endef
	.def	_px_terminate_func_get;	.scl	2;	.type	32;	.endef
	.def	_px_srcline_get;	.scl	2;	.type	32;	.endef
	.def	_px_srcfunc_get;	.scl	2;	.type	32;	.endef
	.def	_px_get;	.scl	2;	.type	32;	.endef
	.def	_px_ctx_onBegin;	.scl	2;	.type	32;	.endef
	.def	_setjmp;	.scl	2;	.type	32;	.endef
	.def	_px_ctx_onLongjmp;	.scl	2;	.type	32;	.endef
	.def	_px_ctx_onEnd;	.scl	2;	.type	32;	.endef
	.def	setvbuf;	.scl	2;	.type	32;	.endef
