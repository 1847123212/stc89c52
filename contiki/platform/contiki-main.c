#include "contiki.h"
#include "stack.h"
#include "sys/clock.h"
#include "sys/autostart.h"
#include "spin_gpio.h"
PROCESS(led, "led");//����led��ת����
AUTOSTART_PROCESSES(&led);//ע��task
PROCESS_THREAD(led, ev, dataa)
{
	static struct etimer xdata et;
    PROCESS_BEGIN();
	while(1)
	{	
	    //����led
		spin_set_gpio_bit_value(GPIO2,1,0);
		//��ʱ1s
		etimer_set(&et,CLOCK_SECOND*1);
    	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
		//�ر�led
		spin_set_gpio_bit_value(GPIO2,1,1);
		//��ʱ1s
		etimer_set(&et,CLOCK_SECOND*1);
    	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
	}
   PROCESS_END();
}
int
main(void)
{
  clock_init();
  while(1);
  process_init();
 /* start services */
  process_start(&etimer_process, NULL);
  autostart_start(autostart_processes);
  for(;;)process_run();
  return 0;
}
