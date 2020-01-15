#include"spin_uart.h"
#include"spin_timer.h"
#include"spin_interupt.h"
#include"spin_gpio.h"
#include<reg52.h>

//static const uint boaud_rate=2400;
//static const uint over_time_us=13;//ÿover_time_us����ʱ��1���1��

uint spin_uart_init(){
	//SCON=0xF0;//��ʽ3�����ͨѶ���������
    //SCON = 0x50;		//8λ����,�ɱ䲨����
    SCON=0xD0;//��ʽ3,������� ֹͣλ1.5λ
    PCON|=0x80;//52��Ƭ��֧�֡�ʹ�ܺ󣬴���ʵ�ʲ����ʼӱ�
	AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	uart_boaud(13);
   spin_interupt_open(serial,high);	//�������ж�
   return 4800;
}
IDATA volatile struct{
	  uchar twi,tri,tcnt;
	  uchar rwi,rri,rcnt;
	  uchar tbuf[SEBULEN];
	  uchar rbuf[REBULEN];
}fifo;

 //������
uchar u_getc(){
   	uchar d;
	uchar i;

	/* Wait while rx fifo is empty */
	while (!fifo.rcnt);

	i = fifo.rri;			/* Get a byte from rx fifo */
	d = fifo.rbuf[i];
	fifo.rri = ++i % REBULEN;
	fifo.rcnt--;
	return d;
}
//���һ�㲻������
void u_putc(uchar c){
   	uchar i;
	/* Wait for tx fifo is not full */
	while (fifo.tcnt >= SEBULEN) ;

	i = fifo.twi;		/* Put a byte into Tx fifo */
	fifo.tbuf[i] = c;
	fifo.twi = ++i % SEBULEN;
	fifo.tcnt++;
	TI=1;//ʹ�ܷ����ж�
}

void intersvr4(void) interrupt 4{
    uchar i;
	uchar d;
    if(RI==1){ //�����ж�
		RI=0;
		d = SBUF;
		i = fifo.rcnt;
		if (i < REBULEN) {	/* Store it into the rx fifo if not full */
		fifo.rcnt = ++i;
		i = fifo.rwi;
		fifo.rbuf[i] = d;
		fifo.rwi = ++i % REBULEN;
		}
	}
	if(TI==1){//�����ж�
		i = fifo.tcnt;
		if (i--) {	/* There is any data in the tx fifo */
			fifo.tcnt = i;
			i = fifo.tri;
			SBUF = fifo.tbuf[i];
			fifo.tri = ++i % SEBULEN;
		} else {	/* No data in the tx fifo */
			TI=0;
		}
	}	
}