/*
 * MyFrameListener.cpp
 *
 *  Created on: 10 nov. 2019
 *      Author: joe
 */
#include "MyFrameListener.h"

MyFrameListener::MyFrameListener(Ogre::RenderWindow* win, Ogre::Camera* cam, Ogre::SceneManager *sM) {
  OIS::ParamList param;
  size_t windowHandle;  std::ostringstream wHandleStr;

  _camera = cam;  _win = win; _node = NULL; _sceneManager = sM;

  _win->getCustomAttribute("WINDOW", &windowHandle);
  wHandleStr << windowHandle;
  param.insert(std::make_pair("WINDOW", wHandleStr.str()));

  _inputManager = OIS::InputManager::createInputSystem(param);
  _keyboard = static_cast<OIS::Keyboard*>
    (_inputManager->createInputObject(OIS::OISKeyboard, false));
  _mouse = static_cast<OIS::Mouse*>
    (_inputManager->createInputObject(OIS::OISMouse, false));

  // capturamos el ancho de pantalla
  _mouse->getMouseState().width= _win->getWidth();
  _mouse->getMouseState().height= _win->getHeight();
}

MyFrameListener::~MyFrameListener() {
  _inputManager->destroyInputObject(_keyboard);
  _inputManager->destroyInputObject(_mouse);
  OIS::InputManager::destroyInputSystem(_inputManager);
}

bool MyFrameListener::frameStarted(const Ogre::FrameEvent& evt) {
  Ogre::Vector3 vt(0,0,0);     Ogre::Real tSpeed = 20.0;
  Ogre::Real r = 0;
  Ogre::Real deltaT = evt.timeSinceLastFrame;

  // vamos a mover la cámara
  _keyboard->capture();
  if(_keyboard->isKeyDown(OIS::KC_ESCAPE)) return false;
  if(_keyboard->isKeyDown(OIS::KC_UP))    vt+=Ogre::Vector3(0,0,-1);
  if(_keyboard->isKeyDown(OIS::KC_DOWN))  vt+=Ogre::Vector3(0,0,1);
  if(_keyboard->isKeyDown(OIS::KC_LEFT))  vt+=Ogre::Vector3(-1,0,0);
  if(_keyboard->isKeyDown(OIS::KC_RIGHT)) vt+=Ogre::Vector3(1,0,0);
  _camera->moveRelative(vt * deltaT * tSpeed);

  if(_keyboard->isKeyDown(OIS::KC_R))
	  r=180;
  _node = _sceneManager->getSceneNode("Node1");
  _node->yaw(Ogre::Degree(r * deltaT));

  _mouse->capture();
  float rotx = _mouse->getMouseState().X.rel * deltaT * -1;
  float roty = _mouse->getMouseState().Y.rel * deltaT * -1;
  _camera->yaw(Ogre::Radian(rotx));
  _camera->pitch(Ogre::Radian(roty));

  return true;
}




