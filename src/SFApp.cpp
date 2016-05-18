#include "SFApp.h"
#include <unistd.h>


SFApp::SFApp(std::shared_ptr<SFWindow> window) : fire(0),fire_down(false),up(false),down(false),left(false),right(false), is_running(true),score(0),endlevel(0), sf_window(window) {
  int canvas_w, canvas_h;
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);

  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);
  player  = make_shared<SFAsset>(SFASSET_PLAYER, sf_window);
  auto player_pos = Point2(canvas_w/2, 22);
  player->SetPosition(player_pos);

cout << "Get 400 Or More Points To Win!"<<endl;

//first for of aliens

  const int number_of_aliens = 5;
  for(int i=0; i<number_of_aliens; i++) {
    // place an alien at width/number_of_aliens * i
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN, sf_window);
    auto pos   = Point2((canvas_w/number_of_aliens) * i+70, 400.0f);
    alien->SetPosition(pos);
    aliens.push_back(alien);
   }

//second row of aliens

  const int number_of_aliens_2 = 4;
  for(int i=0; i<number_of_aliens_2; i++) {
    // place an alien at width/number_of_aliens * i
    auto alien2 = make_shared<SFAsset>(SFASSET_ALIEN2, sf_window);
    auto pos   = Point2((canvas_w/number_of_aliens_2) * i+90, 500.0f);
    alien2->SetPosition(pos);
    aliens2.push_back(alien2);
   }

//thrid row of aliens

   const int number_of_aliens3 = 5;
  for(int i=0; i<number_of_aliens3; i++) {
    // place an alien at width/number_of_aliens * i
    auto alien3 = make_shared<SFAsset>(SFASSET_ALIEN3, sf_window);
    auto pos   = Point2((canvas_w/number_of_aliens3) * i+70, 600.0f);
    alien3->SetPosition(pos);
    aliens3.push_back(alien3);
   }

//fourth row of aliens

  for(int i=0; i<number_of_aliens_2; i++) {
    // place an alien at width/number_of_aliens * i
    auto alien2 = make_shared<SFAsset>(SFASSET_ALIEN2, sf_window);
    auto pos   = Point2((canvas_w/number_of_aliens_2) * i+90, 300.0f);
    alien2->SetPosition(pos);
    aliens2.push_back(alien2);
   }

    auto coin = make_shared<SFAsset>(SFASSET_COIN, sf_window);
    auto pos  = Point2((canvas_w/4), 100);
    coin->SetPosition(pos);
    coins.push_back(coin);

  const int number_of_walls = 3;
  for(int a=0; a <number_of_walls; a++) {
  auto wall = make_shared<SFAsset>(SFASSET_WALL, sf_window);
  auto posw = Point2((canvas_w/3)*a+120, 170);
  wall->SetPosition(posw);
  walls.push_back(wall);
    }
	

}

SFApp::~SFApp() {
}

/**
 * Handle all events that come from SDL.
 * These are timer or keyboard events.
 */
void SFApp::OnEvent(SFEvent& event) {
  SFEVENT the_event = event.GetCode();
  switch (the_event) {
  case SFEVENT_QUIT:
    is_running = false;
    break;
  case SFEVENT_UPDATE:
    OnUpdateWorld();
    OnRender();
    break;
  case SFEVENT_PLAYER_LEFT_KEYDOWN:
    left = true;
    break;
  case SFEVENT_PLAYER_RIGHT_KEYDOWN:
    right = true;
    break;
  case SFEVENT_PLAYER_UP_KEYDOWN:
    up = true;
    break;
  case SFEVENT_PLAYER_DOWN_KEYDOWN:
    down = true;
    break;
  case SFEVENT_FIRE_KEYDOWN:
    fire_down = true;
    break;
  case SFEVENT_PLAYER_LEFT_KEYUP:
    left = false;
    break;
  case SFEVENT_PLAYER_RIGHT_KEYUP:
    right = false;
    break;
  case SFEVENT_PLAYER_UP_KEYUP:
    up = false;
    break;
  case SFEVENT_PLAYER_DOWN_KEYUP:
    down = false;
    break;
  case SFEVENT_FIRE_KEYUP:
    fire_down = false;
    break;
  }
}

int SFApp::OnExecute() {
  // Execute the app
  SDL_Event event;
  while (SDL_WaitEvent(&event) && is_running) {
    // wrap an SDL_Event with our SFEvent
    SFEvent sfevent((const SDL_Event) event);
    // handle our SFEvent
    OnEvent(sfevent);
  }
}

void SFApp::OnUpdateWorld() {


  //Player Movement & Collision
  if (up) player->GoNorth();
for(auto w: walls)
      {
       if (player->CollidesWith(w))
         {
	   player->GoSouth();
	 }
	}
  if (down) player->GoSouth();
for(auto w: walls)
      {
       if (player->CollidesWith(w))
         {
	   player->GoNorth();
	 }
	}
  if (right) player->GoEast();
for(auto w: walls)
      {
       if (player->CollidesWith(w))
         {
	   player->GoWest();
	 }
	}
  if (left) player->GoWest();
for(auto w: walls)
      {
       if (player->CollidesWith(w))
         {
	   player->GoEast();
	 }
	}

 
//projectile delay
  timer++;
  if (timer > 20)
 {
 if (fire_down){
  fire ++;
  FireProjectile();
  timer=0;
  }
 }
  
  // Update projectile positions
  for(auto p: projectiles) {
    p->GoNorth();
  }

// Player Collision With Coin
for(auto c: coins){
    c->GoSouth();
    if(player->CollidesWith(c)){
    c->HandleCollision();
    cout<<"Item Get! Plus 10 Points"<<endl;
    AddScore(10);	
}
}
 
  // Update Random Enemy Movement first enemy

  for(auto a : aliens) {
  int Randnum = rand()%100;

  if (Randnum == 5) {
a->GoEast();
}
if (Randnum == 2){
a->GoWest();
}

}
 // Update Random Enemy Movement Second enemy

for(auto a2 : aliens2){
int Randnum = rand()%100;

  if (Randnum == 5) {
a2->GoEast();
}
if (Randnum == 2){
a2->GoWest();
}

}


 // Update Random Enemy Movement Third enemy
for(auto a3 : aliens3){
int Randnum = rand()%100;

  if (Randnum == 5) {
a3->GoEast();
}
if (Randnum == 2){
a3->GoWest();
}

}


 // Detect collisions with first enemy
  for(auto p : projectiles) {
    for(auto a : aliens) {
      if(p->CollidesWith(a) ) {
        p->HandleCollision();
        a->HandleCollision();
	Powerup();
	}
      }
  }


// Detect collisions with second enemy
  for(auto p : projectiles) {
    for(auto a2 : aliens2) {
      if(p->CollidesWith(a2) ) {
	p->HandleCollision();
	//takes two health away from enemy
	a2->EnemyHealth(2);
	Powerup();
	
      }
  }

}

// Detect collisions with Third enemy
  for(auto p : projectiles) {
    for(auto a3 : aliens3) {
      if(p->CollidesWith(a3) ) {
	p->HandleCollision();
	//takes one health away from enemy
	a3->EnemyHealth(1);
	Powerup();
	
      }
  }

}

// Detect collisions with walls
  for(auto p : projectiles) {
    for(auto w : walls) {
      if(p->CollidesWith(w) ) {
        p->HandleCollision();
	w->WallHealth(1);
      }
  }
}
 
  // remove dead aliens 1 (Row 1)  (the long way)
  list<shared_ptr<SFAsset>> tmp;
  for(auto a : aliens) {
    if(a->IsAlive()) {
      tmp.push_back(a);
    } else {
	AddScore(10);
	Powerup();
	}
  }
  aliens.clear();
  aliens = list<shared_ptr<SFAsset>>(tmp);

  // remove dead aliens (Row 2) (the long way)
	list<shared_ptr<SFAsset>> tmp_3;
  	for(auto a2 : aliens2) {
    	if(a2->IsAlive()) {
      	tmp_3.push_back(a2);
    	} else {
	AddScore(20);
	Powerup();
	  }
  }
  aliens2.clear();
  aliens2 = list<shared_ptr<SFAsset>>(tmp_3);

// remove dead aliens (Row 3) (the long way)
	list<shared_ptr<SFAsset>> tmp_4;
  	for(auto a3 : aliens3) {
    	if(a3->IsAlive()) {
      	tmp_4.push_back(a3);
    	} else {
	AddScore(40);
	Powerup();
	  }
  }
  aliens3.clear();
  aliens3 = list<shared_ptr<SFAsset>>(tmp_4);
	
 // remove projectiles
  list<shared_ptr<SFAsset>> tmp_proj;
  for(auto p : projectiles) {
    if(p->IsAlive()) {
      tmp_proj.push_back(p);
    }
  }
  projectiles.clear();
  projectiles = list<shared_ptr<SFAsset>>(tmp_proj);

//remove walls
tmp.clear();
list<shared_ptr<SFAsset>> tmp_2;
  for(auto w : walls) {
    if(w->IsAlive()) {
      tmp_2.push_back(w);
    }
  }
  walls.clear();
  walls = list<shared_ptr<SFAsset>>(tmp_2);

//remove Coins

list<shared_ptr<SFAsset>> tmp_coin;
  for(auto c : coins) {
    if(c->IsAlive()) {
      tmp_coin.push_back(c);
    }
  }
  coins.clear();
  coins = list<shared_ptr<SFAsset>>(tmp_coin);


}

void SFApp::OnRender() {
  SDL_RenderClear(sf_window->getRenderer());

//Initialise background on Screen

  SDL_Texture* bg_image = NULL;

  bg_image = IMG_LoadTexture(sf_window->getRenderer(),"assets/bg.png");

  SDL_Rect bg_rect;
  	bg_rect.x = 0;
  	bg_rect.y = 0;
  	bg_rect.w = 720;
  	bg_rect.h = 720;
  

  SDL_RenderCopy(sf_window->getRenderer(),bg_image,NULL,&bg_rect);

	if(bg_image == NULL)
	{	
	   cout <<"Couldn't Load Texture"<< endl;

	}

  // draw the player
  player->OnRender();

  for (auto u: powerup){
    if(u->IsAlive()) {u->OnRender();}
  }

  for(auto p: projectiles) {
    if(p->IsAlive()) {p->OnRender();}
  }

  for(auto a: aliens) {
    if(a->IsAlive()) {a->OnRender();}
  }

  for(auto a2: aliens2) {
    if(a2->IsAlive()) {a2->OnRender();}
  }

  for(auto a3: aliens3) {
    if(a3->IsAlive()) {a3->OnRender();}
  }

  for(auto c: coins) {
    c->OnRender();
  }

  for(auto w: walls) {
    w->OnRender();
  }
  
  

//Initialise Frame on Screen

  SDL_Texture* frame_image = NULL;

  frame_image = IMG_LoadTexture(sf_window->getRenderer(),"assets/frame.png");

  SDL_Rect frame_rect;
  	frame_rect.x = 0;
  	frame_rect.y = 0;
  	frame_rect.w = 720;
  	frame_rect.h = 720;
  

  SDL_RenderCopy(sf_window->getRenderer(),frame_image,NULL,&frame_rect);

	if(frame_image == NULL)
	{	
	   cout <<"Couldn't Load Texture"<< endl;

	}

  // Switch the off-screen buffer to be on-screen
  SDL_RenderPresent(sf_window->getRenderer());
}


void SFApp::FireProjectile() {
  auto pb = make_shared<SFAsset>(SFASSET_PROJECTILE, sf_window);
  auto v  = player->GetPosition();
  pb->SetPosition(v);
  projectiles.push_back(pb);
}

void SFApp::AddScore(int s){
	
score += s;
cout << "Score:" << score << endl;

if(score >= 400)
{
cout << "CONGRATULATIONS YOU WIN!" << endl;
is_running = false;
}
}
void SFApp::Powerup(){
//Random item gives 25% chance of dropping a powerup
    if (rand() %100 < 25){
 for(auto p : projectiles) {
    for(auto a : aliens) {
      if(p->CollidesWith(a) ) {
	auto aPos = a->GetPosition();
    	auto coin = make_shared<SFAsset>(SFASSET_COIN, sf_window);
        auto pos  = Point2(aPos);
        coin->SetPosition(pos);
        coins.push_back(coin);
        
        
     }
   }	 
  }

}

}

