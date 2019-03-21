;============================================================
; Autores: Ismael Cervantes de Anda.
;      	   Caballero Huesca Carlos Eduardo
;	   Gonzalez Ambriz Luis Angel
;	   
;
; Medidor de Voltaje, Corriente Temperatura y comunicacion USART
; Fecha: 06/03/2018
; PIC: 16F876A
;============================================================
	LIST    P=PIC16F876A
	#include <p16f876a.inc>
;	__CONFIG	_CP_OFF&_DEBUG_OFF&_WRT_OFF&_CPD_OFF&_LVP_OFF&_BODEN_OFF&_PWRTE_ON&_WDT_OFF&_XT_OSC
	__CONFIG	_CP_ALL&_DEBUG_OFF&_WRT_HALF&_CPD_OFF&_LVP_OFF&_BODEN_OFF&_PWRTE_ON&_WDT_OFF&_XT_OSC
;============================================================
;                  Declaración de Registros
;============================================================
w			equ 0x00
indf		equ 0x00
tmr0		equ 0x01
status		equ 0x03
fsr			equ 0x04
porta		equ 0x05
portb		equ 0x06
portc		equ 0x07
pclath		equ 0x0a
intcon		equ 0x0b
pir1		equ	0x0c
pir2		equ 0x0d
rcsta		equ	0x18
txreg		equ	0x19
rcreg		equ	0x1a
adresh		equ	0x1e
adcon0		equ	0x1f
adresl		equ	0x9e
adcon1		equ 0x9f
;opsion		equ 0x81
trisa		equ 0x85
trisb		equ 0x86
trisc		equ 0x87
pie1		equ 0x8c
pie2		equ 0x8d
txsta		equ 0x98
spbrg		equ 0x99

varLCD		equ 0x20
ValBIN		equ 0x21
adcalto		equ 0x22
adcbajo		equ 0x23
BCDcen		equ 0x24
BCDdec		equ 0x25
BCDuni		equ 0x26
banADC		equ 0x27
ret1		equ 0x28
ret2		equ 0x29
ret3		equ 0x2a
var1		equ 0x2b
var2		equ 0x2c
var3		equ 0x2d

NumeroEntero		equ 0x30
NumeroFraccionCen	equ 0x31
NumeroFraccionDec	equ 0x32
NumeroFraccionUni	equ 0x33
VoltsDec		equ 0x34
VoltsUni		equ 0x35
VoltsFracDec	equ 0x36
VoltsFracUni	equ 0x37
AmperUni		equ 0x38
AmperFraCen		equ 0x39
AmperFraDec		equ 0x3a
AmperFraUni		equ 0x3b
DecTemp		equ 0x3c
UniTemp		equ 0x3d
FraTemp		equ 0x3e

divisorDec	equ 0x40
divisorUni	equ 0x41
contadorMulti	equ 0x42
contadorMultiOper	equ 0x43
TempMultialto	equ 0x44
TempMultibajo	equ 0x45
Ventiladoralto	equ 0x46
Ventiladorbajo	equ 0x47
RutAjuste	equ 0x48
ContResta	equ 0x49
TxUSART		equ 0x4a
RxUSART		equ 0x4b
CorrienteAlto	equ 0x4c
CorrienteBajo	equ 0x4d
VoltAlto	equ 0x4e
VoltBajo	equ 0x4f

var1ren0	equ 0x50
var1ren1	equ 0x51
var1ren2	equ 0x52
var1ren3	equ 0x53
var1ren4	equ 0x54
var1ren5	equ 0x55
var1ren6	equ 0x56
var1ren7	equ 0x57
var1ren8	equ 0x58
var1ren9	equ 0x59
var1ren10	equ 0x5a
var1ren11	equ 0x5b
var1ren12	equ 0x5c
var1ren13	equ 0x5d
var1ren14	equ 0x5e
var1ren15	equ 0x5f
var2ren0	equ 0x60
var2ren1	equ 0x61
var2ren2	equ 0x62
var2ren3	equ 0x63
var2ren4	equ 0x64
var2ren5	equ 0x65
var2ren6	equ 0x66
var2ren7	equ 0x67
var2ren8	equ 0x68
var2ren9	equ 0x69
var2ren10	equ 0x6a
var2ren11	equ 0x6b
var2ren12	equ 0x6c
var2ren13	equ 0x6d
var2ren14	equ 0x6e
var2ren15	equ 0x6f

ValRx		equ 0x70
BCDCen		equ 0x71
BCDDec		equ 0x72
BCDUni		equ 0x73
ValRxHex	equ 0x74
HexAlto		equ 0x75
HexBajo		equ 0x76
RxUSART2	equ 0x77
Talta		equ 0x78
Tbaja		equ 0x79

		
		
T1Alto		equ 0xa0
T1Bajo		equ 0xa1
T2Alto		equ 0xa2
T2Bajo		equ 0xa3
T3Alto		equ 0xa4
T3Bajo		equ 0xa5
T4Alto		equ 0xa6
T4Bajo		equ 0xa7
T5Alto		equ 0xa8
T5Bajo		equ 0xa9
T6Alto		equ 0xaa
T6Bajo		equ 0xab
T7Alto		equ 0xac
T7Bajo		equ 0xad
T8Alto		equ 0xae
T8Bajo		equ 0xaf
;============================================================
;                  Declaración de Bits
;============================================================
c			equ 0
adon		equ	0
z			equ 2
toif		equ	2
go_done		equ	2
pcfg0		equ 0
pcfg1		equ 1
pcfg2		equ 2
pcfg3		equ 3
chs0		equ 3
chs1		equ 4
chs2		equ 5

cren		equ 4
txif		equ 4
rcif		equ 5
rcie		equ 5

rp0			equ 5
rp1			equ 6
peie		equ	6
adie		equ	6
adif		equ	6
adcs0		equ	6
adcs1		equ	7
adfm		equ 7
gie			equ	7
eepgd		equ 7
spen		equ	7
						;Puerto A
SenCorriente	equ 0			;Entrada Analógica
SenVoltaje		equ 1			;Entrada Analógica
SenTemperatura	equ 2			;Entrada Analógica
						;Puerto B
Bit7_LCD		equ 7			;Salida
Bit6_LCD		equ 6			;Salida
Bit5_LCD		equ 5			;Salida
Bit4_LCD		equ 4			;Salida
Enable_LCD		equ 3			;Salida
RS_LCD			equ 0			;Salida
						;Puerto C
Ventilador		equ 7			;Salida
;============================================================
;		Declaración de Letras y Numeros
;============================================================
_espaci		equ	0x20
_0			equ	0x30
_1			equ	0x31
_2			equ	0x32
_3			equ	0x33
_4			equ	0x34
_5			equ	0x35
_6			equ	0x36
_7			equ	0x37
_8			equ	0x38
_9			equ	0x39
_A			equ	0x41
_B			equ	0x42
_C			equ	0x43
_D			equ	0x44
_E			equ	0x45
_F			equ	0x46
_G			equ	0x47
_H			equ	0x48
_I			equ	0x49
_J			equ	0x4a
_K			equ	0x4b
_L			equ	0x4c
_M			equ	0x4d
_N			equ	0x4e
_O			equ	0x4f
_P			equ	0x50
_Q			equ	0x51
_R			equ	0x52
_S			equ	0x53
_T			equ	0x54
_U			equ	0x55
_V			equ	0x56
_W			equ	0x57
_X			equ	0x58
_Y			equ	0x59
_Z			equ	0x5a
_a			equ	0x61
_b			equ	0x62
_c			equ	0x63
_d			equ	0x64
_e			equ	0x65
_f			equ	0x66
_g			equ	0x67
_h			equ	0x68
_i			equ	0x69
_j			equ	0x6a
_k			equ	0x6b
_l			equ	0x6c
_m			equ	0x6d
_n			equ	0x6e
_o			equ	0x6f
_p			equ	0x70
_q			equ	0x71
_r			equ	0x72
_s			equ	0x73
_t			equ	0x74
_u			equ	0x75
_v			equ	0x76
_w			equ	0x77
_x			equ	0x78
_y			equ	0x79
_z			equ	0x7a
_dospuntos	equ	0x3a
_menos		equ 0x2d
_punto		equ	0x2e
_grado		equ 0xdf

;;============================================================
;;		Paginas de memoria de programa
;;============================================================
;P0_0005_07FF	equ 0x00		;Pagina 0	Ubicacion del programa principal 
;P1_0800_0FFF	equ 0x08		;Pagina 1	Subritunas
;P3_1000_17FF	equ 0x10		;Pagina 2
;P4_1800_1FFF	equ 0x18		;Pagina 3
;============================================================
;		Vector del reset
;============================================================
	org		0
	goto	IniProgMed
	org		4
	bcf		status,rp0         ;cambiar al banco 0
	bcf 	status,rp1
	btfsc	pir1,adif			;¿interrupción por ADC?
	goto	ADCinterrup
	btfsc	pir1,rcif
	goto	interserie
	retfie
;============================================================
;	Rutinas de Interrupción
;============================================================
;------------------------------------------------------------
ADCinterrup						;Interrupción por ADC
;------------------------------------------------------------
	bcf		status,rp0			;cambiar al banco 0
	bcf		status,rp1
	bcf		intcon,gie			;desactivación general de interrupciones
	movf	adresh,w			;guarda el byte alto de la conversión en
	movwf	adcalto				;la localidad de memoria RAM correspondiente
	bsf		status,rp0			;cambiar al banco 1
	bcf		status,rp1
	movf	adresl,w			;guarda el byte bajo de la conversión en
	bcf		status,rp0			;cambiar al banco 0
	bcf		status,rp1
	movwf	adcbajo				;la localidad de memoria RAM correspondiente
	bcf		pir1,adif
	bsf		intcon,gie
	movlw	0xaa
	movwf	banADC
	retfie
;------------------------------------------------------------
interserie
;------------------------------------------------------------
	bcf		status,rp0		;cambiar al banco 0
	bcf		status,rp1
	bcf		intcon,gie		;desactivar habilitador general de interrupciones.





	movf	rcreg,w			;CÓDIGO DE PRUEBA
	movwf	RxUSART			;CÓDIGO DE PRUEBA
	movwf	RxUSART2		;CÓDIGO DE PRUEBA
	movwf	ValRx			;CÓDIGO DE PRUEBA
	movwf	ValRxHex		;CÓDIGO DE PRUEBA
	;call	CONV_BINaBCD	;CÓDIGO DE PRUEBA
	;call	CONV_BINaHEX	;CÓDIGO DE PRUEBA
	;call	PantallaRX		;CÓDIGO DE PRUEBA
;	call	display			;CÓDIGO DE PRUEBA
;	call	retardounseg	;CÓDIGO DE PRUEBA
	




	movf	RxUSART2,w			;recuperar el dato recibido por rs232
	movwf	RxUSART
	xorlw	0xe1			;¿Se recibio el "Comando" de Petición?
	btfsc	status,z
	goto	Tx_Protocolo
	goto	Regresa_de_USART
	retfie
Tx_Protocolo



	;call	PantallaTX		;CÓDIGO DE PRUEBA
	;call	display			;CÓDIGO DE PRUEBA
	;call	retardounseg	;CÓDIGO DE PRUEBA



	movlw	0xc1			;Se transmite "Confirmación" de recepción de "Comando" de Petición.
	movwf	TxUSART
	call	transmite
	call	Retardos
;	call	temp10micros

	movf	VoltAlto,w		;Se transmite el valor de Voltaje
	movwf	TxUSART
	call	transmite
	call	Retardos
;	call	temp10micros
	movf	VoltBajo,w
	movwf	TxUSART
	call	transmite
	call	Retardos
;	call	temp10micros


	movf	CorrienteAlto,w	;Se transmite el valor de Corriente
	movwf	TxUSART
	call	transmite
	call	Retardos
;	call	temp10micros
	movf	CorrienteBajo,w
	movwf	TxUSART
	call	transmite
	call	Retardos
;	call	temp10micros


	movf	Talta,w	;Se transmite el valor de Temperatura
	movwf	TxUSART
	call	transmite
	call	Retardos
;	call	temp10micros
	movf	Tbaja,w
	movwf	TxUSART
	call	transmite
	call	Retardos
;	call	temp10micros


	movlw	0xc2				;Se transmite el "Comando" de Cierre
	movwf	TxUSART
	call	transmite

Regresa_de_USART
	bcf		pir1,rcif
	bsf		intcon,gie
	retfie
;============================================================
;		Comienzo del programa principal
;============================================================
IniProgMed
	bsf		status,rp0		;cambiar al banco 1
	bcf		status,rp1
	movlw	b'00111111'		;configurar los pines del puerto A como entradas
	movwf	trisa
	clrf	trisb			;configurar los pines del puerto B como salida
	movlw	b'10111111'		;configurar pin 6 como salida, demás como entradas del puerto C
	movwf	trisc
	bcf		status,rp0		;cambiar al banco 0
	bcf		status,rp1
;============================================================
;Carga valores iniciales
;============================================================
	bcf		status,rp0		;cambiar al banco 0
	bcf		status,rp1
	clrf	varLCD
	clrf	porta			;apaga las salidas del puerto A, B y C
	clrf	portb
	clrf	portc
	clrf	banADC
	clrf	RutAjuste
	movlw	_X
	movwf	VoltsDec
	movwf	VoltsUni
	movwf	VoltsFracUni
	movwf	VoltsFracDec
	movwf	AmperUni
	movwf	AmperFraCen
	movwf	AmperFraDec
	movwf	AmperFraUni
	movwf	DecTemp
	movwf	UniTemp
	movwf	FraTemp
	call	ConfigADC
	call	IniciaDisplayLCD
	call	letreroBienvenida
	call	display
	call	retardounseg
	call	retardounseg
	call	Primerletrero
	call	display
;============================================================
			;Activacion de la USART 9600 BAUDIOS, Sin bit de paridad
;============================================================
	bsf		status,rp0		;cambiar al banco 1
	bcf		status,rp1
	movlw	b'00100110'
	movwf	txsta
	movlw	.25
	movwf	spbrg
	bcf		status,rp0		;cambiar al banco 0
	bcf		status,rp1
	bsf		rcsta,spen		;habilitacion del puerto de comunicacion serial
	bsf		rcsta,cren
	bsf		intcon,gie		;activar habilitador general de interrupciones.
	bsf		intcon,peie		;activar habilitador general de interrupciones por perifericos.
	bsf		status,rp0		;cambiar al banco 1
	bcf		status,rp1
	bsf		pie1,rcie		;activar interrupción por fin de recepción por usart.
;============================================================
MedirCorriente
;============================================================
	bcf		status,rp0		;cambiar al banco 0
	bcf		status,rp1


	bsf		intcon,gie		;activación general de interrupciones
	bsf		intcon,peie		;activación de interrupciones por periférico

	bcf		adcon0,chs0		;selecciona canal 0 de adc
	bcf		adcon0,chs1		;selecciona canal 0 de adc
	bcf		adcon0,chs2		;selecciona canal 0 de adc
	nop
;	call	retardoXseg

	bsf		adcon0,go_done	;iniciar la operación del ADC
esperaCorrienteADCs
	movf	banADC,w
	xorlw	0xaa
	btfss	status,z
	goto	esperaCorrienteADCs

;	bcf		intcon,gie		;activación general de interrupciones
;	bcf		intcon,peie		;activación de interrupciones por periférico

	call	SubRutAjuste
		movf	RutAjuste,w
		xorlw	0x00
		btfsc	status,z
		goto	ContCalCorriente
		movf	RutAjuste,w
		xorlw	0x01
		btfsc	status,z
		goto	Resta4CalCorriente
		movf	RutAjuste,w
		xorlw	0x02
		btfsc	status,z
		goto	Resta9CalCorriente
		movf	RutAjuste,w
		xorlw	0x03
		btfsc	status,z
		goto	Resta18CalCorriente
		goto	ContCalCorriente
		Resta4CalCorriente
			movlw	0x04
			movwf	ContResta
			Sig_Resta4CalCorriente
				decf	adcbajo,1
				movf	adcbajo,w
				xorlw	0xff
				btfsc	status,z
				goto	decrementa_adcalto_Resta4CalCorriente
				goto	continua_Resta4CalCorriente
				decrementa_adcalto_Resta4CalCorriente
					decf	adcalto,1
				continua_Resta4CalCorriente
					decfsz	ContResta,1
					goto	Sig_Resta4CalCorriente
					goto	ContCalCorriente	
		Resta9CalCorriente
			movlw	0x09
			movwf	ContResta
			Sig_Resta9CalCorriente
				decf	adcbajo,1
				movf	adcbajo,w
				xorlw	0xff
				btfsc	status,z
				goto	decrementa_adcalto_Resta9CalCorriente
				goto	continua_Resta9CalCorriente
				decrementa_adcalto_Resta9CalCorriente
					decf	adcalto,1
				continua_Resta9CalCorriente
					decfsz	ContResta,1
					goto	Sig_Resta9CalCorriente
					goto	ContCalCorriente	
		Resta18CalCorriente
			movlw	.018
			movwf	ContResta
			Sig_Resta18CalCorriente
				decf	adcbajo,1
				movf	adcbajo,w
				xorlw	0xff
				btfsc	status,z
				goto	decrementa_adcalto_Resta18CalCorriente
				goto	continua_Resta18CalCorriente
				decrementa_adcalto_Resta18CalCorriente
					decf	adcalto,1
				continua_Resta18CalCorriente
					decfsz	ContResta,1
					goto	Sig_Resta18CalCorriente
					goto	ContCalCorriente	
ContCalCorriente
	clrf	banADC
	movlw	.004
	movwf	contadorMulti
	call	MultiplicacionCalculos
	movlw	0x03
	movwf	divisorDec
	movlw	0xe8
	movwf	divisorUni
	movlw	.009
	movwf	contadorMulti
	movf	adcalto,w
	movwf	CorrienteAlto
	movf	adcbajo,w
	movwf	CorrienteBajo
	call	DivisionCalculos

	movf	NumeroEntero,w				;Calcula el valor BCD de la parte entrera de la corriente
	movwf	ValBIN
	call	convBINaBCD
	movf	BCDuni,w
	iorlw	0x30
	movwf	AmperUni
	movf	NumeroFraccionCen,w			;Calcula el valor BCD de la parte fraccionaria (Centesima) de la corriente
	movwf	ValBIN
	call	convBINaBCD
	movf	BCDuni,w
	iorlw	0x30
	movwf	AmperFraCen
	movf	NumeroFraccionDec,w			;Calcula el valor BCD de la parte fraccionaria (Decima) de la corriente
	movwf	ValBIN
	call	convBINaBCD
	movf	BCDuni,w
	iorlw	0x30
	movwf	AmperFraDec
	movf	NumeroFraccionUni,w			;Calcula el valor BCD de la parte fraccionaria (Unidad) de la corriente
	movwf	ValBIN
	call	convBINaBCD
	movf	BCDuni,w
	iorlw	0x30
	movwf	AmperFraUni
	call	Primerletrero
	call	display
;	call	retardounseg
;============================================================
MedirVoltaje
;============================================================
	bcf		status,rp0		;cambiar al banco 0
	bcf		status,rp1
	bsf		intcon,gie		;activación general de interrupciones
	bsf		intcon,peie		;activación de interrupciones por periférico

	bsf		adcon0,chs0		;selecciona canal 1 de adc
	bcf		adcon0,chs1		;selecciona canal 1 de adc
	bcf		adcon0,chs2		;selecciona canal 1 de adc
	nop
;	call	retardoXseg

	bsf		adcon0,go_done			;iniciar la operación del ADC
esperaVoltajeADCs
	movf	banADC,w
	xorlw	0xaa
	btfss	status,z
	goto	esperaVoltajeADCs

;	bcf		intcon,gie		;activación general de interrupciones
;	bcf		intcon,peie		;activación de interrupciones por periférico

	call	SubRutAjuste
		movf	RutAjuste,w
		xorlw	0x00
		btfsc	status,z
		goto	ContCalVoltaje
		movf	RutAjuste,w
		xorlw	0x01
		btfsc	status,z
		goto	Resta4CalVoltaje
		movf	RutAjuste,w
		xorlw	0x02
		btfsc	status,z
		goto	Resta8CalVoltaje
		movf	RutAjuste,w
		xorlw	0x03
		btfsc	status,z
		goto	Resta11CalVoltaje
		goto	ContCalVoltaje
		Resta4CalVoltaje
			movlw	0x04
			movwf	ContResta
			Sig_Resta4CalVoltaje
				decf	adcbajo,1
				movf	adcbajo,w
				xorlw	0xff
				btfsc	status,z
				goto	decrementa_adcalto_Resta4CalVoltaje
				goto	continua_Resta4CalVoltaje
				decrementa_adcalto_Resta4CalVoltaje
					decf	adcalto,1
				continua_Resta4CalVoltaje
					decfsz	ContResta,1
					goto	Sig_Resta4CalVoltaje
					goto	ContCalVoltaje
		Resta8CalVoltaje
			movlw	0x08
			movwf	ContResta
			Sig_Resta8CalVoltaje
				decf	adcbajo,1
				movf	adcbajo,w
				xorlw	0xff
				btfsc	status,z
				goto	decrementa_adcalto_Resta8CalVoltaje
				goto	continua_Resta8CalVoltaje
				decrementa_adcalto_Resta8CalVoltaje
					decf	adcalto,1
				continua_Resta8CalVoltaje
					decfsz	ContResta,1
					goto	Sig_Resta8CalVoltaje
					goto	ContCalVoltaje
		Resta11CalVoltaje
			movlw	.011
			movwf	ContResta
			Sig_Resta11CalVoltaje
				decf	adcbajo,1
				movf	adcbajo,w
				xorlw	0xff
				btfsc	status,z
				goto	decrementa_adcalto_Resta11CalVoltaje
				goto	continua_Resta11CalVoltaje
				decrementa_adcalto_Resta11CalVoltaje
					decf	adcalto,1
				continua_Resta11CalVoltaje
					decfsz	ContResta,1
					goto	Sig_Resta11CalVoltaje
					goto	ContCalVoltaje
ContCalVoltaje
	clrf	banADC
	movlw	.000
	movwf	divisorDec
	movlw	.022
	movwf	divisorUni
	movlw	.009
	movwf	contadorMulti
	call	DivisionCalculos

	movf	NumeroEntero,w
	movwf	VoltAlto
	movf	NumeroFraccionCen,w
	movwf	VoltBajo
	addwf	VoltBajo,1
	addwf	VoltBajo,1
	addwf	VoltBajo,1
	addwf	VoltBajo,1
	addwf	VoltBajo,1
	addwf	VoltBajo,1
	addwf	VoltBajo,1
	addwf	VoltBajo,1
	addwf	VoltBajo,1
	movf	NumeroFraccionDec,w
	addwf	VoltBajo,1

	movf	NumeroEntero,w				;Calcula el valor BCD de la parte entrera del voltaje
	movwf	ValBIN
	call	convBINaBCD
	movf	BCDuni,w
	iorlw	0x30
	movwf	VoltsUni
	movf	BCDdec,w
	iorlw	0x30
	movwf	VoltsDec
	movf	NumeroFraccionCen,w			;Calcula el valor BCD de la parte fraccionaria (Centesima) del voltaje
	movwf	ValBIN
	call	convBINaBCD
	movf	BCDuni,w
	iorlw	0x30
	movwf	VoltsFracUni
	movf	NumeroFraccionDec,w			;Calcula el valor BCD de la parte fraccionaria (Decima) del voltaje
	movwf	ValBIN
	call	convBINaBCD
	movf	BCDuni,w
	iorlw	0x30
	movwf	VoltsFracDec
	call	Primerletrero
	call	display
;	call	retardounseg
;============================================================
MedirTemperatura
;============================================================
	bcf		status,rp0		;cambiar al banco 0
	bcf		status,rp1
	bsf		intcon,gie		;activación general de interrupciones
	bsf		intcon,peie		;activación de interrupciones por periférico

	bcf		adcon0,chs0		;selecciona canal 2 de adc
	bsf		adcon0,chs1		;selecciona canal 2 de adc
	bcf		adcon0,chs2		;selecciona canal 2 de adc
	nop
;	call	retardoXseg

	bsf		adcon0,go_done			;iniciar la operación del ADC
esperaTemperaturaADCs
	movf	banADC,w
	xorlw	0xaa
	btfss	status,z
	goto	esperaTemperaturaADCs

;	bcf		intcon,gie		;activación general de interrupciones
;	bcf		intcon,peie		;activación de interrupciones por periférico

	clrf	banADC
	movf	adcalto,w
	movwf	Ventiladoralto
	movf	adcbajo,w
	movwf	Ventiladorbajo

	movlw	.009
	movwf	contadorMulti
	call	MultiplicacionCalculos

	movlw	0x00
	movwf	divisorDec
	movlw	0x14
	movwf	divisorUni
	movlw	.009
	movwf	contadorMulti
	call	DivisionCalculos



	movf	NumeroEntero,w				;Calcula el valor BCD de la parte entrera de la temperatura
	movwf	ValBIN
	call	convBINaBCD
	movf	BCDuni,w
	iorlw	0x30
	movwf	UniTemp
	movf	BCDdec,w
	iorlw	0x30
	movwf	DecTemp
	movf	NumeroFraccionCen,w			;Calcula el valor BCD de la parte fraccionaria de la temperatura
	movwf	ValBIN
	call	convBINaBCD
	movf	BCDuni,w
	iorlw	0x30
	movwf	FraTemp
	
	movf	NumeroEntero,w				;Calcula el valor BCD de la parte entrera de la temperatura
	movwf	Talta
	
	movf	NumeroFraccionCen,w			;Calcula el valor BCD de la parte fraccionaria de la temperatura
	movwf	Tbaja
	
	call	Primerletrero
	call	display
;	call	retardounseg
;============================================================
Apaga_Enciende_Ventilador
;============================================================
	bcf		status,c
	rrf		Ventiladoralto,1
	rrf		Ventiladorbajo,1
	bcf		status,c
	movlw	.040
	subwf	Ventiladorbajo,w				;Resultado resta parte baja
	movwf	Ventiladorbajo
	btfsc	status,c
	goto	restaVentilador
acarreoVentilador
	decf	Ventiladoralto,1
	movf	Ventiladoralto,w
	xorlw	0xff
	btfsc	status,z
	goto	apagaVentilador
	goto	restaVentilador
restaVentilador
	bcf		status,c
	movlw	0x00
	subwf	Ventiladoralto,w
	movwf	Ventiladoralto				;Resultado resta parte alta
	btfsc	status,c
	goto	encenderVentilador
	goto	apagaVentilador
encenderVentilador
	bsf		portc,Ventilador
	goto	MedirCorriente
apagaVentilador
	bcf		portc,Ventilador
	goto	MedirCorriente
;==============================================================
;Subrutinas
;==============================================================
;------------------------------------------------------------
ConfigADC					;Activación del ADC
;------------------------------------------------------------
	bsf		status,rp0		;cambia al banco 1
	bcf		status,rp1
	bsf		adcon1,adfm		;justifica ADC a la derecha
	bcf		adcon1,pcfg0	;control de puerto adc		solo el puerto A
	bsf		adcon1,pcfg1	;control de puerto adc		solo el puerto A
	bcf		adcon1,pcfg2	;control de puerto adc		solo el puerto A
	bcf		adcon1,pcfg3	;control de puerto adc		solo el puerto A
	bcf		status,rp0		;cambia al banco 0
	bcf		status,rp1
	bsf		adcon0,adcs0	;configura la frecuencia de muestreo
	bsf		adcon0,adcs1	;configura la frecuencia de muestreo
	bsf		adcon0,adon		;activa el ADC
;	bsf		intcon,gie		;activación general de interrupciones
;	bsf		intcon,peie		;activación de interrupciones por periférico
	bsf		status,rp0		;cambia al banco 1
	bcf		status,rp1
	bsf		pie1,adie		;activación de interrupción por ADC
	bcf		status,rp0		;cambia al banco 0
	bcf		status,rp1
	return
;------------------------------------------------------------
;Modo instruccion
;------------------------------------------------------------
modoinstru
	movf	varLCD,w		;enmascara el nibble 
	andlw	d'240' 			;alto de la variable varLCD
	movwf	portb
	bsf		portb,3			;genera un pulso de
	call	temp10micros	;habilitacion durante 10 microsegundos
	bcf		portb,3
	swapf	varLCD,w 		;intercambia los nibbles
	andlw	d'240'			;enmascara el nibble alto
 	movwf	portb 			;de la variable varLCD
	bsf		portb,3			;genera un pulso de 
	call	temp10micros 	;habilitacion durante 10 microsegundos
	bcf		portb,3
	bsf		portb,0 		;regresa el LCD a modo caracter
	return
;------------------------------------------------------------
;Modo caracter
;------------------------------------------------------------
modocaracter
	movf	varLCD,w		;enmascara el nibble 
	andlw	d'240' 			;alto de la variable varLCD
	movwf	portb
	bsf		portb,0			;coloca al LCD a modo caracter
	bsf		portb,3 		;genera un pulso de 
	call	temp10micros 	;habilitacion durante 10 microsegundos
	bcf		portb,3
	swapf	varLCD,w		;intercambia los nibbles
	andlw	d'240'			;enmascara el nibble alto 
	movwf	portb			;de la variable varLCD
	bsf		portb,0			;coloca al LCD a modo caracter
	bsf		portb,3			;genera un pulso de 
	call	temp10micros	;habilitacion durante 10 microsegundos
	bcf		portb,3
	return
;------------------------------------------------------------
IniciaDisplayLCD			;Rutina que inicializa al LCD
;------------------------------------------------------------
	bcf		status,rp0		;cambiar al banco 0
	bcf		status,rp1
	movlw	0x00
	movwf	portb			;limpia todas las lineas de salida
	movlw	d'200'			;temporizacion de 200 ms
	movwf	ret1			;para reestablecer al LCD
	call	Retardos
	movlw	d'48'			;fija operación de 8 bits en el 
	movwf	portb			;LCD
	bsf		portb,3			;genera un pulso de habilitacion
	call	temp10micros	;durante 10 microsegundos
	bcf		portb,3
	movlw	d'10'			;pausa de 100 ms
	movwf	ret1
	call	Retardos
	bsf		portb,3			;genera un pulso de habilitacion
	call	temp10micros	;durante 10 microsegundos
	bcf		portb,3
	bsf		portb,3			;genera un pulso de habilitacion
	call	temp10micros	;durante 10 microsegundos
	bcf		portb,3
	movlw	d'32'			;fija operación de 4 bits en el 
	movwf	portb			;LCD
	bsf		portb,3			;genera un pulso de habilitacion
	call	temp10micros	;durante 10 microsegundos
	bcf		portb,3
	bsf		portb,3			;genera un pulso de habilitacion
	call	temp10micros	;durante 10 microsegundos
	bcf		portb,3
	movlw	d'128'			;fija operación de 2 lineas en el 
	movwf	portb			;LCD
	bsf		portb,3			;genera un pulso de habilitacion
	call	temp10micros	;durante 10 microsegundos
	bcf		portb,3
	movlw	d'14'			;instruccion que enciende el cursor
	movwf	varLCD			;del LCD
	call	modoinstru		;escribe la instruccion en el LCD
	call	retardounseg
	movlw	d'01'			;instruccion para limpiar el
 	movwf	varLCD			;display y coloca el 
	call	modoinstru		;cursor al inicio de la primera linea
	movlw	_espaci
	movwf	varLCD
	call	modocaracter
	call	retardounseg	;retardo para mostrar los valores
	movlw	d'12'			;esconde el cursor
	movwf	varLCD
	call	modoinstru
	call	display
	return
;------------------------------------------------------------
display						;Imprime letreros en diaplay
;------------------------------------------------------------
	movlw	d'128'			;se coloca en la primer linea
	movwf	varLCD
	call	modoinstru
	movf	var1ren0,w
	movwf	varLCD
	call	modocaracter
	movf	var1ren1,w
	movwf	varLCD
	call	modocaracter
	movf	var1ren2,w
	movwf	varLCD
	call	modocaracter
	movf	var1ren3,w
	movwf	varLCD
	call	modocaracter
	movf	var1ren4,w
	movwf	varLCD
	call	modocaracter
	movf	var1ren5,w
	movwf	varLCD
	call	modocaracter
	movf	var1ren6,w
	movwf	varLCD
	call	modocaracter
	movf	var1ren7,w
	movwf	varLCD
	call	modocaracter
	movf	var1ren8,w
	movwf	varLCD
	call	modocaracter
	movf	var1ren9,w
	movwf	varLCD
	call	modocaracter
	movf	var1ren10,w
	movwf	varLCD
	call	modocaracter
	movf	var1ren11,w
	movwf	varLCD
	call	modocaracter
	movf	var1ren12,w
	movwf	varLCD
	call	modocaracter
	movf	var1ren13,w
	movwf	varLCD
	call	modocaracter
	movf	var1ren14,w
	movwf	varLCD
	call	modocaracter
	movf	var1ren15,w
	movwf	varLCD
	call	modocaracter
	movlw	d'192'			;instruccion para 
	movwf	varLCD			;comenzar la segunda
	call	modoinstru 		;linea
	movf	var2ren0,w
	movwf	varLCD
	call	modocaracter
	movf	var2ren1,w
	movwf	varLCD
	call	modocaracter
	movf	var2ren2,w
	movwf	varLCD
	call	modocaracter
	movf	var2ren3,w
	movwf	varLCD
	call	modocaracter
	movf	var2ren4,w
	movwf	varLCD
	call	modocaracter
	movf	var2ren5,w
	movwf	varLCD
	call	modocaracter
	movf	var2ren6,w
	movwf	varLCD
	call	modocaracter
	movf	var2ren7,w
	movwf	varLCD
	call	modocaracter
	movf	var2ren8,w
	movwf	varLCD
	call	modocaracter
	movf	var2ren9,w
	movwf	varLCD
	call	modocaracter
	movf	var2ren10,w
	movwf	varLCD
	call	modocaracter
	movf	var2ren11,w
	movwf	varLCD
	call	modocaracter
	movf	var2ren12,w
	movwf	varLCD
	call	modocaracter
	movf	var2ren13,w
	movwf	varLCD
	call	modocaracter
	movf	var2ren14,w
	movwf	varLCD
	call	modocaracter
	movf	var2ren15,w
	movwf	varLCD
	call	modocaracter
	return


;------------------------------------------------------------
;Subrutina para convertir a codigo BCD
;------------------------------------------------------------
convBINaBCD
	bcf		status,rp0	;cambiar al banco 0
	bcf		status,rp1
	clrf	BCDuni
	clrf	BCDdec
div_entre_10			;divide entre 10
	bcf		status,c
	movlw	.10
	subwf	ValBIN,1
	btfsc	status,c
	goto	sigresta
negativo
	movlw	.10
	addwf	ValBIN,w
	movwf	BCDuni
	goto	finconversion
sigresta
	incf	BCDdec,1
	movf	ValBIN,w	;pregunta si el resultado de la resta fue 0
	xorlw	0x00
	btfss	status,z
	goto	div_entre_10
finconversion
	return



;------------------------------------------------------------
DivisionCalculos
;------------------------------------------------------------
	bcf		status,rp0	;cambiar al banco 0
	bcf		status,rp1
	clrf	NumeroEntero
	clrf	NumeroFraccionCen
	clrf	NumeroFraccionDec
	clrf	NumeroFraccionUni
calculaDecimal
	bcf		status,c
	movf	divisorUni,w
	subwf	adcbajo,w				;Resultado resta parte baja
	movwf	adcbajo
	btfsc	status,c
	goto	restaDecimal
acarreoDecimal

	decf	adcalto,1
	movf	adcalto,w
	xorlw	0xff
	btfsc	status,z
	goto	terminaDecimal
	goto	restaDecimal
terminaDecimal
	movf	divisorUni,w
	addwf	adcbajo,1
	btfsc	status,c
	goto	restableceadcaltoDecimal
	goto	multiplicaDecimal
restableceadcaltoDecimal
	incf	adcalto,1
	goto	multiplicaDecimal

restaDecimal
	bcf		status,c
	movf	divisorDec,w
	subwf	adcalto,w
	movwf	adcalto				;Resultado resta parte alta
	btfsc	status,c
	goto	resultadopositivoDecimal
resultadonegativoDecimal
	movf	divisorUni,w
	addwf	adcbajo,1
	btfsc	status,c
	goto	incremetaEnteroAlto
	goto	sumarEnteroalta
incremetaEnteroAlto
	incf	adcalto,1
sumarEnteroalta
	movf	divisorDec,w
	addwf	adcalto,1
	goto	multiplicaDecimal
resultadopositivoDecimal
	incf	NumeroEntero,1
	movf	adcbajo,w
	xorlw	0x00
	btfss	status,z
	goto	calculaDecimal
	movf	adcalto,w
	xorlw	0x00
	btfss	status,z
	goto	calculaDecimal
multiplicaDecimal
	call	MultiplicacionCalculos
calculaFraccionCen
	bcf		status,c
	movf	divisorUni,w
	subwf	adcbajo,w				;Resultado resta parte baja
	movwf	adcbajo
	btfsc	status,c
	goto	restaFraccionCen
acarreoFraccionCen

	decf	adcalto,1
	movf	adcalto,w
	xorlw	0xff
	btfsc	status,z
	goto	terminaFraccionCen
	goto	restaFraccionCen
terminaFraccionCen
	movf	divisorUni,w
	addwf	adcbajo,1
	btfsc	status,c
	goto	restableceadcaltoFraccionCen
	goto	multiplicaFraccionCen
restableceadcaltoFraccionCen
	incf	adcalto,1
	goto	multiplicaFraccionCen

restaFraccionCen
	bcf		status,c
	movf	divisorDec,w
	subwf	adcalto,w
	movwf	adcalto				;Resultado resta parte alta
	btfsc	status,c
	goto	resultadopositivoFraccionCen
resultadonegativoFraccionCen
	movf	divisorUni,w
	addwf	adcbajo,1
	btfsc	status,c
	goto	incremetaFraccionCenAlto
	goto	sumarFraccionCenalta
incremetaFraccionCenAlto
	incf	adcalto,1
sumarFraccionCenalta
	movf	divisorDec,w
	addwf	adcalto,1
	goto	multiplicaFraccionCen
resultadopositivoFraccionCen
	incf	NumeroFraccionCen,1
	movf	adcbajo,w
	xorlw	0x00
	btfss	status,z
	goto	calculaFraccionCen
	movf	adcalto,w
	xorlw	0x00
	btfss	status,z
	goto	calculaFraccionCen
multiplicaFraccionCen
	call	MultiplicacionCalculos
calculaFraccionDec
	bcf		status,c
	movf	divisorUni,w
	subwf	adcbajo,w				;Resultado resta parte baja
	movwf	adcbajo
	btfsc	status,c
	goto	restaFraccionDec
acarreoFraccionDec

	decf	adcalto,1
	movf	adcalto,w
	xorlw	0xff
	btfsc	status,z
	goto	terminaFraccionDec
	goto	restaFraccionDec
terminaFraccionDec
	movf	divisorUni,w
	addwf	adcbajo,1
	btfsc	status,c
	goto	restableceadcaltoFraccionDec
	goto	multiplicaFraccionDec
restableceadcaltoFraccionDec
	incf	adcalto,1
	goto	multiplicaFraccionDec

restaFraccionDec
	bcf		status,c
	movf	divisorDec,w
	subwf	adcalto,w
	movwf	adcalto				;Resultado resta parte alta
	btfsc	status,c
	goto	resultadopositivoFraccionDec
resultadonegativoFraccionDec
	movf	divisorUni,w
	addwf	adcbajo,1
	btfsc	status,c
	goto	incremetaFraccionDecAlto
	goto	sumarFraccionDecalta
incremetaFraccionDecAlto
	incf	adcalto,1
sumarFraccionDecalta
	movf	divisorDec,w
	addwf	adcalto,1
	goto	multiplicaFraccionDec
resultadopositivoFraccionDec
	incf	NumeroFraccionDec,1
	movf	adcbajo,w
	xorlw	0x00
	btfss	status,z
	goto	calculaFraccionDec
	movf	adcalto,w
	xorlw	0x00
	btfss	status,z
	goto	calculaFraccionDec
multiplicaFraccionDec
	call	MultiplicacionCalculos
calculaFraccionUni
	bcf		status,c
	movf	divisorUni,w
	subwf	adcbajo,w				;Resultado resta parte baja
	movwf	adcbajo
	btfsc	status,c
	goto	restaFraccionUni
acarreoFraccionUni

	decf	adcalto,1
	movf	adcalto,w
	xorlw	0xff
	btfsc	status,z
	goto	terminaFraccionUni
	goto	restaFraccionUni
terminaFraccionUni
	movf	divisorUni,w
	addwf	adcbajo,1
	btfsc	status,c
	goto	restableceadcaltoFraccionUni
	return
restableceadcaltoFraccionUni
	incf	adcalto,1
	return

restaFraccionUni
	bcf		status,c
	movf	divisorDec,w
	subwf	adcalto,w
	movwf	adcalto				;Resultado resta parte alta
	btfsc	status,c
	goto	resultadopositivoFraccionUni
resultadonegativoFraccionUni
	movf	divisorUni,w
	addwf	adcbajo,1
	btfsc	status,c
	goto	incremetaFraccionUniAlto
	goto	sumarFraccionUnialta
incremetaFraccionUniAlto
	incf	adcalto,1
sumarFraccionUnialta
	movf	divisorDec,w
	addwf	adcalto,1
	return
resultadopositivoFraccionUni
	incf	NumeroFraccionUni,1

	movf	adcbajo,w
	xorlw	0x00
	btfss	status,z
	goto	calculaFraccionUni
	movf	adcalto,w
	xorlw	0x00
	btfss	status,z
	goto	calculaFraccionUni
	return
;------------------------------------------------------------
MultiplicacionCalculos
;------------------------------------------------------------
	movf	contadorMulti,w
	movwf	contadorMultiOper
	movf	adcbajo,w
	movwf	TempMultibajo
	movf	adcalto,w
	movwf	TempMultialto
cicloMulti
	movf	TempMultibajo,w
	addwf	adcbajo,1
	btfsc	status,c
	goto	incremetaVoltsAlto
	goto	sumarpartealta
incremetaVoltsAlto
	incf	adcalto,1
sumarpartealta
	movf	TempMultialto,w
	addwf	adcalto,1
terminociclo?
	decfsz	contadorMultiOper,1
	goto	cicloMulti
	return
;------------------------------------------------------------
SubRutAjuste
;------------------------------------------------------------
	btfsc	adcalto,0			;bit 0 es igual al bit 9
	goto	bit9es1
	btfsc	adcalto,1			;bit 1 es igual al bit 10
	goto	Bit9_es_0_Bit10_es_1
	goto	Bit9_10_son_0
bit9es1
	btfsc	adcalto,1
	goto	Bit9_10_son_1
	goto	Bit9_es_1_Bit10_es_0
Bit9_10_son_0
	movlw	0x00
	movwf	RutAjuste
	return
Bit9_es_1_Bit10_es_0
	movlw	0x01
	movwf	RutAjuste
	return
Bit9_es_0_Bit10_es_1
	movlw	0x02
	movwf	RutAjuste
	return
Bit9_10_son_1
	movlw	0x03
	movwf	RutAjuste
	return
;------------------------------------------------------------
letreroBienvenida
;------------------------------------------------------------
	bcf		status,rp0	;cambiar al banco 0
	bcf		status,rp1
	movlw	_espaci
	movwf	var1ren0
	movlw	_espaci
	movwf	var1ren1
	movlw	_espaci
	movwf	var1ren2
	movlw	_espaci
	movwf	var1ren3
	movlw	_espaci
	movwf	var1ren4
	movlw	_S
	movwf	var1ren5
	movlw	_M
	movwf	var1ren6
	movlw	_C
	movwf	var1ren7
	movlw	_P
	movwf	var1ren8
	movlw	_A
	movwf	var1ren9
	movlw	_M
	movwf	var1ren10
	movlw	_espaci
	movwf	var1ren11
	movlw	_espaci
	movwf	var1ren12
	movlw	_espaci
	movwf	var1ren13
	movlw	_espaci
	movwf	var1ren14
	movlw	_espaci
	movwf	var1ren15
	movlw	_espaci
	movwf	var2ren0
	movlw	_T
	movwf	var2ren1
	movlw	_T
	movwf	var2ren2
	movlw	_espaci
	movwf	var2ren3
	movlw	_2
	movwf	var2ren4
	movlw	_0
	movwf	var2ren5
	movlw	_1
	movwf	var2ren6
	movlw	_8
	movwf	var2ren7
	movlw	_espaci
	movwf	var2ren8
	movlw	_menos
	movwf	var2ren9
	movlw	_espaci
	movwf	var2ren10
	movlw	_A
	movwf	var2ren11
	movlw	_1
	movwf	var2ren12
	movlw	_0
	movwf	var2ren13
	movlw	_2
	movwf	var2ren14
	movlw	_espaci
	movwf	var2ren15
	return
;------------------------------------------------------------
Primerletrero
;------------------------------------------------------------
	bcf		status,rp0	;cambiar al banco 0
	bcf		status,rp1
	movlw	_V
	movwf	var1ren0
	movlw	_espaci
	movwf	var1ren1
	movf	VoltsDec,w
	movwf	var1ren2
	movf	VoltsUni,w
	movwf	var1ren3
	movlw	_punto
	movwf	var1ren4
	movf	VoltsFracUni,w
	movwf	var1ren5
	movf	VoltsFracDec,w
	movwf	var1ren6
	movlw	_V
	movwf	var1ren7
	movlw	_espaci
	movwf	var1ren8
	movlw	_espaci
	movwf	var1ren9
	movlw	_T
	movwf	var1ren10
	movlw	_e
	movwf	var1ren11
	movlw	_m
	movwf	var1ren12
	movlw	_p
	movwf	var1ren13
	movlw	_espaci
	movwf	var1ren14
	movlw	_espaci
	movwf	var1ren15
	movlw	_I
	movwf	var2ren0
	movlw	_espaci
	movwf	var2ren1
	movf	AmperUni,w
	movwf	var2ren2
	movlw	_punto
	movwf	var2ren3
	movf	AmperFraCen,w
	movwf	var2ren4
	movf	AmperFraDec,w
	movwf	var2ren5
	movf	AmperFraUni,w
	movwf	var2ren6
	movlw	_A
	movwf	var2ren7
	movlw	_espaci
	movwf	var2ren8
	movf	DecTemp,w
	movwf	var2ren9
	movf	UniTemp,w
	movwf	var2ren10
	movlw	_punto
	movwf	var2ren11
	movf	FraTemp,w
	movwf	var2ren12
	movlw	_espaci
	movwf	var2ren13
	movlw	_grado
	movwf	var2ren14
	movlw	_C
	movwf	var2ren15
	return




;------------------------------------------------------------
PantallaRX				;CÓDIGO DE PRUEBA
;------------------------------------------------------------
	bcf		status,rp0	;cambiar al banco 0
	bcf		status,rp1
	movlw	_R
	movwf	var1ren0
	movlw	_x
	movwf	var1ren1
	movlw	_D
	movwf	var1ren2
	movlw	_e
	movwf	var1ren3
	movlw	_c
	movwf	var1ren4
	movlw	_espaci
	movwf	var1ren5
	movf	BCDCen,w
	movwf	var1ren6
	movf	BCDDec,w
	movwf	var1ren7
	movf	BCDUni,w
	movwf	var1ren8
	movlw	_espaci
	movwf	var1ren9
	movlw	_H
	movwf	var1ren10
	movlw	_e
	movwf	var1ren11
	movlw	_x
	movwf	var1ren12
	movlw	_espaci
	movwf	var1ren13
	movf	HexAlto,w
	movwf	var1ren14
	movf	HexBajo,w
	movwf	var1ren15
	movlw	_R
	movwf	var2ren0
	movlw	_x
	movwf	var2ren1
	movlw	_A
	movwf	var2ren2
	movlw	_S
	movwf	var2ren3
	movlw	_C
	movwf	var2ren4
	movlw	_C
	movwf	var2ren5
	movlw	_I
	movwf	var2ren6
	movlw	_espaci
	movwf	var2ren7
	movf	RxUSART,w
	movwf	var2ren8
	movlw	_espaci
	movwf	var2ren9
	movlw	_espaci
	movwf	var2ren10
	movlw	_espaci
	movwf	var2ren11
	movlw	_espaci
	movwf	var2ren12
	movlw	_espaci
	movwf	var2ren13
	movlw	_espaci
	movwf	var2ren14
	movlw	_espaci
	movwf	var2ren15
	return
;------------------------------------------------------------
PantallaTX				;CÓDIGO DE PRUEBA
;------------------------------------------------------------
	bcf		status,rp0	;cambiar al banco 0
	bcf		status,rp1
	movlw	_R
	movwf	var1ren0
	movlw	_x
	movwf	var1ren1
	movlw	_D
	movwf	var1ren2
	movlw	_e
	movwf	var1ren3
	movlw	_c
	movwf	var1ren4
	movlw	_espaci
	movwf	var1ren5
	movf	BCDCen,w
	movwf	var1ren6
	movf	BCDDec,w
	movwf	var1ren7
	movf	BCDUni,w
	movwf	var1ren8
	movlw	_espaci
	movwf	var1ren9
	movlw	_H
	movwf	var1ren10
	movlw	_e
	movwf	var1ren11
	movlw	_x
	movwf	var1ren12
	movlw	_espaci
	movwf	var1ren13
	movf	HexAlto,w
	movwf	var1ren14
	movf	HexBajo,w
	movwf	var1ren15
	movlw	_R
	movwf	var2ren0
	movlw	_x
	movwf	var2ren1
	movlw	_A
	movwf	var2ren2
	movlw	_S
	movwf	var2ren3
	movlw	_C
	movwf	var2ren4
	movlw	_C
	movwf	var2ren5
	movlw	_I
	movwf	var2ren6
	movlw	_espaci
	movwf	var2ren7
	movf	RxUSART,w
	movwf	var2ren8
	movlw	_espaci
	movwf	var2ren9
	movlw	_P
	movwf	var2ren10
	movlw	_I
	movwf	var2ren11
	movlw	_C
	movwf	var2ren12
	movlw	_espaci
	movwf	var2ren13
	movlw	_T
	movwf	var2ren14
	movlw	_x
	movwf	var2ren15
	return
;------------------------------------------------------------
valores_TX				;CÓDIGO DE PRUEBA
;------------------------------------------------------------
	bcf		status,rp0	;cambiar al banco 0
	bcf		status,rp1
	movf	T1Alto,w
	movwf	var1ren0
	movf	T1Bajo,w
	movwf	var1ren1
	movlw	_espaci
	movwf	var1ren2
	movf	T2Alto,w
	movwf	var1ren3
	movf	T2Bajo,w
	movwf	var1ren4
	movlw	_espaci
	movwf	var1ren5
	movf	T3Alto,w
	movwf	var1ren6
	movf	T3Bajo,w
	movwf	var1ren7
	movlw	_espaci
	movwf	var1ren8
	movf	T4Alto,w
	movwf	var1ren9
	movf	T4Bajo,w
	movwf	var1ren10
	movlw	_espaci
	movwf	var1ren11
	movf	T5Alto,w
	movwf	var1ren12
	movf	T5Bajo,w
	movwf	var1ren13
	movlw	_espaci
	movwf	var1ren14
	movlw	_espaci
	movwf	var1ren15
	movlw	_espaci
	movwf	var2ren0
	movf	T6Alto,w
	movwf	var2ren1
	movf	T6Bajo,w
	movwf	var2ren2
	movlw	_espaci
	movwf	var2ren3
	movlw	_espaci
	movwf	var2ren4
	movf	T7Alto,w
	movwf	var2ren5
	movf	T7Bajo,w
	movwf	var2ren6
	movlw	_espaci
	movwf	var2ren7
	movlw	_espaci
	movwf	var2ren8
	movf	T8Alto,w
	movwf	var2ren9
	movf	T8Bajo,w
	movwf	var2ren10
	movlw	_espaci
	movwf	var2ren11
	movlw	_espaci
	movwf	var2ren12
	movlw	_espaci
	movwf	var2ren13
	movlw	_espaci
	movwf	var2ren14
	movlw	_espaci
	movwf	var2ren15
	return
;------------------------------------------------------------
CONV_BINaBCD				;CÓDIGO DE PRUEBA		;Subrutina para convertir a codigo BCD
;------------------------------------------------------------
	bcf		status,rp0	;cambiar al banco 0
	bcf		status,rp1
	clrf	BCDUni
	clrf	BCDDec
	clrf	BCDCen
div_entre_100				;divide entre 100
	bcf		status,c
	movlw	.100
	subwf	ValRx,1
	btfsc	status,c
	goto	sigrestaCen
negativo_100
	movlw	.100
	addwf	ValRx,1
	goto	div_entre_10_BCD
sigrestaCen
	incf	BCDCen,1
	movf	ValRx,w			;pregunta si el resultado de la resta fue 0
	xorlw	0x00
	btfss	status,z
	goto	div_entre_100
div_entre_10_BCD			;divide entre 10
	bcf		status,c
	movlw	.10
	subwf	ValRx,1
	btfsc	status,c
	goto	sigrestaBCD
negativo_10
	movlw	.10
	addwf	ValRx,w
	movwf	BCDUni
	goto	finconversionBCD
sigrestaBCD
	incf	BCDDec,1
	movf	ValRx,w	;pregunta si el resultado de la resta fue 0
	xorlw	0x00
	btfss	status,z
	goto	div_entre_10_BCD
finconversionBCD
	movlw	0x30
	iorwf	BCDUni,1
	iorwf	BCDDec,1
	iorwf	BCDCen,1
	return
;------------------------------------------------------------
CONV_BINaHEX				;CÓDIGO DE PRUEBA		;Subrutina para convertir a codigo HEX
;------------------------------------------------------------
	bcf		status,rp0	;cambiar al banco 0
	bcf		status,rp1
	clrf	HexAlto
	clrf	HexBajo
ParteBaja
	movf	ValRxHex,w
	movwf	HexBajo
	movlw	0x0f
	andwf	HexBajo,1
	movf	HexBajo,w
	xorlw	0x00
	btfsc	status,z
	goto	carga0
	movf	HexBajo,w
	xorlw	0x01
	btfsc	status,z
	goto	carga1
	movf	HexBajo,w
	xorlw	0x02
	btfsc	status,z
	goto	carga2
	movf	HexBajo,w
	xorlw	0x03
	btfsc	status,z
	goto	carga3
	movf	HexBajo,w
	xorlw	0x04
	btfsc	status,z
	goto	carga4
	movf	HexBajo,w
	xorlw	0x05
	btfsc	status,z
	goto	carga5
	movf	HexBajo,w
	xorlw	0x06
	btfsc	status,z
	goto	carga6
	movf	HexBajo,w
	xorlw	0x07
	btfsc	status,z
	goto	carga7
	movf	HexBajo,w
	xorlw	0x08
	btfsc	status,z
	goto	carga8
	movf	HexBajo,w
	xorlw	0x09
	btfsc	status,z
	goto	carga9
	movf	HexBajo,w
	xorlw	0x0a
	btfsc	status,z
	goto	cargaa
	movf	HexBajo,w
	xorlw	0x0b
	btfsc	status,z
	goto	cargab
	movf	HexBajo,w
	xorlw	0x0c
	btfsc	status,z
	goto	cargac
	movf	HexBajo,w
	xorlw	0x0d
	btfsc	status,z
	goto	cargad
	movf	HexBajo,w
	xorlw	0x0e
	btfsc	status,z
	goto	cargae
	movf	HexBajo,w
	xorlw	0x0f
	btfsc	status,z
	goto	cargaf
carga0
	movlw	_0
	movwf	HexBajo
	goto	ParteAlta
carga1
	movlw	_1
	movwf	HexBajo
	goto	ParteAlta
carga2
	movlw	_2
	movwf	HexBajo
	goto	ParteAlta
carga3
	movlw	_3
	movwf	HexBajo
	goto	ParteAlta
carga4
	movlw	_4
	movwf	HexBajo
	goto	ParteAlta
carga5
	movlw	_5
	movwf	HexBajo
	goto	ParteAlta
carga6
	movlw	_6
	movwf	HexBajo
	goto	ParteAlta
carga7
	movlw	_7
	movwf	HexBajo
	goto	ParteAlta
carga8
	movlw	_8
	movwf	HexBajo
	goto	ParteAlta
carga9
	movlw	_9
	movwf	HexBajo
	goto	ParteAlta
cargaa
	movlw	_A
	movwf	HexBajo
	goto	ParteAlta
cargab
	movlw	_B
	movwf	HexBajo
	goto	ParteAlta
cargac
	movlw	_C
	movwf	HexBajo
	goto	ParteAlta
cargad
	movlw	_D
	movwf	HexBajo
	goto	ParteAlta
cargae
	movlw	_E
	movwf	HexBajo
	goto	ParteAlta
cargaf
	movlw	_F
	movwf	HexBajo
	goto	ParteAlta
ParteAlta
	swapf	ValRxHex,1
	movlw	0x0f
	andwf	ValRxHex,w
	movwf	HexAlto
	movf	HexAlto,w
	xorlw	0x00
	btfsc	status,z
	goto	carga00
	movf	HexAlto,w
	xorlw	0x01
	btfsc	status,z
	goto	carga01
	movf	HexAlto,w
	xorlw	0x02
	btfsc	status,z
	goto	carga02
	movf	HexAlto,w
	xorlw	0x03
	btfsc	status,z
	goto	carga03
	movf	HexAlto,w
	xorlw	0x04
	btfsc	status,z
	goto	carga04
	movf	HexAlto,w
	xorlw	0x05
	btfsc	status,z
	goto	carga05
	movf	HexAlto,w
	xorlw	0x06
	btfsc	status,z
	goto	carga06
	movf	HexAlto,w
	xorlw	0x07
	btfsc	status,z
	goto	carga07
	movf	HexAlto,w
	xorlw	0x08
	btfsc	status,z
	goto	carga08
	movf	HexAlto,w
	xorlw	0x09
	btfsc	status,z
	goto	carga09
	movf	HexAlto,w
	xorlw	0x0a
	btfsc	status,z
	goto	carga0a
	movf	HexAlto,w
	xorlw	0x0b
	btfsc	status,z
	goto	carga0b
	movf	HexAlto,w
	xorlw	0x0c
	btfsc	status,z
	goto	carga0c
	movf	HexAlto,w
	xorlw	0x0d
	btfsc	status,z
	goto	carga0d
	movf	HexAlto,w
	xorlw	0x0e
	btfsc	status,z
	goto	carga0e
	movf	HexAlto,w
	xorlw	0x0f
	btfsc	status,z
	goto	carga0f
carga00
	movlw	_0
	movwf	HexAlto
	return
carga01
	movlw	_1
	movwf	HexAlto
	return
carga02
	movlw	_2
	movwf	HexAlto
	return
carga03
	movlw	_3
	movwf	HexAlto
	return
carga04
	movlw	_4
	movwf	HexAlto
	return
carga05
	movlw	_5
	movwf	HexAlto
	return
carga06
	movlw	_6
	movwf	HexAlto
	return
carga07
	movlw	_7
	movwf	HexAlto
	return
carga08
	movlw	_8
	movwf	HexAlto
	return
carga09
	movlw	_9
	movwf	HexAlto
	return
carga0a
	movlw	_A
	movwf	HexAlto
	return
carga0b
	movlw	_B
	movwf	HexAlto
	return
carga0c
	movlw	_C
	movwf	HexAlto
	return
carga0d
	movlw	_D
	movwf	HexAlto
	return
carga0e
	movlw	_E
	movwf	HexAlto
	return
carga0f
	movlw	_F
	movwf	HexAlto
	return







;------------------------------------------------------------
Retardos					;Retardo de 200 milisegundos
;------------------------------------------------------------
ret1_3
	movlw	.02
	movwf	ret2
ret1_2
	movlw	.166
	movwf	ret3
ret1_1
	decfsz	ret3,1			;497microsegundos=aprox0.5milisegundos
	goto	ret1_1
	decfsz	ret2,1
	goto	ret1_2
	decfsz	ret1,1
	goto	ret1_3
	return
;------------------------------------------------------------
temp10micros				;Retardo de 10 microsegundos
;------------------------------------------------------------
	movlw	.10
	movwf	ret3
ret2_1
	decfsz	ret3,1
	goto	ret2_1
	return
;------------------------------------------------------------
retardounseg					;Retardo de 1 segundo
;------------------------------------------------------------
	movlw	 .255
	movwf	 var1
ciclo_3
	movlw	.08
	movwf	var2
ciclo_2
	movlw	.166
	movwf	var3
ciclo_1
	decfsz	var3,1		;497 microsegundos = aprox. 0.5 milisegundos
	goto	ciclo_1
	decfsz	var2,1
	goto	ciclo_2
	decfsz	var1,1
	goto	ciclo_3
	return
;------------------------------------------------------------
retardoXseg					;Retardo de X segundos
;------------------------------------------------------------
	movlw	 .125		;.255 Para 1 segundo
	movwf	 var1
ciclos_3
	movlw	.08
	movwf	var2
ciclos_2
	movlw	.166
	movwf	var3
ciclos_1
	decfsz	var3,1		;497 microsegundos = aprox. 0.5 milisegundos
	goto	ciclos_1
	decfsz	var2,1
	goto	ciclos_2
	decfsz	var1,1
	goto	ciclos_3
	return
;--------------------------------------------------------------------------
transmite					;Rutina que se encarga de la transmisión
;--------------------------------------------------------------------------
	bsf    status,rp0		;cambiar al banco 1
	bcf    status,rp1
	movlw  b'00100110'
	movwf  txsta
	movlw  .25
	movwf  spbrg
	bcf    status,rp0		;cambiar al banco 0
	bcf    status,rp1
	bsf    rcsta,spen
	movf   TxUSART,w
	movwf  txreg
txespera
	btfss  pir1,txif
	goto   txespera
	return
	end