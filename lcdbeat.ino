#include <LCDTFT.h>
#include <LCDTP.h>
#include "font.h"
#include "button.h"

#define backcolor 0xf800
//lcd的类对象为TFT
//LCD class object is TFT
TFTLCD TFT;
//字体的类对象为font
//Font class object is font
Font  font;
Font font1;
Font font2;
//触摸TP的类对象为tp
//Touchuscreem TP class object is tp
TP tp;
//声明两个按钮对象 Button1,Button2
//Two Button class object is  Button1,Button2
Button  Button1,Button2,Button3,Button4;
int value =1688; 
int erro=0;
int miss=0;
int cerro=0;
void setup() {
   //TFT初始化
  //TFT initialization
   TFT.begin();
   //lcd清屏  颜色为backcolor
   //LCD Clear the screen, backcolor
   TFT.clear(backcolor);
   
   //设置文本区域 左上角为(30，10)，右下角(320，200)，区域的颜色为红色，如果颜色为NULL或者为R0 G0 B0，即为黑色 也不刷新文本颜色 
   //Set the text area for the upper left corner (30, 10), the lower right corner (320,200), 
   //the color red, if the color is NULL or R0 G0 B0(black), is also not set text color 
  // font.set_txt(30,10,320,200,TFT.RGB_TO_565(255,0,0));
   
   //设置文本内字体的颜色
   //Set the text font color
 //  font.set_fontcolor(TFT.RGB_TO_565(0,0,255));
   //显示字符串
   //Displays a string

  // font.lcd_string("show int number + or -");
   
   //画第一个圆角按钮
   //Draw the first round button1
   Button1.drawButton(20,200,1,"A");
   //画第二个圆角按钮
   //Draw the second round button
#ifdef  H_SCREEM
   Button2.drawButton(250,200,0,"D");
#endif
#ifdef  H_SCREEM
   Button3.drawButton(100,200,1,"B");
#endif
#ifdef  H_SCREEM
   Button4.drawButton(180,200,0,"C");
#endif
   font.set_txt(150,120,220,135,TFT.RGB_TO_565(255,0,0));
   font.lcd_int(value);
    
   
}

void loop() {
  //检测触摸当前的状态
  //check Touch current state detection
    //TFT.draw_circle(x,y,r,TFT.RGB_TO_565(255,255,255));
    //x1=50 y1=20->y200 
    //x2=130
    //x3=210
    //x4=280
  //TFT.draw_circle(210,20,20,TFT.RGB_TO_565(255,255,255));
  int seed=random(9999);
  int seed1=seed%4;  
 // font.set_txt(150,120,220,135,TFT.RGB_TO_565(255,0,0));
 // font.lcd_int(seed1);

  font1.set_txt(150,120,220,135,TFT.RGB_TO_565(255,0,0));
  font1.lcd_int(erro);


  cerro=erro;
  delay (1000);
  print(seed1);
Stop:  
  if(erro>5)
        {TFT.clear(backcolor);
        font.lcd_string("You Lose");goto Stop;}
  tp.pen_down();
      
      if(tp.flag&&tp.y_val&&tp.x_val)
        { 
                //检测是否按下第一个按钮
         //Check whether pressing the first button
        if(Button1.istouch(tp.x,tp.y))
        {
          
          if (seed1!=0)
           if(erro-cerro<1)
              erro++;
          //触摸屏一直被按下 循环
          //Touch screen alway be pressed
           for(;tp.flag;)
           { 
             if (seed1!=0)
               if(erro-cerro<1)
                 erro++;;
          delay(50);
          
          
           tp.pen_down();
           }
           
         Button1.penup();
        }
        else if(Button2.istouch(tp.x,tp.y))
        {
          if (seed1!=3)
            if(erro-cerro<1)
           erro++;
           for(;tp.flag;)
            {
               if (seed1!=3)
                 if(erro-cerro<1)
           erro++;
              delay(50);
               tp.pen_down();
           }
           Button2.penup();
        }
        else if(Button3.istouch(tp.x,tp.y))
        {
           if (seed1!=1)
             if(erro-cerro<1)
           erro++;
          for(;tp.flag;)
            {
              if (seed1!=1)
                if(erro-cerro<1)
           erro++;
           delay(50);
               tp.pen_down();
           }
           Button3.penup(); 
        }
          else if(Button4.istouch(tp.x,tp.y))
        {
           if (seed1!=2)
            if(erro-cerro<1)
           erro++;
          for(;tp.flag;)
            {if (seed1!=2)
             if(erro-cerro<1)
           erro++;
           delay(50);          
               tp.pen_down();
           }
           Button4.penup(); 
        }}
       else erro++;
      
}
void print (int s)
{
  switch (s)
  {
    case 0:  
    for(int y=20;y<200;y=y+30)
       {TFT.draw_circle(50,y,20,TFT.RGB_TO_565(255,255,255));
       delay(100);
       TFT.draw_circle(50,y,20,TFT.RGB_TO_565(255,0,0));
       }
    break;
    case 1:
     for(int y=20;y<200;y=y+30)
       {TFT.draw_circle(130,y,20,TFT.RGB_TO_565(255,255,255));
       delay(100);
       TFT.draw_circle(130,y,20,TFT.RGB_TO_565(255,0,0));
       }
    break;
    case 2:
     for(int y=20;y<200;y=y+30)
       {TFT.draw_circle(210,y,20,TFT.RGB_TO_565(255,255,255));
       delay(100);
       TFT.draw_circle(210,y,20,TFT.RGB_TO_565(255,0,0));
       }
    break;
    case 3:
     for(int y=20;y<200;y=y+30)
       {TFT.draw_circle(280,y,20,TFT.RGB_TO_565(255,255,255));
       delay(100);
       TFT.draw_circle(280,y,20,TFT.RGB_TO_565(255,0,0));
       }
    break;
  }
  
}
void comobo()
{
   font.set_txt(50,10,240,200,backcolor);
   font.lcd_string("Comob");
   delay(200);
   font.lcd_string("");
}
