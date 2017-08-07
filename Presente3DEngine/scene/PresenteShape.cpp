/* 
 * File: PresenteShape.cpp 
 * Company:  
 * Creation Date: 12/22/2011
 * Created by: Vitalii V. Boiko
 * e-mail: vitalymeister@gmail.com
 * 
 * Description: 
 * 
 * 
 * History: 
 * 
 */

#include "stdafx.h"
#include "PresenteShape.h"

#include "ConvertedData.h"
#include "converter\image\ImageConverter.h"

#include "render\VertexStream.h"

#include "OgreGpuProgramManager.h"

#include "OgreGLRenderSystem.h"
#include "OgreGLSLProgramFactory.h"

#include "core\PresenteEngine.h"
#include "material\MaterialHelper.h"

#include "settings\Settings.h"

using namespace Ogre;

PresenteShape::PresenteShape(SceneManager* scm, std::string& name):
    SceneNode(scm)
{
    shape = 0;
    scene_manager = scm;
	shape_entity = 0;
}

bool PresenteShape::FillData(ShapeData& data)
{
    shape = &data;
    return true;
}

void CreateShaders()
{
    /*
    GpuProgramPtr v = Ogre::GpuProgramManager::getSingleton().load("custom_vertex_shader", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
                    "shader.vert",
                    GpuProgramType::GPT_VERTEX_PROGRAM, "glsl");

    GpuProgramPtr p = Ogre::GpuProgramManager::getSingleton().load("custom_pixel_shader", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
                    "shader.frag",
        GpuProgramType::GPT_FRAGMENT_PROGRAM, "glsl");

    MaterialPtr new_material = MaterialManager::getSingleton().create("text_material", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
    //ogreMaterial->setDiffuse(1,0,0,1);
    //ogreMaterial->setShadingMode(Ogre::SO_PHONG);

    new_material->removeTechnique(0);
    Technique* t = new_material->createTechnique();
    t->createPass();
    t->getPass(0)->setVertexProgram("custom_vertex_shader");
    t->getPass(0)->setFragmentProgram("custom_pixel_shader"); 
   
    new_material->compile(); */
}

bool PresenteShape::Generate()
{   
	// add to frame listeners
	PresenteEngine::getInstance().root->addFrameListener(this);
	scene_manager->addEyeFrameListener(this);

    ConvertedShapeData converted_data;
                       converted_data.xml_data = *shape; 
    bool res = ImageConverter::Convert(shape->filepath.c_str(), &converted_data);
    if(!res){return false;}

    GenerateShapeMesh(converted_data);
    GenerateShapeTexture(converted_data);
    //GenerateTempPlane();
                       
    w = converted_data.width;
    h = converted_data.height;       

	float image_width = w;
	float xml_width = this->shape->image_width;
	float scale_ratio = xml_width / image_width;

	this->scale(scale_ratio, scale_ratio, scale_ratio);

	// set actual position in the world
	float x = shape->left;
	float y = slide_height - converted_data.height * scale_ratio - shape->top;


    this->setPosition(x, y, 0); 
	// apply zdepth param
	float zaxis_offset = shape->zdepth * Z_OFFSET;
    this->translate(0, 0, zaxis_offset, Node::TS_PARENT);

    // calculate rotation

    SceneNode* entity_parent        = this;
    Ogre::SceneNode* rotation_point = scene_manager->createSceneNode();
    // attach to main parent rotation point
    entity_parent->addChild(rotation_point);

    float center_x = w / 2.0f;
    float center_y = h / 2.0f;
    rotation_point->translate(center_x, center_y, 0, Ogre::Node::TS_LOCAL);

    Ogre::Vector3 pos_before_rotation = rotation_point->_getDerivedPosition();

    // rotate
    Ogre::Degree rotation_degree(-1 * shape->rotation);
    entity_parent->rotate(Vector3::UNIT_Z, rotation_degree, Ogre::Node::TS_LOCAL);
    entity_parent->_update(true, true);

    // get the offset vector diff
    Ogre::Vector3 pos_after_rotation = rotation_point->_getDerivedPosition();

    Ogre::Vector3 diff = pos_before_rotation - pos_after_rotation;
    entity_parent->translate(diff, Ogre::Node::TS_WORLD);
    // move main parent

    scene_manager->destroySceneNode(rotation_point);

    return true;
}

void PresenteShape::RecalculateScale(float cam_distance)
{
	

	/*
    float zaxis_offset = shape->zdepth * Z_OFFSET;
    this->translate(0, 0, zaxis_offset, Node::TS_PARENT);

    return;
    //! 
    //float relative_scale = (zaxis_offset) / cam_distance;
    float relative_scale = (zaxis_offset) / 541.0f;

    float old_scale = this->getScale().x;

    relative_scale = 1.0f - relative_scale;
    this->setScale(relative_scale, relative_scale, relative_scale);

    float new_width  = w * relative_scale;
    float new_height = h * relative_scale;

    float origin_x = w * old_scale / 2.0f;
    float origin_y = h * old_scale / 2.0f;

    float new_origin_x = new_width / 2.0f;
    float new_origin_y = new_height / 2.0f;

    float offset_x = new_origin_x - origin_x;
    float offset_y = new_origin_y - origin_y;

    float z = this->getPosition().z;
    float offset_z = zaxis_offset - z;

    //this->translate(-offset_x, -offset_y, offset_z, Node::TS_PARENT);

    //this->setPosition(this->getPosition().x,this->getPosition().y, zaxis_offset);
	*/
}

bool PresenteShape::GenerateShapeMesh(ConvertedShapeData& converted_data)
{  
    // generate name
    std::stringstream ss;
    ss << shape->filepath;
    ss << "_id:";
    ss << shape->id;
    ss << "_slide_index:";
    ss << slide_index;
    std::string name = ss.str();

    MeshPtr mesh = MeshManager::getSingleton().createManual(name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    // create a submesh
    SubMesh* sm = mesh->createSubMesh();
    //sm->setMaterialName("Examples/GrassFloor");
    sm->useSharedVertices = false;
    sm->vertexData = OGRE_NEW VertexData();
    sm->vertexData->vertexStart = 0;
    
    int verts_amount = converted_data.GetAllVertsAmount();

    sm->vertexData->vertexCount = verts_amount;

    // specify a vertex format declaration for our mesh: 4 floats for color, 3 floats for position, 3 floats for normal
    // COLOR SHOULD BE FIRST ELEMENT!
    VertexDeclaration* vertex_declaration = sm->vertexData->vertexDeclaration;
    vertex_declaration->addElement(0, 0,                 VET_FLOAT4, VES_DIFFUSE);
    vertex_declaration->addElement(0, sizeof(float) * 4, VET_FLOAT3, VES_POSITION);
    vertex_declaration->addElement(0, sizeof(float) * 7, VET_FLOAT3, VES_NORMAL);


    // create a vertex buffer
    int vertex_size = vertex_declaration->getVertexSize(0);
    HardwareVertexBufferSharedPtr vb = HardwareBufferManager::getSingleton().createVertexBuffer
        (vertex_size, sm->vertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY);

    PresenteShapeVertex* stream = (PresenteShapeVertex*)vb->lock(HardwareBuffer::HBL_DISCARD);  // start filling in vertex data

    // fill data
    int idx = 0;
    FillStream(stream, converted_data, idx);

    vb->unlock();  // commit vertex changes

    sm->vertexData->vertexBufferBinding->setBinding(0, vb);  // bind vertex buffer to our submesh

    // bounds
    Ogre::AxisAlignedBox box;
    box.setMaximum(10000.0f, 10000.0f, 10000.0f);
    box.setMinimum(-10000.0f, -10000.0f, -10000.0f);    
    mesh->_setBounds(box);

    // material
    
    Entity* ent = scene_manager->createEntity(name, name);
    //ent->setMaterialName("Presente3D_VertexColorMaterial");
    ent->setMaterialName("Presente3D_DirectionSpecularLightMaterial");
    ent->setCastShadows(false);
    
    // attach each object separately 
    // scene node required for object space manipulations
    Ogre::SceneNode* node = scene_manager->createSceneNode();
	
    // for proper scale (yet one more patent, lol)
    
    node->attachObject(ent);	
    
    this->addChild(node);

    return true;
}

bool PresenteShape::GenerateShapeTexture(ConvertedShapeData& converted_data)
{
    // generate name
    std::stringstream ss;
    ss << shape->filepath;
    ss << "_id:";
    ss << shape->id;
    ss << "_slide_index:";
    ss << slide_index;

    ss << "_top_texture";
    std::string name = ss.str();
    
    MeshPtr mesh = MeshManager::getSingleton().createManual(name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    // create a submesh
    SubMesh* sm = mesh->createSubMesh();
    sm->useSharedVertices = false;
    sm->vertexData = OGRE_NEW VertexData();
    sm->vertexData->vertexStart = 0;

    // set verts amount from texture data info
    int verts_amount = converted_data.texture_data.verts.size();
    
    
    sm->vertexData->vertexCount = verts_amount;

    //! specify a vertex format declaration for our mesh: 3 floats for position, 3 floats for normal, 2 floats for UV
    VertexDeclaration* vertex_declaration = sm->vertexData->vertexDeclaration;    
    vertex_declaration->addElement(0, 0, VET_FLOAT3, VES_POSITION);
    vertex_declaration->addElement(0, sizeof(float) * 3, VET_FLOAT3, VES_NORMAL);
    vertex_declaration->addElement(0, sizeof(float) * 6, VET_FLOAT2, VES_TEXTURE_COORDINATES);
    

    // create a vertex buffer
    int vertex_size = vertex_declaration->getVertexSize(0);
    HardwareVertexBufferSharedPtr vb = HardwareBufferManager::getSingleton().createVertexBuffer
        (vertex_size, sm->vertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY);

    PresenteTexturedShapeVertex* stream = (PresenteTexturedShapeVertex*)vb->lock(HardwareBuffer::HBL_DISCARD);  // start filling in vertex data

    // fill data
    FillTextureStream(stream, converted_data.texture_data);
    
    vb->unlock();  // commit vertex changes

    sm->vertexData->vertexBufferBinding->setBinding(0, vb);  // bind vertex buffer to our submesh

    // prevent frustum culling
    Ogre::AxisAlignedBox box;
    box.setMaximum(10000.0f, 10000.0f, 10000.0f);
    box.setMinimum(-10000.0f, -10000.0f, -10000.0f);
   // box.setInfinite();
    mesh->_setBounds(box);


    String textured_shape_name = shape->name;
           textured_shape_name += "_texture" ;
    shape_entity = scene_manager->createEntity(name, name);
                
    material_entity = MaterialHelper::Clone("Presente3D_DiffuseTextureMaterial",name);
    material_entity->getTechnique("default")->getPass("default")->getTextureUnitState(0)->setTextureName(shape->filepath);
    material_entity->getTechnique("dimenco")->getPass("default")->getTextureUnitState(0)->setTextureName(shape->filepath);
    
    shape_entity->setMaterial(material_entity);
    shape_entity->setCastShadows(false);

    Ogre::SceneNode* node = scene_manager->createSceneNode();
    node->attachObject(shape_entity);   

    this->addChild(node);

	
    
    return true;
}

void PresenteShape::GenerateTempPlane()
{
    // create temp plane   
    MeshManager::getSingleton().createPlane("ground", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0), 1, 1, 20, 20, true, 1, 6, 6, Vector3::UNIT_Z);	

    Entity* ground = scene_manager->createEntity("Ground", "ground");
    this->attachObject(ground);
}

void PresenteShape::FillStream(PresenteShapeVertex* s, ConvertedShapeData& data, int& idx)
{
    // copy data
    for(size_t i = 0; i < data.verts.size(); i++){
        s[idx].x = data.verts[i].x;
        s[idx].y = data.verts[i].y;
        s[idx].z = data.verts[i].z;
        
        
        data.normals[i].normalize();        
        s[idx].nx = data.normals[i].x;
        s[idx].ny = data.normals[i].y;
        s[idx].nz = data.normals[i].z;
        
                    
        s[idx].a = data.vcolors[i].a;
        s[idx].r = data.vcolors[i].r;
        s[idx].g = data.vcolors[i].g;
        s[idx].b = data.vcolors[i].b;
        
        idx++;
    }

    for(size_t i = 0; i < data.childs.size(); i++){
        FillStream(s, *data.childs[i], idx);
    }
}
void PresenteShape::FillTextureStream(PresenteTexturedShapeVertex* s, shape_texture_data& data)
{      
    for(size_t i = 0; i < data.verts.size(); i++){
        s[i].x = data.verts[i].x;
        s[i].y = data.verts[i].y;
        s[i].z = data.verts[i].z;
        
        data.normals[i].normalize();        
        s[i].nx = data.normals[i].x;
        s[i].ny = data.normals[i].y;
        s[i].nz = data.normals[i].z;
        
        s[i].u = data.u[i];
        s[i].v = data.v[i];        
    }
}

// render interface handelers
bool PresenteShape::frameStarted(const Ogre::FrameEvent& evt)
{	
	return true;
}

bool PresenteShape::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	
	return true;
}

bool PresenteShape::frameEnded(const Ogre::FrameEvent& evt)
{
	return true;
}

bool PresenteShape::eyeLeftFrameStarted(const Ogre::FrameEvent& evt)
{
	//material_entity->getTechnique("default")->getPass("default")->getTextureUnitState(0)->setTextureName(shape->filepath);
    //material_entity->getTechnique("dimenco")->getPass("default")->getTextureUnitState(0)->setTextureName(shape->filepath);
    setImageTexture(true);

	return true;
}

bool PresenteShape::eyeRightFrameStarted(const Ogre::FrameEvent& evt)
{	
    //if (0 < shape->stereopair_path.size())
    //{
	//	material_entity->getTechnique("default")->getPass("default")->getTextureUnitState(0)->setTextureName(shape->stereopair_path);
    //    material_entity->getTechnique("dimenco")->getPass("default")->getTextureUnitState(0)->setTextureName(shape->stereopair_path);
	//}	
    setImageTexture(false);

	return true;
}

void PresenteShape::setImageTexture(bool bLeftEye)
{
    bool bSwap = (-1 == PresenteEngine::getInstance().stereo_camera.GetArgument(StereoCamera::CAMERA_ARGUMENT_LEFT_RIGHT_ORDER)); 

    // Left + No Swap  ===> draw "final eye LEFT"  ===> true
    // Left + Swap     ===> draw "final eye RIGHT" ===> false
    // Right + No Swap ===> draw "final eye RIGHT" ===> false
    // Right + Swap    ===> draw "final eye LEFT"  ===> true
    bool bFinalEyeLeft = bLeftEye ^ bSwap;

    std::string strImageFileName;

    if (true == bFinalEyeLeft)
    {
        strImageFileName = shape->filepath;
    }
    else
    {
        if (0 < shape->stereopair_path.size())
        {
            strImageFileName = shape->stereopair_path;
        }
        else
        {
            // Draw nothing if there is no stereopair available
            return;
        }
    }

    material_entity->getTechnique("default")->getPass("default")->getTextureUnitState(0)->setTextureName(strImageFileName);
    material_entity->getTechnique("dimenco")->getPass("default")->getTextureUnitState(0)->setTextureName(strImageFileName);

    return;
}