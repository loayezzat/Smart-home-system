#ifndef TIMER0_PRIV_H_
#define TIMER0_PRIV_H_

/*** TIMER0 MODES ***/
#define TIMER0_NORMAL_MODE                                 0
#define TIMER0_CTC_MODE                                    1
#define TIMER0_FAST_PWM_MODE                               2
#define TIMER0_PHASE_CORRECT_PWM_MODE                      3

/*** OC0 MODES ***/
#define TIMER0_NON_PWM_DISCONNECT_OC0                      4
#define TIMER0_NON_PWM_TOGGLE_OC0                          5
#define TIMER0_NON_PWM_CLEAR_OC0                           6
#define TIMER0_NON_PWM_SET_OC0                             7

#define TIMER0_FAST_PWM_DISCONNECT_OC0                     8
#define TIMER0_FAST_PWM_SET_OC0_AT_TOP                     9
#define TIMER0_FAST_PWM_CLEAR_OC0_AT_TOP                  10

#define TIMER0_PHASE_CORRECT_PWM_DISCONNECT_OC0           11
#define TIMER0_PHASE_CORRECT_PWM_CLEAR_OC0_AT_UP_COUNT    12
#define TIMER0_PHASE_CORRECT_PWM_SET_OC0_AT_UP_COUNT      13

/*** CLOCK SELECT ***/
#define TIMER0_PRESCALER_1                                1U
#define TIMER0_PRESCALER_8                                8U
#define TIMER0_PRESCALER_64                               64U
#define TIMER0_PRESCALER_256                              256U
#define TIMER0_PRESCALER_1024                             1024U





#endif /* TIMER0_PRIV_H_ */
