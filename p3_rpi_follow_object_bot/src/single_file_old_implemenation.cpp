#include <pigpiod_if2.h>
#include <iostream>
using namespace std;


// Pin Defination
const int PWM_LEFT =19;
const int MOTOR_LEFT_FW =6;
const int MOTOR_LEFT_BW =26;



int PigpioSetup()
{
    char *addrStr = NULL;
    char *portStr = NULL;
    int pi = pigpio_start(addrStr, portStr);

    // Pin Functionality
    set_mode(pi,PWM_LEFT,PI_OUTPUT);
    set_mode(pi,MOTOR_LEFT_FW,PI_OUTPUT);
    set_mode(pi,MOTOR_LEFT_BW,PI_OUTPUT);

    // Set Initialization
    gpio_write(pi,MOTOR_LEFT_FW,0);
    gpio_write(pi,MOTOR_LEFT_BW,0);
    return pi;
}

int main()
{
    int pi = PigpioSetup();
    if(pi<0){
        cout<<"Not Connected to Deamon"<<endl;
        return -1;
    }

    // Drive Forward
    cout<<"Drive Forward"<<endl;
    gpio_write(pi,MOTOR_LEFT_FW,1);
    set_PWM_dutycycle(pi,PWM_LEFT,150);
    time_sleep(3);


    // Stop
        cout<<"Stop"<<endl;

    gpio_write(pi,MOTOR_LEFT_FW,0);
    set_PWM_dutycycle(pi,PWM_LEFT,0);
    time_sleep(3);

    // Drive Backward
        cout<<"Drive backward"<<endl;

    gpio_write(pi,MOTOR_LEFT_BW,1);
    set_PWM_dutycycle(pi,PWM_LEFT,150);
    time_sleep(3);

    // Stop
        cout<<"Stop"<<endl;

    gpio_write(pi,MOTOR_LEFT_FW,0);
    set_PWM_dutycycle(pi,PWM_LEFT,0);
    time_sleep(3);

pigpio_stop(pi);
return 0;
}