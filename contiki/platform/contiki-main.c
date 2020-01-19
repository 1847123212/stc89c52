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
#include"xprintf.h"
void hardware_init(){
   //Ӳ����ʼ������
   spin_set_work_register_group(0);
   spin_interupt_init();
   spin_interupt_enable();
   spin_uart_init();
   spin_watchdog_enable();
   spin_watchdog_overtime(128,FSOC); //�������ʱ��ms ���ڴ�Լ��4000
   spin_exint0_start(down_eage);
   spin_exint1_start(low_vol);
   //���ڲ���
   xdev_in(u_getc);
   xdev_out(u_putc);
}
PROCESS(led,"led");//����led��ת����
PROCESS_THREAD(led, ev, dataa)
{
	static struct etimer et;
    PROCESS_BEGIN();
	//��ʱ1s��ʱ��
	etimer_set(&et,CLOCK_SECOND/4);
	while(1)
	{
		//�ȴ�1s
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));	
	    //����led
		spin_set_gpio_bit_value(GPIO2,0,0);
		//�ȴ�1s
		etimer_restart(&et);
    	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
		//�ر�led
		spin_set_gpio_bit_value(GPIO2,0,1);
		etimer_restart(&et);
	}
   PROCESS_END();
}
PROCESS(led1,"led1");//����led��ת����
PROCESS_THREAD(led1, ev, dataa)
{
	static struct etimer et;
    PROCESS_BEGIN();
	//��ʱ1s��ʱ��
	etimer_set(&et,CLOCK_SECOND/4);
	while(1)
	{
		//�ȴ�1s
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));	
	    //����led
		spin_set_gpio_bit_value(GPIO2,1,0);
		//�ȴ�1s
		etimer_restart(&et);
    	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
		//�ر�led
		spin_set_gpio_bit_value(GPIO2,1,1);
		etimer_restart(&et);
	}
   PROCESS_END();
}
PROCESS(led2,"led2");//����led��ת����
PROCESS_THREAD(led2, ev, dataa)
{
	static struct etimer et;
    PROCESS_BEGIN();
	//��ʱ1s��ʱ��
	etimer_set(&et,CLOCK_SECOND*1);
	while(1)
	{
		//�ȴ�1s
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));	
	    //����led
		spin_set_gpio_bit_value(GPIO2,2,0);
		//�ȴ�1s
		etimer_restart(&et);
    	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
		//�ر�led
		spin_set_gpio_bit_value(GPIO2,2,1);
		etimer_restart(&et);
	}
   PROCESS_END();
}
PROCESS(led3,"led3");//����led��ת����
PROCESS_THREAD(led3, ev, dataa)
{
	static struct etimer et;
    PROCESS_BEGIN();
	//��ʱ1s��ʱ��
	etimer_set(&et,CLOCK_SECOND/2);
	while(1)
	{
		//�ȴ�1s
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));	
	    //����led
		spin_set_gpio_bit_value(GPIO2,3,0);
		//�ȴ�1s
		etimer_restart(&et);
    	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
		//�ر�led
		spin_set_gpio_bit_value(GPIO2,3,1);
		etimer_restart(&et);
	}
   PROCESS_END();
}
PROCESS(led4,"led4");//����led��ת����
PROCESS_THREAD(led4, ev, dataa)
{
	static struct etimer et;
    PROCESS_BEGIN();
	//��ʱ1s��ʱ��
	etimer_set(&et,CLOCK_SECOND/2);
	while(1)
	{
		//�ȴ�1s
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));	
	    //����led
		spin_set_gpio_bit_value(GPIO2,4,0);
		//�ȴ�1s
		etimer_restart(&et);
    	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
		//�ر�led
		spin_set_gpio_bit_value(GPIO2,4,1);
		etimer_restart(&et);
	}
   PROCESS_END();
}
PROCESS(dog,"dog");//����led��ת����
PROCESS_THREAD(dog, ev, dataa)
{
	static struct etimer et;
    PROCESS_BEGIN();
	//��ʱ1s��ʱ��
	etimer_set(&et,CLOCK_SECOND*2);
	while(1)
	{
		//�ȴ�1s
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));	
	    spin_watchdog_clear();//ι��
		etimer_restart(&et);
	}
   PROCESS_END();
}
int
main(void)
{
  hardware_init();
  clock_init();
  rtimer_init();
  process_init();
 /* start services */
  process_start(&etimer_process, NULL);
  process_start(&dog, NULL);
  process_start(&led, NULL);
  process_start(&led1, NULL);
  process_start(&led2, NULL);
  process_start(&led3, NULL);
  process_start(&led4, NULL);
  for(;;)process_run();
  return 0;
}
