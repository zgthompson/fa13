#include "EasyBMP.h"
#include <iostream>
#include <cstdlib>
#include <climits>

using namespace std;

// Filenames for input and output
const string INFILENAMES [16] = { "img1.bmp", "img2.bmp", "img3.bmp",
    "img4.bmp", "img5.bmp", "img6.bmp", "img7.bmp", "img8.bmp",
    "img9.bmp", "img10.bmp", "img11.bmp", "img12.bmp",
                  "img13.bmp", "img14.bmp", "img15.bmp", "img16.bmp"};


int rowMatch (BMP& UseTop, BMP& UseBottom )
{ // Compares the top edge of UseTop to the bottom edge of UseBottom.
  // Assumes UseTop and UseBottom are squares of same size
  // score obtained by adding the difference between color components

    int rowSize = UseTop.TellWidth();
    int total = 0;
    RGBApixel pixelTop;
    RGBApixel pixelBottom;

    for (int i = 0; i < rowSize; i++) {
        pixelTop = UseTop.GetPixel(i, 0);
        pixelBottom = UseBottom.GetPixel(i, rowSize - 1);

        total += abs(pixelTop.Red - pixelBottom.Red) + 
            abs(pixelTop.Green - pixelBottom.Green) +
            abs(pixelTop.Blue - pixelBottom.Blue);
    }
    return total;
}


int columnMatch ( BMP& UseLeft, BMP& UseRight )
{
  // Compares the left edge of UseLeft to the right edge of UseRight.
  // Assumes UseRight and UseLeft are squares of same size
  // score obtained by adding the difference between color components
  // similar to the rowMatch

    int columnSize = UseLeft.TellWidth();
    int total = 0;
    RGBApixel pixelLeft;
    RGBApixel pixelRight;

    for (int i = 0; i < columnSize; i++) {
        pixelLeft = UseLeft.GetPixel(0,i);
        pixelRight = UseRight.GetPixel(columnSize - 1, i);

        total += abs(pixelLeft.Red - pixelRight.Red) + 
            abs(pixelLeft.Green - pixelRight.Green) +
            abs(pixelLeft.Blue - pixelRight.Blue);
    }
    return total;
}


void finalScore (BMP images[16], int score[2][16][16]) {
// uses the rowMatch and columnMatch to create scores
// score[0][i][j] is the WEST SCORE and score[1][i][j] is the NORTH SCORE

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (i == j) {
                score[0][i][j] = INT_MAX;
                score[1][i][j] = INT_MAX;
            }
            else {
                score[0][i][j] = columnMatch(images[i], images[j]);
                score[1][i][j] = rowMatch(images[i], images[j]);
            }
        }
    }
}

int findNorthWest(int score[2][16][16]) {
// finds the North West tile by adding the best North and West scores for each tile and
// choosing the one that maximizes the score
    int max = 0;
    int maxIndex;
    int curTotal;

    for (int i = 0; i < 16; i++) {
        curTotal = 0;
        for (int j = 0; j < 16; j++) {
            curTotal += score[0][i][j] + score[1][i][j];
        }

        if (curTotal > max) {
            max = curTotal;
            maxIndex = i;
        }
    }
    return maxIndex;
}

int findEastNeighbor(int score[2][16][16], int tile, bool remaining[16]) {
   // for a given tile, find its eastern neighbor among the remaining ones
   // remaining[j] is true for tiles that have not yet been placed in the final image

    int minValue = INT_MAX;
    int minIndex;
    for (int i = 0; i < 16; i++) {
        if (remaining[i] && score[0][i][tile] < minValue) {
            minValue = score[0][i][tile];
            minIndex = i;
        }
    }
    return minIndex;


}

int findSouthNeighbor(int score[2][16][16], int tile, bool remaining[16]) {
   // for a given tile, find its southern neighbor, among the remaining ones
   // remaining[j] is true for tiles that have not yet been selected for placement
   // similar to findEastNeighbor
   
    int minValue = INT_MAX;
    int minIndex;
    for (int i = 0; i < 16; i++) {
        if (remaining[i] && score[1][i][tile] < minValue) {
            minValue = score[1][i][tile];
            minIndex = i;
        }
    }
    return minIndex;
}

void copy(BMP & InImg, BMP & OutImg, int xPos, int yPos) {
  // copy image to larger final picture so that the InImg is placed in row i, column j of OutImg
    int width = InImg.TellWidth();
    RGBApixel curPixel;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            curPixel = InImg.GetPixel(i, j);
            OutImg.SetPixel(xPos * width + i, yPos * width + j, curPixel);
        }
    }
}

void greedy(int score[2][16][16], BMP InImg[16], BMP & OutImg) {
  //greedy algorithm to put the image together
    

    bool remaining[16];
    for (int k = 0; k < 16; k++) remaining[k] = true;

    int curImage;
    int topImage;
    int leftImage;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == 0 && j == 0) {
                curImage = findNorthWest(score);
                copy( InImg[curImage], OutImg, j, i );
                remaining[curImage] = false;
                topImage = leftImage = curImage;
            }
            else if (j == 0) {
                curImage = findSouthNeighbor(score, topImage, remaining);
                copy ( InImg[curImage], OutImg, j, i);
                remaining[curImage] = false;
                topImage = leftImage = curImage;
            }
            else {
                curImage = findEastNeighbor(score, leftImage, remaining);
                copy( InImg[curImage], OutImg, j, i);
                remaining[curImage] = false;
                leftImage = curImage;
            }
        }
    }
}

int main()
{
  BMP InImg[16], OutImg; // vector of input images and output image
  int score [2][16][16] ;       // holds EAST and NORTH scores
  for( int i=0; i<16; ++i ) // Read in the sub-images
    InImg[i].ReadFromFile( INFILENAMES[i].c_str());
  int subsize = InImg[0].TellWidth();
  OutImg.SetSize( 4*subsize, 4*subsize ); // Set size of output image
  finalScore(InImg, score);
  greedy( score, InImg, OutImg);
  OutImg.WriteToFile("output.bmp");

  return 0;
}

