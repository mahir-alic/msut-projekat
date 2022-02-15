	.cpu cortex-m4
	.eabi_attribute 27, 1
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"speed.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.align	1
	.p2align 2,,3
	.global	initSPEED
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv4-sp-d16
	.type	initSPEED, %function
initSPEED:
.LFB110:
	.file 1 "speed.c"
	.loc 1 10 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	.cfi_offset 4, -12
	.cfi_offset 5, -8
	.cfi_offset 14, -4
	.loc 1 12 0
	bl	initSYSTIMER
.LVL0:
	.loc 1 14 0
	ldr	r0, .L4
	.loc 1 15 0
	ldr	r2, .L4+4
	.loc 1 14 0
	ldr	r1, [r0, #48]
	.loc 1 22 0
	ldr	r3, .L4+8
.LBB4:
.LBB5:
	.file 2 "../sdk/core_cm4.h"
	.loc 2 1075 0
	ldr	r4, .L4+12
.LBE5:
.LBE4:
	.loc 1 14 0
	orr	r1, r1, #8
	str	r1, [r0, #48]
	.loc 1 15 0
	ldr	r1, [r2]
	bic	r1, r1, #-16777216
	str	r1, [r2]
	.loc 1 16 0
	ldr	r1, [r2]
	orr	r1, r1, #-1442840576
	str	r1, [r2]
	.loc 1 17 0
	ldr	r1, [r2, #36]
	orr	r1, r1, #570425344
	orr	r1, r1, #2228224
	str	r1, [r2, #36]
	.loc 1 20 0
	ldr	r2, [r0, #64]
	orr	r2, r2, #4
	str	r2, [r0, #64]
	.loc 1 22 0
	ldrh	r2, [r3]
	orr	r2, r2, #128
	strh	r2, [r3]	@ movhi
	.loc 1 23 0
	ldrh	r1, [r3, #4]
	.loc 1 24 0
	movs	r2, #0
	.loc 1 26 0
	movs	r0, #1
	.loc 1 23 0
	uxth	r1, r1
	.loc 1 25 0
	movs	r5, #3
	.loc 1 23 0
	strh	r1, [r3, #4]	@ movhi
	.loc 1 24 0
	str	r2, [r3, #36]
	.loc 1 25 0
	str	r5, [r3, #44]
	.loc 1 26 0
	strh	r0, [r3, #12]	@ movhi
	.loc 1 29 0
	ldrh	r1, [r3, #8]
	orr	r1, r1, #87
	strh	r1, [r3, #8]	@ movhi
	.loc 1 31 0
	str	r2, [r3, #52]
	.loc 1 32 0
	str	r2, [r3, #56]
	.loc 1 33 0
	str	r2, [r3, #60]
	.loc 1 34 0
	str	r2, [r3, #64]
	.loc 1 36 0
	ldrh	r2, [r3, #20]
	orrs	r2, r2, r0
	strh	r2, [r3, #20]	@ movhi
	.loc 1 38 0
	ldrh	r2, [r3]
.LBB8:
.LBB6:
	.loc 2 1075 0
	mov	r1, #1073741824
.LBE6:
.LBE8:
	.loc 1 38 0
	orrs	r2, r2, r0
	strh	r2, [r3]	@ movhi
.LVL1:
.LBB9:
.LBB7:
	.loc 2 1075 0
	str	r1, [r4]
.LVL2:
.LBE7:
.LBE9:
	.loc 1 45 0
	bl	getSYSTIMER
.LVL3:
	ldr	r3, .L4+16
	str	r0, [r3]
	.loc 1 46 0
	bl	getSYSTIMER
.LVL4:
	ldr	r3, .L4+20
	str	r0, [r3]
	.loc 1 47 0
	pop	{r3, r4, r5, pc}
.L5:
	.align	2
.L4:
	.word	1073887232
	.word	1073875968
	.word	1073743872
	.word	-536813312
	.word	.LANCHOR0
	.word	speedTimeOut
	.cfi_endproc
.LFE110:
	.size	initSPEED, .-initSPEED
	.align	1
	.p2align 2,,3
	.global	setNCirc
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv4-sp-d16
	.type	setNCirc, %function
setNCirc:
.LFB111:
	.loc 1 49 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
.LVL5:
	.loc 1 51 0
	add	r0, r0, r0, lsl #1
.LVL6:
	lsls	r3, r0, #1
	vmov	s15, r3	@ int
	vldr.32	s14, .L7
	ldr	r3, .L7+4
	vcvt.f32.s32	s15, s15
	vmul.f32	s15, s15, s14
	vstr.32	s15, [r3, #4]
	.loc 1 52 0
	bx	lr
.L8:
	.align	2
.L7:
	.word	1078530000
	.word	.LANCHOR0
	.cfi_endproc
.LFE111:
	.size	setNCirc, .-setNCirc
	.align	1
	.p2align 2,,3
	.global	TIM4_IRQHandler
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv4-sp-d16
	.type	TIM4_IRQHandler, %function
TIM4_IRQHandler:
.LFB112:
	.loc 1 54 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 55 0
	ldr	r3, .L15
	ldrh	r3, [r3, #16]
	lsls	r3, r3, #31
	.loc 1 54 0
	push	{r4, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	.loc 1 55 0
	bpl	.L10
.LBB10:
	.loc 1 57 0
	ldr	r4, .L15+4
	.loc 1 56 0
	bl	getSYSTIMER
.LVL7:
	ldr	r3, [r4]
	.loc 1 57 0
	vldr.32	s13, [r4, #4]
	vldr.32	s14, .L15+8
	.loc 1 56 0
	subs	r0, r0, r3
.LVL8:
	vmov	s15, r0	@ int
	.loc 1 57 0
	vmul.f32	s13, s13, s14
	.loc 1 56 0
	vcvt.f32.u32	s15, s15
.LVL9:
	.loc 1 57 0
	vdiv.f32	s14, s13, s15
	vcvt.s32.f32	s14, s14
	vstr.32	s14, [r4, #8]	@ int
	.loc 1 59 0
	bl	getSYSTIMER
.LVL10:
	str	r0, [r4]
	.loc 1 60 0
	bl	getSYSTIMER
.LVL11:
	.loc 1 61 0
	vldr.32	s12, [r4, #4]
	vldr.32	s13, .L15+12
	vldr.32	s14, [r4, #12]
	.loc 1 60 0
	ldr	r3, .L15+16
	.loc 1 61 0
	vdiv.f32	s15, s12, s13
	.loc 1 60 0
	str	r0, [r3]
	.loc 1 61 0
	vadd.f32	s15, s15, s14
	vstr.32	s15, [r4, #12]
.L10:
.LBE10:
	.loc 1 64 0
	ldr	r2, .L15
	ldrh	r3, [r2, #16]
	bic	r3, r3, #1
	lsls	r3, r3, #16
	lsrs	r3, r3, #16
	strh	r3, [r2, #16]	@ movhi
	.loc 1 66 0
	pop	{r4, pc}
.L16:
	.align	2
.L15:
	.word	1073743872
	.word	.LANCHOR0
	.word	1080452710
	.word	1148846080
	.word	speedTimeOut
	.cfi_endproc
.LFE112:
	.size	TIM4_IRQHandler, .-TIM4_IRQHandler
	.global	distance
	.global	radius
	.global	speed
	.global	n_circ
	.comm	speedTimeOut,4,4
	.global	speedTime
	.bss
	.align	2
	.set	.LANCHOR0,. + 0
	.type	speedTime, %object
	.size	speedTime, 4
speedTime:
	.space	4
	.type	n_circ, %object
	.size	n_circ, 4
n_circ:
	.space	4
	.type	speed, %object
	.size	speed, 4
speed:
	.space	4
	.type	distance, %object
	.size	distance, 4
distance:
	.space	4
	.type	radius, %object
	.size	radius, 2
radius:
	.space	2
	.text
.Letext0:
	.file 3 "../sdk/stm32f4xx.h"
	.file 4 "/home/mahir/msut/gcc-arm-none-eabi/arm-none-eabi/include/machine/_default_types.h"
	.file 5 "/home/mahir/msut/gcc-arm-none-eabi/arm-none-eabi/include/sys/_stdint.h"
	.file 6 "../sdk/system_stm32f4xx.h"
	.file 7 "speed.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0xa37
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF187
	.byte	0xc
	.4byte	.LASF188
	.4byte	.LASF189
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF0
	.uleb128 0x2
	.byte	0x4
	.byte	0x4
	.4byte	.LASF1
	.uleb128 0x3
	.4byte	.LASF190
	.byte	0x5
	.byte	0x1
	.4byte	0x261
	.byte	0x3
	.byte	0x91
	.4byte	0x261
	.uleb128 0x4
	.4byte	.LASF2
	.sleb128 -14
	.uleb128 0x4
	.4byte	.LASF3
	.sleb128 -12
	.uleb128 0x4
	.4byte	.LASF4
	.sleb128 -11
	.uleb128 0x4
	.4byte	.LASF5
	.sleb128 -10
	.uleb128 0x4
	.4byte	.LASF6
	.sleb128 -5
	.uleb128 0x4
	.4byte	.LASF7
	.sleb128 -4
	.uleb128 0x4
	.4byte	.LASF8
	.sleb128 -2
	.uleb128 0x4
	.4byte	.LASF9
	.sleb128 -1
	.uleb128 0x5
	.4byte	.LASF10
	.byte	0
	.uleb128 0x5
	.4byte	.LASF11
	.byte	0x1
	.uleb128 0x5
	.4byte	.LASF12
	.byte	0x2
	.uleb128 0x5
	.4byte	.LASF13
	.byte	0x3
	.uleb128 0x5
	.4byte	.LASF14
	.byte	0x4
	.uleb128 0x5
	.4byte	.LASF15
	.byte	0x5
	.uleb128 0x5
	.4byte	.LASF16
	.byte	0x6
	.uleb128 0x5
	.4byte	.LASF17
	.byte	0x7
	.uleb128 0x5
	.4byte	.LASF18
	.byte	0x8
	.uleb128 0x5
	.4byte	.LASF19
	.byte	0x9
	.uleb128 0x5
	.4byte	.LASF20
	.byte	0xa
	.uleb128 0x5
	.4byte	.LASF21
	.byte	0xb
	.uleb128 0x5
	.4byte	.LASF22
	.byte	0xc
	.uleb128 0x5
	.4byte	.LASF23
	.byte	0xd
	.uleb128 0x5
	.4byte	.LASF24
	.byte	0xe
	.uleb128 0x5
	.4byte	.LASF25
	.byte	0xf
	.uleb128 0x5
	.4byte	.LASF26
	.byte	0x10
	.uleb128 0x5
	.4byte	.LASF27
	.byte	0x11
	.uleb128 0x5
	.4byte	.LASF28
	.byte	0x12
	.uleb128 0x5
	.4byte	.LASF29
	.byte	0x13
	.uleb128 0x5
	.4byte	.LASF30
	.byte	0x14
	.uleb128 0x5
	.4byte	.LASF31
	.byte	0x15
	.uleb128 0x5
	.4byte	.LASF32
	.byte	0x16
	.uleb128 0x5
	.4byte	.LASF33
	.byte	0x17
	.uleb128 0x5
	.4byte	.LASF34
	.byte	0x18
	.uleb128 0x5
	.4byte	.LASF35
	.byte	0x19
	.uleb128 0x5
	.4byte	.LASF36
	.byte	0x1a
	.uleb128 0x5
	.4byte	.LASF37
	.byte	0x1b
	.uleb128 0x5
	.4byte	.LASF38
	.byte	0x1c
	.uleb128 0x5
	.4byte	.LASF39
	.byte	0x1d
	.uleb128 0x5
	.4byte	.LASF40
	.byte	0x1e
	.uleb128 0x5
	.4byte	.LASF41
	.byte	0x1f
	.uleb128 0x5
	.4byte	.LASF42
	.byte	0x20
	.uleb128 0x5
	.4byte	.LASF43
	.byte	0x21
	.uleb128 0x5
	.4byte	.LASF44
	.byte	0x22
	.uleb128 0x5
	.4byte	.LASF45
	.byte	0x23
	.uleb128 0x5
	.4byte	.LASF46
	.byte	0x24
	.uleb128 0x5
	.4byte	.LASF47
	.byte	0x25
	.uleb128 0x5
	.4byte	.LASF48
	.byte	0x26
	.uleb128 0x5
	.4byte	.LASF49
	.byte	0x27
	.uleb128 0x5
	.4byte	.LASF50
	.byte	0x28
	.uleb128 0x5
	.4byte	.LASF51
	.byte	0x29
	.uleb128 0x5
	.4byte	.LASF52
	.byte	0x2a
	.uleb128 0x5
	.4byte	.LASF53
	.byte	0x2b
	.uleb128 0x5
	.4byte	.LASF54
	.byte	0x2c
	.uleb128 0x5
	.4byte	.LASF55
	.byte	0x2d
	.uleb128 0x5
	.4byte	.LASF56
	.byte	0x2e
	.uleb128 0x5
	.4byte	.LASF57
	.byte	0x2f
	.uleb128 0x5
	.4byte	.LASF58
	.byte	0x30
	.uleb128 0x5
	.4byte	.LASF59
	.byte	0x31
	.uleb128 0x5
	.4byte	.LASF60
	.byte	0x32
	.uleb128 0x5
	.4byte	.LASF61
	.byte	0x33
	.uleb128 0x5
	.4byte	.LASF62
	.byte	0x34
	.uleb128 0x5
	.4byte	.LASF63
	.byte	0x35
	.uleb128 0x5
	.4byte	.LASF64
	.byte	0x36
	.uleb128 0x5
	.4byte	.LASF65
	.byte	0x37
	.uleb128 0x5
	.4byte	.LASF66
	.byte	0x38
	.uleb128 0x5
	.4byte	.LASF67
	.byte	0x39
	.uleb128 0x5
	.4byte	.LASF68
	.byte	0x3a
	.uleb128 0x5
	.4byte	.LASF69
	.byte	0x3b
	.uleb128 0x5
	.4byte	.LASF70
	.byte	0x3c
	.uleb128 0x5
	.4byte	.LASF71
	.byte	0x3d
	.uleb128 0x5
	.4byte	.LASF72
	.byte	0x3e
	.uleb128 0x5
	.4byte	.LASF73
	.byte	0x3f
	.uleb128 0x5
	.4byte	.LASF74
	.byte	0x40
	.uleb128 0x5
	.4byte	.LASF75
	.byte	0x41
	.uleb128 0x5
	.4byte	.LASF76
	.byte	0x42
	.uleb128 0x5
	.4byte	.LASF77
	.byte	0x43
	.uleb128 0x5
	.4byte	.LASF78
	.byte	0x44
	.uleb128 0x5
	.4byte	.LASF79
	.byte	0x45
	.uleb128 0x5
	.4byte	.LASF80
	.byte	0x46
	.uleb128 0x5
	.4byte	.LASF81
	.byte	0x47
	.uleb128 0x5
	.4byte	.LASF82
	.byte	0x48
	.uleb128 0x5
	.4byte	.LASF83
	.byte	0x49
	.uleb128 0x5
	.4byte	.LASF84
	.byte	0x4a
	.uleb128 0x5
	.4byte	.LASF85
	.byte	0x4b
	.uleb128 0x5
	.4byte	.LASF86
	.byte	0x4c
	.uleb128 0x5
	.4byte	.LASF87
	.byte	0x4d
	.uleb128 0x5
	.4byte	.LASF88
	.byte	0x4e
	.uleb128 0x5
	.4byte	.LASF89
	.byte	0x4f
	.uleb128 0x5
	.4byte	.LASF90
	.byte	0x50
	.uleb128 0x5
	.4byte	.LASF91
	.byte	0x51
	.byte	0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF92
	.uleb128 0x6
	.4byte	.LASF93
	.byte	0x3
	.byte	0xef
	.4byte	0x33
	.uleb128 0x6
	.4byte	.LASF94
	.byte	0x4
	.byte	0x2b
	.4byte	0x27e
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF95
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF96
	.uleb128 0x6
	.4byte	.LASF97
	.byte	0x4
	.byte	0x39
	.4byte	0x297
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF98
	.uleb128 0x6
	.4byte	.LASF99
	.byte	0x4
	.byte	0x4d
	.4byte	0x2a9
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF100
	.uleb128 0x6
	.4byte	.LASF101
	.byte	0x4
	.byte	0x4f
	.4byte	0x2bb
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF102
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF103
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF104
	.uleb128 0x7
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x6
	.4byte	.LASF105
	.byte	0x5
	.byte	0x18
	.4byte	0x273
	.uleb128 0x8
	.4byte	0x2d7
	.uleb128 0x6
	.4byte	.LASF106
	.byte	0x5
	.byte	0x24
	.4byte	0x28c
	.uleb128 0x8
	.4byte	0x2e7
	.uleb128 0x6
	.4byte	.LASF107
	.byte	0x5
	.byte	0x2c
	.4byte	0x29e
	.uleb128 0x8
	.4byte	0x2f7
	.uleb128 0x6
	.4byte	.LASF108
	.byte	0x5
	.byte	0x30
	.4byte	0x2b0
	.uleb128 0x8
	.4byte	0x307
	.uleb128 0x9
	.2byte	0xe04
	.byte	0x2
	.2byte	0x130
	.4byte	0x3d3
	.uleb128 0xa
	.4byte	.LASF109
	.byte	0x2
	.2byte	0x132
	.4byte	0x3e3
	.byte	0
	.uleb128 0xa
	.4byte	.LASF110
	.byte	0x2
	.2byte	0x133
	.4byte	0x3e8
	.byte	0x20
	.uleb128 0xa
	.4byte	.LASF111
	.byte	0x2
	.2byte	0x134
	.4byte	0x3e3
	.byte	0x80
	.uleb128 0xa
	.4byte	.LASF112
	.byte	0x2
	.2byte	0x135
	.4byte	0x3e8
	.byte	0xa0
	.uleb128 0xb
	.4byte	.LASF113
	.byte	0x2
	.2byte	0x136
	.4byte	0x3e3
	.2byte	0x100
	.uleb128 0xb
	.4byte	.LASF114
	.byte	0x2
	.2byte	0x137
	.4byte	0x3e8
	.2byte	0x120
	.uleb128 0xb
	.4byte	.LASF115
	.byte	0x2
	.2byte	0x138
	.4byte	0x3e3
	.2byte	0x180
	.uleb128 0xb
	.4byte	.LASF116
	.byte	0x2
	.2byte	0x139
	.4byte	0x3e8
	.2byte	0x1a0
	.uleb128 0xb
	.4byte	.LASF117
	.byte	0x2
	.2byte	0x13a
	.4byte	0x3e3
	.2byte	0x200
	.uleb128 0xb
	.4byte	.LASF118
	.byte	0x2
	.2byte	0x13b
	.4byte	0x3f8
	.2byte	0x220
	.uleb128 0xc
	.ascii	"IP\000"
	.byte	0x2
	.2byte	0x13c
	.4byte	0x418
	.2byte	0x300
	.uleb128 0xb
	.4byte	.LASF119
	.byte	0x2
	.2byte	0x13d
	.4byte	0x41d
	.2byte	0x3f0
	.uleb128 0xb
	.4byte	.LASF120
	.byte	0x2
	.2byte	0x13e
	.4byte	0x312
	.2byte	0xe00
	.byte	0
	.uleb128 0xd
	.4byte	0x312
	.4byte	0x3e3
	.uleb128 0xe
	.4byte	0x25
	.byte	0x7
	.byte	0
	.uleb128 0x8
	.4byte	0x3d3
	.uleb128 0xd
	.4byte	0x307
	.4byte	0x3f8
	.uleb128 0xe
	.4byte	0x25
	.byte	0x17
	.byte	0
	.uleb128 0xd
	.4byte	0x307
	.4byte	0x408
	.uleb128 0xe
	.4byte	0x25
	.byte	0x37
	.byte	0
	.uleb128 0xd
	.4byte	0x2e2
	.4byte	0x418
	.uleb128 0xe
	.4byte	0x25
	.byte	0xef
	.byte	0
	.uleb128 0x8
	.4byte	0x408
	.uleb128 0xd
	.4byte	0x307
	.4byte	0x42e
	.uleb128 0xf
	.4byte	0x25
	.2byte	0x283
	.byte	0
	.uleb128 0x10
	.4byte	.LASF121
	.byte	0x2
	.2byte	0x13f
	.4byte	0x317
	.uleb128 0x11
	.4byte	.LASF122
	.byte	0x2
	.2byte	0x51b
	.4byte	0x302
	.uleb128 0x12
	.4byte	.LASF123
	.byte	0x6
	.byte	0x35
	.4byte	0x307
	.uleb128 0xd
	.4byte	0x307
	.4byte	0x461
	.uleb128 0xe
	.4byte	0x25
	.byte	0x1
	.byte	0
	.uleb128 0x13
	.byte	0x28
	.byte	0x3
	.2byte	0x28e
	.4byte	0x4ed
	.uleb128 0xa
	.4byte	.LASF124
	.byte	0x3
	.2byte	0x290
	.4byte	0x312
	.byte	0
	.uleb128 0xa
	.4byte	.LASF125
	.byte	0x3
	.2byte	0x291
	.4byte	0x312
	.byte	0x4
	.uleb128 0xa
	.4byte	.LASF126
	.byte	0x3
	.2byte	0x292
	.4byte	0x312
	.byte	0x8
	.uleb128 0xa
	.4byte	.LASF127
	.byte	0x3
	.2byte	0x293
	.4byte	0x312
	.byte	0xc
	.uleb128 0x14
	.ascii	"IDR\000"
	.byte	0x3
	.2byte	0x294
	.4byte	0x312
	.byte	0x10
	.uleb128 0x14
	.ascii	"ODR\000"
	.byte	0x3
	.2byte	0x295
	.4byte	0x312
	.byte	0x14
	.uleb128 0xa
	.4byte	.LASF128
	.byte	0x3
	.2byte	0x296
	.4byte	0x2f2
	.byte	0x18
	.uleb128 0xa
	.4byte	.LASF129
	.byte	0x3
	.2byte	0x297
	.4byte	0x2f2
	.byte	0x1a
	.uleb128 0xa
	.4byte	.LASF130
	.byte	0x3
	.2byte	0x298
	.4byte	0x312
	.byte	0x1c
	.uleb128 0x14
	.ascii	"AFR\000"
	.byte	0x3
	.2byte	0x299
	.4byte	0x4fd
	.byte	0x20
	.byte	0
	.uleb128 0xd
	.4byte	0x312
	.4byte	0x4fd
	.uleb128 0xe
	.4byte	0x25
	.byte	0x1
	.byte	0
	.uleb128 0x8
	.4byte	0x4ed
	.uleb128 0x10
	.4byte	.LASF131
	.byte	0x3
	.2byte	0x29a
	.4byte	0x461
	.uleb128 0x13
	.byte	0x88
	.byte	0x3
	.2byte	0x2dd
	.4byte	0x69d
	.uleb128 0x14
	.ascii	"CR\000"
	.byte	0x3
	.2byte	0x2df
	.4byte	0x312
	.byte	0
	.uleb128 0xa
	.4byte	.LASF132
	.byte	0x3
	.2byte	0x2e0
	.4byte	0x312
	.byte	0x4
	.uleb128 0xa
	.4byte	.LASF133
	.byte	0x3
	.2byte	0x2e1
	.4byte	0x312
	.byte	0x8
	.uleb128 0x14
	.ascii	"CIR\000"
	.byte	0x3
	.2byte	0x2e2
	.4byte	0x312
	.byte	0xc
	.uleb128 0xa
	.4byte	.LASF134
	.byte	0x3
	.2byte	0x2e3
	.4byte	0x312
	.byte	0x10
	.uleb128 0xa
	.4byte	.LASF135
	.byte	0x3
	.2byte	0x2e4
	.4byte	0x312
	.byte	0x14
	.uleb128 0xa
	.4byte	.LASF136
	.byte	0x3
	.2byte	0x2e5
	.4byte	0x312
	.byte	0x18
	.uleb128 0xa
	.4byte	.LASF110
	.byte	0x3
	.2byte	0x2e6
	.4byte	0x307
	.byte	0x1c
	.uleb128 0xa
	.4byte	.LASF137
	.byte	0x3
	.2byte	0x2e7
	.4byte	0x312
	.byte	0x20
	.uleb128 0xa
	.4byte	.LASF138
	.byte	0x3
	.2byte	0x2e8
	.4byte	0x312
	.byte	0x24
	.uleb128 0xa
	.4byte	.LASF139
	.byte	0x3
	.2byte	0x2e9
	.4byte	0x451
	.byte	0x28
	.uleb128 0xa
	.4byte	.LASF140
	.byte	0x3
	.2byte	0x2ea
	.4byte	0x312
	.byte	0x30
	.uleb128 0xa
	.4byte	.LASF141
	.byte	0x3
	.2byte	0x2eb
	.4byte	0x312
	.byte	0x34
	.uleb128 0xa
	.4byte	.LASF142
	.byte	0x3
	.2byte	0x2ec
	.4byte	0x312
	.byte	0x38
	.uleb128 0xa
	.4byte	.LASF114
	.byte	0x3
	.2byte	0x2ed
	.4byte	0x307
	.byte	0x3c
	.uleb128 0xa
	.4byte	.LASF143
	.byte	0x3
	.2byte	0x2ee
	.4byte	0x312
	.byte	0x40
	.uleb128 0xa
	.4byte	.LASF144
	.byte	0x3
	.2byte	0x2ef
	.4byte	0x312
	.byte	0x44
	.uleb128 0xa
	.4byte	.LASF116
	.byte	0x3
	.2byte	0x2f0
	.4byte	0x451
	.byte	0x48
	.uleb128 0xa
	.4byte	.LASF145
	.byte	0x3
	.2byte	0x2f1
	.4byte	0x312
	.byte	0x50
	.uleb128 0xa
	.4byte	.LASF146
	.byte	0x3
	.2byte	0x2f2
	.4byte	0x312
	.byte	0x54
	.uleb128 0xa
	.4byte	.LASF147
	.byte	0x3
	.2byte	0x2f3
	.4byte	0x312
	.byte	0x58
	.uleb128 0xa
	.4byte	.LASF118
	.byte	0x3
	.2byte	0x2f4
	.4byte	0x307
	.byte	0x5c
	.uleb128 0xa
	.4byte	.LASF148
	.byte	0x3
	.2byte	0x2f5
	.4byte	0x312
	.byte	0x60
	.uleb128 0xa
	.4byte	.LASF149
	.byte	0x3
	.2byte	0x2f6
	.4byte	0x312
	.byte	0x64
	.uleb128 0xa
	.4byte	.LASF119
	.byte	0x3
	.2byte	0x2f7
	.4byte	0x451
	.byte	0x68
	.uleb128 0xa
	.4byte	.LASF150
	.byte	0x3
	.2byte	0x2f8
	.4byte	0x312
	.byte	0x70
	.uleb128 0x14
	.ascii	"CSR\000"
	.byte	0x3
	.2byte	0x2f9
	.4byte	0x312
	.byte	0x74
	.uleb128 0xa
	.4byte	.LASF151
	.byte	0x3
	.2byte	0x2fa
	.4byte	0x451
	.byte	0x78
	.uleb128 0xa
	.4byte	.LASF152
	.byte	0x3
	.2byte	0x2fb
	.4byte	0x312
	.byte	0x80
	.uleb128 0xa
	.4byte	.LASF153
	.byte	0x3
	.2byte	0x2fc
	.4byte	0x312
	.byte	0x84
	.byte	0
	.uleb128 0x10
	.4byte	.LASF154
	.byte	0x3
	.2byte	0x2fd
	.4byte	0x50e
	.uleb128 0x13
	.byte	0x54
	.byte	0x3
	.2byte	0x369
	.4byte	0x885
	.uleb128 0x14
	.ascii	"CR1\000"
	.byte	0x3
	.2byte	0x36b
	.4byte	0x2f2
	.byte	0
	.uleb128 0xa
	.4byte	.LASF110
	.byte	0x3
	.2byte	0x36c
	.4byte	0x2e7
	.byte	0x2
	.uleb128 0x14
	.ascii	"CR2\000"
	.byte	0x3
	.2byte	0x36d
	.4byte	0x2f2
	.byte	0x4
	.uleb128 0xa
	.4byte	.LASF139
	.byte	0x3
	.2byte	0x36e
	.4byte	0x2e7
	.byte	0x6
	.uleb128 0xa
	.4byte	.LASF155
	.byte	0x3
	.2byte	0x36f
	.4byte	0x2f2
	.byte	0x8
	.uleb128 0xa
	.4byte	.LASF114
	.byte	0x3
	.2byte	0x370
	.4byte	0x2e7
	.byte	0xa
	.uleb128 0xa
	.4byte	.LASF156
	.byte	0x3
	.2byte	0x371
	.4byte	0x2f2
	.byte	0xc
	.uleb128 0xa
	.4byte	.LASF116
	.byte	0x3
	.2byte	0x372
	.4byte	0x2e7
	.byte	0xe
	.uleb128 0x14
	.ascii	"SR\000"
	.byte	0x3
	.2byte	0x373
	.4byte	0x2f2
	.byte	0x10
	.uleb128 0xa
	.4byte	.LASF118
	.byte	0x3
	.2byte	0x374
	.4byte	0x2e7
	.byte	0x12
	.uleb128 0x14
	.ascii	"EGR\000"
	.byte	0x3
	.2byte	0x375
	.4byte	0x2f2
	.byte	0x14
	.uleb128 0xa
	.4byte	.LASF119
	.byte	0x3
	.2byte	0x376
	.4byte	0x2e7
	.byte	0x16
	.uleb128 0xa
	.4byte	.LASF157
	.byte	0x3
	.2byte	0x377
	.4byte	0x2f2
	.byte	0x18
	.uleb128 0xa
	.4byte	.LASF151
	.byte	0x3
	.2byte	0x378
	.4byte	0x2e7
	.byte	0x1a
	.uleb128 0xa
	.4byte	.LASF158
	.byte	0x3
	.2byte	0x379
	.4byte	0x2f2
	.byte	0x1c
	.uleb128 0xa
	.4byte	.LASF159
	.byte	0x3
	.2byte	0x37a
	.4byte	0x2e7
	.byte	0x1e
	.uleb128 0xa
	.4byte	.LASF160
	.byte	0x3
	.2byte	0x37b
	.4byte	0x2f2
	.byte	0x20
	.uleb128 0xa
	.4byte	.LASF161
	.byte	0x3
	.2byte	0x37c
	.4byte	0x2e7
	.byte	0x22
	.uleb128 0x14
	.ascii	"CNT\000"
	.byte	0x3
	.2byte	0x37d
	.4byte	0x312
	.byte	0x24
	.uleb128 0x14
	.ascii	"PSC\000"
	.byte	0x3
	.2byte	0x37e
	.4byte	0x2f2
	.byte	0x28
	.uleb128 0xa
	.4byte	.LASF162
	.byte	0x3
	.2byte	0x37f
	.4byte	0x2e7
	.byte	0x2a
	.uleb128 0x14
	.ascii	"ARR\000"
	.byte	0x3
	.2byte	0x380
	.4byte	0x312
	.byte	0x2c
	.uleb128 0x14
	.ascii	"RCR\000"
	.byte	0x3
	.2byte	0x381
	.4byte	0x2f2
	.byte	0x30
	.uleb128 0xa
	.4byte	.LASF163
	.byte	0x3
	.2byte	0x382
	.4byte	0x2e7
	.byte	0x32
	.uleb128 0xa
	.4byte	.LASF164
	.byte	0x3
	.2byte	0x383
	.4byte	0x312
	.byte	0x34
	.uleb128 0xa
	.4byte	.LASF165
	.byte	0x3
	.2byte	0x384
	.4byte	0x312
	.byte	0x38
	.uleb128 0xa
	.4byte	.LASF166
	.byte	0x3
	.2byte	0x385
	.4byte	0x312
	.byte	0x3c
	.uleb128 0xa
	.4byte	.LASF167
	.byte	0x3
	.2byte	0x386
	.4byte	0x312
	.byte	0x40
	.uleb128 0xa
	.4byte	.LASF168
	.byte	0x3
	.2byte	0x387
	.4byte	0x2f2
	.byte	0x44
	.uleb128 0xa
	.4byte	.LASF169
	.byte	0x3
	.2byte	0x388
	.4byte	0x2e7
	.byte	0x46
	.uleb128 0x14
	.ascii	"DCR\000"
	.byte	0x3
	.2byte	0x389
	.4byte	0x2f2
	.byte	0x48
	.uleb128 0xa
	.4byte	.LASF170
	.byte	0x3
	.2byte	0x38a
	.4byte	0x2e7
	.byte	0x4a
	.uleb128 0xa
	.4byte	.LASF171
	.byte	0x3
	.2byte	0x38b
	.4byte	0x2f2
	.byte	0x4c
	.uleb128 0xa
	.4byte	.LASF172
	.byte	0x3
	.2byte	0x38c
	.4byte	0x2e7
	.byte	0x4e
	.uleb128 0x14
	.ascii	"OR\000"
	.byte	0x3
	.2byte	0x38d
	.4byte	0x2f2
	.byte	0x50
	.uleb128 0xa
	.4byte	.LASF173
	.byte	0x3
	.2byte	0x38e
	.4byte	0x2e7
	.byte	0x52
	.byte	0
	.uleb128 0x10
	.4byte	.LASF174
	.byte	0x3
	.2byte	0x38f
	.4byte	0x6a9
	.uleb128 0x15
	.4byte	.LASF175
	.byte	0x7
	.byte	0x9
	.4byte	0x307
	.uleb128 0x5
	.byte	0x3
	.4byte	speedTime
	.uleb128 0x15
	.4byte	.LASF176
	.byte	0x7
	.byte	0xa
	.4byte	0x307
	.uleb128 0x5
	.byte	0x3
	.4byte	speedTimeOut
	.uleb128 0x12
	.4byte	.LASF177
	.byte	0x7
	.byte	0xb
	.4byte	0x2d0
	.uleb128 0x12
	.4byte	.LASF178
	.byte	0x7
	.byte	0xc
	.4byte	0x2e7
	.uleb128 0x12
	.4byte	.LASF179
	.byte	0x7
	.byte	0xe
	.4byte	0x2c
	.uleb128 0x15
	.4byte	.LASF180
	.byte	0x7
	.byte	0x10
	.4byte	0x2c
	.uleb128 0x5
	.byte	0x3
	.4byte	n_circ
	.uleb128 0x16
	.4byte	0x8b3
	.byte	0x1
	.byte	0x5
	.uleb128 0x5
	.byte	0x3
	.4byte	speed
	.uleb128 0x16
	.4byte	0x8be
	.byte	0x1
	.byte	0x6
	.uleb128 0x5
	.byte	0x3
	.4byte	radius
	.uleb128 0x16
	.4byte	0x8c9
	.byte	0x1
	.byte	0x8
	.uleb128 0x5
	.byte	0x3
	.4byte	distance
	.uleb128 0x17
	.4byte	.LASF191
	.byte	0x1
	.byte	0x36
	.4byte	.LFB112
	.4byte	.LFE112-.LFB112
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x967
	.uleb128 0x18
	.4byte	.LBB10
	.4byte	.LBE10-.LBB10
	.uleb128 0x19
	.4byte	.LASF185
	.byte	0x1
	.byte	0x38
	.4byte	0x2c
	.4byte	.LLST2
	.uleb128 0x1a
	.4byte	.LASF183
	.byte	0x1
	.byte	0x2d
	.4byte	0x2d0
	.4byte	0x94a
	.uleb128 0x1b
	.byte	0
	.uleb128 0x1c
	.4byte	.LVL7
	.4byte	0xa24
	.uleb128 0x1c
	.4byte	.LVL10
	.4byte	0xa24
	.uleb128 0x1c
	.4byte	.LVL11
	.4byte	0xa24
	.byte	0
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF181
	.byte	0x1
	.byte	0x31
	.4byte	.LFB111
	.4byte	.LFE111-.LFB111
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x98a
	.uleb128 0x1e
	.ascii	"r\000"
	.byte	0x1
	.byte	0x31
	.4byte	0x2e7
	.4byte	.LLST1
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF182
	.byte	0x1
	.byte	0xa
	.4byte	.LFB110
	.4byte	.LFE110-.LFB110
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xa0a
	.uleb128 0x1a
	.4byte	.LASF184
	.byte	0x1
	.byte	0xc
	.4byte	0x2d0
	.4byte	0x9b0
	.uleb128 0x1b
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF186
	.byte	0x1
	.byte	0x2b
	.4byte	0x2c
	.byte	0x4
	.4byte	0
	.uleb128 0x1a
	.4byte	.LASF183
	.byte	0x1
	.byte	0x2d
	.4byte	0x2d0
	.4byte	0x9d1
	.uleb128 0x1b
	.byte	0
	.uleb128 0x20
	.4byte	0xa0a
	.4byte	.LBB4
	.4byte	.Ldebug_ranges0+0
	.byte	0x1
	.byte	0x28
	.4byte	0x9ee
	.uleb128 0x21
	.4byte	0xa17
	.4byte	.LLST0
	.byte	0
	.uleb128 0x1c
	.4byte	.LVL0
	.4byte	0xa2f
	.uleb128 0x1c
	.4byte	.LVL3
	.4byte	0xa24
	.uleb128 0x1c
	.4byte	.LVL4
	.4byte	0xa24
	.byte	0
	.uleb128 0x22
	.4byte	.LASF192
	.byte	0x2
	.2byte	0x430
	.byte	0x3
	.4byte	0xa24
	.uleb128 0x23
	.4byte	.LASF190
	.byte	0x2
	.2byte	0x430
	.4byte	0x268
	.byte	0
	.uleb128 0x24
	.4byte	.LASF183
	.4byte	.LASF183
	.byte	0x1
	.byte	0x2d
	.uleb128 0x24
	.4byte	.LASF184
	.4byte	.LASF184
	.byte	0x1
	.byte	0xc
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x34
	.byte	0
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST2:
	.4byte	.LVL7-.Ltext0
	.4byte	.LVL8-.Ltext0
	.2byte	0xe
	.byte	0x70
	.sleb128 0
	.byte	0x3
	.4byte	speedTime
	.byte	0x6
	.byte	0x1c
	.byte	0xf7
	.uleb128 0x25
	.byte	0xf7
	.uleb128 0x2c
	.byte	0x9f
	.4byte	.LVL9-.Ltext0
	.4byte	.LVL10-1-.Ltext0
	.2byte	0x2
	.byte	0x90
	.uleb128 0x4f
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LVL5-.Ltext0
	.4byte	.LVL6-.Ltext0
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL6-.Ltext0
	.4byte	.LFE111-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST0:
	.4byte	.LVL1-.Ltext0
	.4byte	.LVL2-.Ltext0
	.2byte	0x2
	.byte	0x4e
	.byte	0x9f
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LBB4-.Ltext0
	.4byte	.LBE4-.Ltext0
	.4byte	.LBB8-.Ltext0
	.4byte	.LBE8-.Ltext0
	.4byte	.LBB9-.Ltext0
	.4byte	.LBE9-.Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF88:
	.ascii	"DCMI_IRQn\000"
.LASF90:
	.ascii	"HASH_RNG_IRQn\000"
.LASF143:
	.ascii	"APB1ENR\000"
.LASF123:
	.ascii	"SystemCoreClock\000"
.LASF157:
	.ascii	"CCMR1\000"
.LASF149:
	.ascii	"APB2LPENR\000"
.LASF78:
	.ascii	"DMA2_Stream5_IRQn\000"
.LASF59:
	.ascii	"SDIO_IRQn\000"
.LASF138:
	.ascii	"APB2RSTR\000"
.LASF32:
	.ascii	"CAN1_SCE_IRQn\000"
.LASF89:
	.ascii	"CRYP_IRQn\000"
.LASF44:
	.ascii	"I2C2_ER_IRQn\000"
.LASF66:
	.ascii	"DMA2_Stream0_IRQn\000"
.LASF40:
	.ascii	"TIM4_IRQn\000"
.LASF72:
	.ascii	"ETH_WKUP_IRQn\000"
.LASF0:
	.ascii	"unsigned int\000"
.LASF26:
	.ascii	"DMA1_Stream5_IRQn\000"
.LASF150:
	.ascii	"BDCR\000"
.LASF99:
	.ascii	"__int32_t\000"
.LASF21:
	.ascii	"DMA1_Stream0_IRQn\000"
.LASF14:
	.ascii	"FLASH_IRQn\000"
.LASF16:
	.ascii	"EXTI0_IRQn\000"
.LASF85:
	.ascii	"OTG_HS_EP1_IN_IRQn\000"
.LASF50:
	.ascii	"EXTI15_10_IRQn\000"
.LASF182:
	.ascii	"initSPEED\000"
.LASF53:
	.ascii	"TIM8_BRK_TIM12_IRQn\000"
.LASF186:
	.ascii	"prev\000"
.LASF146:
	.ascii	"AHB2LPENR\000"
.LASF8:
	.ascii	"PendSV_IRQn\000"
.LASF52:
	.ascii	"OTG_FS_WKUP_IRQn\000"
.LASF62:
	.ascii	"UART4_IRQn\000"
.LASF177:
	.ascii	"speed\000"
.LASF176:
	.ascii	"speedTimeOut\000"
.LASF15:
	.ascii	"RCC_IRQn\000"
.LASF3:
	.ascii	"MemoryManagement_IRQn\000"
.LASF174:
	.ascii	"TIM_TypeDef\000"
.LASF92:
	.ascii	"signed char\000"
.LASF160:
	.ascii	"CCER\000"
.LASF108:
	.ascii	"uint32_t\000"
.LASF184:
	.ascii	"initSYSTIMER\000"
.LASF12:
	.ascii	"TAMP_STAMP_IRQn\000"
.LASF168:
	.ascii	"BDTR\000"
.LASF109:
	.ascii	"ISER\000"
.LASF1:
	.ascii	"float\000"
.LASF77:
	.ascii	"OTG_FS_IRQn\000"
.LASF140:
	.ascii	"AHB1ENR\000"
.LASF164:
	.ascii	"CCR1\000"
.LASF152:
	.ascii	"SSCGR\000"
.LASF166:
	.ascii	"CCR3\000"
.LASF112:
	.ascii	"RSERVED1\000"
.LASF183:
	.ascii	"getSYSTIMER\000"
.LASF68:
	.ascii	"DMA2_Stream2_IRQn\000"
.LASF158:
	.ascii	"CCMR2\000"
.LASF45:
	.ascii	"SPI1_IRQn\000"
.LASF34:
	.ascii	"TIM1_BRK_TIM9_IRQn\000"
.LASF192:
	.ascii	"NVIC_EnableIRQ\000"
.LASF104:
	.ascii	"long long unsigned int\000"
.LASF159:
	.ascii	"RESERVED7\000"
.LASF57:
	.ascii	"DMA1_Stream7_IRQn\000"
.LASF97:
	.ascii	"__uint16_t\000"
.LASF23:
	.ascii	"DMA1_Stream2_IRQn\000"
.LASF76:
	.ascii	"CAN2_SCE_IRQn\000"
.LASF31:
	.ascii	"CAN1_RX1_IRQn\000"
.LASF185:
	.ascii	"time\000"
.LASF188:
	.ascii	"speed.c\000"
.LASF127:
	.ascii	"PUPDR\000"
.LASF93:
	.ascii	"IRQn_Type\000"
.LASF75:
	.ascii	"CAN2_RX1_IRQn\000"
.LASF80:
	.ascii	"DMA2_Stream7_IRQn\000"
.LASF48:
	.ascii	"USART2_IRQn\000"
.LASF154:
	.ascii	"RCC_TypeDef\000"
.LASF83:
	.ascii	"I2C3_ER_IRQn\000"
.LASF124:
	.ascii	"MODER\000"
.LASF13:
	.ascii	"RTC_WKUP_IRQn\000"
.LASF87:
	.ascii	"OTG_HS_IRQn\000"
.LASF156:
	.ascii	"DIER\000"
.LASF180:
	.ascii	"n_circ\000"
.LASF142:
	.ascii	"AHB3ENR\000"
.LASF18:
	.ascii	"EXTI2_IRQn\000"
.LASF137:
	.ascii	"APB1RSTR\000"
.LASF43:
	.ascii	"I2C2_EV_IRQn\000"
.LASF61:
	.ascii	"SPI3_IRQn\000"
.LASF39:
	.ascii	"TIM3_IRQn\000"
.LASF25:
	.ascii	"DMA1_Stream4_IRQn\000"
.LASF181:
	.ascii	"setNCirc\000"
.LASF105:
	.ascii	"uint8_t\000"
.LASF165:
	.ascii	"CCR2\000"
.LASF167:
	.ascii	"CCR4\000"
.LASF155:
	.ascii	"SMCR\000"
.LASF54:
	.ascii	"TIM8_UP_TIM13_IRQn\000"
.LASF103:
	.ascii	"long long int\000"
.LASF10:
	.ascii	"WWDG_IRQn\000"
.LASF187:
	.ascii	"GNU C11 7.3.1 20180622 (release) [ARM/embedded-7-br"
	.ascii	"anch revision 261907] -mlittle-endian -mthumb -mcpu"
	.ascii	"=cortex-m4 -mthumb-interwork -mfloat-abi=hard -mfpu"
	.ascii	"=fpv4-sp-d16 -g -O2 -fsingle-precision-constant\000"
.LASF189:
	.ascii	"/home/mahir/msut/msut-projekat\000"
.LASF148:
	.ascii	"APB1LPENR\000"
.LASF70:
	.ascii	"DMA2_Stream4_IRQn\000"
.LASF4:
	.ascii	"BusFault_IRQn\000"
.LASF36:
	.ascii	"TIM1_TRG_COM_TIM11_IRQn\000"
.LASF20:
	.ascii	"EXTI4_IRQn\000"
.LASF11:
	.ascii	"PVD_IRQn\000"
.LASF28:
	.ascii	"ADC_IRQn\000"
.LASF115:
	.ascii	"ICPR\000"
.LASF191:
	.ascii	"TIM4_IRQHandler\000"
.LASF144:
	.ascii	"APB2ENR\000"
.LASF60:
	.ascii	"TIM5_IRQn\000"
.LASF145:
	.ascii	"AHB1LPENR\000"
.LASF41:
	.ascii	"I2C1_EV_IRQn\000"
.LASF126:
	.ascii	"OSPEEDR\000"
.LASF29:
	.ascii	"CAN1_TX_IRQn\000"
.LASF106:
	.ascii	"uint16_t\000"
.LASF22:
	.ascii	"DMA1_Stream1_IRQn\000"
.LASF190:
	.ascii	"IRQn\000"
.LASF30:
	.ascii	"CAN1_RX0_IRQn\000"
.LASF135:
	.ascii	"AHB2RSTR\000"
.LASF120:
	.ascii	"STIR\000"
.LASF175:
	.ascii	"speedTime\000"
.LASF51:
	.ascii	"RTC_Alarm_IRQn\000"
.LASF136:
	.ascii	"AHB3RSTR\000"
.LASF110:
	.ascii	"RESERVED0\000"
.LASF139:
	.ascii	"RESERVED1\000"
.LASF114:
	.ascii	"RESERVED2\000"
.LASF116:
	.ascii	"RESERVED3\000"
.LASF118:
	.ascii	"RESERVED4\000"
.LASF119:
	.ascii	"RESERVED5\000"
.LASF151:
	.ascii	"RESERVED6\000"
.LASF96:
	.ascii	"short int\000"
.LASF161:
	.ascii	"RESERVED8\000"
.LASF162:
	.ascii	"RESERVED9\000"
.LASF79:
	.ascii	"DMA2_Stream6_IRQn\000"
.LASF82:
	.ascii	"I2C3_EV_IRQn\000"
.LASF100:
	.ascii	"long int\000"
.LASF47:
	.ascii	"USART1_IRQn\000"
.LASF171:
	.ascii	"DMAR\000"
.LASF63:
	.ascii	"UART5_IRQn\000"
.LASF122:
	.ascii	"ITM_RxBuffer\000"
.LASF2:
	.ascii	"NonMaskableInt_IRQn\000"
.LASF67:
	.ascii	"DMA2_Stream1_IRQn\000"
.LASF179:
	.ascii	"distance\000"
.LASF37:
	.ascii	"TIM1_CC_IRQn\000"
.LASF125:
	.ascii	"OTYPER\000"
.LASF56:
	.ascii	"TIM8_CC_IRQn\000"
.LASF27:
	.ascii	"DMA1_Stream6_IRQn\000"
.LASF133:
	.ascii	"CFGR\000"
.LASF58:
	.ascii	"FSMC_IRQn\000"
.LASF17:
	.ascii	"EXTI1_IRQn\000"
.LASF121:
	.ascii	"NVIC_Type\000"
.LASF64:
	.ascii	"TIM6_DAC_IRQn\000"
.LASF132:
	.ascii	"PLLCFGR\000"
.LASF131:
	.ascii	"GPIO_TypeDef\000"
.LASF42:
	.ascii	"I2C1_ER_IRQn\000"
.LASF81:
	.ascii	"USART6_IRQn\000"
.LASF9:
	.ascii	"SysTick_IRQn\000"
.LASF147:
	.ascii	"AHB3LPENR\000"
.LASF102:
	.ascii	"long unsigned int\000"
.LASF38:
	.ascii	"TIM2_IRQn\000"
.LASF141:
	.ascii	"AHB2ENR\000"
.LASF107:
	.ascii	"int32_t\000"
.LASF178:
	.ascii	"radius\000"
.LASF86:
	.ascii	"OTG_HS_WKUP_IRQn\000"
.LASF129:
	.ascii	"BSRRH\000"
.LASF128:
	.ascii	"BSRRL\000"
.LASF7:
	.ascii	"DebugMonitor_IRQn\000"
.LASF153:
	.ascii	"PLLI2SCFGR\000"
.LASF5:
	.ascii	"UsageFault_IRQn\000"
.LASF95:
	.ascii	"unsigned char\000"
.LASF101:
	.ascii	"__uint32_t\000"
.LASF33:
	.ascii	"EXTI9_5_IRQn\000"
.LASF6:
	.ascii	"SVCall_IRQn\000"
.LASF55:
	.ascii	"TIM8_TRG_COM_TIM14_IRQn\000"
.LASF163:
	.ascii	"RESERVED10\000"
.LASF169:
	.ascii	"RESERVED11\000"
.LASF170:
	.ascii	"RESERVED12\000"
.LASF172:
	.ascii	"RESERVED13\000"
.LASF173:
	.ascii	"RESERVED14\000"
.LASF74:
	.ascii	"CAN2_RX0_IRQn\000"
.LASF111:
	.ascii	"ICER\000"
.LASF69:
	.ascii	"DMA2_Stream3_IRQn\000"
.LASF46:
	.ascii	"SPI2_IRQn\000"
.LASF117:
	.ascii	"IABR\000"
.LASF65:
	.ascii	"TIM7_IRQn\000"
.LASF94:
	.ascii	"__uint8_t\000"
.LASF24:
	.ascii	"DMA1_Stream3_IRQn\000"
.LASF73:
	.ascii	"CAN2_TX_IRQn\000"
.LASF98:
	.ascii	"short unsigned int\000"
.LASF19:
	.ascii	"EXTI3_IRQn\000"
.LASF113:
	.ascii	"ISPR\000"
.LASF84:
	.ascii	"OTG_HS_EP1_OUT_IRQn\000"
.LASF49:
	.ascii	"USART3_IRQn\000"
.LASF35:
	.ascii	"TIM1_UP_TIM10_IRQn\000"
.LASF91:
	.ascii	"FPU_IRQn\000"
.LASF71:
	.ascii	"ETH_IRQn\000"
.LASF134:
	.ascii	"AHB1RSTR\000"
.LASF130:
	.ascii	"LCKR\000"
	.ident	"GCC: (GNU Tools for Arm Embedded Processors 7-2018-q2-update) 7.3.1 20180622 (release) [ARM/embedded-7-branch revision 261907]"
