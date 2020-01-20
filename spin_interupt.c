#include"spin_interupt.h"
#include"spin_gpio.h"
uint inter_vector_function[inter_num]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};	//�����û���ʼ��
mutex_t it0,it1,it2,it3,it4,it5,it6,it7;
//code uchar* inter_src_list[inter_num]={0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xC2,0xC6};
//code uchar* inter_prority[inter_num]={0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xC3,0xC7};
 //�����ź��������û��жϻص�ע��Ϊtask�����������ź�����taskִ��
void spin_interupt_init(){
  it0=it1=it2=it3=it4=it5=it6=it7=0;
}
void spin_interupt_enable(){
	   EA=1;
}
void spin_interupt_disable(){
	   EA=0;
}
void spin_interupt_open(INTER_LIST num,INTER_PRORITY prority){
     if(out_int2 ==num){
		EX2=1;
		PX2=prority;
		}
	 else if(out_int3 == num) {
	 	EX3=1;
		PX3=prority;
		}
	 else {
		IE |= 0x01<<num;
		IP |= prority<<num;
		}
}
void spin_interupt_close(INTER_LIST num){
	if(out_int2 ==num)
		EX2=0;
	 else if(out_int3 == num)
	 	EX3=0;
	 else
	 	IE &= (~(0x01<<num));
}
//void intersvr0() interrupt 0{
//	   spin_set_gpio_bit_value(GPIO2,0,0);
//	   if(inter_vector_function[0]!=NULL)
//	   		mutex_unlock(it0);
//}
//static DATA uchar counter = 0; //ÿ��timer0�����250us��4�β���1ms
//void intersvr1(void) interrupt 1{
//		counter++;
//		if(counter==4){
//			counter = 0;
//			if(inter_vector_function[1]!=NULL){
//	   			mutex_unlock(it1);
//				spin_set_gpio_bit_value(GPIO2,1,0);
//				((interupt_callback)inter_vector_function[1])(); //ִ���������
//			}
//		}
//}

void intersvr2(void) interrupt 2{
//		spin_set_gpio_bit_value(GPIO2,2,0);
		if(inter_vector_function[2]!=NULL)
	  		 mutex_unlock(it2);
}
//void intersvr3(void) interrupt 3{
//		spin_set_gpio_bit_value(GPIO2,3,0);
//		if(inter_vector_function[3]!=NULL)
//	   		mutex_unlock(it3);
//}
//tim2�ж�
void intersvr5(void) interrupt 5{
//	spin_set_gpio_bit_value(GPIO2,5,0);
	if(inter_vector_function[5]!=NULL)
	   		mutex_unlock(it5);
}
//ext2�ж�
void intersvr6(void) interrupt 6{
//	spin_set_gpio_bit_value(GPIO2,6,0);
	if(inter_vector_function[6]!=NULL)
	   		mutex_unlock(it6);
}
//ext3�ж�
void intersvr7(void) interrupt 7{
//	spin_set_gpio_bit_value(GPIO2,7,0);
	if(inter_vector_function[7]!=NULL)
	   		mutex_unlock(it7);
}
