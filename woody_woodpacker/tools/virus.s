section .text

global start

start:

  push rbp
  push rsp
  mov rbp, rsp

  push rbx
  push rax
  push rdi
  push rsi
  push rsp
  push rdx
  push rcx

  push 0x0A    ; les adresses de la stacks sont décroissantes
  push '.'
  push '.'
  push '.'
  push '.'
  push '.'
  push 'Y'
  push 'D'
  push 'O'
  push 'O'
  push 'W'
  push '.'
  push '.'
  push '.'
  push '.'

  mov rax, 0x91929394
  mov rax, 1
  mov rdi, 1
  mov rsi, rsp      ; on affiche de la plus petite adresse à la plus grande
  mov rdx, 0x78     ; nombre de bits (??????)
  syscall           ; );

  pop rax
  pop rax
  pop rax
  pop rax
  pop rax
  pop rax
  pop rax
  pop rax
  pop rax
  pop rax
  pop rax
  pop rax
  pop rax
  pop rax
  pop rax
  ;mov rax, 0x0242424242424242 ;

  call next42lol
next42lol:
  mov rbx, 0x4141414141414141
  pop rax
  add rax, 2
   mov rcx, 0x4343434343434342
 
 sub rax, rbx
 
  mov rdx, 0x4444444444444444 ; la clef de déchiffrement\

  ;relative start (exec time) - hard coded start = ASLR


  add rcx, rax
while:

;push rcx
;push rdx
; push rax
;  push '-'
;  mov rax, 1
;  mov rdi, 1
;  mov rsi, rsp      ; on affiche de la plus petite adresse à la plus grande
;  mov rdx, 1     ; nombre de bits (??????)
;  syscall           ; );
;  pop rax
; pop rax
;pop rdx
;pop rcx

   xor [rax], dl
;mov [rax], rbx
  ror rdx, 8
  inc rax
  cmp rax, rcx  
  jnz while

;  push '@'
;  mov rax, 1
;  mov rdi, 1
;  mov rsi, rsp      ; on affiche de la plus petite adresse à la plus grande
;  mov rdx, 1     ; nombre de bits (??????)
;  syscall           ; );
;  pop rax
 

pop rcx
pop rdx
pop rsp
pop rsi
pop rdi 
pop rax
pop rbx

  pop rsp
  pop rbp
