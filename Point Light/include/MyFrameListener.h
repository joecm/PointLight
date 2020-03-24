/*
 * MyFrameListener.h
 *
 *  Created on: 10 nov. 2019
 *      Author: joe
 */

#ifndef INCLUDE_MYFRAMELISTENER_H_
#define INCLUDE_MYFRAMELISTENER_H_

#include <Ogre.h>
#include <OIS/OIS.h>

class MyFrameListener : public Ogre::FrameListener {
private:
  Ogre::SceneManager* _sceneManager;
  OIS::InputManager* _inputManager;
  OIS::Keyboard* _keyboard;
  OIS::Mouse* _mouse;
  Ogre::Camera* _camera;
  Ogre::SceneNode *_node;
  Ogre::RenderWindow* _win;

public:
  MyFrameListener(Ogre::RenderWindow* win, Ogre::Camera* camera, Ogre::SceneManager* sM);
  ~MyFrameListener();
  bool frameStarted(const Ogre::FrameEvent& evt);
};

#endif /* INCLUDE_MYFRAMELISTENER_H_ */
