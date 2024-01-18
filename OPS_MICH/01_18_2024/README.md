# 18.1. 2024 PISEMKA - mozna
## ZADANI A PROGRESS
Vytvorte seriovy terminal pro zarizeni, ktere obslouzi prikazy:
1. help
2. sh[ow]
	- config - **hotovo**
	- led
	- ip route
3. en[able] - **hotovo**
4. blink [led #n] [period #t]
5. timer [MM:SS]
6. measure [#n samples]
7. setup
	- set volts [0/1]
	- set password [heslo]
	- ip route [NET_IP] [MASK]
	- interface loopback [IP] [MASK]

8. Pred vstupem do zarizeni je treba aktivovat pin na KBD : 1337 - **hotovo**
9. Prijem na UARTu pomoci UART_getc() a UART_putc() - **hotovo**