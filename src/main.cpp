#include <mbed.h>

enum{ON,OFF}; /* a hack to invert bit logic for common anode LED */

Semaphore flag(1);

void flash_led(DigitalOut *led)
{
	wait_ms( rand()%1000 );
	while(true) {
		flag.wait();
		*led = ON;
		wait_ms( rand()%1000 );
		flag.release();
		*led = OFF;
		wait_ms( rand()%1000 );
	}
}

int main(void)
{
	DigitalOut red(LED1,OFF);
	DigitalOut green(LED2,OFF);
	DigitalOut blue(LED3,OFF);
        DigitalOut red_as(D5,OFF);
	DigitalOut green_as(D8,OFF);
	DigitalOut blue_as(D9,OFF);
	Thread p,q,r,s,t,u;

	r.start( callback(flash_led, &red) );
	p.start( callback(flash_led, &green) );
	q.start( callback(flash_led, &blue) );
        s.start( callback(flash_led, &red_as) );
	t.start( callback(flash_led, &green_as) );
	u.start( callback(flash_led, &blue_as) );
	r.join();	
}

