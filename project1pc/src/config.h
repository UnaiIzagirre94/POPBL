#ifndef CONFIG_H_
#define CONFIG_H_

#define ZYNQ_7000
#define MAX_ARRAY 100
#define TIMERS
#define FALSE 0
#define TRUE 1
#define STANDING   1
#define SITTING  2
#define SITTINGWRONG 3
#define MOVINGFAST 4
#define NULL 0
#define MAXIMUM_ARRAY 250
#define MAXIMUM_CHARAC 40
typedef unsigned char BOOLEAN;


typedef struct {
	int hour;
	int min;
	int seg;
} T_TIME;


#endif /* CONFIG_H_ */
