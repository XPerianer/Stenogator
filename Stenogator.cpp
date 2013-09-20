// Stenogator.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "Imageedit.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
using namespace std;


string B_to_A(const char* input)
{
	int length = strlen(input);     //get length of string
	string str;
	int binary[8];    //array used to store 1 byte of binary number (1 character)
	int asciiNum = 0;      //the ascii number after conversion from binary
	char ascii;      //the ascii character itself
	
	cout << " ";
	
	int z = 0;   //counter used
	
	for(int x = 0; x < length / 8; x++)     //reading in bytes. total characters = length / 8
	{
		for(int a = 0; a < 8; a++)      //store info into binary[0] through binary[7]
		{
			binary[a] = (int) input[z] - 48;      //z never resets
			z++;
		}
		
		int power[8];    //will set powers of 2 in an array
		int counter = 7;        //power starts at 2^0, ends at 2^7
		for(int x = 0; x < 8; x++)
		{
			power[x] = counter;      //power[] = {7, 6, 5, ..... 1, 0}
			counter--;    //decrement counter each time
		}
		
		for(int y = 0; y < 8; y++)    //will compute asciiNum
		{
			double a = binary[y];    //store the element from binary[] as "a"
			double b = power[y];    //store the lement from power[] as "b"
			
			asciiNum += a* pow(2, b);   //asciiNum = sum of a * 2^power where 0 <= power <= 7, power is int
		}
		
		ascii = asciiNum;   //assign the asciiNum value to ascii, to change it into an actual character
		asciiNum = 0;    //reset asciiNum for next loop
		
		str += ascii;	// store the ascii character
	}
return str;
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}


int _tmain(int argc, _TCHAR* argv[])
{
	// Initialize GDI+.
   GdiplusStartupInput gdiplusStartupInput;
   ULONG_PTR gdiplusToken;
   GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	const int laenge = 2000;
	using namespace std;
	std::cout << "Willkommen beim Stenogator\n";
	string str;
	cin >> str;

	Bitmap Source(L"Source.png",false);
	
	hidestring(&Source,&str);

	CLSID pngClsid;
	GetEncoderClsid(L"image/png",&pngClsid);
	Source.Save(L"Final.png", &pngClsid, NULL);

	system("PAUSE");
	return 0;
}
