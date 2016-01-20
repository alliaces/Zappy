#include "Map.h"


Map::Map(Ogre::SceneManager* mSceneMgr, int x, int y)
{
	sizex = x;
	sizey = y;
	this->mSceneMgr = mSceneMgr;
	Ogre::Light *light = mSceneMgr->createLight("lumiere1");
	light->setType(Ogre::Light::LT_POINT);
	light->setDirection(x / 2, 0, y / 2);
	light->setDiffuseColour(1, 1, 1);
	light->setSpecularColour(1, 1, 1);
	light->setPosition(x + 10, 20, -10);
	light->setCastShadows(true);
	Ogre::Plane plan(Ogre::Vector3::UNIT_Y, 0);
	mapNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();

	Ogre::Entity *plateau = mSceneMgr->createEntity("Cube.mesh");
	Ogre::SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
	node->attachObject(plateau);
	node->setPosition(Ogre::Vector3(x / 2 - 0.5f, -0.051f, y / 2 - 0.5f));
	node->setScale(0.5f * x + 0.1f, 0.05f, 0.5f * y + 0.1f);
	plateau->setMaterialName("Bois");

	Ogre::MeshManager::getSingleton().createPlane("sol", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plan, x, y, 5, 5, true, 1, 1, 1, Ogre::Vector3::UNIT_Z);
	
	createTexture();
	Ogre::Entity *ent = mSceneMgr->createEntity("sol");
	ent->setMaterialName("GroundMaterial");
	Ogre::SceneNode* caseNode = mapNode->createChildSceneNode();
	caseNode->attachObject(ent);
	caseNode->setPosition(x / 2 - 0.5, 0, y / 2 - 0.5);
	int i = 0;
	/*while (i != x)
	{
		int w = 0;
		while (w != y)
		{
			Ogre::Entity *ent = mSceneMgr->createEntity("sol");
			if ((i + w) % 2 == 0)
				ent->setMaterialName("Tsol");
			else
				ent->setMaterialName("Tsol2");
			ent->setCastShadows(false);
			Ogre::SceneNode* caseNode = mapNode->createChildSceneNode();
			caseNode->attachObject(ent);
			caseNode->setPosition(i, 0, w);
			w++;
		}
		i++;
	}*/
	content = new char**[x];
	i = 0;
	while (i != x)
	{
		content[i] = new char*[y];
		int j = 0;
		while (j != y)
		{
			content[i][j] = new char[7];
			int u = 0;
			while (u != 7)
			{
				content[i][j][u] = 0;
				u++;
			}
			j++;
		}
		i++;
	}
	contentNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
}

void Map::createTexture()
{
	Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().createManual(
		"GroundTexture",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::TEX_TYPE_2D,
		sizex * COEF, sizey * COEF,
		0,
		Ogre::PF_BYTE_BGRA,
		Ogre::TU_DEFAULT);
	Ogre::HardwarePixelBufferSharedPtr pixelBuffer = texture->getBuffer();
	pixelBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL);
	const Ogre::PixelBox& pixelBox = pixelBuffer->getCurrentLock();

	Ogre::uint8* pDest = static_cast<Ogre::uint8*>(pixelBox.data);

	for (size_t j = 0; j < sizex * COEF; j++)
	{
		for (size_t i = 0; i < sizey * COEF; i++)
		{
			int abs = floor((i / COEF + j / COEF));
			//MessageBoxA(NULL, ("absolue of :" + std::to_string(i + j) + " : " + std::to_string(abs)).c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
			if (abs % 2 == 0)
			{
				*pDest++ = 255; // B
				*pDest++ = 255; // G
				*pDest++ = 255; // R
				*pDest++ = 255; // A
			}
			else
			{
				*pDest++ = 0; // B
				*pDest++ = 0; // G
				*pDest++ = 0; // R
				*pDest++ = 255; // A
			}
		}

		pDest += pixelBox.getRowSkip() * Ogre::PixelUtil::getNumElemBytes(pixelBox.format);
	}

	pixelBuffer->unlock();

	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(
		"GroundMaterial",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	material->getTechnique(0)->getPass(0)->createTextureUnitState("GroundTexture");
	material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
}

void Map::updateMap()
{
	contentNode->removeAllChildren();
	int i = 0;
	while (i != sizex)
	{
		int j = 0;
		while (j != sizey)
		{
			if (content[i][j][0] != 0)
			{
				Ogre::Entity *cristal = mSceneMgr->createEntity("Cristal.mesh");
				cristal->getAnimationState("Action")->setLoop(true);
				cristal->getAnimationState("Action")->setEnabled(true);
				//cristal->getAnimationState("Action")->setTimePosition((rand() + 1) % 25);
				anims.push_back(cristal->getAnimationState("Action"));
				cristal->setMaterialName("Tres1");
				Ogre::SceneNode *node = contentNode->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
				node->attachObject(cristal);
				node->setPosition(Ogre::Vector3(i, 0.1f, j));
				node->setScale(Ogre::Vector3(0.05f, 0.05f, 0.05f));
			}
			if (content[i][j][1] != 0)
			{
				Ogre::Entity *cristal = mSceneMgr->createEntity("Cristal.mesh");
				cristal->getAnimationState("Action")->setLoop(true);
				cristal->getAnimationState("Action")->setEnabled(true);
				//cristal->getAnimationState("Action")->setTimePosition((rand() + 1) % 25);
				anims.push_back(cristal->getAnimationState("Action"));
				cristal->setMaterialName("Tres2");
				Ogre::SceneNode *node = contentNode->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
				node->attachObject(cristal);
				node->setPosition(Ogre::Vector3(i - 0.3f, 0.1f, j - 0.3f));
				node->setScale(Ogre::Vector3(0.05f, 0.05f, 0.05f));
			}
			if (content[i][j][2] != 0)
			{
				Ogre::Entity *cristal = mSceneMgr->createEntity("Cristal.mesh");
				cristal->getAnimationState("Action")->setLoop(true);
				cristal->getAnimationState("Action")->setEnabled(true);
				//cristal->getAnimationState("Action")->setTimePosition((rand() + 1) % 25);
				anims.push_back(cristal->getAnimationState("Action"));
				cristal->setMaterialName("Tres3");
				Ogre::SceneNode *node = contentNode->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
				node->attachObject(cristal);
				node->setPosition(Ogre::Vector3(i + 0.3f, 0.1f, j - 0.3f));
				node->setScale(Ogre::Vector3(0.05f, 0.05f, 0.05f));
			}
			if (content[i][j][3] != 0)
			{
				Ogre::Entity *cristal = mSceneMgr->createEntity("Cristal.mesh");
				cristal->getAnimationState("Action")->setLoop(true);
				cristal->getAnimationState("Action")->setEnabled(true);
				//cristal->getAnimationState("Action")->setTimePosition((rand() + 1) % 25);
				anims.push_back(cristal->getAnimationState("Action"));
				cristal->setMaterialName("Tres4");
				Ogre::SceneNode *node = contentNode->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
				node->attachObject(cristal);
				node->setPosition(Ogre::Vector3(i - 0.3f, 0.1f, j));
				node->setScale(Ogre::Vector3(0.05f, 0.05f, 0.05f));
			}
			if (content[i][j][4] != 0)
			{
				Ogre::Entity *cristal = mSceneMgr->createEntity("Cristal.mesh");
				cristal->getAnimationState("Action")->setLoop(true);
				cristal->getAnimationState("Action")->setEnabled(true);
				//cristal->getAnimationState("Action")->setTimePosition((rand() + 1) % 25);
				anims.push_back(cristal->getAnimationState("Action"));
				cristal->setMaterialName("Tres5");
				Ogre::SceneNode *node = contentNode->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
				node->attachObject(cristal);
				node->setPosition(Ogre::Vector3(i + 0.3f, 0.1f, j));
				node->setScale(Ogre::Vector3(0.05f, 0.05f, 0.05f));
			}
			if (content[i][j][5] != 0)
			{
				Ogre::Entity *cristal = mSceneMgr->createEntity("Cristal.mesh");
				cristal->getAnimationState("Action")->setLoop(true);
				cristal->getAnimationState("Action")->setEnabled(true);
				//cristal->getAnimationState("Action")->setTimePosition((rand() + 1) % 25);
				anims.push_back(cristal->getAnimationState("Action"));
				cristal->setMaterialName("Tres6");
				Ogre::SceneNode *node = contentNode->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
				node->attachObject(cristal);
				node->setPosition(Ogre::Vector3(i - 0.3f, 0.1f, j + 0.3f));
				node->setScale(Ogre::Vector3(0.05f, 0.05f, 0.05f));
			}
			if (content[i][j][6] != 0)
			{
				Ogre::Entity *cristal = mSceneMgr->createEntity("Cristal.mesh");
				cristal->getAnimationState("Action")->setLoop(true);
				cristal->getAnimationState("Action")->setEnabled(true);
				//cristal->getAnimationState("Action")->setTimePosition((rand() + 1) % 25);
				anims.push_back(cristal->getAnimationState("Action"));
				cristal->setMaterialName("Tres7");
				Ogre::SceneNode *node = contentNode->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
				node->attachObject(cristal);
				node->setPosition(Ogre::Vector3(i, 0.1f, j + 0.3f));
				node->setScale(Ogre::Vector3(0.05f, 0.05f, 0.05f));
			}
			j++;
		}
		i++;
	}
}

void Map::fillMap(int x, int y, std::vector<int> content)
{
	int i = 0;
	while (i != 7)
	{
		this->content[x][y][i] = content[i];
		i++;
	}
			if (this->content[x][y][0] != 0)
			{
				Ogre::Entity *cristal = mSceneMgr->createEntity("Cristal.mesh");
				cristal->getAnimationState("Action")->setLoop(true);
				cristal->getAnimationState("Action")->setEnabled(true);
				//cristal->getAnimationState("Action")->setTimePosition((rand() + 1) % 25);
				anims.push_back(cristal->getAnimationState("Action"));
				cristal->setMaterialName("Tres1");
				Ogre::SceneNode *node = contentNode->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
				node->attachObject(cristal);
				node->setPosition(Ogre::Vector3(x, 0.1f, y));
				node->setScale(Ogre::Vector3(0.05f, 0.05f, 0.05f));
			}
			if (this->content[x][y][1] != 0)
			{
				Ogre::Entity *cristal = mSceneMgr->createEntity("Cristal.mesh");
				cristal->getAnimationState("Action")->setLoop(true);
				cristal->getAnimationState("Action")->setEnabled(true);
				//cristal->getAnimationState("Action")->setTimePosition((rand() + 1) % 25);
				anims.push_back(cristal->getAnimationState("Action"));
				cristal->setMaterialName("Tres2");
				Ogre::SceneNode *node = contentNode->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
				node->attachObject(cristal);
				node->setPosition(Ogre::Vector3(x - 0.3f, 0.1f, y - 0.3f));
				node->setScale(Ogre::Vector3(0.05f, 0.05f, 0.05f));
			}
			if (this->content[x][y][2] != 0)
			{
				Ogre::Entity *cristal = mSceneMgr->createEntity("Cristal.mesh");
				cristal->getAnimationState("Action")->setLoop(true);
				cristal->getAnimationState("Action")->setEnabled(true);
				//cristal->getAnimationState("Action")->setTimePosition((rand() + 1) % 25);
				anims.push_back(cristal->getAnimationState("Action"));
				cristal->setMaterialName("Tres3");
				Ogre::SceneNode *node = contentNode->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
				node->attachObject(cristal);
				node->setPosition(Ogre::Vector3(x + 0.3f, 0.1f, y - 0.3f));
				node->setScale(Ogre::Vector3(0.05f, 0.05f, 0.05f));
			}
			if (this->content[x][y][3] != 0)
			{
				Ogre::Entity *cristal = mSceneMgr->createEntity("Cristal.mesh");
				cristal->getAnimationState("Action")->setLoop(true);
				cristal->getAnimationState("Action")->setEnabled(true);
				//cristal->getAnimationState("Action")->setTimePosition((rand() + 1) % 25);
				anims.push_back(cristal->getAnimationState("Action"));
				cristal->setMaterialName("Tres4");
				Ogre::SceneNode *node = contentNode->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
				node->attachObject(cristal);
				node->setPosition(Ogre::Vector3(x - 0.3f, 0.1f, y));
				node->setScale(Ogre::Vector3(0.05f, 0.05f, 0.05f));
			}
			if (this->content[x][y][4] != 0)
			{
				Ogre::Entity *cristal = mSceneMgr->createEntity("Cristal.mesh");
				cristal->getAnimationState("Action")->setLoop(true);
				cristal->getAnimationState("Action")->setEnabled(true);
				//cristal->getAnimationState("Action")->setTimePosition((rand() + 1) % 25);
				anims.push_back(cristal->getAnimationState("Action"));
				cristal->setMaterialName("Tres5");
				Ogre::SceneNode *node = contentNode->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
				node->attachObject(cristal);
				node->setPosition(Ogre::Vector3(x + 0.3f, 0.1f, y));
				node->setScale(Ogre::Vector3(0.05f, 0.05f, 0.05f));
			}
			if (this->content[x][y][5] != 0)
			{
				Ogre::Entity *cristal = mSceneMgr->createEntity("Cristal.mesh");
				cristal->getAnimationState("Action")->setLoop(true);
				cristal->getAnimationState("Action")->setEnabled(true);
				//cristal->getAnimationState("Action")->setTimePosition((rand() + 1) % 25);
				anims.push_back(cristal->getAnimationState("Action"));
				cristal->setMaterialName("Tres6");
				Ogre::SceneNode *node = contentNode->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
				node->attachObject(cristal);
				node->setPosition(Ogre::Vector3(x - 0.3f, 0.1f, y + 0.3f));
				node->setScale(Ogre::Vector3(0.05f, 0.05f, 0.05f));
			}
			if (this->content[x][y][6] != 0)
			{
				Ogre::Entity *cristal = mSceneMgr->createEntity("Cristal.mesh");
				cristal->getAnimationState("Action")->setLoop(true);
				cristal->getAnimationState("Action")->setEnabled(true);
				//cristal->getAnimationState("Action")->setTimePosition((rand() + 1) % 25);
				anims.push_back(cristal->getAnimationState("Action"));
				cristal->setMaterialName("Tres7");
				Ogre::SceneNode *node = contentNode->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
				node->attachObject(cristal);
				node->setPosition(Ogre::Vector3(x, 0.1f, y + 0.3f));
				node->setScale(Ogre::Vector3(0.05f, 0.05f, 0.05f));
			}
//	updateMap();
}

void Map::updateMap(Ogre::Real time)
{
	int i = 0;
	if (!anims.empty())
	{
		while (i < anims.size())
		{
			anims[i]->addTime(time);
			i++;
		}
	}
}


Map::~Map()
{

}
