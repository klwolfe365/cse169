////////////////////////////////////////
// tester.cpp
////////////////////////////////////////

#include "tester.h"

#define WINDOWTITLE	"Spinning Cube"

////////////////////////////////////////////////////////////////////////////////

static Tester *TESTER;

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	TESTER = new Tester(argc,argv);
	glutMainLoop();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////

// These are really HACKS to make glut call member functions instead of static functions
static void display()									{TESTER->Draw();}
static void idle()										{TESTER->Update();}
static void animate(int v)                              {TESTER->Animate();}
static void resize(int x,int y)							{TESTER->Resize(x,y);}
static void keyboard(unsigned char key,int x,int y)		{TESTER->Keyboard(key,x,y);}
static void mousebutton(int btn,int state,int x,int y)	{TESTER->MouseButton(btn,state,x,y);}
static void mousemotion(int x, int y)					{TESTER->MouseMotion(x,y);}

////////////////////////////////////////////////////////////////////////////////

Tester::Tester(int argc,char **argv) {
	WinX=640;
	WinY=480;
	LeftDown=MiddleDown=RightDown=false;
	MouseX=MouseY=0;

	// Create the window
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize( WinX, WinY );
	glutInitWindowPosition( 0, 0 );
	WindowHandle = glutCreateWindow( WINDOWTITLE );
	glutSetWindowTitle( WINDOWTITLE );
	glutSetWindow( WindowHandle );

	// Background color
	glClearColor( 0., 0., 0., 1. );

	// Callbacks
	glutDisplayFunc( display );
	glutIdleFunc( idle );
	glutKeyboardFunc( keyboard );
	glutMouseFunc( mousebutton );
	glutMotionFunc( mousemotion );
	glutPassiveMotionFunc( mousemotion );
	glutReshapeFunc( resize );



	// Initialize components

	Cam.SetAspect(float(WinX)/float(WinY));
    
    const char * skelFilename;
    const char * skinFilename;
    const char * animFilename;
    if(argv[1] && argv[2]){
        skelFilename = argv[1];
        skinFilename = argv[2];
    }
    else{
        skelFilename = "/Users/karen/cse169/skeletons/wasp.skel";
        skinFilename = "/Users/karen/cse169/skins/wasp.skin";
    }
    if(argv[3])
        animFilename = argv[3];
    printf("%s\n",skinFilename);
    Skel.Load(skelFilename);
    SkelSkin.Load(skinFilename, &Skel);
    
    if(argv[3]){
        Anim.Load(animFilename);
        AnimPlayer.SetTime(Anim.GetTimeStart());
        AnimPlayer.SetSkeleton(&Skel);
        AnimPlayer.SetSkin(&SkelSkin);
        AnimPlayer.SetAnimation(&Anim);
        glutTimerFunc(33, animate, 0);
    }
    //SkelSkin.PrintSkin();
    
//    Skel.PrintJoints();
    
    /***** LIGHTING *****/
    GLfloat light_position0[] = { 6.0, 2.0, 2.0, 0.0 };
    GLfloat spot_direction0[] = { -6.0, -2.0, 0.0 };
    GLfloat light_position1[] = { -5.0, -1.0, -2.0, 0.0 };
    GLfloat spot_direction1[] = { 5.0, 1.0, 2.0 };
    GLfloat light_position2[] = { 0.0, 5.0, 0.0, 0.0 };
    GLfloat spot_direction2[] = { 0.0, -5.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    
    GLfloat light_ambient0[] = { 1.0, 0.0, 1.0, 1.0};
    GLfloat light_ambient1[] = { 0.0, 1.0, 1.0, 1.0};
    GLfloat light_ambient2[] = { 0.5, 1.0, 0.5, 1.0};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction0);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 20.0);
    
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_ambient1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0);
    
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_ambient2);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction2);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 180.0);
    
//    glEnable(GL_LIGHT1);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);
    
    
    
}

////////////////////////////////////////////////////////////////////////////////

Tester::~Tester() {
	glFinish();
	glutDestroyWindow(WindowHandle);
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Update() {
	// Update the components in the world
	Cam.Update();
	//Cube.Update();
    Matrix34 identity = Matrix34();
    Skel.Update(identity);
    SkelSkin.Update();
//    AnimPlayer.Update();

	// Tell glut to re-display the scene
	glutSetWindow(WindowHandle);
	glutPostRedisplay();
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Animate(){
    AnimPlayer.Update();
    glutTimerFunc(33, animate, 0);
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Reset() {
	Cam.Reset();
	Cam.SetAspect(float(WinX)/float(WinY));

	//Cube.Reset();
//    Skel.Reset();
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Draw() {

	// Begin drawing scene
	glViewport(0, 0, WinX, WinY);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw components
	Cam.Draw();		// Sets up projection & viewing matrices
//	Cube.Draw();
//    Skel.Draw();
    SkelSkin.Draw();

	// Finish drawing scene
	glFinish();
	glutSwapBuffers();
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Quit() {
	glFinish();
	glutDestroyWindow(WindowHandle);
	exit(0);
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Resize(int x,int y) {
	WinX = x;
	WinY = y;
	Cam.SetAspect(float(WinX)/float(WinY));
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Keyboard(int key,int x,int y) {
	switch(key) {
		case 0x1b:		// Escape
			Quit();
			break;
		case 'r':
			Reset();
			break;
        case 'a':
            Skel.GetPrevJoint();
            break;
        case 'd':
            Skel.GetNextJoint();
            break;
        case 'w':
            Skel.GetCurrentJoint()->GetNextDof();
            break;
        case 's':
            Skel.GetCurrentJoint()->GetPrevDof();
            break;
        case '<':{
            Skel.GetCurrentJoint()->GetCurrentDof()->Decrement();
            break;
        }
        case '>':{
            Skel.GetCurrentJoint()->GetCurrentDof()->Increment();
            break;
        }
        case 'p':{
            Skel.GetPrevJoint();
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Tester::MouseButton(int btn,int state,int x,int y) {
	if(btn==GLUT_LEFT_BUTTON) {
		LeftDown = (state==GLUT_DOWN);
	}
	else if(btn==GLUT_MIDDLE_BUTTON) {
		MiddleDown = (state==GLUT_DOWN);
	}
	else if(btn==GLUT_RIGHT_BUTTON) {
		RightDown = (state==GLUT_DOWN);
	}
}

////////////////////////////////////////////////////////////////////////////////

void Tester::MouseMotion(int nx,int ny) {
	int dx = nx - MouseX;
	int dy = -(ny - MouseY);

	MouseX = nx;
	MouseY = ny;

	// Move camera
	// NOTE: this should really be part of Camera::Update()
	if(LeftDown) {
		const float rate=1.0f;
		Cam.SetAzimuth(Cam.GetAzimuth()+dx*rate);
		Cam.SetIncline(Cam.GetIncline()-dy*rate);
	}
	if(RightDown) {
		const float rate=0.01f;
		Cam.SetDistance(Cam.GetDistance()*(1.0f-dx*rate));
	}
}

////////////////////////////////////////////////////////////////////////////////
