

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "bitmapdll.h"

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
Bitmap_Dll_Loader::Bitmap_Dll_Loader()
{
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Bitmap_Dll_Loader::Init( HWND hwnd )
{
	HandleWindow = hwnd;

    Dll_Instance = LoadLibrary(TEXT("bitmap")); 
   
    if( !Dll_Instance )
    { 
      MessageBox(hwnd, "Failed loading Bitmap.dll!" , "Error" ,MB_OK | MB_ICONINFORMATION);         
      return;
    }
      	
    FunctionLoad();

	if( FunctionCheck() == 0 )
	    MessageBox(hwnd,  "Dll loading failed!", "Error" ,MB_OK | MB_ICONINFORMATION);     
	          
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Bitmap_Dll_Loader::FunctionLoad()
{

    Bitmap_Init= (_Bitmap_Init ) GetProcAddress(Dll_Instance, "_Bitmap_Init@12" );
    Bitmap_LoadBitMapFile = ( _Bitmap_LoadBitMapFile ) GetProcAddress(Dll_Instance, "_Bitmap_LoadBitMapFile@16" );
    Bitmap_LoadBitMapFileScaled = (_Bitmap_LoadBitMapFileScaled ) GetProcAddress(Dll_Instance, "_Bitmap_LoadBitMapFileScaled@24" );
    Bitmap_InitFont = (_Bitmap_InitFont) GetProcAddress(Dll_Instance, "_Bitmap_InitFont@8" );
    Bitmap_SetTextForeColor = (_Bitmap_SetTextForeColor  ) GetProcAddress(Dll_Instance, "_Bitmap_SetTextForeColor@12" );
    Bitmap_SetTextBackColor  = (_Bitmap_SetTextBackColor ) GetProcAddress(Dll_Instance, "_Bitmap_SetTextBackColor@12" );
    Bitmap_DrawCell  = (_Bitmap_DrawCell ) GetProcAddress(Dll_Instance, "_Bitmap_DrawCell@12" );
    Bitmap_DrawCellStretch = (_Bitmap_DrawCellStretch ) GetProcAddress(Dll_Instance, "_Bitmap_DrawCellStretch@36" );
    Bitmap_DrawText  = (_Bitmap_DrawText ) GetProcAddress(Dll_Instance, "_Bitmap_DrawText@12" );
    Bitmap_DrawTextList  = (_Bitmap_DrawTextList ) GetProcAddress(Dll_Instance, "_Bitmap_DrawTextList@16" );
    Bitmap_Buffer2Window  = (_Bitmap_Buffer2Window ) GetProcAddress(Dll_Instance, "_Bitmap_Buffer2Window@4" );
    Bitmap_ClearBuffer = (_Bitmap_ClearBuffer ) GetProcAddress(Dll_Instance, "_Bitmap_ClearBuffer@0" ); 
    Bitmap_SetOption = (_Bitmap_SetOption ) GetProcAddress(Dll_Instance, "_Bitmap_SetOption@4" );
   
    Bitmap_InitPen = ( _Bitmap_InitPen) GetProcAddress(Dll_Instance, "_Bitmap_InitPen@12" );  
    Bitmap_InitBrush = ( _Bitmap_InitBrush) GetProcAddress(Dll_Instance, "_Bitmap_InitBrush@8" ); 
	Bitmap_DrawEllipse = ( _Bitmap_DrawEllipse) GetProcAddress(Dll_Instance, "_Bitmap_DrawEllipse@20" );
	Bitmap_DrawLine = ( _Bitmap_DrawLine) GetProcAddress(Dll_Instance, "_Bitmap_DrawLine@20" );
	Bitmap_DrawLines = ( _Bitmap_DrawLines) GetProcAddress(Dll_Instance, "_Bitmap_DrawLines@12" ); 
	Bitmap_DrawPolygon = ( _Bitmap_DrawPolygon) GetProcAddress(Dll_Instance, "_Bitmap_DrawPolygon@12" ); 
	Bitmap_DrawRectangle = ( _Bitmap_DrawRectangle) GetProcAddress(Dll_Instance, "_Bitmap_DrawRectangle@20" );
    Bitmap_FillRectangle = ( _Bitmap_FillRectangle) GetProcAddress(Dll_Instance, "_Bitmap_FillRectangle@20" ); 
    Bitmap_DrawImageGDI = (_Bitmap_DrawImageGDI) GetProcAddress(Dll_Instance, "_Bitmap_DrawImageGDI@36" );
    Bitmap_LoadImageGDI = (_Bitmap_LoadImageGDI) GetProcAddress(Dll_Instance, "_Bitmap_LoadImageGDI@8" );
    Bitmap_InitFontGDI = (_Bitmap_InitFontGDI)GetProcAddress(Dll_Instance, "_Bitmap_InitFontGDI@16" );  
    Bitmap_DrawTextGDI = (_Bitmap_DrawTextGDI)GetProcAddress(Dll_Instance, "_Bitmap_DrawTextGDI@16" );      
    
    Sound_Init = (_Sound_Init)GetProcAddress(Dll_Instance, "_Sound_Init@4" );
    Sound_LoadWaveFile = (_Sound_LoadWaveFile)GetProcAddress(Dll_Instance, "_Sound_LoadWaveFile@8" );
    Sound_PlayWaveFile = (_Sound_PlayWaveFile)GetProcAddress(Dll_Instance, "_Sound_PlayWaveFile@4" );
    Sound_ShutDown = (_Sound_ShutDown)GetProcAddress(Dll_Instance, "_Sound_ShutDown@0" );   
         
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
int Bitmap_Dll_Loader::FunctionCheck()
{
	
void *PtrList[] = 
{
    (void *)Bitmap_Init ,
    (void *)Bitmap_LoadBitMapFile ,
    (void *)Bitmap_LoadBitMapFileScaled ,
    (void *)Bitmap_InitFont,
    (void *)Bitmap_SetTextForeColor,
    (void *)Bitmap_SetTextBackColor ,
    (void *)Bitmap_DrawCell ,
    (void *)Bitmap_DrawCellStretch ,
    (void *)Bitmap_DrawText ,
    (void *)Bitmap_DrawTextList ,
    (void *)Bitmap_Buffer2Window ,
    (void *)Bitmap_ClearBuffer, 
    (void *)Bitmap_SetOption,
    
    (void *)Bitmap_InitPen,
    (void *)Bitmap_InitBrush,
	(void *)Bitmap_DrawEllipse,
	(void *)Bitmap_DrawLine,
	(void *)Bitmap_DrawLines,
	(void *)Bitmap_DrawPolygon,
	(void *)Bitmap_DrawRectangle,
    (void *)Bitmap_FillRectangle,  
	(void *)Bitmap_LoadImageGDI,
    (void *)Bitmap_DrawImageGDI,
	(void *)Bitmap_DrawTextGDI,   
	(void *)Bitmap_InitFontGDI,
	
    (void *)Sound_Init,
    (void *)Sound_LoadWaveFile,
    (void *)Sound_PlayWaveFile,
    (void *)Sound_ShutDown   	
};

int Count = sizeof(PtrList)/sizeof(void *);
int i, SuccessFlag = 1;

 for( i = 0; i < Count; i++ )
   if( PtrList[i] == NULL )
   {
        SuccessFlag = 0;
        break;
   }
   
 return SuccessFlag;

}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
bool Bitmap_Dll_Loader::Unload()
{
   // Free the DLL module.
 
   bool bFreeResult = FreeLibrary(Dll_Instance); 
   return bFreeResult;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
HINSTANCE Bitmap_Dll_Loader::Dll_Instance = NULL;
HWND Bitmap_Dll_Loader::HandleWindow = NULL;
  
_Bitmap_Init Bitmap_Dll_Loader::Bitmap_Init = NULL;
_Bitmap_LoadBitMapFile Bitmap_Dll_Loader::Bitmap_LoadBitMapFile = NULL;
_Bitmap_LoadBitMapFileScaled Bitmap_Dll_Loader::Bitmap_LoadBitMapFileScaled = NULL;
_Bitmap_InitFont Bitmap_Dll_Loader::Bitmap_InitFont = NULL;
_Bitmap_SetTextForeColor Bitmap_Dll_Loader::Bitmap_SetTextForeColor = NULL;
_Bitmap_SetTextBackColor Bitmap_Dll_Loader::Bitmap_SetTextBackColor = NULL;
_Bitmap_DrawCell Bitmap_Dll_Loader::Bitmap_DrawCell = NULL;
_Bitmap_DrawCellStretch Bitmap_Dll_Loader::Bitmap_DrawCellStretch = NULL;
_Bitmap_DrawText Bitmap_Dll_Loader::Bitmap_DrawText = NULL;
_Bitmap_DrawTextList Bitmap_Dll_Loader::Bitmap_DrawTextList = NULL;
_Bitmap_Buffer2Window Bitmap_Dll_Loader::Bitmap_Buffer2Window = NULL;
_Bitmap_ClearBuffer Bitmap_Dll_Loader::Bitmap_ClearBuffer = NULL;
_Bitmap_SetOption Bitmap_Dll_Loader::Bitmap_SetOption = NULL;    

_Bitmap_InitPen Bitmap_Dll_Loader::Bitmap_InitPen = NULL;
_Bitmap_InitBrush Bitmap_Dll_Loader::Bitmap_InitBrush = NULL;
_Bitmap_DrawEllipse Bitmap_Dll_Loader::Bitmap_DrawEllipse = NULL;
_Bitmap_DrawLine Bitmap_Dll_Loader::Bitmap_DrawLine = NULL;
_Bitmap_DrawLines Bitmap_Dll_Loader::Bitmap_DrawLines = NULL;
_Bitmap_DrawPolygon Bitmap_Dll_Loader::Bitmap_DrawPolygon = NULL;
_Bitmap_DrawRectangle Bitmap_Dll_Loader::Bitmap_DrawRectangle = NULL;
_Bitmap_FillRectangle Bitmap_Dll_Loader::Bitmap_FillRectangle  = NULL;
_Bitmap_LoadImageGDI Bitmap_Dll_Loader::Bitmap_LoadImageGDI = NULL;
_Bitmap_DrawImageGDI Bitmap_Dll_Loader::Bitmap_DrawImageGDI = NULL;
_Bitmap_DrawTextGDI Bitmap_Dll_Loader::Bitmap_DrawTextGDI = NULL;
_Bitmap_InitFontGDI Bitmap_Dll_Loader::Bitmap_InitFontGDI = NULL;

_Sound_Init Bitmap_Dll_Loader::Sound_Init = NULL;
_Sound_LoadWaveFile Bitmap_Dll_Loader::Sound_LoadWaveFile = NULL;
_Sound_PlayWaveFile Bitmap_Dll_Loader::Sound_PlayWaveFile = NULL;
_Sound_ShutDown Bitmap_Dll_Loader::Sound_ShutDown = NULL;
	  

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

