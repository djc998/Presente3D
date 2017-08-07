#ifndef PresenteMath_header
#define PresenteMath_header

/* 
* File: PresenteMath.h 
* Created by: Vitaly V. Boiko
* Short Description: 
* 
*/

#include "Vertex.h"

void CrossProduct(Vertex& n, Vertex& v1, Vertex& v2)
{
    n.x = v1.y*v2.z - v2.y*v1.z;
    n.y = -v1.x*v2.z + v2.x*v1.z;
    n.z = v1.x*v2.y - v2.x*v2.y;
}

Vertex FindNormal(Vertex& vertex_1, Vertex& vertex_2, Vertex& vertex_3)
{
    Vertex v1, v2;

	// Calculate two vectors from the three points. Assumes counter clockwise
	// winding!
    v1.x = vertex_1.x - vertex_2.x;
	v1.y = vertex_1.y - vertex_2.y;
	v1.z = vertex_1.z - vertex_2.z;

	v2.x = vertex_2.x - vertex_3.x;
	v2.y = vertex_2.y - vertex_3.y;
	v2.z = vertex_2.z - vertex_3.z;

	// Take the cross product of the two vectors to get
	// the normal vector.
    Vertex n;
    CrossProduct(n, v1, v2);

    n.normalize();

    return n;
};


#endif /* PresenteMath_header */
