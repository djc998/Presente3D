#ifndef _Color_header_
#define _Color_header_

struct Color
{	
	Color(){};
	Color(float _r, float _g, float _b, float _a = 1.0f){r = _r; g = _g; b = _b; a = _a;}
    Color(int c){
        int alpha = (c >> 24) & 0xff;
        int blue = (c >> 16) & 0xff;
        int green = (c >> 8) & 0xff;
        int red = c & 0xff;
        
        r = (float)red / 255.0f;
        g = (float)green / 255.0f;
        b = (float)blue / 255.0f;
        a = (float)alpha / 255.0f;
    }
	float r;
	float g;
	float b;
	float a;
};

#endif 