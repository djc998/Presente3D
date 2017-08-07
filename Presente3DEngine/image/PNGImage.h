#ifndef _PNGIMAGE_HEADER_
#define _PNGIMAGE_HEADER_

#include "gl/gl.h"

#include <string>

#include "Ogre.h"

#include "SimpleImage.h"

class PNGImage: public SimpleImage
{
public: 
    PNGImage(const char* path);
    ~PNGImage();

    bool Initialize();
    void Release();

    void RemoveSideAlpha();

    void GetPixel(int w, int h, int& r, int& g, int& b, int& a);
	int  GetWidth(){return box->getWidth();}
	int  GetHeight(){return box->getHeight();}    

    std::string& GetFilePath(){return filepath;}

//    bool LoadGL(Texture* texture);

    bool Read();
    
private:   
    Ogre::PixelBox* box;
    Ogre::Image image;    

    
};

#endif