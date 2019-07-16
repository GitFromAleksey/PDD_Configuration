/******************************************************************************************************************
LCD ������� �� ����������� ST7920

��� ������������� ����������������� (SPI) ������ �������� ������ ���������� ��������� SERIAL
��� ������������� 8 ������ �������� ������ ������� ��������� SERIAL

										�������� �������
LCD12864_DataOut    - ���������� ������ �� �������, ������ ������ ��������� � �������� Data
LCD12864_CommandOut - ���������� ������� �� �������, ������� ������ ��������� � �������� Data
LCD12864_out_string - ���������� ������ �� Flash ������ ���������, ����� 2 ���������, 
					  1 - ��� ��������� �� ������ ������� ������ �������� � �������� Z
					  2 - ��� ���������� ������������ ��������, ������ ��������� � ��������  Temp1
LCD12864_mov_cursor - ������������� ��������� ������� �� �������, � ����� 2 ��������� ���������� X � Y
					  1 - ��� X ����������, ���������� � �������� r16
					  2 - ��� Y ����������, ���������� � �������� r17
							


										�������� ��������
LCD8_MACRO_SET_SR - ������������� ��������� SR
				   (1<<SET_SR) - ������������ ��������
				   (1<<SR) - ������������� �������� SR � 1

LCD8_MACRO_ENTRY_MODE_SET - ENTRY MODE
							(1<<ENTRY_MODE) - ������������ ��������
							(1<<ENTRY_ID)
							(1<<ENTRY_S)		
			
LCD8_MACRO_SET_FUNCTION - 	������������� �������� �������
							(1<<SET_FUNCT) - ������������ ��������
							(1<<BIT_8) - ��������������� ���� ������������ 8 ������ ����
							(1<<EXT_FUNC) - ������������ ����� ���������� �������
							(1<<GRAPH_DISP_ON) - �������� ����������� �������		
							
LCD8_MACRO_SET_DISPLAY_STATUS - ������������� ������� �������  
								(1<<SET_DISPLAY) - ������������ ��������
								(1<<BLINC_CURSOR) - ������ ��������
								(1<<CURSOR_ON) - ���������� ������
								(1<<DISPLAY_ON) - �������� �������
								

LCD8_MACRO_MOV_CURSOR - ����������� ������ � ������ ���������� ������� 
							   1 �������� ��� X
							   2 �������� ��� Y	
							   
LCD8_MACRO_DISPLAY_RIGHT - ����������� ������� ������	

LCD8_MACRO_DISPLAY_LIFT - ����������� ������� �����				

LCD8_MACRO_CLEAR - ��������� �����	

LCD8_MACRO_HOME - ����������� ������ � ������� � ������	

LCD8_MACRO_CURSOR_RIGHT - ����������� ������ ������

LCD8_MACRO_CURSOR_LIFT  - ����������� ������ ����� 

LCD8_MACRO_OUT_COMMAND - ��������� ������� 
						1 �������� - ������� 
						
LCD8_MACRO_OUT_DATA - ��������� ������ 
					  1 �������� - ������	
					  
LCD8_MACRO_DELAY - �������� � �������������
				   1 �������� ���������� ��������
				   2 ��������, ���������� ����������� � ��������
				   

LCD8_MACRO_OUT_STRING - ���������� ������ �� ������ ���������
						1 �������� ����� ������ �� ������ ���������
						2 �������� ���������� �������� 				   					  																					  
******************************************************************************************************************/

.equ DDRx = DDRB
.equ PCom = PORTD ; ���� ��������� � 8 ��� ������, � ������� �������� ������ � ���������� � ���������������� ������
.equ PW = PORTB	  ; ���� ������ � 8 ������ ������, � ���������������� ������ �� ������������
.def Temp = R16	  ; �������� �������
.def Temp1 = R17  ; ��������� �������
.def Data = R18   ; ������� ������������ ��� ������ ������ � ����

.equ SERIAL = 0 ; ���� ������������ �� �������� �� ����������������� �����,
				; ��� �� ������� ����������� ���� 8 ��� ������� ��� ���������

; ����������� ����� ��� 8 ������ �������� ������
.equ RS = 2
.equ E = 0
.equ RW = 1

; ����������� ����� ��� ���������������� �������� ������
.equ SID = 1 ; RW
.equ CS = 2  ; RS - �� ������������!!!
.equ SCLK = 0; E

; ��� ������� LCD8_MACRO_SET_SR
.equ SET_SR = 1			; - ������������� ��������� SR
.equ SR = 0				; - �������� SR

; ��� ������� LCD8_MACRO_SET_FUNCTION
.equ SET_FUNCT = 5		; ������������� ��������� ������� 
.equ BIT_8 = 4			;- ��������������� ���� ������������ 8 ������ ����
.equ EXT_FUNC = 2		; - ������������ ����� ���������� �������
.equ GRAPH_DISP_ON = 1  ; - �������� ����������� �������


; ��� ������� LCD8_MACRO_SET_DISPLAY_STATUS
.equ SET_DISPLAY = 3	; - ������������� ������� ������ � ��������
.equ BLINC_CURSOR = 0	; - ������ �������� 
.equ CURSOR_ON = 1		; - ���������� ������
.equ DISPLAY_ON = 2		; - �������� �������

; ��� ������� LCD8_MACRO_ENTRY_MODE_SET 
.equ ENTRY_MODE = 2	; ������������� ������� ENTRY MODE
.equ ENTRY_ID = 1
.equ ENTRY_S = 0


; ������������� ��������� SR
; (1<<SET_SR) - ������������ ��������
; (1<<SR) - ������������� �������� SR � 1
.MACRO LCD8_MACRO_SET_SR 
	LCD8_MACRO_OUT_COMMAND  @0
.ENDM

; ENTRY MODE
; (1<<ENTRY_MODE) - ������������ ��������
; (1<<ENTRY_ID)
; (1<<ENTRY_S)
.MACRO LCD8_MACRO_ENTRY_MODE_SET
	LCD8_MACRO_OUT_COMMAND  @0
.ENDM

; ������������� �������� �������
; (1<<SET_FUNCT) - ������������ ��������
; (1<<BIT_8) - ��������������� ���� ������������ 8 ������ ����
; (1<<EXT_FUNC) - ������������ ����� ���������� �������
; (1<<GRAPH_DISP_ON) - �������� ����������� �������
.MACRO LCD8_MACRO_SET_FUNCTION
	LCD8_MACRO_OUT_COMMAND   @0
.ENDM

; ������������� ������� ������� 
; (1<<SET_DISPLAY) - ������������ ��������
; (1<<BLINC_CURSOR) - ������ ��������
; (1<<CURSOR_ON) - ���������� ������
; (1<<DISPLAY_ON) - �������� �������
.MACRO LCD8_MACRO_SET_DISPLAY_STATUS  
	LCD8_MACRO_OUT_COMMAND @0
.ENDM

; ����������� ������ � ������ ���������� �������
.MACRO LCD8_MACRO_MOV_CURSOR ; 1 �������� ��� X,  2 �������� ��� Y
	ldi r16, @0
	ldi r17, @1
	rcall LCD12864_mov_cursor
.ENDM


; ����������� ������� ������
.MACRO LCD8_MACRO_DISPLAY_RIGHT 
	LCD8_MACRO_OUT_COMMAND 0b00011100
.ENDM

; ����������� ������� �����
.MACRO LCD8_MACRO_DISPLAY_LIFT 
	LCD8_MACRO_OUT_COMMAND 0b00011000
.ENDM

; ��������� �����
.MACRO LCD8_MACRO_CLEAR ; ��������� �����
	LCD8_MACRO_OUT_COMMAND 0b00000001
.ENDM

; ����������� ������ � ������� � ������
.MACRO LCD8_MACRO_HOME 
	LCD8_MACRO_OUT_COMMAND 0b00000010
.ENDM

; ����������� ������ ������
.MACRO LCD8_MACRO_CURSOR_RIGHT 
	LCD8_MACRO_OUT_COMMAND 0b00010100
.ENDM

; ����������� ������ �����
.MACRO LCD8_MACRO_CURSOR_LIFT 
	LCD8_MACRO_OUT_COMMAND 0b00010000
.ENDM

; ��������� ������� 
.MACRO LCD8_MACRO_OUT_COMMAND ; 1 �������� - �������
     ldi  Data,  @0
     rcall  LCD12864_CommandOut
.ENDM

; ��������� ������
.MACRO LCD8_MACRO_OUT_DATA    ; 1 �������� - ������
     ldi  Data,  @0
     rcall  LCD12864_DataOut
.ENDM

; ��������
.MACRO LCD8_MACRO_DELAY ; 1 �������� ���������� ��������, 2 ��������, ���������� ����������� � ��������
       ldi  Temp,  @0               
       ldi  Temp1, @1
     rcall  LCD12864_Delay
.ENDM

; ���������� ������ �� ������ ���������
.MACRO LCD8_MACRO_OUT_STRING ; 1 �������� ����� ������ �� ������ ���������, 2 �������� ���������� �������� 
	ldi ZL, low(@0*2)
	ldi ZH, high(@0*2)
	ldi temp1, @1
	rcall LCD12864_out_string
.ENDM


; ���������� ������ �� Flash ������ ���������, ��������� �� ������ ������ ��������� � Z ��������
LCD12864_out_string:
for1:
	lpm Temp, Z+
	cpi Temp1, 0
	breq exit1
	dec Temp1
	push Temp1
	mov  Data,  Temp
	rcall  LCD12864_DataOut
	pop Temp1
	rjmp for1
exit1:
	ret



/*************************************
������� �������� ������� � ������ �� ������������ ����� 8 ���
	LCD12864_CommandOut - ���������� �������
	LCD12864_DataOut    - ���������� ������

	������� ��� ������ ������ ��������� � �������� Data
**************************************/
.ifndef SERIAL
LCD12864_DataOut:
       sbi  PCom,  RS               ;RS=1;
	   LCD8_MACRO_DELAY 1, 1
	   sbi  PCom,  E                ;E=1.
	   out  PW,    Data             ;����� ������.
	   LCD8_MACRO_DELAY 1, 1
       cbi  PCom,  E                ;RS=0, E=0.
       cbi  Pcom,  RS   
	   LCD8_MACRO_DELAY 1, 50
       ret



LCD12864_CommandOut:                ;����� ������� �� ���������.
       cbi  PCom,  E                ;E=0 � RS.
       cbi  PCom,  RS
	   cbi  PCom,  RW
	   LCD8_MACRO_DELAY 1, 1
	   sbi  PCom,  E                ;E=1.
       out  PW,    Data             ;�������� ������.
       LCD8_MACRO_DELAY 1, 1
	   cbi  PCom,  E                ;E=0 
	   LCD8_MACRO_DELAY 1, 50
	   ret


.endif



/*************************************
������� �������� ������� � ������ �� ����������������� �����
	LCD12864_CommandOut - ���������� �������
	LCD12864_DataOut    - ���������� ������

	������� ��� ������ ������ ��������� � �������� Data
**************************************/
.ifdef SERIAL
LCD12864_CommandOut:
	ldi r20, 0
	rjmp command
LCD12864_DataOut:

	sbi DDRx, RW
	sbi DDRx, E
	ldi r20, 1	 
command:	      
	LCD8_MACRO_DELAY 1, 1
	;sbi PCom, CS
	sbi PCom, SID
	rcall strob ; 1
	rcall strob ; 1
	rcall strob ; 1
	rcall strob ; 1
	rcall strob ; 1
	cbi PCom, SID  ; rw = 0
	rcall strob

	cbi PCom, SID  ; rs = 0
	cpi r20, 0
	breq command1
	sbi PCom, SID  ; rs = 1

command1:
	rcall strob
	cbi PCom, SID  ; 0
	rcall strob


	ldi r20, 8
for_send_data:
	cpi r20, 0
	breq  stop_send_data
	cpi r20, 4
	brne  no_strob
	cbi PCom, SID
	rcall strob
	rcall strob
	rcall strob
	rcall strob
no_strob:
	dec r20
	rol		Data			
	brcs  send_bit_1
	cbi PCom, SID ; ������ 0 ���
	rcall strob
	rjmp for_send_data
send_bit_1:
	sbi PCom, SID ; ������ 1 ���
	rcall strob
	rjmp for_send_data
stop_send_data:
	cbi PCom, SID 
	rcall strob
	rcall strob
	rcall strob
	rcall strob
	cbi PCom, SID 
	;cbi PCom, CS
	ret



strob:
	LCD8_MACRO_DELAY 1, 1
	sbi PCom, SCLK	
	LCD8_MACRO_DELAY 1, 1
	cbi PCom, SCLK
	LCD8_MACRO_DELAY 1, 1
	ret
.endif
;******************************************************




LCD12864_Init:                      ;������������� �������.
	 LCD8_MACRO_DELAY 1, 50
     LCD8_MACRO_SET_FUNCTION (1<<SET_FUNCT)    ;����� �������.
	 LCD8_MACRO_DELAY 1, 120
	 LCD8_MACRO_SET_DISPLAY_STATUS (1<< SET_DISPLAY) |  (1<<CURSOR_ON) | (1<<DISPLAY_ON)  | (1<<BLINC_CURSOR)
	 LCD8_MACRO_DELAY 1, 50
     LCD8_MACRO_SET_FUNCTION (1<<SET_FUNCT)    ;����� �������.
	 LCD8_MACRO_DELAY 1, 120
	 LCD8_MACRO_CLEAR       ;����� �������.
   	 LCD8_MACRO_DELAY 1, 20
     LCD8_MACRO_ENTRY_MODE_SET (1<<ENTRY_MODE) | (1<<ENTRY_ID)

	 LCD8_MACRO_DELAY 1, 120


    ret

LCD12864_Delay:
	push  Temp                  ;��������� ������� �������� � ���.
ES0:
	dec  Temp                   ;- ��������.
	cpi  Temp,  0               ;�����������?
    brne  ES0                   ;��� - ��� ���.
	
	pop  Temp                   ;��? ������������ �������.
	dec  Temp1                  ;������ �� "���������� ��������" �������.
	cpi  Temp1, 0               ;���������� �������� = 0?
    brne  LCD12864_Delay               
    ret



; ������� ����������� ������� �� �������
LCD12864_mov_cursor: ; r16 - x ; r17 - y
	push r16
	push r17
	push r18

	cpi r17, 0
	breq exet5

	cpi r17, 1
	breq one

	cpi r17, 2
	breq two

	cpi r17, 3
	breq three

one:
	ldi r17, 16
	add r16, r17
	rjmp exet5
two:
	ldi r17, 8
	add r16, r17	
	rjmp exet5
three:
	ldi r17, 24
	add r16, r17

exet5:
	ldi Data, 0b10000000
	add Data, r16
	rcall  LCD12864_CommandOut
	pop r18
	pop r17
	pop r16

	ret