#ifndef PUB_TYPE_H
#define PUB_TYPE_H
typedef long LONG;
typedef wchar_t TCHAR;
typedef unsigned char       BYTE;
typedef wchar_t *LPCWSTR, *PCWSTR;
typedef void *PVOID;
#define WINAPI      __stdcall
#define LPVOID void*
typedef void *HANDLE;

#define WPARAM unsigned int 
#define LPARAM unsigned long

#define WINBASEAPI


//typedef void far *LPVOID;

typedef struct tagRECT
{
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;
} RECT;

typedef struct tagPOINT
{
    LONG  x;
    LONG  y;
} POINT, *PPOINT;
typedef unsigned long       DWORD;
DWORD GetTickCount();
typedef DWORD   COLORREF;
typedef int                 BOOL;
typedef unsigned long WORD;
#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))

typedef unsigned int        UINT;
#define CALLBACK    

typedef struct tagSIZE
{
    LONG        cx;
    LONG        cy;
} SIZE, *PSIZE, *LPSIZE;
typedef DWORD *LPDWORD;
typedef unsigned long ULONG_PTR, *PULONG_PTR;
typedef struct _OVERLAPPED {
    ULONG_PTR Internal;
    ULONG_PTR InternalHigh;
    union {
        struct {
            DWORD Offset;
            DWORD OffsetHigh;
        };

        PVOID Pointer;
    };

    HANDLE  hEvent;
} OVERLAPPED, *LPOVERLAPPED;

#define LPCTSTR TCHAR*
#define VOID void
#define LOWORD(l)           ((WORD)((DWORD_PTR)(l) & 0xffff))
#define HIWORD(l)           ((WORD)((DWORD_PTR)(l) >> 16))
#define WM_MOUSEFIRST                   0x0200
#define WM_MOUSEMOVE                    0x0200
#define WM_LBUTTONDOWN                  0x0201
#define WM_LBUTTONUP                    0x0202
#define WM_LBUTTONDBLCLK                0x0203
#define WM_RBUTTONDOWN                  0x0204
#define WM_RBUTTONUP                    0x0205
#define WM_RBUTTONDBLCLK                0x0206
#define WM_MBUTTONDOWN                  0x0207
#define WM_MBUTTONUP                    0x0208
#define WM_MBUTTONDBLCLK                0x0209

#define WM_NULL                         0x0000
#define WM_CREATE                       0x0001
#define WM_DESTROY                      0x0002
#define WM_MOVE                         0x0003
#define WM_SIZE                         0x0005
#define WM_USER                         0x0400


BOOL
WINAPI
PostMessageW(
    __in_opt HWND hWnd,
    __in UINT Msg,
    __in WPARAM wParam,
    __in LPARAM lParam);
#define PostMessage PostMessageW
#include <QThread>

Qt::HANDLE GetCurrentThreadId();
void Sleep(int x);

typedef DWORD (*funCall)(LPVOID lparam);

class CreateThread0 : public QThread
{


    virtual
    void run()  {
		funCall(0);
    }

	funCall funMe;
public:
	CreateThread0(funCall fun){
		funMe=fun;
	}
signals:
    void resultReady(const QString &s);
};
typedef unsigned char	UINT8 ;
typedef unsigned int	UINT32;
typedef unsigned __int64    UINT64;
typedef unsigned short UINT16;
#define LRESULT int
#define _T(x) x
typedef unsigned char byte;
typedef ULONG_PTR DWORD_PTR;
#define MAKEWORD(a, b)      ((WORD)(((BYTE)((DWORD_PTR)(a) & 0xff)) | ((WORD)((BYTE)((DWORD_PTR)(b) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)((DWORD_PTR)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD_PTR)(b) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)((DWORD_PTR)(l) & 0xffff))
#define HIWORD(l)           ((WORD)((DWORD_PTR)(l) >> 16))
#define LOBYTE(w)           ((BYTE)((DWORD_PTR)(w) & 0xff))
#define HIBYTE(w)           ((BYTE)((DWORD_PTR)(w) >> 8))
typedef __int64 LONGLONG;



#define GetRValue(rgb)      (LOBYTE(rgb))
#define GetGValue(rgb)      (LOBYTE(((WORD)(rgb)) >> 8))
#define GetBValue(rgb)      (LOBYTE((rgb)>>16))
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


#endif 