	.set noat
	.set noreorder
	.globl	MemCardFormat
	.type	MemCardFormat, @function
MemCardFormat:
	addiu	$29,$29,-0x58
	lui	$3,%hi(mc)
	addiu	$3,$3,%lo(mc)
	sw	$31,0x50($29)
	lw	$2,0x0($3)
	nop
	bnez	$2,.L800FC048
	addiu	$2,$0,0x1
	lw	$5,0xC($3)
	lui	$3,%hi(_mc_present)
	lw	$3,%lo(_mc_present)($3)
	sllv	$2,$2,$5
	or	$3,$3,$2
	addiu	$5,$29,0x10
	lui	$1,%hi(_mc_present)
	jal	MemCardMakeDevname
	sw	$3,%lo(_mc_present)($1)
	jal	_clr_card_event
	nop
	jal	format
	addiu	$4,$29,0x10
	jal	_get_card_event_x
	nop
	jal	MemCardEventToRslt
	addu	$4,$2,$0
	j	.L800FC058
	nop
.L800FC048:
	lui	$4,%hi($LC5)
	jal	printf
	addiu	$4,$4,%lo($LC5)
	addiu	$2,$0,-0x1
.L800FC058:
	lw	$31,0x50($29)
	addiu	$29,$29,0x58
	jr	$31
	nop
	.size	MemCardFormat, . - MemCardFormat
