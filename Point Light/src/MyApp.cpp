/*
 * MyApp.cpp
 *
 *  Created on: 10 nov. 2019
 *      Author: joe
 */

#include "MyApp.h"

MyApp::MyApp() {
	_root=nullptr;
	_sceneManager=nullptr;
	_framelistener=nullptr;
}

MyApp::~MyApp() {
	delete _sceneManager;
	delete _framelistener;
	delete _root;
}

int MyApp::start() {
	_root = new Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");
	if (! _root->restoreConfig()) {
		_root->showConfigDialog();
		_root->saveConfig();
	}

	Ogre::RenderWindow* window = _root->initialise(true, "Time for Action");
	_sceneManager = _root->createSceneManager(Ogre::ST_GENERIC); // SceneTypeMask typeMask,
	_sceneManager->setAmbientLight(Ogre::ColourValue(1,1,1));

	Ogre::Camera* cam = _sceneManager->createCamera("MainCamera");
	cam->setPosition(Ogre::Vector3(0,60,60));
	cam->lookAt(Ogre::Vector3(0,0,0));
	cam->setNearClipDistance(5);
	cam->setFarClipDistance(10000);

	Ogre::Viewport* viewport = window->addViewport(cam);
	viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
	double width=viewport->getActualWidth();
	double height=viewport->getActualHeight();
	cam->setAspectRatio(width/height);

	loadResources();
	createScene();

	_framelistener = new MyFrameListener(window, cam, _sceneManager);
	_root->addFrameListener(_framelistener);

	_root->startRendering();

	return 0;
}

void MyApp::loadResources() {
	Ogre::ConfigFile cf;
	cf.load("resource.cfg");

	Ogre::ConfigFile::SectionIterator sI = cf.getSectionIterator();
	Ogre::String sectionstr, typestr, datastr;

	while(sI.hasMoreElements()) {
		sectionstr = sI.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = sI.getNext();

		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i=settings->begin(); i!=settings->end(); ++i) {
			typestr=i->first; datastr=i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(datastr, typestr, sectionstr);
		}
	}
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void MyApp::createScene() {

	// Plano del suelo y luz direccional
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -10);
	Ogre::MeshManager::getSingleton().createPlane("plane",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
			1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* ent = _sceneManager->createEntity("LightPlaneEntity", "plane");

	// crea un nodo al que se le asigna un nombre automáticamente y se añade una entidad
	_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
	// vamos a obtener el nodo del
	Ogre::LogManager::getSingletonPtr()->logMessage(ent->getParentNode()->getName());

	ent->setMaterialName("Examples/BeachStones");


	Ogre::SceneNode* node = _sceneManager->createSceneNode("Node1");
	_sceneManager->getRootSceneNode()->addChild(node);

	// Punto de Luz
	Ogre::Light* light1 = _sceneManager->createLight("Light1");
	light1->setType(Ogre::Light::LT_POINT);
	light1->setPosition(0,20,0);
	light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
	Ogre::Entity* LightEnt = _sceneManager->createEntity("MyEntity", "Sphere.mesh");
	Ogre::SceneNode* node3 = node->createChildSceneNode("node3");
	node3->setScale(0.8f, 0.8f,0.8f);
	node3->setPosition(0,20,0);
	node3->attachObject(LightEnt);

	Ogre::Light* light2 = _sceneManager->createLight("Light2");
	light2->setType(Ogre::Light::LT_POINT);
	light2->setPosition(20,20,20);
	light2->setDiffuseColour(1.0f, 0.0f, 0.0f);
	Ogre::Entity* LightEnt2 = _sceneManager->createEntity("MyEntity2", "Sphere.mesh");
	Ogre::SceneNode* node4 = node->createChildSceneNode("node4");
	node4->setPosition(20, 20, 20);
	node4->attachObject(LightEnt2);

	Ogre::Entity* ent1 = _sceneManager->createEntity("MiBote", "Spray.mesh");
	Ogre::SceneNode* node5 = _sceneManager->getRootSceneNode()->createChildSceneNode("node5");
	node5->setPosition(0.0f, 0.0f, 15.0f);
	node5->pitch(Ogre::Degree(90));
	node5->roll(Ogre::Degree(-45));
	node5->attachObject(ent1);


	// _sceneManager->setDisplaySceneNodes(true);
}


