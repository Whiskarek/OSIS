.model small
.stack 1000
.data
    old dd 0 		
    count dw 0 ; согласный
    ten dw 10

.code
.486
       
	сounts dw 0 ; согласные
 
new_handle proc   
      
    push ds si es di dx cx bx ax ; заносим в стек значения регистров перед выполнением нашего обработчика прерываний
        
    xor ax, ax ; обнуляем регистр
		
    in al, 60h         ; скан-код символа        
		
	cmp al, 2Ch        ; z
    je new_handler
    cmp al, 2Dh        ; x
    je new_handler
	сmp al, 2Eh        ; c
    je new_handler
    cmp al, 2Fh        ; v
    je new_handler
    cmp al, 30h        ; b
    je new_handler
    cmp al, 31h        ; n
    je new_handler
    cmp al, 32h        ; m
    je new_handler
    cmp al, 1Fh        ; s
    je new_handler
    cmp al, 20h        ; d
    je new_handler
    cmp al, 21h        ; f
    je new_handler
    cmp al, 22h        ; g
    je new_handler
    cmp al, 23h        ; h
    je new_handler
	cmp al, 24h        ; j
    je new_handler
    cmp al, 25h        ; k
    je new_handler
    cmp al, 26h        ; l
    je new_handler		
	cmp al, 10h        ; q
    je new_handler
    cmp al, 11h        ; w
    je new_handler
    cmp al, 13h        ; r
    je new_handler
    cmp al, 14h        ; t
    je new_handler 
    cmp al, 19h        ; p
    je new_handler
      
	cmp al,3Ch 		   ; F2
	
	je output
    jmp old_handler  
	
	output:
		mov 	AX, count 
		push    -1      
		mov     CX, 10   
    
	l3: 
		mov 	DX, 0   	   
		div 	CX  	   
		push 	DX    	   
		cmp 	AX, 0  	   
		jne     l3  	   
		mov     AH, 2h
	l4:
		pop     DX  	   
		cmp     DX, -1   
		je exit
		add     DL, '0'  
		int     21h 	   
		jmp     l4  	   		
		
    new_handler: 
    	inc count ; счетчик каждой согласной буквы
		jmp exit
    
    old_handler: 
        pop ax bx cx dx di es si ds                       
    	jmp dword ptr cs:old         ; вызов стандартного обработчика прерывания
        xor ax, ax
        mov al, 20h
        out 20h, al 		
        jmp exit
        
    exit:	
        xor ax, ax	
		mov ax, 5
        mov al, 20h
        out 20h, al 		
        pop ax bx cx dx di es si ds  ; восстановление регистров
				
    iret
new_handle endp

new_res:
 
start:
    mov ax, @data
    mov ds, ax

    cli 	
    pushf 
		
    push 0       
    pop ds
    mov eax, ds:[09h*4] 
    mov cs:[old], eax 		; сохранение системного обработчика
        		
    mov ax, cs
    shl eax, 16
    mov ax, offset new_handle
    mov ds:[09h*4], eax 	; запись нового обработчика
		
    sti     
		
    xor ax, ax
    mov ah, 31h
    INT 21H 
    MOV DX, (new_res - @code + 10FH) / 16 
end start