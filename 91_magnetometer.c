#include <18f67j94.h>
//#fuses HS, NOWDT, NOBROWNOUT, NOPUT // FOR PIC16F877A
#include <math.h> 
//#include <PIC16F1787_REG.h>
#fuses NOWDT  // FOR pic18F
#use delay(crystal=16Mhz,clock=16Mhz)
//#use delay(crystal=20Mhz)

#use rs232(baud=9600, parity=N, bits=8,xmit=pin_b6,rcv=pin_b7, stream=port)
//#use rs232(baud=9600,parity=N,xmit=pin_b0,rcv=pin_b1,bits=8,stream=XX)
//#use rs232(baud=9600,parity=N,xmit=pin_d7,rcv=pin_d6,bits=8,stream=XX)
#use i2c(Master,Slow=200000,sda=pin_c4,scl=pin_c3)
 
#define x_low    0x00
#define x_high   0x01
#define temp     0x06
#define id       0x2f
#define write    0b01100000
#define read     0b01100001
int8 chi_id();
void read_data_SET();
void read_data_RESET();
unsigned int8 Lx,Ly,Lz,Hx,Hy,Hz,    rLx,rLy,rLz,rHx,rHy,rHz;

double df,dg,dk,rf,rg,rk;
double X,Y,Z,Zpre;

void main()
{ 

//TRISD2=0;  

   
 
   while(true)
   {
    //printf("Hello");
    //RD2=1;
    delay_ms(300);
    
    //RD2=0;
    
    read_data_SET(); 
    DELAY_MS(100);
    read_data_reSET();
    
    df = make16(Hx,Lx)-32768;
    dg = make16(Hy,Ly)-32768;
    dk = make16(Hz,Lz)-32768;
    
    rf = make16(rHx,rLx)-32768;
    rg = make16(rHy,rLy)-32768;
    rk = make16(rHz,rLz)-32768;
    
    X = (-rf+df)*0.244/2;
    Y = (-rg+dg)*0.244/2;
    Z = (-rk+dk)*0.244/2;
    
    if(X > 600)
    {
      X = X + 600;
    }else if(X < -600)
    {
      X = X - 600;
    }
    
    if(Y > 600)
    {
      Y = Y + 600;
    }else if(Y < -600)
    {
      Y = Y - 600;
    }
    
    if(Z > 600)
    {
      Z = Z + 600;
    }else if(Z < -600)
    {
      Z = Z - 600;
    }
    
    if(Z-Zpre<100&&Z-Zpre>-100)
    {
//!    printf("x=%03f\r\n", (-rf+df)*0.244/2); 
//!    printf("y=%03f\r\n", (-rg+dg)*0.244/2);
//!    printf("z=%03f\r\n", (-rk+dk)*0.244/2);
    printf("%03f,%03f,%03f\r\n", X,Y,Z);
    delay_ms(500);
    }
    Zpre = Z;
   }
   
   
}



void read_data_SET()
{
    
    
    i2c_start();
    if(i2c_write(0b01100000)==0) //10
    {
       
       i2c_write(0x08);      // 2nd
       delay_ms(1);
    
       i2c_write(0b00001001);      // 3rd
       delay_ms(1);
    }
    
    i2c_start();
    if(i2c_write(0b01100000)==0) //10
    {
       
       i2c_write(0x0a);      // 2nd
       delay_ms(1);
    
       i2c_write(0b00000001);      // 3rd
       delay_ms(1);
    }

    
    //________________________________________________________________________    
    i2c_start();
    i2c_write(0b01100000);      // 8
    delay_ms(1);
    
    i2c_write(0x00);      // 9
    delay_ms(20);
    
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    i2c_start();
    if(i2c_write(0b01100001)==0) //10
    {
       Lx = i2c_read(0); 
   
    }
    
   i2c_start();
    if(i2c_write(0b01100001)==0) //10
    {
       
        Hx = i2c_read(0);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    i2c_start();
    if(i2c_write(0b01100001)==0) //10
    {
       Ly = i2c_read(0); 
   
    }
    
   i2c_start();
    if(i2c_write(0b01100001)==0) //10
    {
       
        Hy = i2c_read(0);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    i2c_start();
    if(i2c_write(0b01100001)==0) //10
    {
       Lz = i2c_read(0); 
   
    }
    
   i2c_start();
    if(i2c_write(0b01100001)==0) //10
    {
       
        Hz = i2c_read(0);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    i2c_stop();
    //0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
    //0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

    
    
   
}

void read_data_RESET()
{
    
    i2c_start();
    if(i2c_write(0b01100000)==0) //10
    {
       
       i2c_write(0x08);      // 2nd                         control reg 0
       delay_ms(1);
    
       i2c_write(0b00010001);      // 3rd
       delay_ms(1);
    }
    delay_ms(2);
    
    i2c_start();
    if(i2c_write(0b01100000)==0) //10
    {
       
       i2c_write(0x0a);      // 2nd
       delay_ms(1);
    
       i2c_write(0b00000001);      // 3rd
       delay_ms(1);
    }
    
    //________________________________________________________________________    
    i2c_start();
    i2c_write(0b01100000);      // 8
    delay_ms(1);
    
    i2c_write(0x00);      // 9
    delay_ms(6);
    
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    i2c_start();
    if(i2c_write(0b01100001)==0) //10
    {
       rLx = i2c_read(0); 
   
    }
    
   i2c_start();
    if(i2c_write(0b01100001)==0) //10
    {
       
        rHx = i2c_read(0);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    i2c_start();
    if(i2c_write(0b01100001)==0) //10
    {
       rLy = i2c_read(0); 
   
    }
    
   i2c_start();
    if(i2c_write(0b01100001)==0) //10
    {
       
        rHy = i2c_read(0);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    i2c_start();
    if(i2c_write(0b01100001)==0) //10
    {
       rLz = i2c_read(0); 
   
    }
    
   i2c_start();
    if(i2c_write(0b01100001)==0) //10
    {
       
        rHz = i2c_read(0);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    i2c_stop();
    //0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
    //0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

    
    
   
}
int8 chi_id()
{   
     
    
    
    i2c_start();
    i2c_write(0b01100000);
    delay_ms(1);
    i2c_write(0x2f);
    delay_ms(1);
    
    i2c_start(); 
    i2c_write(0b01100001);
    delay_ms(1);
    
    // = i2c_read(0);
    
    
    i2c_stop();
    
    //return k;
    
}
