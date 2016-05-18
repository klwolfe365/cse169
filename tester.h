////////////////////////////////////////
// tester.h
////////////////////////////////////////

#ifndef CSE169_TESTER_H
#define CSE169_TESTER_H

#include "core.h"
#include "camera.h"
#include "cube.h"
#include "Skeleton.h"
#include "Skin.h"
#include "Animation.h"
#include "Rig.h"
#include "Player.h"
#include "Cloth.h"

////////////////////////////////////////////////////////////////////////////////

class Tester {
public:    
    Tester(int argc,char **argv);
	~Tester();

	void Update();
	void Reset();
	void Draw();
    
    void Animate();

	void Quit();

	// Event handlers
	void Resize(int x,int y);
	void Keyboard(int key,int x,int y);
	void MouseButton(int btn,int state,int x,int y);
	void MouseMotion(int x,int y);

private:
	// Window management
	int WindowHandle;
	int WinX,WinY;

	// Input
	bool LeftDown,MiddleDown,RightDown;
	int MouseX,MouseY;

	// Components
	Camera Cam;
	//SpinningCube Cube;
    Skeleton Skel;
    Skin SkelSkin;
    Animation Anim;
    Player AnimPlayer;
    Rig rig;
    Cloth cloth;
    Vector3 airVelocity;
};

////////////////////////////////////////////////////////////////////////////////

/*
The 'Tester' is a simple top level application class. It creates and manages a
window with the GLUT extension to OpenGL and it maintains a simple 3D scene
including a camera and some other components.
*/

#endif
