#ifndef PresenteSlide_header
#define PresenteSlide_header

/* 
* File: PresenteSlide.h 
* Created by: Vitaly V. Boiko
* Short Description: 
* 
*/

#include "Ogre.h"
#include "data\SlideData.h"

#include <string>


class PresenteShape;

typedef std::vector<PresenteShape*> ShapesContainer;

class PresenteSlide: public Ogre::SceneNode
{
public:
    PresenteSlide(Ogre::SceneManager* scm, std::string& name);

    bool FillData(SlideData& data);
    bool Generate();

    void RecalculateScale(float cam_distance);

    void SetHeight(float v){slide_height = v;}

	const std::string& getBackgroundImage() const
	{ return slide->background_file; }

    ShapesContainer shapes;

	Ogre::Vector3 GetCameraPosition(){return cam_pos;}
	Ogre::Quaternion GetCameraOrientation(){return cam_ori;}

	void SetCameraPosition(Ogre::Vector3 p){cam_pos = p;}
	void SetCameraOrientation(Ogre::Quaternion o){cam_ori = o;}

	float GetFocusDistance(){return focusDistance;}
	float GetEyeSeparation(){return eyeSeparation;}

	void SetFocusDistance(float v){focusDistance = v;}
	void SetEyeSeparation(float v){eyeSeparation = v;}

    void SetEmpiricalNearClippingPlane(float d){empirical_nearClippingPlane = d;}
    float GetEmpiricalNearClippingPlane(){return empirical_nearClippingPlane;}

    void SetScreenHeight(float d){screen_height = d;}
    float GetScreenHeight(){return screen_height;}

	void SetScreenDistance(float d){screen_distance = d;}
	float GetScreenDistance(){return screen_distance;}

	void SetPopOutDistance(float d){popout_distance = d;}
	float GetPopOutDistance(){return popout_distance;}

	void SetPopInDistance(float d){popIn_distance = d;}
	float GetPopInDistance(){return popIn_distance;}

	SlideData* GetSlideData(){return slide;};
private:

	Ogre::SceneNode* getBackgroundNode(SlideData& data);

    SlideData* slide;

    float slide_height;  

	Ogre::Vector3 cam_pos;
	Ogre::Quaternion cam_ori;    

    float focusDistance;
    float eyeSeparation;

    float empirical_nearClippingPlane;
    float screen_height;
	float screen_distance;
	float popout_distance;
	float popIn_distance;
};

#endif /* PresenteSlide_header */
