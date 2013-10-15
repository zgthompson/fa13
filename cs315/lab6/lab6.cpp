#include "EasyBMP.h"

void tile(BMP& Input, BMP& Output) {
    if (Input.TellHeight() == 1) {
        Output.SetPixel(Output.TellWidth() - 1, 0, Input.GetPixel(0, 0));
    }
    else {
        BMP* ScaledInput = new BMP(Input);
        Rescale(*ScaledInput, 'p', 50);

        // SW quadrant
        RangedPixelToPixelCopy(*ScaledInput, 0, ScaledInput -> TellWidth(), 0, ScaledInput -> TellHeight(), 
                Output, Output.TellWidth() - 2 * ScaledInput -> TellWidth(), ScaledInput -> TellHeight());

        // NE quadrant
        tile(*ScaledInput, Output);

        // NW quadrant
        RangedPixelToPixelCopy(Output, Output.TellWidth() - ScaledInput -> TellWidth(), Output.TellWidth() - ScaledInput -> TellWidth() / 2 - 1,
                0, ScaledInput -> TellHeight() - 1, Output, Output.TellWidth() - 2 * ScaledInput -> TellWidth(), 0);

        RangedPixelToPixelCopy(Output, Output.TellWidth() - ScaledInput -> TellWidth(), Output.TellWidth() - ScaledInput -> TellWidth() / 2 - 1,
                0, ScaledInput -> TellHeight() - 1, Output, Output.TellWidth() - 3 * ScaledInput -> TellWidth() / 2, 0);

        // SE quadrant
        RangedPixelToPixelCopy(Output, Output.TellWidth() - ScaledInput -> TellWidth(), Output.TellWidth() - 1, ScaledInput -> TellHeight() / 2,
                ScaledInput -> TellHeight()  - 1, Output, Output.TellWidth() - ScaledInput -> TellWidth(), ScaledInput -> TellHeight());

        RangedPixelToPixelCopy(Output, Output.TellWidth() - ScaledInput -> TellWidth(), Output.TellWidth() - 1, ScaledInput -> TellHeight() / 2,
                ScaledInput -> TellHeight() - 1, Output, Output.TellWidth() - ScaledInput -> TellWidth(), 3 * ScaledInput -> TellHeight() / 2);
    }

}

int main(void) {
    BMP in, out;
    in.ReadFromFile("in.bmp");
    int width = in.TellWidth();
    int height = in.TellHeight();

    // width and height must be equal, nonzero, and powers of 2
    if (width == height && width != 0 && ((width & (width - 1)) == 0)) {
        out.SetSize(in.TellWidth(), in.TellHeight());
        tile(in, out);
        out.WriteToFile("output.bmp");
    }
    else {
        std::cout << "Width and height of in.bmp must be equal, nonzero, and powers of 2" << std::endl;
    }
}
