#ifndef SOUNDS_H
#define SOUNDS_H

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

typedef struct wavFileHeader
{
    long chunkId;           //"RIFF" (0x52,0x49,0x46,0x46)
    long chunkSize;         // (fileSize - 8)  - could also be thought of as bytes of data in file following this field (bytesRemaining)
    long riffType;          // "WAVE" (0x57415645)
};
 
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
 
typedef struct fmtChunk
{
    long chunkId;                       // "fmt " - (0x666D7420)
    long chunkDataSize;                 // 16 + extra format bytes
    short compressionCode;              // 1 - 65535
    short numChannels;                  // 1 - 65535
    long sampleRate;                    // 1 - 0xFFFFFFFF
    long avgBytesPerSec;                // 1 - 0xFFFFFFFF
    short blockAlign;                   // 1 - 65535
    short significantBitsPerSample;     // 2 - 65535
    short extraFormatBytes;             // 0 - 65535
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* 

typedef struct wavChunk
{
    long chunkId;
    long chunkDataSize;
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

struct SoundData
{    
    char *filebuffer;
    long filesize;
    
    WAVEFORMATEX wf;
    WAVEHDR wh;
    HWAVEOUT hWaveOut;
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* 

char *readFileData(char *szFilename, long &dataLengthOut)
{
    FILE *fp = fopen(szFilename, "rb");
    long len;
    char *buffer;
    fseek(fp, 0, SEEK_END);
    len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    buffer = (char*) calloc(1, len+1);
    fread(buffer, 1, len, fp);
    fclose(fp);
    dataLengthOut = len;
    return buffer;
} 
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* 

int parseWav(char *data, SoundData &ItsSoundData )
{
    long *mPtr;
    void *tmpPtr;
 
    char *buffer;
 
    WAVEFORMATEX wf;
    WAVEHDR wh;
    HWAVEOUT hWaveOut;
 
    fmtChunk mFmtChunk;
    wavChunk mDataChunk;
     
    mPtr = (long*)data;
 
    int SuccessFlag = 0;
 
    if ( mPtr[0] == 0x46464952) //  little endian check for 'RIFF'
    {
        mPtr += 3;
        if (mPtr[0] == 0x20746D66)  // little endian for "fmt "
        {
           // printf("Format chunk found\n");

            tmpPtr = mPtr;
            memcpy(&mFmtChunk, tmpPtr, sizeof(mFmtChunk));
            tmpPtr += 8;
            tmpPtr += mFmtChunk.chunkDataSize;
 
            mPtr = (long*)tmpPtr;
            if (mPtr[0] == 0x61746164)        // little endian for "data"
            {
            //    printf("Data chunk found\n");

                tmpPtr = mPtr;
                memcpy(&mDataChunk, tmpPtr, sizeof(mDataChunk));
                mPtr += 2;
 
                buffer = (char*) malloc(mDataChunk.chunkDataSize);
                
                memcpy(buffer, mPtr, mDataChunk.chunkDataSize);
 
                //printf("sampleRate: %d\n", mFmtChunk.sampleRate);
 
                wf.wFormatTag = mFmtChunk.compressionCode;
                wf.nChannels = mFmtChunk.numChannels;
                wf.nSamplesPerSec = mFmtChunk.sampleRate;
                wf.nAvgBytesPerSec = mFmtChunk.avgBytesPerSec;
                wf.nBlockAlign = mFmtChunk.blockAlign;
                wf.wBitsPerSample = mFmtChunk.significantBitsPerSample;
                wf.cbSize = mFmtChunk.extraFormatBytes;
 
                wh.lpData = buffer;
                wh.dwBufferLength = mDataChunk.chunkDataSize;
                wh.dwFlags = 0;
                wh.dwLoops = 0;
 
                waveOutOpen(&hWaveOut,WAVE_MAPPER,&wf,0,0,CALLBACK_NULL);
                waveOutPrepareHeader(hWaveOut,&wh,sizeof(wh));
                
                ItsSoundData.wf = wf;
                ItsSoundData.wh = wh;
                ItsSoundData.hWaveOut = hWaveOut;
/*                
                waveOutWrite(hWaveOut,&wh,sizeof(wh));

                do {}
                while (!(wh.dwFlags & WHDR_DONE));
 
                waveOutUnprepareHeader(hWaveOut,&wh,sizeof(wh));
                waveOutClose(hWaveOut);

                free(buffer);                            
*/                
                SuccessFlag = 1;
            }
        }
 
    }
 
    else
        SuccessFlag = 0; //printf("Invalid WAV\n");
        
        return SuccessFlag;
}
 
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
struct SoundBox
{
static const int MAX_SOUNDS = 10;

SoundData SoundDataList[MAX_SOUNDS];

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
SoundBox()
{
    int i;
    for( i = 0; i < MAX_SOUNDS; i++ )
    {
      SoundDataList[i].filebuffer = NULL;
      SoundDataList[i].filesize = 0;
    }
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
int LoadSound( int index, char *filename )
{
int i;

SoundDataList[index].filebuffer = readFileData(filename, SoundDataList[index].filesize);

if( parseWav(SoundDataList[index].filebuffer, SoundDataList[index] ) >= 1 )
{
    return 1;
}
else
{
   SoundDataList[index].filesize = 0;    
   free(SoundDataList[index].filebuffer);
   return 0;
}

}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void PlaySound( int index )
{   
/*
   int i;   
 if( index == 0 )
   for( i = 0; i < SoundDataList[index].wh.dwBufferLength; i++ )
       SoundDataList[index].wh.lpData[i] = (char)(rand() % 256);
*/
   waveOutWrite(SoundDataList[index].hWaveOut,&SoundDataList[index].wh,sizeof(SoundDataList[index].wh)); 
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
~SoundBox()
{
    int i;
    for( i = 0; i < MAX_SOUNDS; i++ )
     if( SoundDataList[i].filesize > 0 )
     {
      free(SoundDataList[i].filebuffer);
      waveOutUnprepareHeader(SoundDataList[i].hWaveOut,&SoundDataList[i].wh,sizeof(SoundDataList[i].wh));
      waveOutClose(SoundDataList[i].hWaveOut);
     }
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
/*
int main()
{
    char *filename = "c:/windows/media/tada.wav";
    char *buffer;
    long fileSize;
 
    buffer = readFileData(filename, fileSize);
    parseWav(buffer); 
    free(buffer);
    return 0;
}
*/

#endif

