#include"spin_userstart.h"

//�û������ı�־λ
void spin_set_F0(uchar value){
	F0 = !!value;//�����������1����
}
	   //rs1��rs0������ʹ�õļĴ�����
void spin_set_RS1(uchar value){
	 RS1  = !!value;
}
void spin_set_RS0(uchar value){
	 RS0  = !!value;
}
		   //range from 0~3
void spin_set_work_register_group(uchar index){
	 spin_set_RS0(index&0x01);
	 spin_set_RS1((index>>1)&0x01);
}
   //��λ��־λ
uchar spin_get_CY(){
	  return CY;
}
uchar spin_get_F0(){
	  return F0;
}
uchar spin_get_RS1(){
      return RS1;
}
uchar spin_get_RS0(){
	  return RS0;
}
//�����־λ
uchar spin_get_OV(){
      return OV;
}
void spin_set_sp(uchar addr){
	  SP=addr;
}
uchar spin_get_sp(){
 	return SP;
}


