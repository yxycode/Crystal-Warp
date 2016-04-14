/* Creation of a simple Windows API program */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include  <mmsystem.h>
#include "bitmapdll.h"
#include "Game.h"
//#include "sounds.h"

//================================================================================================================
//_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-
//================================================================================================================

const int STRING_LENGTH = 1000;

//================================================================================================================
float Distance( float X1, float Y1, float X2, float Y2 )
{
    return sqrt( (X1 - X2) * (X1 - X2) +  (Y1 - Y2) * (Y1 - Y2));
}
//================================================================================================================
void CenterWindow( HWND hwnd )
{
  RECT rc;
  int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
  int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
  GetWindowRect(hwnd, &rc);

  int WindowWidth = (rc.right - rc.left);
  int WindowHeight = (rc.bottom - rc.top);

  SetWindowPos(hwnd, 0, ScreenWidth/2 - WindowWidth/2,
    ScreenHeight/2 - WindowHeight/2, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
}
//================================================================================================================
//_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-_*-*_*-
//================================================================================================================

unsigned int TIMER_ID = 1;
static int pos_x = 0, pos_y = 0;

World TheWorld;

HDC TheWindowDC;

Bitmap_Dll_Loader *Bitmap_Dll;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "Crystal Warp";

#define VK_F1             0x70
#define VK_F2             0x71
#define VK_F3             0x72
#define VK_F4             0x73
#define VK_F5             0x74
#define VK_F6             0x75
#define VK_F7             0x76
#define VK_F8             0x77
#define VK_F9             0x78
#define VK_F10            0x79
#define VK_F11            0x7A
#define VK_F12            0x7B

//------------------------------------------------------------------------------------------------------------

  // *** these 3 variables must be outside WinMain() to prevent "segmentation fault"
  HWND hwnd;               /* This is the handle for our window */
  MSG messages;            /* Here messages to the application are saved */
  WNDCLASSEX wincl;        /* Data structure for the windowclass */

  //SoundBox sbx;

//------------------------------------------------------------------------------------------------------------   
	    
int WINAPI
WinMain (HINSTANCE hThisInstance,
         HINSTANCE hPrevInstance,
         LPSTR lpszArgument,
         int nFunsterStil)

{    
    //HWND hwnd;               /* This is the handle for our window */
    //MSG messages;            /* Here messages to the application are saved */
    //WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
/*
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
*/
/*
    wincl.hIcon = (HICON)LoadImage(NULL, "servers.ico",IMAGE_ICON,32,32,LR_LOADFROMFILE); 
    wincl.hIconSm = (HICON)LoadImage(NULL, "servers.ico",IMAGE_ICON,32,32,LR_LOADFROMFILE); 
*/

    wincl.hIcon = (HICON)LoadImage(GetModuleHandle(NULL), "IDI_ICON1",IMAGE_ICON,32,32,0); 
    wincl.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), "IDI_ICON1",IMAGE_ICON,32,32,0); 

    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
  
    HBRUSH BackgroundColor;

    BackgroundColor = (HBRUSH) COLOR_BACKGROUND;
    BackgroundColor = CreateSolidBrush(RGB(100, 100, 100));
    
    wincl.hbrBackground = BackgroundColor;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "*** Crystal Warp ***",       /* Title Text */
           WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU /*| WS_THICKFRAME*/ | WS_MINIMIZEBOX /*| WS_MAXIMIZEBOX*/, /* no resizing */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           800,                  /* The programs width */
           600,                  /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    //MessageBox( hwnd, lpszArgument, "Commandline Arguments", MB_ICONHAND );
    
    CenterWindow(hwnd);
    /* Make the window visible on the screen */
    ShowWindow (hwnd, nFunsterStil);
    
    TheWindowDC = GetDC(hwnd);
    //hDC=CreateCompatibleDC(NULL);
    
    SetBkMode(TheWindowDC, TRANSPARENT);
    
    // Derive a region from that path
    SelectClipPath(TheWindowDC, RGN_AND);


    srand(time(NULL));
      
    Bitmap_Dll = new Bitmap_Dll_Loader();
    Bitmap_Dll_Loader::Init(hwnd);
    Bitmap_Dll_Loader::Bitmap_Init( hwnd, 800, 600 );
   
    Bitmap_Dll_Loader::Bitmap_InitPen( 0, 1, Color(255,0,0) );
    Bitmap_Dll_Loader::Bitmap_InitPen( 1, 2, Color(150,150,150));
    Bitmap_Dll_Loader::Bitmap_InitPen( 2, 3, Color(0,0,255) );     
    Bitmap_Dll_Loader::Bitmap_InitPen( 3, 4, Color(200,200,255) );  
    Bitmap_Dll_Loader::Bitmap_InitPen( 4, 1, Color(255,255,0) );  
    
    Bitmap_Dll_Loader::Bitmap_InitBrush( 0, Color(0,255,0) ); 
/*           
    Bitmap_Dll_Loader::Bitmap_InitPen( 3, 4, Color(255,255,0) );    
    Bitmap_Dll_Loader::Bitmap_InitBrush( 0, Color(255,0,255) );
    Bitmap_Dll_Loader::Bitmap_LoadBitMapFile( 0, "star.bmp", 128, 128 );
    Bitmap_Dll_Loader::Bitmap_LoadImageGDI( 0, "star.png" );
*/  
   	Bitmap_Dll_Loader::Bitmap_InitFontGDI( "Arial Black", 12, Color(0,150,0), 0 );   	 	 
/*       	
    Bitmap_Dll_Loader::Bitmap_InitFontGDI( NULL, 0, Color(255,0,0), 1 );   
    Bitmap_Dll_Loader::Bitmap_InitFontGDI( NULL, 0, Color(0,255,0), 2 );   
	Bitmap_Dll_Loader::Bitmap_InitFontGDI( NULL, 0, Color(0,0,255), 3 );  
	Bitmap_Dll_Loader::Bitmap_InitFontGDI( NULL, 0, Color(0,255,255), 4 ); 
*/	
    GameObject::ItsWorld = &TheWorld;
    Nasty::Init();
    StaticObject::Init();
    ScoreBar *sb = new ScoreBar();
	TheWorld.Init(1);    	
	TheWorld.Add(sb);
    
    
/*    
    sbx.LoadSound( 0, "warp.wav" );
    sbx.LoadSound( 1, "death.wav" );
*/    
    Bitmap_Dll_Loader::Sound_Init(hwnd);
    Bitmap_Dll_Loader::Sound_LoadWaveFile( 0, "projectile.wav" );
    Bitmap_Dll_Loader::Sound_LoadWaveFile( 1, "breakup.wav" );
    Bitmap_Dll_Loader::Sound_LoadWaveFile( 2, "warp.wav" );
    Bitmap_Dll_Loader::Sound_LoadWaveFile( 3, "death.wav" );

/*
    if(joySetCapture(hwnd, JOYSTICKID1, 10, true)) 
    {     
        MessageBeep(MB_ICONEXCLAMATION); 
        MessageBox(hwnd, "Couldn't capture the joystick.", NULL, 
            MB_OK | MB_ICONEXCLAMATION);            
    }     
*/      
    
    SetTimer( hwnd, TIMER_ID, (UINT)50, (TIMERPROC)NULL);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);        
    }

    KillTimer(hwnd, TIMER_ID);
    Bitmap_Dll_Loader::Unload();
    MessageBox(hwnd,  "Program closing!", "Message" ,MB_OK | MB_ICONINFORMATION);    
    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

//------------------------------------------------------------------------------------------------------------
/*          
	 Point xylist[] = {{100, 10}, {110, 20}, {130, 20}, {140, 50}, {150, 60}, {170, 100} };       
     Point xylist2[] = {{100, 100}, {200, 130}, {150, 200}, {50, 200}, {0,130} };    
*/
char dummystr[200];
	           	           
LRESULT CALLBACK
WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT   Ps;
    HDC          hDC;
    HBRUSH  NewBrush;
    char tempstr[STRING_LENGTH];      
	          
    switch (message)                  /* handle the messages */
    {
       
/*  
        case MM_JOY1BUTTONDOWN:
             sprintf(dummystr, "D [%d] [%d, %d]", wParam, LOWORD(lParam), HIWORD(lParam) );
             break;
        case MM_JOY1BUTTONUP:       
              sprintf(dummystr, "U [%d] [%d, %d]", wParam, LOWORD(lParam), HIWORD(lParam) );
              break;
        case MM_JOY1MOVE:        	
            sprintf(dummystr, "M [%d] [%d, %d]", wParam, LOWORD(lParam), HIWORD(lParam) );
            break;
        case MM_JOY1ZMOVE:
            sprintf(dummystr, "Z [%d] [%d, %d]", wParam, LOWORD(lParam), HIWORD(lParam) );
             break;                         
*/                                                                   
        case WM_KEYUP:
           TheWorld.InputKey(0, wParam);           
           //RedrawWindow(hwnd, NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
           break;         
        case WM_KEYDOWN:

          TheWorld.InputKey(1, wParam);
       
         switch( wParam )
          {
           case VK_UP:          
               break;
           case VK_DOWN:
               break;
           case VK_LEFT:   
               break;
           case VK_RIGHT:     
               break;
           case 'G':
/*               
               sbx.PlaySound( 0 );
               sbx.PlaySound( 1 );
*/               
               break;
           case 'I':
               break;
           case 'O':
               break;
           case 'C':
               break;
           case 'D':
               break;
           case 'E':
               break;
           case 'Z':
               break;
           case 'U':
               break;
           case 'F':               
               break;
           case 'B':
               break;              
           case 'A':
               break;  
           case '1':
               break;
           case '2':
               break;
           case '0':
               exit(0);
               break;   
           default:
           	   break;
         }
         
             break;
//------------------------------------------------------------------------------------------------------------             
        case WM_DESTROY:        	                       
             PostQuitMessage (0);       /* send a WM_QUIT to the message queue */               
             break;
             
        case WM_TIMER:
                           
           if( wParam == TIMER_ID )    
           {  
               TheWorld.Do();
               pos_x++; pos_y++;                
	           RedrawWindow(hwnd, NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);                              	           
	       }
             break;         
//------------------------------------------------------------------------------------------------------------
        case WM_PAINT:
          
           //TextOut( TheWindowDC, 0, 0, "TESTING!", strlen("TESTING!"));

           hDC = BeginPaint(hwnd, &Ps);
/*           
           Bitmap_Dll_Loader::Bitmap_DrawText( "jsdklfjskljfdfsZ", pos_x, pos_y );
       
   Bitmap_Dll_Loader::Bitmap_DrawCellStretch( 0, 100, 100, 0, 0, 64, 64,  64, 64 );	   
   Bitmap_Dll_Loader::Bitmap_DrawCellStretch( 0, 200, 100, 64, 0, 64, 150,  64, 64 );	   
   Bitmap_Dll_Loader::Bitmap_DrawCellStretch( 0, 300, 100, 0, 64, 150, 64,  64, 64 );	   
   Bitmap_Dll_Loader::Bitmap_DrawCellStretch( 0, 400, 100, 64, 64, 150, 150,  64, 64 );
    //Bitmap_Dll_Loader::Bitmap_DrawCell( 0, 0, 0 );	        

           Bitmap_Dll_Loader::Bitmap_DrawLines( 3, xylist, 6 );
	       Bitmap_Dll_Loader::Bitmap_DrawLine( 0, 1,1, 800, 600 );
	       Bitmap_Dll_Loader::Bitmap_DrawLine( 1, 1,600, 800, 0 );
	      	       
	       Bitmap_Dll_Loader::Bitmap_DrawRectangle( 0, 100, 100,150, 200 );
	       Bitmap_Dll_Loader::Bitmap_FillRectangle( 0, 200, 100,150, 50 );	        
	       Bitmap_Dll_Loader::Bitmap_DrawEllipse( 2, 100, 100,50, 100 );	      
		  
		   Bitmap_Dll_Loader::Bitmap_DrawPolygon( 1, xylist2, 5 ); 	  

           Bitmap_Dll_Loader::Bitmap_DrawImageGDI( 0, 300, 320, 200, 300, 
           64, 64, 64, 64 ); 
    
Bitmap_Dll_Loader::Bitmap_DrawTextGDI( "helfasdlaf310301249 3=1493  3", 200, 10, 0 );
Bitmap_Dll_Loader::Bitmap_DrawTextGDI( "helfasdlaf310301249 3=1493  3", 200, 30, 1 );	        
Bitmap_Dll_Loader::Bitmap_DrawTextGDI( "helfasdlaf310301249 3=1493  3", 200, 50, 2 );
Bitmap_Dll_Loader::Bitmap_DrawTextGDI( "helfasdlaf310301249 3=1493  3", 200, 70, 3 );
Bitmap_Dll_Loader::Bitmap_DrawTextGDI( "helfasdlaf310301249 3=1493  3", 200, 90, 4 ); 
*/
           TheWorld.Draw();
           //Bitmap_Dll_Loader::Bitmap_DrawTextGDI( dummystr, 10, 400, 0 ); 
           Bitmap_Dll_Loader::Bitmap_Buffer2Window(hDC);
           Bitmap_Dll_Loader::Bitmap_ClearBuffer(); 
/*
           //SelectObject(hDC, NewBrush);
           SelectObject(hDC, CustomFont);
           
           sprintf( TempStr1, "%d", hDC );
        
           SetTextColor(hDC, RGB( rand() % 255, rand() % 255, rand() % 255));
           SetBkColor(hDC, RGB( rand() % 255, rand() % 255, rand() % 255));
           TextOut(hDC, 0, 0, TempStr1, strlen(TempStr1));
           TextOut(hDC, 0, 16, TempStr2, strlen(TempStr2));
           TextOut(hDC, 0, 32, TempStr3, strlen(TempStr3));
           TextOut(hDC, 0, 48, TempStr4, strlen(TempStr4));
*/
             
           EndPaint(hwnd, &Ps);
                       
            break;
//------------------------------------------------------------------------------------------------------------                      
        case WM_CLOSE:        	
            KillTimer(hwnd, TIMER_ID);
            //Bitmap_Dll_Loader::Unload();        
            DestroyWindow(hwnd);   						   		    
			exit(0);                
            break;

        default:                      /* for messages that we don't deal with */  
                   
          return DefWindowProc (hwnd, message, wParam, lParam);
          break;
    }

    return 0;
}

//------------------------------------------------------------------------------------------------------------
