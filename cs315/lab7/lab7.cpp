#include "EasyBMP.h"
#include <iostream>
#include <vector>
#include <queue>

template<class T>
class Queue : public std::queue<T> {
    public:
        T pop() {
            T tmp = std::queue<T>::front();
            std::queue<T>::pop();
            return tmp;
        }
};

struct Point {
    int x, y;
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

// pixel is assumed to be fully black or fully white
bool isBlack(RGBApixel* pixel) {
    return pixel->Red == 0;
}

void makeGreen(RGBApixel* pixel) {
    pixel->Red = 0;
    pixel->Blue = 0;
    pixel->Green = 255;
}

void drawBox(BMP &image, int lowx, int lowy, int highx, int highy) {

    RGBApixel redPixel;
    // make pixel red
    redPixel.Red = 255;
    redPixel.Blue = 0;
    redPixel.Green = 0;

    // color upper and bottom bounds
    for (int i = lowx; i <= highx; ++i) {
        image.SetPixel(i, lowy, redPixel);
        image.SetPixel(i, highy, redPixel);
    }
    
    // color left and right bounds
    for (int j = lowy; j <= highy; ++j) {
        image.SetPixel(lowx, j, redPixel);
        image.SetPixel(highx, j, redPixel);
    }
}

bool validCoords(int x, int y, int xmax, int ymax) {
    return x < xmax && y < ymax && x >= 0 && y >=0;
}

int main(void) {

    BMP TextImage;
    TextImage.ReadFromFile("text.bmp");
    toBlackAndWhite(TextImage);

    int width = TextImage.TellWidth(), height = TextImage.TellHeight();

    // a vector of bool vectors, simililar to a 2D array but dynamically allocated
    std::vector< std::vector<bool> > visited(width, std::vector<bool>(height, false));

    // character count
    int symbolCount = 0, lineCount = 0;

    bool thisLineWhite = true, lastLineWhite = true;

    Queue<Point*> Q;

    int lowx, lowy, highx, highy, curx, cury, neighx, neighy, lineBottom = -1;
    Point* curPoint;

    for (int j = 0; j < height; ++j) {

        // if j is past lineBottom, it starts out as white line
        if (j > lineBottom) {
            thisLineWhite = true;
        }

        for (int i = 0; i < width; ++i) {

            // check if current pixel is black
            if ( !visited[i][j] && isBlack( TextImage(i,j) ) ) {

                // this line has a black pixel
                thisLineWhite = false;

                // we have found a new character
                ++symbolCount;

                // create a new point
                Point* newPoint = new Point;

                // mark the starting values for border box and initialize newPoint
                newPoint -> x = lowx = highx = i;
                newPoint -> y = lowy = highy = j;

                // insert point of pixel into queue
                Q.push(newPoint);

                // mark pixel as visited
                visited[i][j] = true;

                while (!Q.empty()) {
                    // remove curPoint from queue
                    curPoint = Q.pop();
                    // grab x and y coords and cleanup curPoint
                    curx = curPoint -> x;
                    cury = curPoint -> y;
                    delete curPoint;
                    
                    // color the pixel green
                    makeGreen(TextImage(curx,cury));

                    // update values of border box
                    if (curx < lowx) lowx = curx;
                    else if (curx > highx) highx = curx;

                    if (cury < lowy) lowy = cury;
                    else if (cury > highy) highy = cury;

                    // check out the neighbors
                    for (int x = -1; x < 2; ++x) {
                        for (int y = -1; y < 2; ++y) {
                            if (!(x == 0 && y == 0)) {
                                neighx = curx + x;
                                neighy = cury + y;

                                if (    validCoords(neighx, neighy, width, height) &&
                                        !visited[neighx][neighy] &&
                                        isBlack( TextImage(neighx, neighy) )    ) 
                                {
                                    // create new point
                                    newPoint = new Point;
                                    newPoint -> x = neighx;
                                    newPoint -> y = neighy;

                                    // insert it into queue
                                    Q.push(newPoint);

                                    // mark as visited
                                    visited[neighx][neighy] = true;

                                
                                }
                            }
                        }
                    }
                }

                // draw red box around character
                drawBox(TextImage, lowx - 1, lowy - 1, highx + 1, highy + 1);
                lineBottom = highy;
            }
        }

        if (lastLineWhite && !thisLineWhite) {
            ++lineCount;
        }

        lastLineWhite = thisLineWhite;
    }

    TextImage.WriteToFile("output.bmp");
    std::cout << "symbols: " << symbolCount << std::endl;
    std::cout << "lines: " << lineCount << std::endl;

}
