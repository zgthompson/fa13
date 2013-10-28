/******************
Course: CS315
Assignment: Lab07
Date: 10/21/13
File: Lab07.cpp
Author: Joji Kubota
Description: Implement the first phase of OCR by chaning the 
             color of letters and put bounding box around each letter.
******************/

#include "EasyBMP.h"
#include <queue>
#include <iostream>

using namespace std;

class point{
private:
  int x; int y;

public:
  point(int p, int q){
    x = p; y = q;
  }

  int getx(){
    return x;
  }

  int gety() {
    return y;
  }
};

void toBlackAndWhite(BMP &image) {

    int total, newColor;

    for (int j = 0; j < image.TellHeight(); ++j) {
        for (int i = 0; i < image.TellWidth(); ++i) {

            // total is the sum of the three color components of a pixel
            total = image(i,j)->Red + image(i,j)->Green + image(i,j)->Blue;

            // if sum is greater than 382 newColor is white, else black
            newColor = total > 382 ? 255 : 0;

            // make the pixel black or white 
            image(i,j)->Red = newColor;
            image(i,j)->Green = newColor;
            image(i,j)->Blue = newColor;
        }
    }
}



int label (BMP& I, BMP& O)
{
  int w = I.TellWidth (); // Width of the image.
  int h = I.TellHeight (); // Height of the image.
  int xlow, ylow, xhigh, yhigh; // Track the NWSE boundery.
  bool visited [w][h]; // Array to track visited pixel.
  for (int i = 0; i < w; i++) // Initialize all (i, j) to false.
    for (int j = 0; j < h; j++)
      visited [i][j] = false;
  queue <point>  Q; // Initialize an empty queue.
  O.SetSize (w, h); // Set O size the same as I.
  int count = 0; // Number of letters.
  for (int j = 0; j < w; j++)
    for (int k = 0; k < h; k++)
      { // If the pixel is near black.
	if (I (j, k) -> Red < 128 &&
	    I (j, k) -> Green < 128 &&
	    I (j, k) -> Blue < 128)
	  {
	    count++;
	    xlow = j; // Initialize the NWSE boundery.
	    ylow = k;
	    xhigh = j;
	    yhigh = k;
	    Q.push (point (j, k)); // Add to stack.
	    visited [j][k] = true;
	    while (!Q.empty ())
	      {  
		point p = Q.front ();
		Q.pop ();
		int x1 = p.getx ();
		int y1 = p.gety ();
		O (x1, y1) -> Red = 0;
		O (x1, y1) -> Green = 255;
		O (x1, y1) -> Blue = 0;
		O (x1, y1) -> Alpha = 0;
		if (x1 < xlow)
		  xlow = x1;
		if (y1 < ylow)
		  ylow = y1;
		if (x1 > xhigh)
		  xhigh = x1;
		if (y1 > yhigh)
		  yhigh = y1;
		for (int h = x1 - 1; h <= x1 + 1; h++)
		  for (int i = y1 - 1; i <= y1 + 1; i++)
		    { // Check the neighbor pixels.
		      if (visited [h][i] == false)
			{
			  visited [h][i] = true;
			  if (I (h, i) -> Red < 128 &&
			      I (h, i) -> Green < 128 &&
			      I (h, i) -> Blue < 128)
			    Q.push (point (h, i));
			}
		    }
	      }
	    cout << "xlow is " << xlow << endl;
	    cout << "xhigh is " << xhigh << endl;
	    cout << "ylow is " << ylow << endl;
	    cout << "yhigh is " << yhigh << endl;
	    cout << endl;
	    for (int i = xlow - 1; i <= xhigh + 1; i++)
	      { // Draw South bound line.
		O (i, ylow - 1) -> Red = 255;
		O (i, ylow - 1) -> Green = 0;
		O (i, ylow - 1) -> Blue = 0;
		O (i, ylow - 1) -> Alpha = 0;
		// Draw North bound line.
		O (i, yhigh + 1) -> Red = 255;
		O (i, yhigh + 1) -> Green = 0;
 		O (i, yhigh + 1) -> Blue = 0;
		O (i, yhigh + 1) -> Alpha = 0;
	      }
	    for (int j = ylow - 1; j <= yhigh + 1; j++)
	      { // Draw West bound line.
		O (xlow - 1, j) -> Red = 255;
		O (xlow - 1, j) -> Green = 0;
		O (xlow - 1, j) -> Blue = 0;
		O (xlow - 1, j) -> Alpha = 0;
		// Draw East bound line.
		O (xhigh + 1, j) -> Red = 255;
		O (xhigh + 1, j) -> Green = 0;
 		O (xhigh + 1, j) -> Blue = 0;
		O (xhigh + 1, j) -> Alpha = 0;
	      }
	  }
	else visited [j][k] = true;
      }
  return count;
}




int main(int argc, char* argv [])
{
  BMP inImage, outImage; // Declare input & output BMP images.
  char inputFile [128];
  char outputFile [128];
  cout << "Enter the name of the input file" << endl;
  cin >> inputFile;
  cout << "Enter the name of the output file" << endl;
  cin >> outputFile;
  inImage.ReadFromFile (inputFile); // Read input file.

  toBlackAndWhite(inImage);

  int x = label (inImage, outImage); // Perform OCR first state.
  cout << "The number of letters is " << x << endl;
  outImage.WriteToFile (outputFile); // Write out the output file.

  return 0;
 }
