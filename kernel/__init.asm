;;-----------------_DEFINITIONS ONLY_-----------------------
;; IMPORT FUNCTIONS FROM C
%macro IMPORTFROMC 1-*
%rep  %0
    %ifidn __OUTPUT_FORMAT__, win32 ; win32 builds from Visual C decorate C names using _ 
    extern _%1
    %1 equ _%1
    %else
    extern %1
    %endif
%rotate 1 
%endrep
%endmacro

;; EXPORT TO C FUNCTIONS
%macro EXPORT2C 1-*
%rep  %0
    %ifidn __OUTPUT_FORMAT__, win32 ; win32 builds from Visual C decorate C names using _ 
    global _%1
    _%1 equ %1
    %else
    global %1
    %endif
%rotate 1 
%endrep
%endmacro


%define break xchg bx, bx

IMPORTFROMC KernelMain, isr14_handler

TOP_OF_STACK                equ 0x200000
KERNEL_BASE_PHYSICAL        equ 0x200000


;page tables =>2mb pages when using p4,p3,p2
;if we want 1gb pages use p1 as well
P4_TABLE                    equ 0x300000
P3_TABLE                    equ 0x301000
P2_TABLE                    equ 0x302000


;;-----------------^DEFINITIONS ONLY^-----------------------

segment .text
[BITS 32]
ASMEntryPoint:
    cli
    MOV     DWORD [0x000B8000], 'O1S1'
%ifidn __OUTPUT_FORMAT__, win32
    MOV     DWORD [0x000B8004], '3121'                  ; 32 bit build marker
%else
    MOV     DWORD [0x000B8004], '6141'                  ; 64 bit build marker
%endif



    MOV     ESP, TOP_OF_STACK                           ; just below the kernel
    
	CALL set_up_page_tables
    CALL enable_paging
	LGDT [gdt64.pointer]
	JMP gdt64.code:long_mode_start
	
[BITS 64]
long_mode_start:

	; load 0 into all data segment registers
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
	
	 ; print `OKAY` to screen
    ; mov rax, 0x2f592f412f4b2f4f
    ; mov qword [0xb8000], rax
	break
	CALL KernelMain
    CLI
    hlt
	


;;--------------------------------------------------------
[BITS 32]
__cli:
    CLI
    RET

__sti:
    STI
    RET

__magic:
    XCHG    BX,BX
    RET
    
__enableSSE:                ;; enable SSE instructions (CR4.OSFXSR = 1)  
    MOV     EAX, CR4
    OR      EAX, 0x00000200
    MOV     CR4, EAX
    RET
	
;;--------------------------------------------------------
set_up_page_tables:
	;map first P4 Entry to P3 table
	MOV EAX,P3_TABLE
	OR EAX, 0b11 ;present+writable
	MOV [P4_TABLE],EAX
	
	;map first P3 entry to P2 table
	MOV EAX, P2_TABLE
	OR EAX,0b11 ;present + writable
	MOV [P3_TABLE],EAX
	
	;map each P2 entry to a huge 2MiB 
	MOV ECX, 0 ;counter variable
	
.map_p2_table:
	;map ecx-th P2 entry to a huge page that starts at address 2Mib*ecx-th =>first gigabyte of our kernel is mapped
	MOV EAX, 0x200000 ;2MiB
	MUL ECX ; start address of ecx-th page
	OR EAX, 0B10000011;present +writable+...+huge
	MOV [P2_TABLE + ECX * 8], EAX; map ecx-th entry
	
	INC ECX ;increase counter
	CMP ECX,512 ; if counter ===512, the whole P2 table is mapped
	JNE .map_p2_table ; else map the next entry
	
	RET
	
enable_paging:
	; load P4 to CR3 register (cpu uses this to access the P$ table)
	MOV EAX, P4_TABLE
	MOV CR3,EAX
	
	; enable PAE-flag in CR4 (Physical Address Extension)
	MOV EAX,CR4
	OR EAX, 1<<5
	MOV CR4 ,EAX
	
	; set the long mode  bit in the EFER MSR (model specific register)
	MOV ECX, 0xC0000080
	RDMSR
	OR EAX,1<<8
	WRMSR
	
	
	;enable paging  in the cr0 register
	MOV EAX,CR0
	OR EAX, 1<<31
	MOV CR0,EAX
	
	RET

[BITS 64]
gdt64:
	dq 0 ; zero entry
.code: equ $ - gdt64 ; new
    dq (1<<43) | (1<<44) | (1<<47) | (1<<53) ; code segment
.pointer:
    dw $ - gdt64 - 1
    dq gdt64


[EXTERN pidt] 

__load_idt:
	lidt [pidt]
	sti
	ret

__isr14:

  call isr14_handler
 
  iretq

__myfunc:
	mov rax, 0x2f592f412f4b2f4f
	mov qword [0xb8000], rax
	break
	int 0x0E
	ret
 
EXPORT2C ASMEntryPoint, __cli, __sti, __magic, __enableSSE,__isr14,__load_idt,__myfunc




