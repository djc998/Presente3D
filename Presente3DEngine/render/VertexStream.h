#ifndef VertexStream_header
#define VertexStream_header

/* 
* File: VertexStream.h 
* Created by: Vitaly V. Boiko
* Short Description: 
* 
*/

struct PresenteTexturedShapeVertex
{    
    float x, y, z;
    float nx, ny, nz;    
    float u,v;
};

struct PresenteShapeVertex
{
    float r, g, b, a;
    float x, y, z;
	float nx, ny, nz;    
};

#endif /* VertexStream_header */
