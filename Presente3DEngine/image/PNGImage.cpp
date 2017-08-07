#include "stdafx.h"

#include "PNGImage.h"

#include <stdio.h>

#include "FreeImage.h"

#ifndef png_jmpbuf
#  define png_jmpbuf(png_ptr) ((png_ptr)->png_jmpbuf)
#endif

void abort_(const char * s, ...)
{
    va_list args; 
    va_start(args, s);  
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
}


PNGImage::PNGImage(const char* path)
{
    filepath = path;

    x      = 0;
    y      = 0;
    width  = 0;
    height = 0;
    number_of_passes = 0;       

    left_side_columns   = 0;
    right_side_columns  = 0;
    top_side_columns    = 0;
    bottom_side_columns = 0;
    original_height = 0;
    original_width = 0;
}

PNGImage::~PNGImage()
{

}

bool PNGImage::Initialize()
{
    return Read();
}


void PNGImage::Release()
{

}


//! simple non optimized version
void PNGImage::RemoveSideAlpha()
{
    // find alpha lines
           

    // left side
    for(int x = 0; x < (int)box->getWidth(); x++){
        float column_alpha = 0.0f;
        bool nonalpha_data = false;

        for(int y = 0; y < (int)box->getHeight(); y++){
            Ogre::ColourValue color = box->getColourAt(x, y, 0);
            if(color.a > 0.0f){
                nonalpha_data = true;
                break;
            }
        }
        
        if(nonalpha_data == true){
            left_side_columns = x;
            break;
        }
    }

    // right side
    for(int x = box->getWidth() - 1; x > 0; x--){
        float column_alpha = 0.0f;
        bool nonalpha_data = false;

        for(int y = 0; y < (int)box->getHeight(); y++){
            Ogre::ColourValue color = box->getColourAt(x, y, 0);
            if(color.a > 0.0f){
                nonalpha_data = true;
                break;
            }
        }

        if(nonalpha_data == true){
            right_side_columns = x + 1;
            break;
        }
    }

    // top side
    for(int y = 0; y < (int)box->getHeight(); y++){    
        float column_alpha = 0.0f;
        bool nonalpha_data = false;
        for(int x = 0; x < (int)box->getWidth(); x++){        
            Ogre::ColourValue color = box->getColourAt(x, y, 0);
            if(color.a > 0.0f){
                nonalpha_data = true;
                break;
            }
        }

        if(nonalpha_data == true){
            top_side_columns = y;
            break;
        }
    }

    // bottom side
    for(int y = box->getHeight() - 1; y > 0; y--){    
        float column_alpha = 0.0f;
        bool nonalpha_data = false;
        for(int x = 0; x < (int)box->getWidth(); x++){        
            Ogre::ColourValue color = box->getColourAt(x, y, 0);
            if(color.a > 0.0f){
                nonalpha_data = true;
                break;
            }
        }

        if(nonalpha_data == true){
            bottom_side_columns = y + 1;
            break;
        }
    }

    // create image without alpha at sides
    Ogre::Box new_picture_box(left_side_columns, 
                              top_side_columns, 
                              right_side_columns, 
                              bottom_side_columns);


    //Ogre::PixelBox new_pb =     

    //! FREE THIS DATA
    box = new Ogre::PixelBox(box->getSubVolume(new_picture_box));
    
}

void PNGImage::GetPixel(int w, int h, int& r, int& g, int& b, int& a)
{	
    if(w < 0 || (w > (int)box->getWidth() - 1) || (h < 0) || (h > (int)box->getHeight() - 1)){
        r = g = b = a = 0;
        return;
    }

    Ogre::ColourValue color = box->getColourAt(w, h, 0); 

    r = (int)(color.r * 255.0f);
    g = (int)(color.g * 255.0f);
    b = (int)(color.b * 255.0f);
    a = (int)(color.a * 255.0f);  
}

bool PNGImage::Read()
{      
    image.load(filepath, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    //! PLACEHOLDER QUICK FIX 
    /*
    if(image.getBPP() != 32){
        return false;
    }*/

    box = new Ogre::PixelBox(image.getPixelBox());        
    original_width = box->getWidth();
    original_height = box->getHeight();
    return true;
}