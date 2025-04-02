#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define LED_DELAY_TIME	(500) //ms

#define sbi(REG, n) (REG |= (0x01 << n))
#define cbi(REG, n) (REG &= ~(0X01 << n))

int main(void) {
	sbi(DDRB, PINB5); // LED 출력으로 설정
	cbi(PORTB, PINB5); // (=LED가 꺼진다)

	cbi(DDRB, PINB7);	// 스위치 입력으로 설정
	
	while(1) {				
		if((PINB >> PINB7) & 0x01) == 0) {
			sbi(PORTB, PINB5); // (=LED가 켜진다)
		} else {
			cbi(PORTB, PINB5); // (=LED가 꺼진다)
		}
	}
		
#if 0
	while (1) {
		sbi(PORTB, 5); // PB[7:0]에 모두 1을 출력한다. (=LED가 켜진다)
		_delay_ms(LED_DELAY_TIME); // LED_DELAY_TIME 만큼 기다린다.

		cbi(PORTB, 5); // PB[7:0]에 모두 0을 출력한다. (=LED가 꺼진다)
		_delay_ms(LED_DELAY_TIME); // LED_DELAY_TIME 만큼 기다린다.
		// 무한 루프로 계속 반복한다.
	}
#endif

	return (0);
}