#ifndef SFAPP_H
#define SFAPP_H

#include <memory>   // Pull in std::shared_ptr
#include <iostream> // Pull in std::cerr, std::endl
#include <list>     // Pull in list
#include <sstream>

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFAsset.h"

/**
 * Represents the StarshipFontana application.  It has responsibilities for
 * * Creating and destroying the app window
 * * Processing game events
 */
class SFApp {
public:
  SFApp(std::shared_ptr<SFWindow>);
  virtual ~SFApp();
  void    OnEvent(SFEvent &);
  int     OnExecute();
  void    OnUpdateWorld();
  void    OnRender();
  void    AddScore(int);
  void    FireProjectile();
  void 	  Powerup();
private:
  bool                    is_running;

  shared_ptr<SFWindow>       sf_window;

  shared_ptr<SFAsset>        player;
  shared_ptr<SFBoundingBox>  app_box;
  list<shared_ptr<SFAsset> > projectiles;
  list<shared_ptr<SFAsset> > aliens;
  list<shared_ptr<SFAsset> > coins;
  list<shared_ptr<SFAsset> > walls;
  list<shared_ptr<SFAsset> > aliens2;
  list<shared_ptr<SFAsset> > aliens3;
  list<shared_ptr<SFAsset> > powerup;
  list<shared_ptr<SFAsset> > box;
  
  int fire;
  bool fire_down;
  bool up;
  bool down;
  bool left;
  bool right;
  int timer;	
  int score;
  int endlevel;
};
#endif
