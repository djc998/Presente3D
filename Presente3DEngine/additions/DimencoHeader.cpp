#include "stdafx.h"

#include "DimencoHeader.h"

#include "core/PresenteEngine.h"
#include "material/MaterialHelper.h"


DimencoHeader::DimencoHeader(Ogre::SceneManager* scene_mananger) :
    Ogre::SceneNode(scene_mananger, PresenteDimencoHeader),
    m_pSceneManager(scene_mananger)
{
    return;
};

DimencoHeader::~DimencoHeader()
{

}

bool DimencoHeader::FillData()
{
    return true;
}

bool DimencoHeader::Generate()
{
    char tmpstr[1024] = {0};

    // Create background material
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingletonPtr()->getByName("Presente3D_DimencoHeaderMaterial");

    // Create background rectangle covering the whole screen
    Ogre::Rectangle2D* rect = new Ogre::Rectangle2D(true);
    rect->setCorners(-1.0, 1.0, 1.0, -1.0);
    rect->setMaterial("Presente3D_DimencoHeaderMaterial");

    // Render the header in the last turn
    rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);

    // Hacky, but we need to set the bounding box to something big
    rect->setBoundingBox(Ogre::AxisAlignedBox(-100000.0*Ogre::Vector3::UNIT_SCALE, 100000.0*Ogre::Vector3::UNIT_SCALE));

    // Addting to the root node...
    this->attachObject(rect);
    m_pSceneManager->getRootSceneNode()->addChild(this);

    // By default we are invisible
    this->setVisible(false);

    return true;
}

void DimencoHeader::RecalculateScale(float cam_distance)
{
    return;
}
