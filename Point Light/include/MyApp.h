/*
 * MyApp.h
 *
 *  Created on: 10 nov. 2019
 *      Author: joe
 */

#ifndef INCLUDE_MYAPP_H_
#define INCLUDE_MYAPP_H_

#include <Ogre.h>
#include "MyFrameListener.h"

class MyApp {

private:
  Ogre::SceneManager* _sceneManager;
  Ogre::Root* _root;
  MyFrameListener* _framelistener;

public:
  MyApp();
  ~MyApp();
  int start();
  void loadResources();
  void createScene();
};
#endif /* INCLUDE_MYAPP_H_ */
