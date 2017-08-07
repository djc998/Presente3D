#pragma once

#include "framework\Color.h"
#include "framework\Vertex.h"

#include "ConvertedData.h"
#include "SimpleImage.h"

enum NEIGHBOR_LIST
{
    NL_RIGHT, 
    NL_LEFT,
    NL_UP,
    NL_DOWN
};

struct VertexColor
{
	VertexColor(){
		remove = false;
	}
	Vertex v;
	Color c;
	bool remove;
};

struct PixelVertex{
	Vertex v;
	Color  c; 
	int    x;
	int    y;
	bool   used;
    bool   added_to_edge;
    bool   first_vertex; // flag for shape vertex sequence connection
    NEIGHBOR_LIST dir;
    int n_amount; 
};

typedef std::vector<std::vector<PixelVertex>> PixelVertexLines;

class ImageDataParser
{
public: 
	static bool GenerateEdgeData(SimpleImage& image, PixelVertexLines& lines);
	static bool GenerateFullPictureData(SimpleImage& image, PixelVertexLines& lines);
	static bool GenerateConvertedData(ConvertedShapeData* render_object, PixelVertexLines& lines);
	static bool GenerateRenderOnTopObject(SimpleImage& image, ConvertedShapeData* render_object, PixelVertexLines& lines);	

    static void GenerateCCWOrientedData(basic_stream& src, basic_stream& dst);
    static void GenerateCCWOrientedTexturedData(shape_texture_data& src, ConvertedShapeData* render_object);
};