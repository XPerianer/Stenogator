#include "stdafx.h"
//Hilfsfunktion f�r Konvertierung von ASCII in bin�r
string A_to_B(const char* input) 
{
	string str;
	int ascii;           // used to store the ASCII number of a character
	int length = strlen(input);        //find the length of the user's input
	
	cout << " ";
	
	for(int x = 0; x < length; x++)          //repeat until user's input have all been read
	// x < length because the last character is "\0"
	{
		ascii = input[x];        //store a character in its ASCII number
		
		/* Refer to http://www.wikihow.com/Convert-from-Decimal-to-Binary for conversion method used 
		 * in this program*/		
		
		char* binary_reverse = new char [9];       //dynamic memory allocation
		char* binary = new char [9];
		
		int y = 0;    //counter used for arrays
		
		while(ascii != 1)    //continue until ascii == 1
		{
			if(ascii % 2 == 0)    //if ascii is divisible by 2
			{
				binary_reverse[y] = '0';   //then put a zero
			}
			else if(ascii % 2 == 1)    //if it isnt divisible by 2
			{
				binary_reverse[y] = '1';   //then put a 1
			}
			ascii /= 2;    //find the quotient of ascii / 2
			y++;    //add 1 to y for next loop
		}
		
		if(ascii == 1)    //when ascii is 1, we have to add 1 to the beginning
		{
			binary_reverse[y] = '1';
			y++;
		}
		
		if(y < 8)  //add zeros to the end of string if not 8 characters (1 byte)
		{
			for(; y < 8; y++)  //add until binary_reverse[7] (8th element)
			{
				binary_reverse[y] = '0';
			}
		}
	
		for(int z = 0; z < 8; z++)  //our array is reversed. put the numbers in the rigth order (last comes first)
		{
			binary[z] = binary_reverse[7 - z];
		}
		binary[8] = NULL;
		str += binary;   //store the 8 digit binary number
		
		delete [] binary_reverse;     //free the memory created by dynamic mem. allocation
		delete [] binary;
	}
	
	cout << endl;
	return str;
}


int hidestring(Bitmap* img,string* str)
{
	string bin = "0";
	bin = A_to_B(str->c_str());
	cout << bin;
	Color col;
	int width = img->GetWidth();
	int position = 0;
	cout << "Breite" << width;
	
	int i = 1;
	while(position <= width/3)
	{
	
	img->GetPixel(i,1,&col);
	int a=255,r=0,g=0,b=0;
	
	bool bBit=true;
	if(bin[position]=='0'){bBit=false;}else{bBit=true;}
		cout << "C-String: " << bBit << "Pixel: " << (int)col.GetRed() % 2;
		
		//Farbwerte anpassen Adjust Colors
		if((int)col.GetRed() % 2 == bBit)
		{
			cout << "y" << endl;
			r = col.GetRed();
		}
		else
		{
			r = 1 + col.GetRed();
			cout << "n" << endl;
		}
		position++;
		if((int)col.GetGreen() % 2 == bin[position])
		{
			cout << "y" << endl;
			g = col.GetGreen();
		}
		else
		{
			g = 1 + col.GetGreen();
			cout << "n" << endl;
		}
		position++;
		if((int)col.GetBlue() % 2 == bin[position])
		{
			cout << "y" << endl;
			b = col.GetBlue();
		}
		else
		{
			b = 1 + col.GetBlue();
			cout << "n" << endl;
		}
		position++;

	ARGB argb = Color::MakeARGB(a, r, g, b);
	col.SetValue(argb);

	img->SetPixel(i,1,col);
	}
	
	return 1;

}



