#ifndef SIMPLE_IMAGE_HEADER
#define SIMPLE_IMAGE_HEADER

#include <string>

class SimpleImage
{
public:
    ~SimpleImage(){};

    virtual bool Initialize() = 0;
    virtual void Release() = 0;

    virtual void GetPixel(int w, int h, int& r, int& g, int& b, int& a) = 0;
    virtual int  GetWidth() = 0;
    virtual int  GetHeight() = 0;

    virtual std::string& GetFilePath() = 0;

    virtual bool Read() = 0;

    // columns that contains alpha
    int left_side_columns;
    int right_side_columns;
    int top_side_columns;
    int bottom_side_columns;


    int  GetOriginalWidth(){return original_width;}
    int  GetOriginalHeight(){return original_height;}

    int original_width;
    int original_height;

protected:
    SimpleImage(){};

    std::string filepath;

    int x;
    int y;
    int width;
    int height;
    int number_of_passes;

   
};

#endif 