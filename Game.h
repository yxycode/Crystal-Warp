
#ifndef GAME_H
#define GAME_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include "bitmapdll.h"

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
struct PointXY
{
//static const float PI = 3.141592654;
static const float PI;

float x, y;
int AngleDegrees, Radius;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void RotateDegrees( int degrees )
{
	AngleDegrees += degrees;
	AngleDegrees = AngleDegrees % 360;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void ConvertPolar2Rectangular()
{
	x = cos( AngleDegrees * PI/180 ) * Radius;
	y = -sin( AngleDegrees * PI/180 ) * Radius;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

const float PointXY::PI = 3.141592654;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
float AbsoluteValue( float f )
{
    if( f < 0 )
       return -f;
    else
       return f;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
class GameObject
{
public:
  static const float PI;
  static const int ID_NOTHING = 0,
    ID_ASTEROID = 1,
    ID_SHIP = 2,
    ID_PROJECTILE = 3,
    ID_SCOREBAR = 4,
    ID_EXPLODING_SHIP = 5,
    ID_FLYING_SAUCER = 6,
    ID_NASTY = 7,
    ID_STATIC_OBJECT = 8;
    
  static const int SCREEN_WIDTH_PIXELS = 800, SCREEN_HEIGHT_PIXELS = 600;
  
  int Id;
  static void *ItsWorld;
  
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*  
GameObject()
{
  Id = ID_NOTHING;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*  
virtual void Do() {}
virtual void Draw() {}
virtual void InputKey( int pressflag, int vk_code ) {}
virtual void InputMouse() {}
virtual void InputGamePad() {}
virtual ~GameObject() {}

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
static float Distance( float X1, float Y1, float X2, float Y2 )
{
    return sqrt( (X1 - X2) * (X1 - X2) +  (Y1 - Y2) * (Y1 - Y2));
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
static int CheckRectangularCollision( float x1, float y1, float width1, float height1,
                              float x2, float y2, float width2, float height2 )
{
   float xlist[4], ylist[4];
   float xlist2[4], ylist2[4];
   int x, y, i, collideflag = 0;
   
   xlist[0] = x1; ylist[0] = y1; xlist[1] = x1 + width1; ylist[1] = y1;
   xlist[2] = x1; ylist[2] = y1 + height1; xlist[3] = x1 + width1; ylist[3] = y1 + height1;
   
   for( i = 0; i < 4; i++ )
   {
      if( x2 <= xlist[i] && xlist[i] <= x2 + width2 && y2 <= ylist[i] && ylist[i] <= y2 + height2 )
      {
         collideflag = 1;
         return 1;
      }
   }
   
   xlist2[0] = x2; ylist2[0] = y2; xlist2[1] = x2 + width2; ylist2[1] = y2;
   xlist2[2] = x2; ylist2[2] = y2 + height2; xlist2[3] = x2 + width2; ylist2[3] = y2 + height2;
   
   for( i = 0; i < 4; i++ )
   {
      if( x1 <= xlist2[i] && xlist2[i] <= x1 + width1 && y1 <= ylist2[i] && ylist2[i] <= y1 + height1 )
      {
         collideflag = 1;
         return 1;
      }
   }   
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void *GameObject::ItsWorld = NULL;

const float GameObject::PI = 3.141592654;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* 
class Asteroid : public GameObject
{
public:
  static const int MAX_VERTICES = 10;
  static const int BORDER_PIXELS = 50;
  
  PointXY VertexList[MAX_VERTICES];
  Point PointList[MAX_VERTICES];
  float X_Center, Y_Center;
  int AverageRadius, Angle;
  
  static const float SPEED;  
  static const int MIN_RADIUS = 10, MAX_RADIUS = 40;
  static const int RADIUS_VARIATION = 4, ROTATE_DEGREES_SPEED = 2;
  static const int CHILD_COUNT = 5;
 
Asteroid();  
void Init(int nAverageRadius, int xcenter, int ycenter);
void Do();
void Draw();
void BreakUp();
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

const float Asteroid::SPEED = 3.0;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* 
class Ship : public GameObject
{
public:
  static const int MAX_VERTICES = 3;
  static const int SHIP_RADIUS = 20;
  static const int MAX_VECTORS = 359;
  static const float SPEED_INCREMENT;
  static const float MAX_SPEED;
  static const float FRICTION;
  static const int BORDER_PIXELS = SHIP_RADIUS * 2;
  
  PointXY VertexList[MAX_VERTICES];
  Point PointList[MAX_VERTICES];
  float X_Center, Y_Center;
  int Angle;
  float Vectors[MAX_VECTORS];
  float X_Sum, Y_Sum;
  
  static const int MAX_PROJECTILES = 10;
  static const int PROJECTILE_DELAY = 5;
  int ProjectileDelayCounter;
  
  static const int WARP_DELAY = 5;
  int WarpCounter, WarpFlag;
  
Ship();
void Do();
void Draw();
void InputKey( int pressflag, int vk_code ); 

protected:
    
int AccelerateFlag, ShootFlag, RotateLeftFlag, RotateRightFlag;
    
void ProcessVectors();
void Shoot();
void Accelerate();
void Rotate( int degrees );   
void UpdatePointList();
void Warp();
int CheckCollide();
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

const float Ship::SPEED_INCREMENT = 0.70;
const float Ship::MAX_SPEED = 10.0;
const float Ship::FRICTION = -0.3;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* 
class ExplodingShip : public GameObject
{
public:
  static const int MAX_SEGMENTS = 3;
  static const float SPEED;
  static const int LIFE_SPAN_TICKS = 50;
  
  int X1_List[MAX_SEGMENTS];
  int Y1_List[MAX_SEGMENTS];
  int X2_List[MAX_SEGMENTS];
  int Y2_List[MAX_SEGMENTS];  
  int AngleList[MAX_SEGMENTS];
  int LifeSpanTicks;

ExplodingShip( Ship *pShip );
void Do();
void Draw();
  
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

const float ExplodingShip::SPEED = 4.0;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* 
class Projectile : public GameObject
{
public:    
    static const float SPEED;
    static const int LIFE_SPAN_TICKS = 80;
    static const int RADIUS = 5;
        
    float X_Center, Y_Center;
    int Angle, TickCount;     
    float X_Speed_Plus, Y_Speed_Plus;
    int SelfBoostFlag;
    
Projectile( float xcenter, float ycenter, int angle );
void Do();
void Draw();
int CheckCollide();      
void AddSpeed( float x_sum, float y_sum );
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

const float Projectile::SPEED = 5.0;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
class ScoreBar : public GameObject
{
public:
  static const int GAME_STATE_GAME_OVER = 0;
  static const int GAME_STATE_PLAYING = 1;
  static const int GAME_STATE_SHIP_DEAD = 2;
  static int GameState;
  
  static int CurrentLives, CurrentLevel, CurrentScore, HighScore;
  static char *debugstr;
  
ScoreBar();
void Do();
void Draw();  
void InputKey( int pressflag, int vk_code );
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

char *ScoreBar::debugstr = NULL;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
class FlyingSaucer : public GameObject
{
public:
  static const int SHIP_RADIUS = 20;
  static const int MAX_VECTORS = 359;
  static const float SPEED_INCREMENT;
  static const float MAX_SPEED;
  static const float FRICTION;
  static const int BORDER_PIXELS = SHIP_RADIUS * 2;
  
  static float X_Center, Y_Center;
  float Vectors[MAX_VECTORS];
  float X_Sum, Y_Sum;
  
  static const int MAX_PROJECTILES = 20;
  static const int PROJECTILE_DELAY = 5;
  int ProjectileDelayCounter;
  static int StillnessCounter;
  static const int STILLNESS_COUNTER_MAX = 30;
  
FlyingSaucer();
void Do();
void Draw();
void InputKey( int pressflag, int vk_code ); 

protected:
    
int ShootFlag, UpFlag, DownFlag, LeftFlag, RightFlag, BombFlag;
    
void ProcessVectors();    
void Shoot();
void MoveXY( int xdir, int ydir );
int CheckCollide();
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

const float FlyingSaucer::SPEED_INCREMENT = 1.00;
const float FlyingSaucer::MAX_SPEED = 6.0;
const float FlyingSaucer::FRICTION = -0.2;

float FlyingSaucer::X_Center = 0.0;
float FlyingSaucer::Y_Center = 0.0;
int FlyingSaucer::StillnessCounter = 0;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

class Nasty : public GameObject
{
public:
  const static float PI = 3.141592654;
    
  const static int
    SID_NOTHING = 0,
    SID_ANNOYER = 1, SID_WORRIER = 2, SID_PEST = 3, SID_DUMPLE = 4, SID_ZARKLEPHASER  = 5, SID_TRIMPET = 6,
    SID_HUSKET = 7, SID_BANE = 8, SID_MENACE = 9, SID_TENTAWARBLE = 10, SID_SHRAPWARDEN = 11, SID_PARASITE = 12,
    SID_NASTY_MINE = 13, SID_NASTY_EXPLOSION = 14,
    SID_NASTY_BEAM = 15, SID_NASTY_BEAM_TRAIL = 16, SID_NASTY_BOUNCY_BOMB = 17, SID_NASTY_PROJECTILE = 18, SID_NASTY_HAIL = 19,
    SID_SHRAPWARDEN_BITS = 20, SID_BONUS_CRYSTAL = 21;
    
  int SubId;
  float X, Y;
  int Width, Height, Angle;
  float Speed;
  int PictureIndex;
  
  int TickCounter;
  const static int TICK_COUNTER_MAX = 10000;  
  
  const static int MAX_ANIMATION_FRAMES = 4;
  const static int ANIMATION_DELAY_1 = 5;
  const static int ANIMATION_DELAY_2 = 1;
  const static int PROJECTILE_HIT_POINTS = 100;
  const static int EXPLOSION_HIT_POINTS = 10;
  
  int AnimationFrameList_Y;
  int AnimationIndex;
  int AnimationDelay;
  
  int RandomBounceDelay;
  int RandomSpeedChangeDelay;
  float SpeedMultiplier, MaxSpeed;
  int ShootDelay;
  int HitPoints;
  int BounceWallsFlag;
  
  int ShootAngle, WaitCounter, StatusFlag;
  int FollowPlayerShipCounter;
  int FOLLOW_PLAYER_SHIP_COUNTER_MAX = 50;
  
  int SpeedUp;
  
  const static int 
    BEAM_ATTACK_CHARGE_TIME = 20,
    STATUS_NORMAL = 0, 
    STATUS_BEAM_ATTACK_WAIT = 1,
    STATUS_TRIMPET_SLEEP = 2,
    TRIMPET_SLEEP_TIME = 80,
    TENTAWARBLE_SPEED_UP = 10;
    
  int SlideTimeCounter, StopSlideWithinPlayFieldFlag;
    
  Nasty( int sid );
  static void Init();
    
protected:  
  static void CalculateBounceAngles( int angle_list[] );
  int CheckCollideBoundaries();
  void Move();
  void BounceSolid();
  void BounceRandom();
  void SpeedChangeRandom();
  void Do();
  void Draw();
  int CheckCollideProjectiles();
  void CenterNasty( Nasty *ns );
  int CheckOutsideBoundaries();
  int CheckHitPoints();
  void SpawnObjects();
  Nasty* SpawnNastyCentered(int sid);
  void OrthogonalTargeting();
  int CalculateAngleTowardsPlayerShip();

public:  
  void SetSpecialXYPosition( int options[] );
  void StartSlide( int nSlideTimeCount, int nStopSlideWithinPlayFieldFlag );
  int CalculateAngleTowardsPoint( float fx, float fy );  
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
class StaticObject : public GameObject
{
public:
    
  int SubId;
  float X, Y;
  int Width, Height;
  float Speed;
  
  int TickCounter;
  const static int TICK_COUNTER_MAX = 10000;  
  
  const static int ANIMATION_DELAY_1 = 5;  
  
  const static int MAX_SUB_OBJECT_COUNT = 10;

  int SubObjectCount;
  float XList[MAX_SUB_OBJECT_COUNT], YList[MAX_SUB_OBJECT_COUNT];
  int WidthList[MAX_SUB_OBJECT_COUNT], HeightList[MAX_SUB_OBJECT_COUNT];
    
  int PictureIndex[MAX_SUB_OBJECT_COUNT];  
  int AnimationFrameSrcXList[MAX_SUB_OBJECT_COUNT];  
  int AnimationFrameSrcYList[MAX_SUB_OBJECT_COUNT];  
  int AnimationFrameCount[MAX_SUB_OBJECT_COUNT];
  int AnimationDelay[MAX_SUB_OBJECT_COUNT];
  int AnimationIndex[MAX_SUB_OBJECT_COUNT];

  const static int SID_NOTHING = 0,
    SID_HORIZONTAL_WALL = 1,
    SID_VERTICAL_WALL = 2,
    SID_LEFT_PORTAL = 3,
    SID_RIGHT_PORTAL = 4,
    SID_EXIT_PORTAL = 5;
    
  int StatusFlag;  
  
  const static int STATUS_NORMAL = 0,
    STATUS_OPENED_PORTAL = 1,
    STATUS_MOVING_CLOSED_PORTAL = 2,
    STATUS_MOVING_OPENED_PORTAL = 3;    
    
StaticObject( int nSubId );
void Draw();
void Do();

protected:
void Animate();
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

class World
{
  public:
   static const int MAX_GAME_OBJECTS = 1000;
   GameObject *GameObjectList[MAX_GAME_OBJECTS];
   //SoundBox ItsSoundBox;

World();
void Init(int level);
void Do();
void Draw();
void InputKey( int pressflag, int vk_code);
void Add( GameObject *obj );
int GetCount( int Object_Id );
void *GetObject( int Object_Id, int Object_SubId );

void PlaySound( int index );
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* 
Asteroid::Asteroid()
{
    Id = ID_ASTEROID;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* 
void Asteroid::Init(int nAverageRadius, int xcenter, int ycenter )
{ 
  if( nAverageRadius <= 0 )
  {
     AverageRadius =  MAX_RADIUS;
     X_Center = rand() % SCREEN_WIDTH_PIXELS;
     Y_Center = rand() % SCREEN_HEIGHT_PIXELS;     
  }
  else
  {
    X_Center = xcenter; Y_Center = ycenter;
    AverageRadius = nAverageRadius;
  }
  
  int i;
  for( i = 0; i < MAX_VERTICES; i++ )
  {
  	 VertexList[i].AngleDegrees = 360/MAX_VERTICES * i;
  	 VertexList[i].Radius = abs(AverageRadius - rand() % RADIUS_VARIATION);  	 
  	 VertexList[i].ConvertPolar2Rectangular();  	 
  	 PointList[i].X = VertexList[i].x + X_Center;  PointList[i].Y = VertexList[i].y + Y_Center;
  }
  Angle = rand() % 360;
	
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Asteroid::Do()
{
    
  int i;
  for( i = 0; i < MAX_VERTICES; i++ )
  {
  	 VertexList[i].AngleDegrees = ( VertexList[i].AngleDegrees + ROTATE_DEGREES_SPEED ) % 360;	 
  	 VertexList[i].ConvertPolar2Rectangular();
  	 PointList[i].X = VertexList[i].x + X_Center;  PointList[i].Y = VertexList[i].y + Y_Center;
  }
  
  X_Center += SPEED * cos(Angle * PI/180);
  Y_Center += SPEED * sin(Angle * PI/180);
  
  if( X_Center < -BORDER_PIXELS )
      X_Center = SCREEN_WIDTH_PIXELS + BORDER_PIXELS - 1;
  else
  if( X_Center > SCREEN_WIDTH_PIXELS + BORDER_PIXELS )
      X_Center = -BORDER_PIXELS + 1;

  if( Y_Center < -BORDER_PIXELS )
      Y_Center = SCREEN_HEIGHT_PIXELS + BORDER_PIXELS - 1;
  else
  if( Y_Center > SCREEN_HEIGHT_PIXELS + BORDER_PIXELS )
      Y_Center = -BORDER_PIXELS + 1;
            
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Asteroid::Draw()
{
    Bitmap_Dll_Loader::Bitmap_DrawPolygon( 1, PointList, MAX_VERTICES ); 	 
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*    
void Asteroid::BreakUp()
{       
   World *WorldPtr = (World*)ItsWorld;
   Id = ID_NOTHING;
 
   if( AverageRadius/2 < MIN_RADIUS )
       return;
          
   int i;
   Asteroid *as;
   
   for( i = 0; i < CHILD_COUNT; i++ )
   {
      as = new Asteroid();
      as->Init(AverageRadius/2, X_Center, Y_Center);
      WorldPtr->Add(as);
   }
     
   //WorldPtr->ItsSoundBox.PlaySound(1);
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* 
World::World()
{
 int i;
 for( i = 0; i < MAX_GAME_OBJECTS; i++ )
      GameObjectList[i] = NULL;

/*
 ItsSoundBox.LoadSound(0, "c:/windows/media/tada.wav");
 ItsSoundBox.LoadSound(1, "c:/windows/media/notify.wav");      
*/  

}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*       
void World::Init(int level)
{

 int i;
 for( i = 0; i < MAX_GAME_OBJECTS; i++ )
 {
     if( GameObjectList[i] != NULL )
      if( GameObjectList[i]->Id != GameObject::ID_SCOREBAR )
      {
         delete GameObjectList[i];         
         GameObjectList[i] = NULL;
      }
 }
 /*
 Asteroid *as;
      
 for( i = 0; i < level + 3; i++ )
 {
    as = new Asteroid();
    as->Init(0,0,0);
    Add( (GameObject*)as );
 }
*/
/*
    SID_NOTHING = 0,
    SID_ANNOYER = 1, SID_WORRIER = 2, SID_PEST = 3, SID_DUMPLE = 4, SID_ZARKLEPHASER  = 5, SID_TRIMPET = 6,
    SID_HUSKET = 7, SID_BANE = 8, SID_MENACE = 9, SID_TENTAWARBLE = 10, SID_SHRAPWARDEN = 11, SID_PARASITE = 12,
    SID_NASTY_MINE = 13, SID_NASTY_EXPLOSION = 14,
    SID_NASTY_BEAM = 15, SID_NASTY_BEAM_TRAIL = 16, SID_NASTY_BOUNCY_BOMB = 17, SID_NASTY_PROJECTILE = 18, SID_NASTY_HAIL = 19,
    SID_SHRAPWARDEN_BITS = 20, SID_BONUS_CRYSTAL = 21;  
    
*/
FlyingSaucer *fs = new FlyingSaucer();
Add(fs);

Nasty *nsty;
int id;
int num_list[] = { 1, 2, 3, 4, 7, 9, 5, 6, 8, 10, 11, 12, 21 };
int options[] = { 0, 0, 0 };

for( i = 0; i < 20; i++ )
{
     id = num_list[rand() % (sizeof(num_list)/sizeof(int) + 1)];
/*     
     if( id == 5 )
       MessageBox(0, "And text here", "MessageBox caption", MB_OK);
*/       
     nsty = new Nasty(id);
     options[0] = rand() % 2 + 1;
     nsty->SetSpecialXYPosition( options );
     nsty->Angle = nsty->CalculateAngleTowardsPoint( GameObject::SCREEN_WIDTH_PIXELS/2, GameObject::SCREEN_HEIGHT_PIXELS/2 );
     nsty->StartSlide(20, 1);
     Add(nsty);
}
 
/* 
 Ship *ship = new Ship();
 Add(ship);
*/ 
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void World::Do()
{   
	int i;
	for( i = 0; i < MAX_GAME_OBJECTS; i++ )
	   if( GameObjectList[i] != NULL )
	   {
	       GameObjectList[i]->Do();
	       if( GameObjectList[i]->Id == GameObject::ID_NOTHING )
	       {
	          delete GameObjectList[i];
	          GameObjectList[i] = NULL;
	       }
       }
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void World::Draw()
{
	int i;
	for( i = 0; i < MAX_GAME_OBJECTS; i++ )
	   if( GameObjectList[i] != NULL )
	       GameObjectList[i]->Draw();
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void World::InputKey(int pressflag, int vk_code)
{
	int i;
	for( i = 0; i < MAX_GAME_OBJECTS; i++ )
	   if( GameObjectList[i] != NULL )
	       GameObjectList[i]->InputKey(pressflag, vk_code);
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void World::Add( GameObject *obj )
{
	int i;
	for( i = 0; i < MAX_GAME_OBJECTS; i++ )
	   if( GameObjectList[i] == NULL )
	   {
	      GameObjectList[i] = obj;
          break;
       }
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
int World::GetCount( int Object_Id )
{    
	int i, count = 0;
	
	for( i = 0; i < MAX_GAME_OBJECTS; i++ )
	   if( GameObjectList[i] != NULL )
	     if( GameObjectList[i]->Id == Object_Id )
	         count++;
    
    return count;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void *World::GetObject( int Object_Id, int Object_SubId )
{
    int i;
    Nasty *nstyptr;
    StaticObject *sttc_obj_ptr;
    void *gm_obj_ptr = NULL;
    
	for( i = 0; i < MAX_GAME_OBJECTS; i++ )
	 if( GameObjectList[i] != NULL )
	  if( GameObjectList[i]->Id == Object_Id ) 
      {
        if( Object_Id == GameObject::ID_NASTY )
        {
          nstyptr = (Nasty*)GameObjectList[i];          
          
          if( nstyptr->SubId == Object_SubId )
          {
            gm_obj_ptr = GameObjectList[i];  
            break;
          }
        }
        else
        if( Object_Id == GameObject::ID_STATIC_OBJECT )
        {
           sttc_obj_ptr = (StaticObject*)GameObjectList[i];
          
          if( sttc_obj_ptr->SubId == Object_SubId )
          {
            gm_obj_ptr = GameObjectList[i];  
            break;
          }    
        }
      }  
      
    return gm_obj_ptr;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void World::PlaySound( int index )
{
  Bitmap_Dll_Loader::Sound_PlayWaveFile(index);
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
Ship::Ship()
{
   Id = ID_SHIP;
   
   X_Center = SCREEN_WIDTH_PIXELS/2; Y_Center = SCREEN_HEIGHT_PIXELS/2;
   Angle = 90;
   
   int i;
   
   for( i = 0; i < MAX_VERTICES; i++ )
   {
     if( i == 0 )
       VertexList[i].AngleDegrees = Angle - 140;
     else
     if( i == 1 )
       VertexList[i].AngleDegrees = Angle;
     else
     if( i == 2 )
       VertexList[i].AngleDegrees = Angle + 140;
     
     VertexList[i].AngleDegrees %= 360;
     VertexList[i].Radius = SHIP_RADIUS;
     VertexList[i].ConvertPolar2Rectangular();
     PointList[i].X = VertexList[i].x + X_Center;
     PointList[i].Y = VertexList[i].y + Y_Center;
   }
   for( i = 0; i < MAX_VECTORS; i++ )
     Vectors[i] = 0.0;
     
   AccelerateFlag = ShootFlag = RotateLeftFlag = RotateRightFlag = 0;
   ProjectileDelayCounter = 0;
   WarpCounter = WarpFlag = 0;
   X_Sum = Y_Sum = 0;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Ship::Do()
{
    if( WarpFlag == 1 )
    {
       WarpCounter++;
       
       if( WarpCounter > WARP_DELAY )
       {
           WarpCounter = 0;
           WarpFlag = 0;
           
           X_Center = rand() % SCREEN_WIDTH_PIXELS ; 
           Y_Center = rand() % SCREEN_HEIGHT_PIXELS;
       }
    }
    
    ProcessVectors();
    CheckCollide();
    
  if( X_Center < -BORDER_PIXELS )
      X_Center = SCREEN_WIDTH_PIXELS + BORDER_PIXELS - 1;
  else
  if( X_Center > SCREEN_WIDTH_PIXELS + BORDER_PIXELS )
      X_Center = -BORDER_PIXELS + 1;

  if( Y_Center < -BORDER_PIXELS )
      Y_Center = SCREEN_HEIGHT_PIXELS + BORDER_PIXELS - 1;
  else
  if( Y_Center > SCREEN_HEIGHT_PIXELS + BORDER_PIXELS )
      Y_Center = -BORDER_PIXELS + 1;      
      
 
  if( AccelerateFlag == 1 )
      Accelerate();  
  if( RotateLeftFlag == 1 )
      Rotate(8);
  if( RotateRightFlag == 1 )
      Rotate(-8);
  if( ShootFlag == 1 )
  {
    if( ProjectileDelayCounter <= 0 )
    {
      Shoot();               
      ProjectileDelayCounter = PROJECTILE_DELAY; 
    }
  }
  
  if( ProjectileDelayCounter > 0 )      
      ProjectileDelayCounter--;    
         
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Ship::Draw()
{
    int pen_index = 0;
    
    if( WarpFlag == 1 )
        pen_index = 3;
    else
        pen_index = 2;
        
    Bitmap_Dll_Loader::Bitmap_DrawPolygon( pen_index, PointList, MAX_VERTICES ); 
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Ship::InputKey( int pressflag, int vk_code )
{    
   World *WorldPtr = (World*)ItsWorld;
   
   if( pressflag == 1 )
   {
     switch( vk_code )
     {
       case VK_UP:     
         AccelerateFlag = 1;     
         //Accelerate();
         break;
       case VK_DOWN:
         break;
       case VK_LEFT:   
         RotateLeftFlag = 1;
         //Rotate(8);
         break;
       case VK_RIGHT:    
         RotateRightFlag = 1;  
         //Rotate(-8);  
         break;
       case 'F':
         ShootFlag = 1;
         //WorldPtr->ItsSoundBox.PlaySound(0);
         //WorldPtr->ItsSoundBox.PlaySound(1);
         //Shoot();
         break;
       case 'W':
         Warp();
         break;
       default:
         break; 
     }
   }
   else
   if( pressflag == 0 )
   {
     switch( vk_code )
     {
       case VK_UP:     
         AccelerateFlag = 0;     
         break;
       case VK_DOWN:
         break;
       case VK_LEFT:   
         RotateLeftFlag = 0;
         break;
       case VK_RIGHT:    
         RotateRightFlag = 0;   
         break;
       case 'F':
         ShootFlag = 0;
         break;
       default:
         break; 
     }
   }   
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Ship::ProcessVectors()
{
   int i;
   float sum_x = 0, sum_y = 0;
   
   for( i = 0; i < MAX_VECTORS; i++ )
   {
     sum_x += Vectors[i] * cos(i * PI/180);
     sum_y += Vectors[i] * -sin(i * PI/180);   
   }
   
   X_Center += sum_x;
   Y_Center += sum_y;

   X_Sum = sum_x; Y_Sum = sum_y;
   
   for( i = 0; i < MAX_VECTORS; i++ )
   {
     Vectors[i] += FRICTION;
     if( Vectors[i] < 0 )
         Vectors[i] = 0;
   }    
   UpdatePointList();
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Ship::Shoot()
{   
   World *WorldPtr = (World*)ItsWorld;
   
   if( WorldPtr->GetCount(ID_PROJECTILE) < MAX_PROJECTILES )
   {
     Projectile *proj = new Projectile( X_Center, Y_Center, Angle );      
     proj->AddSpeed( X_Sum, Y_Sum );
     WorldPtr->Add(proj);   
   }
   
  WorldPtr->PlaySound(0);
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Ship::Accelerate()
{
    Vectors[Angle] += SPEED_INCREMENT;
    if( Vectors[Angle] > MAX_SPEED )
        Vectors[Angle] = MAX_SPEED;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Ship::Rotate( int degrees )
{
    Angle += degrees;
    
    if( Angle < 0 )
    {
       Angle = 360 + Angle;
    }
    else
    {
       Angle = Angle % 360;
    }
    
    UpdatePointList();  
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Ship::UpdatePointList()
{
   int i;
   
   for( i = 0; i < MAX_VERTICES; i++ )
   {
     if( i == 0 )
       VertexList[i].AngleDegrees = Angle - 140;
     else
     if( i == 1 )
       VertexList[i].AngleDegrees = Angle;
     else
     if( i == 2 )
       VertexList[i].AngleDegrees = Angle + 140;
              
     VertexList[i].AngleDegrees %= 360;
     VertexList[i].Radius = SHIP_RADIUS;
     VertexList[i].ConvertPolar2Rectangular();
     PointList[i].X = VertexList[i].x + X_Center;
     PointList[i].Y = VertexList[i].y + Y_Center;
   }      
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Ship::Warp()
{
  World *WorldPtr = (World *)ItsWorld;
  
  if( WarpFlag == 0 )
  {  
    WarpCounter = 0; WarpFlag = 1;
    WorldPtr->PlaySound(2);
  }
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
int Ship::CheckCollide()
{
  World *WorldPtr = (World*)ItsWorld;
  GameObject *go;
  Asteroid *ast;
  ExplodingShip *es;
  float distance;
  int CollideFlag = 0;

  int i; 
  for( i = 0; i < World::MAX_GAME_OBJECTS; i++ )
  {
     go = WorldPtr->GameObjectList[i];
     
     if( go != NULL )
      if( go->Id == ID_ASTEROID )
      {
        ast = (Asteroid *)go;
        distance = Distance( X_Center, Y_Center, ast->X_Center, ast->Y_Center );
        if( distance <= ast->AverageRadius )
        {
            CollideFlag = 1;
            break;
        }
      }
  }
  
  if( CollideFlag == 1 )
  {
      Id = ID_NOTHING;      
      es = new ExplodingShip(this);
      WorldPtr->Add(es);      
      
      WorldPtr->PlaySound(3);
  }
  return CollideFlag;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
ExplodingShip::ExplodingShip( Ship *pShip )
{
   Id = ID_EXPLODING_SHIP;   
   
    int i;
    
    X1_List[0] = pShip->PointList[0].X;
    Y1_List[0] = pShip->PointList[0].Y;
    X2_List[0] = pShip->PointList[1].X;
    Y2_List[0] = pShip->PointList[1].Y;    
    
    X1_List[1] = pShip->PointList[1].X;
    Y1_List[1] = pShip->PointList[1].Y;
    X2_List[1] = pShip->PointList[2].X;
    Y2_List[1] = pShip->PointList[2].Y;    
    
    X1_List[2] = pShip->PointList[2].X;
    Y1_List[2] = pShip->PointList[2].Y;
    X2_List[2] = pShip->PointList[0].X;
    Y2_List[2] = pShip->PointList[0].Y;     
    
    for( i = 0; i < MAX_SEGMENTS; i++ )
       AngleList[i] = rand() % 360;     
     
    LifeSpanTicks = LIFE_SPAN_TICKS;     
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void ExplodingShip::Do()
{
    int i;
  
    for( i = 0; i < MAX_SEGMENTS; i++ )
    {
       X1_List[i] += cos(AngleList[i] * PI/180) * SPEED;
       Y1_List[i] += sin(AngleList[i] * PI/180) * SPEED;
       X2_List[i] += cos(AngleList[i] * PI/180) * SPEED;
       Y2_List[i] += sin(AngleList[i] * PI/180) * SPEED;
    }

    if( LifeSpanTicks <= 0 )
    {
      Id = ID_NOTHING;  
      ScoreBar::GameState = ScoreBar::GAME_STATE_SHIP_DEAD;
    }
    else
      LifeSpanTicks--;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void ExplodingShip::Draw()
{
    int i;
    World *WorldPtr = (World*)ItsWorld;
    
     for( i = 0; i < MAX_SEGMENTS; i++ )
        Bitmap_Dll_Loader::Bitmap_DrawLine( 0, X1_List[i], Y1_List[i], X2_List[i], Y2_List[i] );
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
Projectile::Projectile( float xcenter, float ycenter, int angle )
{
   Id = ID_PROJECTILE;
   X_Center = xcenter; Y_Center = ycenter;
   Angle = angle;
   TickCount = LIFE_SPAN_TICKS;
   SelfBoostFlag = 0;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Projectile::Do()
{
if( SelfBoostFlag == 0 )
{
    X_Center += SPEED * cos(Angle * PI/180 ) + X_Speed_Plus;
    Y_Center += SPEED * -sin(Angle * PI/180 ) + Y_Speed_Plus;
}
else
{
    float x_ratio = AbsoluteValue(X_Speed_Plus / ( X_Speed_Plus + 0.0001));
    float y_ratio = AbsoluteValue(Y_Speed_Plus / ( Y_Speed_Plus + 0.0001));
    
    X_Center += SPEED * x_ratio * cos(Angle * PI/180 ) + X_Speed_Plus;
    Y_Center += SPEED * y_ratio * -sin(Angle * PI/180 ) + Y_Speed_Plus;
}
    if( TickCount <= 0 )
        Id = ID_NOTHING;
    else
        TickCount--;
        
    CheckCollide();
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Projectile::Draw()
{
  Bitmap_Dll_Loader::Bitmap_DrawEllipse( 0, X_Center - RADIUS, Y_Center - RADIUS, RADIUS * 2, RADIUS * 2 );     
/*  
  char str[100];
  sprintf( str, "proj %d", ProjectileCount );
  Bitmap_Dll_Loader::Bitmap_DrawTextGDI( str, 10, 380, 0 );
*/  
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
int Projectile::CheckCollide()
{
   World *WorldPtr = (World*)ItsWorld;
   GameObject *go;
   Asteroid *ast;
   int CollideFlag = 0;
   int distance;
   
  int i; 
  for( i = 0; i < World::MAX_GAME_OBJECTS; i++ )
  {
     go = WorldPtr->GameObjectList[i];
     
     if( go != NULL )
      if( go->Id == ID_ASTEROID )
      {
        ast = (Asteroid *)go;
        distance = Distance( X_Center, Y_Center, ast->X_Center, ast->Y_Center );
        if( distance <= ast->AverageRadius )
        {
            CollideFlag = 1;
            break;
        }
      }
  }   
  
  if( CollideFlag == 1 )
  {
    Id = ID_NOTHING;
    ast->BreakUp();
    ScoreBar::CurrentScore += 10;
    WorldPtr->PlaySound(1);
  }
  
  return CollideFlag;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Projectile::AddSpeed( float x_sum, float y_sum )
{
    X_Speed_Plus = x_sum;  Y_Speed_Plus = y_sum;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
/*
class ScoreBar : public GameObject
{
public:
  static const int GAME_STATE_GAME_OVER = 0;
  static const int GAME_STATE_PLAYING = 1;
  static const int GAME_STATE_SHIP_DEAD = 2;
  static int GameState;
  
  static int CurrentLives, CurrentLevel, CurrentScore, HighScore;

ScoreBar();
ScoreBar::void Do();
ScoreBar::void Draw();  
};
*/ 
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
ScoreBar::ScoreBar()
{
  Id = ID_SCOREBAR;
  GameState = GAME_STATE_PLAYING;
  CurrentLives = 3; CurrentLevel = 1; CurrentScore = 0; HighScore = 0;
  
  debugstr = new char[200];
  debugstr[0] = NULL;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void ScoreBar::Do()
{
   World *WorldPtr = (World*)ItsWorld;
   
   if( GameState == GAME_STATE_SHIP_DEAD )
   {
     if( CurrentLives > 0 )
     {
         Ship *ship = new Ship();         
         WorldPtr->Add(ship);
         GameState = GAME_STATE_PLAYING;
         CurrentLives = CurrentLives - 1;
     }
     else
     {
        GameState = GAME_STATE_GAME_OVER;
        
        if( CurrentScore > HighScore )
            HighScore = CurrentScore;
     }
   }
   else
   if( GameState == GAME_STATE_PLAYING )
   {
/*       
     if( WorldPtr->GetCount(ID_ASTEROID) <= 0 )  
     {
        CurrentLevel++;
        WorldPtr->Init(CurrentLevel);
     }
*/     
   }
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void ScoreBar::Draw()
{ 
  World *WorldPtr = (World *)ItsWorld;
  
  char str[1000];
  sprintf(str,"SHIP x %2d  LEVEL %2d  SCORE %10d  HIGHSCORE %10d", CurrentLives, CurrentLevel,
      CurrentScore, HighScore );
      
  Bitmap_Dll_Loader::Bitmap_DrawTextGDI( str, 5, 10, 0 );
  Bitmap_Dll_Loader::Bitmap_DrawTextGDI( debugstr, 5, 30, 0 );
  
  if( GameState == GAME_STATE_GAME_OVER )
       Bitmap_Dll_Loader::Bitmap_DrawTextGDI( "Game Over", GameObject::SCREEN_WIDTH_PIXELS/2.2, GameObject::SCREEN_HEIGHT_PIXELS/2, 0 );          
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void ScoreBar::InputKey( int pressflag, int vk_code )
{
    World *WorldPtr = (World*)ItsWorld;
    
    if( pressflag == 1 )
    {
       if( GameState == GAME_STATE_GAME_OVER )
       {
          CurrentLives = 3; CurrentLevel = 1; CurrentScore = 0;
          GameState = GAME_STATE_PLAYING;          
          WorldPtr->Init(1);
       }
    }
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
int ScoreBar::GameState = ScoreBar::GAME_STATE_PLAYING;
int ScoreBar::CurrentLives = 3;
int ScoreBar::CurrentLevel = 1;
int ScoreBar::CurrentScore = 0;
int ScoreBar::HighScore = 0;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
FlyingSaucer::FlyingSaucer()
{
  Id = ID_FLYING_SAUCER;
  
  int i;
  for( i = 0; i < MAX_VECTORS; i++ )
    Vectors[i] = 0;
    
  X_Center = SCREEN_WIDTH_PIXELS/2;
  Y_Center = SCREEN_HEIGHT_PIXELS/2;
  ProjectileDelayCounter = 0;    
  
  ShootFlag = UpFlag = DownFlag = LeftFlag = RightFlag = BombFlag = 0;
  StillnessCounter = 0;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void FlyingSaucer::Do()
{
  
  if( ProjectileDelayCounter <= PROJECTILE_DELAY )    
      ProjectileDelayCounter++;   
  if( StillnessCounter < STILLNESS_COUNTER_MAX )
      StillnessCounter++;
  
  int x, y;
  x = y = 0;
  
  if( UpFlag == 1 )
     y = -1;
  if( DownFlag == 1 )
     y = 1;
  if( LeftFlag == 1 )
     x = -1;
  if( RightFlag == 1 )
     x = 1;
  if( ShootFlag == 1 )      
     Shoot();
           
  MoveXY( x, y );
             
  ProcessVectors();              
  
  if( UpFlag == 1 || DownFlag == 1 || LeftFlag == 1 || RightFlag == 1 )
      StillnessCounter = 0;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void FlyingSaucer::Draw()
{
   Bitmap_Dll_Loader::Bitmap_DrawEllipse( 2, X_Center - SHIP_RADIUS, Y_Center - SHIP_RADIUS, SHIP_RADIUS*2, SHIP_RADIUS*2 );      
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void FlyingSaucer::InputKey( int pressflag, int vk_code )
{ 
   if( pressflag == 1 )
   {
     switch( vk_code )
     {
       case VK_UP:     
         UpFlag = 1;
         break;
       case VK_DOWN:
         DownFlag = 1;
         break;
       case VK_LEFT:   
         LeftFlag = 1;
         break;
       case VK_RIGHT:    
         RightFlag = 1;
         break;
       case 'F':
         ShootFlag = 1;
         break;
       case 'D':
         BombFlag = 1;
         break;
       default:
         break; 
     }
   }
   else
   if( pressflag == 0 )
   {
     switch( vk_code )
     {
       case VK_UP:     
         UpFlag = 0;
         break;
       case VK_DOWN:
         DownFlag = 0;
         break;
       case VK_LEFT:   
         LeftFlag = 0;
         break;
       case VK_RIGHT:    
         RightFlag = 0;
         break;
       case 'F':
         ShootFlag = 0;
         break;
       case 'D':
         BombFlag = 0;
         break;
       default:
         break; 
     }
   }       
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void FlyingSaucer::ProcessVectors()
{  
  int i;
  
  X_Sum = Y_Sum = 0;
  //sprintf( ScoreBar::debugstr, "%f %f %f %f", Vectors[0], Vectors[90], Vectors[180], Vectors[270] );
  
  for( i = 0; i < MAX_VECTORS; i++ )
  {               
     X_Sum += Vectors[i] * cos( i * PI/180 );
     Y_Sum += Vectors[i] * sin( i * PI/180 ); 
     
     Vectors[i] += FRICTION;
     if( Vectors[i] < 0 )
         Vectors[i] = 0;
     else
     if( Vectors[i] > MAX_SPEED )
         Vectors[i] = MAX_SPEED;         
  }
  
  X_Center += X_Sum; Y_Center += Y_Sum;
  
  if( X_Center < -BORDER_PIXELS )
      X_Center = SCREEN_WIDTH_PIXELS + BORDER_PIXELS;
  if( X_Center > SCREEN_WIDTH_PIXELS + BORDER_PIXELS )
      X_Center = -BORDER_PIXELS;      

  if( Y_Center < -BORDER_PIXELS )
      Y_Center = SCREEN_HEIGHT_PIXELS + BORDER_PIXELS;
  if( Y_Center > SCREEN_HEIGHT_PIXELS + BORDER_PIXELS )
      Y_Center = -BORDER_PIXELS;          
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void FlyingSaucer::Shoot()
{
   World *WorldPtr = (World*)ItsWorld;
   Projectile *prj;
   int angle;
   
   if( ProjectileDelayCounter >= PROJECTILE_DELAY )
   {  
      angle = atan2( -Y_Sum, X_Sum ) * 180 / PI;
      if( angle < 0 )
          angle = 360 + angle;
                
      ProjectileDelayCounter = 0;
      prj = new Projectile(X_Center, Y_Center, angle );
      prj->X_Speed_Plus = X_Sum;
      prj->Y_Speed_Plus = Y_Sum;
      prj->SelfBoostFlag = 1;      
      WorldPtr->Add(prj);
   }
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void FlyingSaucer::MoveXY( int xdir, int ydir )
{

  if( xdir < 0 )
    Vectors[180] += SPEED_INCREMENT;
  else
  if( xdir > 0 )
    Vectors[0] += SPEED_INCREMENT;
    
  if( ydir < 0 )
    Vectors[270] += SPEED_INCREMENT;
  else
  if( ydir > 0 )
    Vectors[90] += SPEED_INCREMENT;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
int FlyingSaucer::CheckCollide()
{
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
Nasty::Nasty( int sid )
{
Id = ID_NASTY;
TickCounter = 1;

SubId = SID_ANNOYER;
Width = Height = 40;
PictureIndex = 1;
AnimationFrameList_Y = 0;
AnimationIndex = 0;
MaxSpeed = 4;
BounceWallsFlag = 1;
HitPoints = 1;
AnimationDelay = ANIMATION_DELAY_1;
ShootDelay = 100;
FollowPlayerShipCounter = 0;

SpeedMultiplier = (rand() % 70 + 30 )/100.0;
Speed = MaxSpeed * SpeedMultiplier; 

Angle = rand() % 360;

RandomBounceDelay = (rand() % 70 + 30 )/100.0 * 100;
RandomSpeedChangeDelay = (rand() % 70 + 30 )/100.0 * 100;

X = rand() % SCREEN_WIDTH_PIXELS * 1.2 - Width * 3;
Y = rand() % SCREEN_HEIGHT_PIXELS * 1.2 - Height * 3;

ShootAngle = WaitCounter = 0;
StatusFlag = STATUS_NORMAL;

SubId = sid;

SlideTimeCounter = 0; StopSlideWithinPlayFieldFlag = 0;

if( SubId == SID_ANNOYER )
{
PictureIndex = 1;
AnimationFrameList_Y = 0;          
}
else
if( SubId == SID_WORRIER )
{
PictureIndex = 1;    
AnimationFrameList_Y = 1;
ShootDelay = (rand() % 40 + 60 )/100.0 * 100;
}
else
if( SubId == SID_PEST )
{
PictureIndex = 1;    
AnimationFrameList_Y = 2;  
ShootDelay = (rand() % 40 + 60 )/100.0 * 100;  
}
else
if( SubId == SID_DUMPLE )
{
PictureIndex = 2;
AnimationFrameList_Y = 0;      
Width = 80; Height = 80;
HitPoints = 10;
}
else
if( SubId == SID_ZARKLEPHASER )
{
PictureIndex = 1;
AnimationFrameList_Y = 4;        
ShootDelay = (rand() % 40 + 60 )/100.0 * 10;
}
else
if( SubId == SID_TRIMPET )
{
PictureIndex = 1;
AnimationFrameList_Y = 6;        
}
else
if( SubId == SID_HUSKET )
{
PictureIndex = 1;
AnimationFrameList_Y = 3;       
ShootDelay = (rand() % 40 + 60 )/100.0 * 50;
}
else
if( SubId == SID_BANE )
{
PictureIndex = 1;
AnimationFrameList_Y = 8;      
ShootDelay = (rand() % 40 + 60 )/100.0 * 100;    
}
else
if( SubId == SID_MENACE)
{
PictureIndex = 1;    
AnimationFrameList_Y = 5;    
ShootDelay = 1;
}
else
if( SubId == SID_TENTAWARBLE )
{
PictureIndex = 1;
AnimationFrameList_Y = 9;        
}
else
if( SubId == SID_SHRAPWARDEN )
{
PictureIndex = 1;
AnimationFrameList_Y = 10;        
}
else
if( SubId == SID_PARASITE )
{
PictureIndex = 1;
AnimationFrameList_Y = 11;        
}
else
if( SubId == SID_NASTY_MINE )
{
  PictureIndex = 1; 
  AnimationFrameList_Y = 12;
  HitPoints = 3;
  AnimationDelay = ANIMATION_DELAY_1;    
}
else
if( SubId == SID_NASTY_EXPLOSION )
{
  PictureIndex = 1;   
  AnimationFrameList_Y = 13;
  HitPoints = EXPLOSION_HIT_POINTS;
  AnimationDelay = ANIMATION_DELAY_2;    
}
else
if( SubId == SID_NASTY_BEAM )
{
 PictureIndex = 0;
 AnimationFrameList_Y = 0;
 HitPoints = PROJECTILE_HIT_POINTS;
 AnimationDelay = ANIMATION_DELAY_2;
 Width = 20; Height = 20;
 Speed = MaxSpeed = 20;
 ShootDelay = 1;
 BounceWallsFlag = 0;
}
else
if( SubId == SID_NASTY_BEAM_TRAIL )
{
 PictureIndex = 0;
 AnimationFrameList_Y = 1;
 HitPoints = 4;
 AnimationDelay = ANIMATION_DELAY_2;
 Width = 20; Height = 20;
 Speed = MaxSpeed = 0;
}
else
if( SubId == SID_NASTY_BOUNCY_BOMB )
{
 PictureIndex = 0;
 AnimationFrameList_Y = 2;    
 HitPoints = PROJECTILE_HIT_POINTS * 3;
 AnimationDelay = ANIMATION_DELAY_2; 
 Width = 20; Height = 20; 
 Speed = MaxSpeed = 8; 
 BounceWallsFlag = 1;
}
else
if( SubId == SID_NASTY_PROJECTILE )
{
 PictureIndex = 0;
 AnimationFrameList_Y = 3;
 HitPoints = PROJECTILE_HIT_POINTS;
 AnimationDelay = ANIMATION_DELAY_2;
 Width = 20; Height = 20;
 Speed = MaxSpeed = 8;
 BounceWallsFlag = 0;
}
else
if( SubId == SID_NASTY_HAIL )
{
 PictureIndex = 0;
 AnimationFrameList_Y = 4;
 HitPoints = PROJECTILE_HIT_POINTS;
 AnimationDelay = ANIMATION_DELAY_2;
 Width = 20; Height = 20;
 Speed = MaxSpeed = 10;
 BounceWallsFlag = 0;
}
else
if( SubId == SID_SHRAPWARDEN_BITS )
{
 PictureIndex = 0;
 AnimationFrameList_Y = 5;
 HitPoints = PROJECTILE_HIT_POINTS;
 AnimationDelay = ANIMATION_DELAY_2;
 Width = 20; Height = 20;
 Speed = MaxSpeed = 10;
 BounceWallsFlag = 0;
}
else
if( SubId == SID_BONUS_CRYSTAL )
{
PictureIndex = 2;
AnimationFrameList_Y = 1;      
Width = 80; Height = 80;
HitPoints = 1;    
BounceWallsFlag = 1;
}


}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Nasty::Init()    
{
    
Bitmap_Dll_Loader::Bitmap_LoadImageGDI( 0, "sprites_20x20.png" );    
Bitmap_Dll_Loader::Bitmap_LoadImageGDI( 1, "sprites_40x40.png" );    
Bitmap_Dll_Loader::Bitmap_LoadImageGDI( 2, "sprites_80x80.png" );    

}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Nasty::CalculateBounceAngles( int angle_list[] )
{
  int angle = angle_list[0];
  int i, quandrant;
  
  for( i = 0; i < 4; i++ )
     angle_list[i] = 0;

  if( 0 <= angle && angle <= 90 )
  {
     quandrant = 1; 
  }
  else
  if( 91 <= angle && angle <= 180 )
  {
    angle = 180 - angle;
    quandrant = 2;
  }
  else
  if( 181 <= angle && angle <= 270 )
  {
    angle = angle - 180;
    quandrant = 3;
  }
  else
  if( 271 <= angle && angle <= 360 )
  {
    angle = 360 - angle;
    quandrant = 4;
  }
    angle_list[0] = angle;
    angle_list[1] = 180 - angle;  
    angle_list[2] = 180 + angle;
    angle_list[3] = 360 - angle;
    
  switch(quandrant)
  {
    case 1:
     angle_list[0] *= -1;
     angle_list[2] *= -1;
     break;
    case 2:
     angle_list[1] *= -1;
     angle_list[3] *= -1;
     break;        
    case 3:
     angle_list[2] *= -1;
     angle_list[0] *= -1;
     break;        
    case 4:
     angle_list[3] *= -1;
     angle_list[1] *= -1;
     break;        
    default:
      break;
  }
        
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
int Nasty::CheckCollideBoundaries()
{
   if( X < 0 || Y < 0 || X + Width > SCREEN_WIDTH_PIXELS || Y + Height > SCREEN_HEIGHT_PIXELS )
       return 1;
   else
       return 0;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Nasty::Move()
{

if( SlideTimeCounter <= 0 )
{
    
if( SubId == SID_TENTAWARBLE && FollowPlayerShipCounter == 0 && FlyingSaucer::StillnessCounter == FlyingSaucer::STILLNESS_COUNTER_MAX )
{
    FollowPlayerShipCounter =  FOLLOW_PLAYER_SHIP_COUNTER_MAX;
    Angle = CalculateAngleTowardsPlayerShip();
}
else
if( SubId == SID_TENTAWARBLE && FollowPlayerShipCounter > 0 )
{
    FollowPlayerShipCounter--;
    Angle = CalculateAngleTowardsPlayerShip();
    SpeedUp = TENTAWARBLE_SPEED_UP;
}
else
if( SubId == SID_PARASITE )
{
    Angle = CalculateAngleTowardsPlayerShip();
}
}
  X += cos(Angle * PI/180) * (Speed + SpeedUp);
  Y += -sin(Angle * PI/180) * (Speed + SpeedUp);

if( BounceWallsFlag >= 1 && SlideTimeCounter <= 0)
{
  if( CheckCollideBoundaries() >= 1 )
      BounceSolid();  
}

   SpeedUp = 0;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Nasty::BounceSolid()
{
  int angle_list[4];
  float cur_x = X;
  float cur_y = Y;
  int i;
  
  angle_list[0] = Angle;
      
  CalculateBounceAngles(angle_list);
  
  for( i = 0; i < 4; i++ )
  {
    if( angle_list[i] < 0 )
        continue;
        
    X += cos(angle_list[i] * PI/180) * Speed;  
    Y += -sin(angle_list[i] * PI/180) * Speed;  
    Angle = (angle_list[i] + rand() % 4) % 360;
    
    if( CheckCollideBoundaries() == 0 )
        break;
    X = cur_x; Y = cur_y;   
  }
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Nasty::BounceRandom()
{
  Angle = rand() % 360;     
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Nasty::SpeedChangeRandom()
{
 SpeedMultiplier = (rand() % 70 + 30 )/100.0;
 Speed = MaxSpeed * SpeedMultiplier;     
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Nasty::Do()
{
  if( SubId == SID_NASTY_PROJECTILE || SubId == SID_NASTY_BEAM || SubId == SID_NASTY_HAIL || SubId == SID_NASTY_BOUNCY_BOMB || SubId == SID_SHRAPWARDEN_BITS )
  {     
     Move();   
     HitPoints--;
     CheckHitPoints();                   
     SpawnObjects();
  }
  else
  if( SubId == SID_NASTY_MINE )
  {
    CheckCollideProjectiles();
    CheckHitPoints();      
  }
  else
  if( SubId == SID_NASTY_EXPLOSION || SubId == SID_NASTY_BEAM_TRAIL )
  {
     HitPoints--;
     CheckHitPoints();     
  }
  else
  {
    
    if( WaitCounter > 0 )
        WaitCounter--;
    else
    { 
      if( StatusFlag == STATUS_BEAM_ATTACK_WAIT )
      {
        Nasty *nsty;
        StatusFlag = STATUS_NORMAL;
        WaitCounter = 0;
        nsty = SpawnNastyCentered(SID_NASTY_BEAM);   
        nsty->Angle = ShootAngle;
      }
      else
      if( StatusFlag == STATUS_TRIMPET_SLEEP )
      {
         AnimationFrameList_Y = 6;   
         StatusFlag = STATUS_NORMAL;
         WaitCounter = 0;
      }
      
       if( SlideTimeCounter > 0 )
       {
         SlideTimeCounter--;
         Move();
        
        if( StopSlideWithinPlayFieldFlag == 1 )         
         if( CheckOutsideBoundaries() == 0 )   
         {
             SlideTimeCounter = 0;
             BounceRandom();
         }
       }
       else
       {
         if( CheckOutsideBoundaries() == 0 )   
         {
           Move();
           SpawnObjects();
         }
        
         if( TickCounter % RandomBounceDelay == 0 )
            BounceRandom();
         if( TickCounter % RandomSpeedChangeDelay == 0 )
           SpeedChangeRandom();
       }
    }
    
      CheckCollideProjectiles();
      CheckHitPoints();   
  }
    
  if( TickCounter % AnimationDelay == 0 )
      AnimationIndex++;
  if( AnimationIndex >= MAX_ANIMATION_FRAMES )
      AnimationIndex = 0;
      
  TickCounter++;
  if( TickCounter >= TICK_COUNTER_MAX )
      TickCounter = 1;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Nasty::Draw()
{
  Bitmap_Dll_Loader::Bitmap_DrawImageGDI( PictureIndex, X, Y, Width, Height, 
      AnimationIndex * (Width + 1), AnimationFrameList_Y * (Height + 1), Width, Height );    
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
int Nasty::CheckCollideProjectiles()
{
   World *WorldPtr = (World*)ItsWorld;

  int i, CollideFlag = 0, distance;
  GameObject *go;
  Projectile *proj;
  Nasty *nsty;
  
  for( i = 0; i < World::MAX_GAME_OBJECTS; i++ )
  {
     go = WorldPtr->GameObjectList[i];
     
     if( go != NULL )
      if( go->Id == ID_PROJECTILE )
      {
        proj = (Projectile*)go;
        distance = Distance( X + Width/2, Y + Height/2, proj->X_Center, proj->Y_Center );
        if( distance <= Width/2 )
        {
            proj->Id = ID_NOTHING;
            CollideFlag = 1;
            break;
        }
      }
  }      
  
  if( CollideFlag >= 1 )
  {
    if( SubId == SID_TRIMPET )
    {
     WaitCounter = TRIMPET_SLEEP_TIME;
     StatusFlag = STATUS_TRIMPET_SLEEP;
     AnimationFrameList_Y = 7;
    }
    else
      HitPoints--;
  }
  return CollideFlag;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Nasty::CenterNasty( Nasty *ns )
{
    X = ns->X + ns->Width/2 - Width/2;
    Y = ns->Y + ns->Height/2 - Height/2;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
int Nasty::CheckOutsideBoundaries()
{      
  if( X < 0 || X + Width < 0 ||  X + Width > SCREEN_WIDTH_PIXELS ||  X > SCREEN_WIDTH_PIXELS ||
      Y < 0 || Y + Width < 0 ||  Y + Width > SCREEN_HEIGHT_PIXELS ||  Y > SCREEN_HEIGHT_PIXELS )
  {
      Angle = atan2( -1 * ( SCREEN_HEIGHT_PIXELS/2 - Y ), SCREEN_WIDTH_PIXELS/2 - X ) * 180 / PI;
      
      if( Angle < 0 )
          Angle = 360 + Angle;
                
      X += cos(Angle * PI/180) * Speed;  
      Y += -sin(Angle * PI/180) * Speed;        

      return 1; 
  }
  else
    return 0;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
int Nasty::CheckHitPoints()
{
   World *WorldPtr = (World*)ItsWorld;
   Nasty *nsty;
   int i;
   
   if( HitPoints <= 0 )
   {
       Id = ID_NOTHING;
       
     switch( SubId )
     {
       case SID_NASTY_EXPLOSION:
       case SID_NASTY_BEAM:
       case SID_NASTY_BEAM_TRAIL:       
       case SID_NASTY_PROJECTILE:
       case SID_NASTY_HAIL:
         break;
       case SID_SHRAPWARDEN:
         for( i = 0; i < 360; i += 10 )
         {
           nsty = new Nasty( SID_SHRAPWARDEN_BITS );
           nsty->CenterNasty(this);           
           nsty->Angle = i;
           WorldPtr->Add(nsty);                               
         }
         break;
       case SID_NASTY_BOUNCY_BOMB:      
       default:
         nsty = new Nasty( SID_NASTY_EXPLOSION );
         nsty->CenterNasty(this);
         WorldPtr->Add(nsty);       
         break;      
     }
   }
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Nasty::SpawnObjects()
{    
   //World *WorldPtr = (World*)ItsWorld;
   Nasty *nsty;
   int anglelist1[4] = { 45, 45 * 3, 45 * 5, 45 * 7 };

   if( TickCounter % ShootDelay == 0 )
    switch(SubId)
    {
       case SID_WORRIER:
        nsty = SpawnNastyCentered(SID_NASTY_PROJECTILE);
        nsty->Angle = anglelist1[ rand() % 4 ];
        break;
       case SID_PEST:
        nsty = SpawnNastyCentered(SID_NASTY_MINE);  
        break;
       case SID_ZARKLEPHASER:
        nsty = SpawnNastyCentered(SID_NASTY_HAIL);
        nsty->Angle = rand() % 37 * 10;    
        break;
       case SID_HUSKET:
        nsty = SpawnNastyCentered(SID_NASTY_PROJECTILE);
        nsty->Angle = anglelist1[ rand() % 4 ];         
        break;
       case SID_BANE:
        nsty = SpawnNastyCentered(SID_NASTY_BOUNCY_BOMB);
        nsty->Angle = rand() % 37 * 10;                
        break;
       case SID_MENACE:
        OrthogonalTargeting();
        break;
       case SID_NASTY_BEAM:
        nsty = SpawnNastyCentered(SID_NASTY_BEAM_TRAIL);     
        break;    
       case SID_NASTY_HAIL:
        break;
       default:
         break;           
    }
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
Nasty* Nasty::SpawnNastyCentered( int sid )
{
   World *WorldPtr = (World*)ItsWorld;
   Nasty *nsty;
   
   nsty = new Nasty(sid);
   nsty->CenterNasty(this);   
   WorldPtr->Add(nsty); 
   return nsty;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Nasty::OrthogonalTargeting()
{
   int x_delta = 0, y_delta = 0;
   
   if( AbsoluteValue( FlyingSaucer::X_Center - (X + Width/2) ) < FlyingSaucer::SHIP_RADIUS )
   {
      y_delta = FlyingSaucer::Y_Center - Y;
   }
   else
   if( AbsoluteValue( FlyingSaucer::Y_Center - (Y + Height/2) ) < FlyingSaucer::SHIP_RADIUS )
   {
      x_delta = FlyingSaucer::X_Center - X;
   }
   
   if( x_delta == 0 && y_delta < 0 )
   {
       // up
       ShootAngle = 90;
       WaitCounter = BEAM_ATTACK_CHARGE_TIME;
       StatusFlag = STATUS_BEAM_ATTACK_WAIT;
   } 
   else
   if( x_delta == 0 && y_delta > 0 )
   {
       // down
       ShootAngle = 270;
       WaitCounter = BEAM_ATTACK_CHARGE_TIME;
       StatusFlag = STATUS_BEAM_ATTACK_WAIT;
   } 
   else
   if( x_delta < 0 && y_delta == 0 )
   {
       // left
       ShootAngle = 180;
       WaitCounter = BEAM_ATTACK_CHARGE_TIME;
       StatusFlag = STATUS_BEAM_ATTACK_WAIT;
   } 
   else
   if( x_delta > 0 && y_delta == 0 )
   {
       // right
       ShootAngle = 0;
       WaitCounter = BEAM_ATTACK_CHARGE_TIME;
       StatusFlag = STATUS_BEAM_ATTACK_WAIT;
   }          
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
int Nasty::CalculateAngleTowardsPlayerShip()
{        
    float delta_x = FlyingSaucer::X_Center - X;
    float delta_y = FlyingSaucer::Y_Center - Y;
    int angle = atan2 (-delta_y, delta_x) * 180 / PI;

    return angle;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Nasty::SetSpecialXYPosition( int options[] )
{
int object_id, object_sub_id, relative_x, relative_y;
Nasty *nstyptr = NULL;
StaticObject *sttc_obj_ptr = NULL;

switch( options[0] )
{

case 1:
// *** middle left ***
    X = 0 - Width;
    Y = SCREEN_HEIGHT_PIXELS/2 - Height/2;
    break;  
case 2:
// *** middle right ***  
    X = SCREEN_WIDTH_PIXELS + Width;
    Y = SCREEN_HEIGHT_PIXELS/2 - Height/2;
    break;
case 3:
// *** middle top ***
    X = SCREEN_WIDTH_PIXELS/2 + Width/2;
    Y = 0 - Height;
    break;
case 4:
// *** middle bottom ***   
    X = SCREEN_WIDTH_PIXELS/2 + Width/2;
    Y = SCREEN_HEIGHT_PIXELS - Height; 
case 5:
// *** relative to another object (center-to-center) ***
    object_id = options[1];
    object_sub_id = options[2];
    relative_x = options[3];
    relative_y = options[4];
    
    if( object_id == ID_NASTY )
    {
       nstyptr = (Nasty*)((World*)ItsWorld)->GetObject( object_id, object_sub_id );
       X = nstyptr->X + nstyptr->Width/2 + relative_x - Width/2;
       Y = nstyptr->Y + nstyptr->Height/2 + relative_y - Height/2;
    }
    else
    if( object_id == ID_STATIC_OBJECT )
    {
       sttc_obj_ptr = (StaticObject*)((World*)ItsWorld)->GetObject( object_id, object_sub_id ); 
       X =  sttc_obj_ptr->X + sttc_obj_ptr->Width/2 + relative_x - Width/2;
       Y = sttc_obj_ptr->Y + sttc_obj_ptr->Height/2 + relative_y - Height/2;       
    }
    
    break;
  default:
    break;
}
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Nasty::StartSlide( int nSlideTimeCount, int nStopSlideWithinPlayFieldFlag )
{
  SlideTimeCounter = nSlideTimeCount;    
  StopSlideWithinPlayFieldFlag = nStopSlideWithinPlayFieldFlag;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
int Nasty::CalculateAngleTowardsPoint( float fx, float fy )
{
    float delta_x = fx - X;
    float delta_y = fy - Y;
    int angle = atan2 (-delta_y, delta_x) * 180 / PI;    
    return angle;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*  
StaticObject::StaticObject( int nSubId )
{
int i;

Id = ID_STATIC_OBJECT;
SubId = nSubId;
StatusFlag = STATUS_NORMAL;
Speed = 0;
SubObjectCount = 1;
TickCounter = 1;

for( i = 0; i < MAX_SUB_OBJECT_COUNT; i++ )
{
   AnimationFrameCount[i] = AnimationFrameSrcXList[i] = AnimationFrameSrcYList[i] = WidthList[i] = HeightList[i] = AnimationIndex[i] = 0;   
   AnimationDelay[i] = ANIMATION_DELAY_1;
}

switch( SubId )
{
case SID_HORIZONTAL_WALL:
Width = 40; Height = 20;
break;
case SID_VERTICAL_WALL:
Width = 20; Height = 40;
break;
case SID_LEFT_PORTAL:
Width = 40; Height = 80;
break;
case SID_RIGHT_PORTAL:
Width = 40; Height = 80;
break;
case SID_EXIT_PORTAL:
Width = 80; Height = 40;

AnimationFrameCount[0] = 1;
AnimationFrameSrcXList[0] = 0;
AnimationFrameSrcYList[0] = 0;
WidthList[0] = 120;
HeightList[0] = 40;

default:
break;
}

}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*  
void StaticObject::Draw()
{
int i;

for( i = 0; i < SubObjectCount; i++ )
{
  Bitmap_Dll_Loader::Bitmap_DrawImageGDI( PictureIndex[i], X + XList[i], Y + YList[i], WidthList[i], HeightList[i], 
      AnimationFrameSrcXList[i] + AnimationIndex[i] * (WidthList[i] + 1), AnimationFrameSrcYList[i], WidthList[i], HeightList[i] );      
}

/*    
  Bitmap_Dll_Loader::Bitmap_DrawImageGDI( PictureIndex, X, Y, Width, Height, 
      AnimationIndex * (Width + 1), AnimationFrameList_Y * (Height + 1), Width, Height );        
*/

}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*  
void StaticObject::Do()
{
int i;

for( i = 0; i < SubObjectCount; i++ )
{
  if( TickCounter % AnimationDelay[i] == 0 )
      AnimationIndex[i]++;
      
  if( AnimationIndex[i] >= AnimationFrameCount[i] )
      AnimationIndex[i] = 0;    
}

  TickCounter++;
  if( TickCounter >= TICK_COUNTER_MAX )
      TickCounter = 1;
      
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*  
void StaticObject::Animate()
{
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*  
#endif

