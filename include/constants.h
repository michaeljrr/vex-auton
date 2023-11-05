#ifndef _PROS_SENSORS_H_
#define _PROS_SENSORS_H_


#define lf_port 10
#define lt_port 6
#define lb_port 8
#define rf_port 20
#define rt_port 19
#define rb_port 18
#define imu_port 9


//flipper
#define fs_port 5
#define fr_port 4
#define flipperrot_port 15

//cata
#define lc_port 7
#define rc_port 17
#define catarot_port 12

//side rollers
#define lr_port 2
#define rr_port 11


#define DEFAULT_KP 0.17
#define DEFAULT_KI 0
#define DEFAULT_KD 5
#define DEFAULT_TURN_KP 0.29
#define DEFAULT_TURN_KI 0
#define DEFAULT_TURN_KD 10
#define KI_LIMIT 0
#define RAMPING_POW 1
#define DISTANCE_LEEWAY 15
#define MAX_POW 100

#endif