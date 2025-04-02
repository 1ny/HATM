#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define sbi(REG, n) (REG |=  (1<<n))
#define cbi(REG, n) (REG &= ~(1<<n))

#define LED_PIN (PINB5)
#define EINT0_PIN (PIND2)

volatile int state = 0;

ISR(INT0_vect){
	state = !state;		//상태 토글
}

int main(){
	sbi(DDRB, LED_PIN); // LED 핀 출력 설정
	
	// 외부 인터럽트 설정
	cbi(DDRD, EINT0_PIN); // 외부 인터럽트 핀 0 입력으로 설정
	sbi(PORTD, EINT0_PIN); // 풀업 저항 활성화 (option, 외부 풀업이 없을경우)
	
	sbi(EICRA, ISC01); // ISC01,ISC00=1,0 폴링 엣지
	cbi(EICRA, ISC00);
	sbi(EIMSK, INT0); // INT0 활성화
	sei(); // 전역 인터럽트 활서와
	
	while(1){
		if(state == 1){
			sbi(PORTB, LED_PIN);
		}
		else{
			cbi(PORTB, LED_PIN);
		}
	}
	return 0;
}