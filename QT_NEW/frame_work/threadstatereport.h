#ifndef _TH003
#define _TH003

#define MAX_STATE	100
#define MAX_THREAD	100

//#define OUTPUT_RS_AS_SERIAL
//#define OUTPUT_AS_FILE
//#define OUTPUT_AS_THREAD

void setThreadState(char*);
void sendByFile(char*c);
void startScanThread();

#endif