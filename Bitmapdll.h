

#ifndef BITMAPDLL_H
#define BITMAPDLL_H

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include <gdiplus.h>

using namespace Gdiplus;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* 
    
    typedef void (__stdcall *_Bitmap_Init )( HWND pProgramWindowHandle, int nBufferWidth, int nBufferHeight );
    typedef void (__stdcall *_Bitmap_LoadBitMapFile )(  int Index, char *FileName, int Width, int Height );
    typedef void (__stdcall *_Bitmap_LoadBitMapFileScaled )( int Index, char *FileName, int Width, int Height, 
     float fScaleX, float fScaleY );
    typedef void (__stdcall *_Bitmap_InitFont )( int nHeight, char FontFace[] );
    typedef void (__stdcall *_Bitmap_SetTextForeColor )( int r, int g, int b );
    typedef void (__stdcall *_Bitmap_SetTextBackColor )( int r, int g, int b );
    typedef void (__stdcall *_Bitmap_DrawCell )( int PicIndex, int X, int Y );
    typedef void (__stdcall *_Bitmap_DrawCellStretch )( int PicIndex, int DestX, int DestY, int SrcX, int SrcY, int DestWidth, int DestHeight, 
    int SrcWidth, int SrcHeight );	   
    typedef void (__stdcall *_Bitmap_DrawText )( char *Text, int X, int Y );
    typedef void (__stdcall *_Bitmap_DrawTextList )( char **TextList, int *X, int *Y, int Count );
    typedef void (__stdcall *_Bitmap_Buffer2Window )( HDC DestDC );
    typedef void (__stdcall *_Bitmap_ClearBuffer )();
    typedef void (__stdcall *_Bitmap_SetOption )( char *OptionStr );
    
    typedef void (__stdcall *_Bitmap_InitPen )( int nPenListIndex, int width, Color rgb );
    typedef void (__stdcall *_Bitmap_InitBrush )( int nBrushListIndex,  Color rgb );    
	typedef void (__stdcall *_Bitmap_DrawEllipse )( int nPenListIndex, int x, int y, int width, int height );   
	typedef void (__stdcall *_Bitmap_DrawLine )( int nPenListIndex, int x1, int y1, int x2, int y2 );
	typedef void (__stdcall *_Bitmap_DrawLines )( int nPenListIndex, Point *PointList, int pointcount );
	typedef void (__stdcall *_Bitmap_DrawPolygon )( int nPenListIndex, Point *PointList, int pointcount );
	typedef void (__stdcall *_Bitmap_DrawRectangle )( int nPenListIndex, int x, int y, int width, int height );
    typedef void (__stdcall *_Bitmap_FillRectangle  )( int nBrushListIndex, int x, int y, int width, int height );

    typedef void (__stdcall *_Bitmap_LoadImageGDI)( int index, char *filename );
    typedef void (__stdcall *_Bitmap_DrawImageGDI)( int index, int destx, int desty, int destwidth, int destheight, 
           int srcx, int srcy, int srcwidth, int srcheight );

    typedef void (__stdcall *_Bitmap_InitFontGDI)( char *fontname, int fontsize, Color rgb, int brushindex );
    typedef void (__stdcall *_Bitmap_DrawTextGDI)( char *text, int x, int y, int brushindex );
    

    typedef bool (__stdcall *_Sound_Init)( HWND hwnd );
    typedef int (__stdcall *_Sound_LoadWaveFile)( int index, char *filename );
    typedef void (__stdcall *_Sound_PlayWaveFile)( int index );
    typedef void (__stdcall *_Sound_ShutDown)();    
           

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*                   
class Bitmap_Dll_Loader
{    
    static HINSTANCE Dll_Instance;
    static HWND HandleWindow;
    
public:
        
    static _Bitmap_Init Bitmap_Init;
    static _Bitmap_LoadBitMapFile Bitmap_LoadBitMapFile ;
    static _Bitmap_LoadBitMapFileScaled Bitmap_LoadBitMapFileScaled ;
    static _Bitmap_InitFont Bitmap_InitFont ;
    static _Bitmap_SetTextForeColor Bitmap_SetTextForeColor;
    static _Bitmap_SetTextBackColor Bitmap_SetTextBackColor ;
    static _Bitmap_DrawCell Bitmap_DrawCell ;
    static _Bitmap_DrawCellStretch Bitmap_DrawCellStretch ;
    static _Bitmap_DrawText Bitmap_DrawText ;
    static _Bitmap_DrawTextList Bitmap_DrawTextList ;
    static _Bitmap_Buffer2Window Bitmap_Buffer2Window ;
    static _Bitmap_ClearBuffer Bitmap_ClearBuffer; 
    static _Bitmap_SetOption Bitmap_SetOption; 
    
    static _Bitmap_InitPen Bitmap_InitPen;
    static _Bitmap_InitBrush Bitmap_InitBrush;
	static _Bitmap_DrawEllipse Bitmap_DrawEllipse;
	static _Bitmap_DrawLine Bitmap_DrawLine;
	static _Bitmap_DrawLines Bitmap_DrawLines;
	static _Bitmap_DrawPolygon Bitmap_DrawPolygon; 
	static _Bitmap_DrawRectangle Bitmap_DrawRectangle;
    static _Bitmap_FillRectangle Bitmap_FillRectangle;  
	static _Bitmap_LoadImageGDI Bitmap_LoadImageGDI;
    static _Bitmap_DrawImageGDI Bitmap_DrawImageGDI;
    static _Bitmap_DrawTextGDI Bitmap_DrawTextGDI;
    static _Bitmap_InitFontGDI Bitmap_InitFontGDI;
    
    static _Sound_Init Sound_Init;
    static _Sound_LoadWaveFile Sound_LoadWaveFile;
    static _Sound_PlayWaveFile Sound_PlayWaveFile;
    static _Sound_ShutDown Sound_ShutDown;   
    
   Bitmap_Dll_Loader();
   static void Init( HWND hwnd );
   static void FunctionLoad();
   static int FunctionCheck();
   static bool Unload();

};


//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

#endif

