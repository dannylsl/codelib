#ifndef MOTORLIB_H
#define MOTORLIB_H

int init_motor();//return:0 success, -1 failure
void close_motor();
void set_motor_count(int count);
void set_motor_direction(int direction);//direction:1 turn left, 0 turn right
void set_motor_offline(int on_off);//on_off:1 online, 0 offline
void rotate_motor();

#endif // MOTORLIB_H
