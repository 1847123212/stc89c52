#include "contiki.h"
#include "stack.h"
#include "sys/clock.h"
#include "sys/autostart.h"
#include"spin_common.h"
#include"spin_userstart.h"
#include"spin_interupt.h"
#include"spin_timer.h"
#include"spin_exinterupt.h"
#include"spin_gpio.h"
#include"spin_uart.h"
#include"spin_watchdog.h"
#include"spin_pwrmgr.h"

void hardware_init(){
   //Ӳ����ʼ������
   spin_set_work_register_group(0);
   spin_interupt_init();
   spin_interupt_enable();
   spin_uart_init();
   //spin_watchdog_enable();
   //spin_watchdog_overtime(32,FSOC); //�������ʱ��ms ���ڴ�Լ��1000
   spin_exint0_start(down_eage);
   spin_exint1_start(low_vol);
   //���ڲ���
   //xdev_in(u_getc);
   //xdev_out(u_putc);
}
PROCESS(led);//����led��ת����
AUTOSTART_PROCESSES(&led);//ע��task
PROCESS_THREAD(led, ev, dataa)
{
	static struct etimer xdata et;
    PROCESS_BEGIN();
	//��ʱ1s��ʱ��
	etimer_set(&et,CLOCK_SECOND*1);
	while(1)
	{
		spin_set_gpio_bit_value(GPIO2,0,0);
		//�ȴ�1s
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));	
	    //����led
		spin_set_gpio_bit_value(GPIO2,0,1);
		//�ȴ�1s
		etimer_set(&et,CLOCK_SECOND*1);
		etimer_restart(&et);
    	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
		//�ر�led
		spin_set_gpio_bit_value(GPIO2,0,0);
		etimer_set(&et,CLOCK_SECOND*1);
		etimer_restart(&et);
	}
   PROCESS_END();
}
int
main(void)
{
  hardware_init();
  clock_init();
  process_init();
 /* start services */
  process_start(&etimer_process, NULL);
  autostart_start(autostart_processes);
  for(;;)process_run();
  return 0;
}
