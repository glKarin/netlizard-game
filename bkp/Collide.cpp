/*
 *		��Щ��������Jeff Molofee ��2000��д�ģ��ٴ��ұ����лFredric Echols����Ϊ��ʹ��Щ���뿴���������͸�Ч����ʹ������ʹ�á�
 *		����㷢����Щ�����������������������ҵ�վ�� http://nehe.gamedev.net/default.asp ��������֪����
 *********************************************************************************************************************************
 *		����ĵ�����DancingWind����ģ������ʲô������e-mail:zhouwei02@mails.tsinghua.edu.cn
 *		//old code			//�����˴�����//ɾ��
 *		/********************************************************************************************************************/	/*
 *		new code			//�µĴ���λ������/*************/ /*֮�䣬���ڲ���
 *		/********************************************************************************************************************/	/*
/***********************************����Ĵ���***********************************************************************************/

/*********************�������ӵĿ��ļ�*******************************************************************************************/
#pragma comment( lib, "opengl32.lib" )				
#pragma comment( lib, "glu32.lib" )	
#pragma comment( lib, "glut32.lib")
#pragma comment( lib, "glew32.lib")
#pragma comment( lib, "glaux.lib")
#pragma comment( lib, "vfw32.lib" )	
/********************************************************************************************************************************/

#include <windows.h>		
#include <math.h>			
#include <stdio.h>			
#include <stdlib.h>			
#include "glew.h"		
#include "tvector.h"
#include "tmatrix.h"
#include "tray.h"
#include <mmsystem.h>
#include "image.h"


GLfloat spec[]={1.0, 1.0 ,1.0 ,1.0};      //���ù���
GLfloat posl[]={0,400,0,1};               
GLfloat amb[]={0.2f, 0.2f, 0.2f ,1.0f};   
GLfloat amb2[]={0.3f, 0.3f, 0.3f ,1.0f};  

TVector dir(0,0,-10);                     //��ʼ�����߻��ķ���
TVector pos(0,-50,1000);                  //��ʼ�����߻���λ��
float camera_rotation=0;                  //��ʼ�����߻�����ת�ٶ�


TVector veloc(0.5,-0.1,0.5);              //��ʼ������ٶ�
TVector accel(0,-0.05,0);                 //��ʼ������������ٶ�

TVector ArrayVel[10];                     //�����������ٶ�
TVector ArrayPos[10];                     //�����������λ��
TVector OldPos[10];                       //������һ�����λ��
int NrOfBalls;                            //������ĸ���
double Time=0.6;                          //����ģ���ʱ�侫��
int hook_toball1=0, sounds=1;             //�Ƿ���������׼��, ��������
                                          
//ƽ��ṹ
struct Plane
{
	TVector _Position;
	TVector _Normal;
};
                                         
//Բ���ṹ
struct Cylinder
{                          
	TVector _Position;
    TVector _Axis;
    double _Radius;
};
                                          
//��ը�ṹ
struct Explosion
{
	TVector _Position;
	float   _Alpha;
	float   _Scale;
};

Plane pl1,pl2,pl3,pl4,pl5;                //�����5��ƽ��
Cylinder cyl1,cyl2,cyl3;                  //3��Բ��
GLUquadricObj *cylinder_obj;              //ʹ�ö��μ�������ȾԲ��
GLuint texture[4], dlist;                 //�����������ʾ�б�
Explosion ExplosionArray[20];             //���汬ըЧ��

//������ײ����
int TestIntersionPlane(const Plane& plane,const TVector& position,const TVector& direction, double& lamda, TVector& pNormal);
int TestIntersionCylinder(const Cylinder& cylinder,const TVector& position,const TVector& direction, double& lamda, TVector& pNormal,TVector& newposition);
void LoadGLTextures();                    //��������
void InitVars();
void idle();

HDC				hDC=NULL;			
HGLRC			hRC=NULL;			
HWND			hWnd=NULL;			
HINSTANCE		hInstance;			

DEVMODE			DMsaved;			// ����ǰһ����ʾ�����趨

bool			keys[256];			
bool			active=TRUE;		
bool			fullscreen=TRUE;	


int ProcessKeys();
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		
{
	if (height==0)										
	{
		height=1;										
	}

	glViewport(0,0,width,height);						

	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();									

	gluPerspective(50.0f,(GLfloat)width/(GLfloat)height,10.f,1700.0f);

	glMatrixMode(GL_MODELVIEW);						
	glLoadIdentity();								
}

int InitGL(GLvoid)										// ��ʼ��OpenGL
{
   	float df=100.0;

	glClearDepth(1.0f);									
	glEnable(GL_DEPTH_TEST);							
	glDepthFunc(GL_LEQUAL);								
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	

	glClearColor(0,0,0,0);
  	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	
	glMaterialfv(GL_FRONT,GL_SPECULAR,spec);
	glMaterialfv(GL_FRONT,GL_SHININESS,&df);

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,GL_POSITION,posl);
	glLightfv(GL_LIGHT0,GL_AMBIENT,amb2);
	glEnable(GL_LIGHT0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,amb);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
   
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
   	
	glEnable(GL_TEXTURE_2D);
    LoadGLTextures();

	//���������ഹֱ��ƽ��ģ�ⱬըЧ��
    glNewList(dlist=glGenLists(1), GL_COMPILE);
    glBegin(GL_QUADS);
	glRotatef(-45,0,1,0);
	glNormal3f(0,0,1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-50,-40,0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(50,-40,0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(50,40,0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-50,40,0);
    glNormal3f(0,0,-1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-50,40,0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(50,40,0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(50,-40,0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-50,-40,0);

	glNormal3f(1,0,0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0,-40,50);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0,-40,-50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0,40,-50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0,40,50);
    glNormal3f(-1,0,0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0,40,50);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0,40,-50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0,-40,-50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0,-40,50);
	glEnd();
    glEndList();

	return TRUE;										
}

int DrawGLScene(GLvoid)	            // ���Ƴ���
{								
	int i;
	
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //���������������
	if (hook_toball1)
	{
		TVector unit_followvector=ArrayVel[0];
		unit_followvector.unit();
 		gluLookAt(ArrayPos[0].X()+250,ArrayPos[0].Y()+250 ,ArrayPos[0].Z(), ArrayPos[0].X()+ArrayVel[0].X() ,ArrayPos[0].Y()+ArrayVel[0].Y() ,ArrayPos[0].Z()+ArrayVel[0].Z() ,0,1,0);  
    
    }
	//���쳯��̶���
	else
	    gluLookAt(pos.X(),pos.Y(),pos.Z(), pos.X()+dir.X(),pos.Y()+dir.Y(),pos.Z()+dir.Z(), 0,1.0,0.0);
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glRotatef(camera_rotation,0,1,0);

	//��Ⱦ��
	for (i=0;i<NrOfBalls;i++)
	{
		switch(i){
        case 1: glColor3f(1.0f,1.0f,1.0f);
			       break;
		case 2: glColor3f(1.0f,1.0f,0.0f);
			       break;
		case 3: glColor3f(0.0f,1.0f,1.0f);
			       break;
		case 4: glColor3f(0.0f,1.0f,0.0f);
			       break;
		case 5: glColor3f(0.0f,0.0f,1.0f);
			       break;
		case 6: glColor3f(0.65f,0.2f,0.3f);
			       break;
		case 7: glColor3f(1.0f,0.0f,1.0f);
			       break;
		case 8: glColor3f(0.0f,0.7f,0.4f);
			       break;
		default: glColor3f(1.0f,0,0);
		}
		glPushMatrix();
		glTranslated(ArrayPos[i].X(),ArrayPos[i].Y(),ArrayPos[i].Z());
		gluSphere(cylinder_obj,20,20,20);
		glPopMatrix();
	}
		
	glEnable(GL_TEXTURE_2D);
	//��Ⱦǽ��
	glBindTexture(GL_TEXTURE_2D, texture[3]); 
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(320,320,320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(320,-320,320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-320,-320,320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-320,320,320);
        
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-320,320,-320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-320,-320,-320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(320,-320,-320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(320,320,-320);
    
	glTexCoord2f(1.0f, 0.0f); glVertex3f(320,320,-320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(320,-320,-320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(320,-320,320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(320,320,320);
	
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-320,320,320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-320,-320,320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-320,-320,-320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-320,320,-320);
	glEnd();

	//��Ⱦ����
	glBindTexture(GL_TEXTURE_2D, texture[2]); 
    glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-320,-320,320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(320,-320,320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(320,-320,-320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-320,-320,-320);
	glEnd();

    //��ȾԲ��
	glBindTexture(GL_TEXTURE_2D, texture[0]);   
	glColor3f(0.5,0.5,0.5);
    glPushMatrix();
	glRotatef(90, 1,0,0);
	glTranslatef(0,0,-500);
	gluCylinder(cylinder_obj, 60, 60, 1000, 20, 2);
	glPopMatrix();

  	glPushMatrix();
  	glTranslatef(200,-300,-500);
	gluCylinder(cylinder_obj, 60, 60, 1000, 20, 2);
	glPopMatrix();

	glPushMatrix();
    glTranslatef(-200,0,0);
	glRotatef(135, 1,0,0);
	glTranslatef(0,0,-500);
	gluCylinder(cylinder_obj, 30, 30, 1000, 20, 2);
	glPopMatrix();
	
	//��Ⱦ��ı�ըЧ��
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
    glBindTexture(GL_TEXTURE_2D, texture[1]);   
	for(i=0; i<20; i++)
	{
		if(ExplosionArray[i]._Alpha>=0)
		{
		   glPushMatrix();
           ExplosionArray[i]._Alpha-=0.01f;
		   ExplosionArray[i]._Scale+=0.03f;
		   glColor4f(1,1,0,ExplosionArray[i]._Alpha);	 
		   glScalef(ExplosionArray[i]._Scale,ExplosionArray[i]._Scale,ExplosionArray[i]._Scale);
           glTranslatef((float)ExplosionArray[i]._Position.X()/ExplosionArray[i]._Scale, (float)ExplosionArray[i]._Position.Y()/ExplosionArray[i]._Scale, (float)ExplosionArray[i]._Position.Z()/ExplosionArray[i]._Scale);
           glCallList(dlist);
	       glPopMatrix();
		}
	}
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
 

	return TRUE;										
}

GLvoid KillGLWindow(GLvoid)								
{
	if (fullscreen)										
	{
		if (!ChangeDisplaySettings(NULL,CDS_TEST)) { 
			ChangeDisplaySettings(NULL,CDS_RESET);		
			ChangeDisplaySettings(&DMsaved,CDS_RESET);	
		} else {
			ChangeDisplaySettings(NULL,CDS_RESET);
		}
			
		ShowCursor(TRUE);								
	}

	if (hRC)											
	{
		if (!wglMakeCurrent(NULL,NULL))					
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;									
	}

	if (hWnd && !DestroyWindow(hWnd))				
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;									
	}

	if (!UnregisterClass("OpenGL",hInstance))			
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;								
	}
}
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			
	WNDCLASS	wc;						
	DWORD		dwExStyle;				
	DWORD		dwStyle;				
	RECT		WindowRect;				
	WindowRect.left=(long)0;			
	WindowRect.right=(long)width;		
	WindowRect.top=(long)0;				
	WindowRect.bottom=(long)height;		

	fullscreen=fullscreenflag;			

	hInstance			= GetModuleHandle(NULL);				
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	
	wc.lpfnWndProc		= (WNDPROC) WndProc;					
	wc.cbClsExtra		= 0;									
	wc.cbWndExtra		= 0;									
	wc.hInstance		= hInstance;							
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			
	wc.hbrBackground	= NULL;									
	wc.lpszMenuName		= NULL;									
	wc.lpszClassName	= "OpenGL";								
	
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &DMsaved); 

	if (fullscreen)												
	{
		DEVMODE dmScreenSettings;								
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		
		dmScreenSettings.dmPelsWidth	= width;				
		dmScreenSettings.dmPelsHeight	= height;				
		dmScreenSettings.dmBitsPerPel	= bits;					
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		
			}
			else
			{
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									
			}
		}
	}

	if (!RegisterClass(&wc))									
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											
	}

	if (fullscreen)												
	{
		dwExStyle=WS_EX_APPWINDOW;								
		dwStyle=WS_POPUP;										
		ShowCursor(FALSE);										
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			
		dwStyle=WS_OVERLAPPEDWINDOW;							
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);	

	if (!(hWnd=CreateWindowEx(	dwExStyle,						
								"OpenGL",						
								title,							
								dwStyle |						
								WS_CLIPSIBLINGS |				
								WS_CLIPCHILDREN,				
								0, 0,							
								WindowRect.right-WindowRect.left,	
								WindowRect.bottom-WindowRect.top,	
								NULL,								
								NULL,								
								hInstance,							
								NULL)))								
	{
		KillGLWindow();								
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	static	PIXELFORMATDESCRIPTOR pfd=				
	{
		sizeof(PIXELFORMATDESCRIPTOR),				
		1,											
		PFD_DRAW_TO_WINDOW |						
		PFD_SUPPORT_OPENGL |						
		PFD_DOUBLEBUFFER,							
		PFD_TYPE_RGBA,								
		bits,										
		0, 0, 0, 0, 0, 0,							
		0,											
		0,											
		0,											
		0, 0, 0, 0,									
		16,											
		0,											
		0,											
		PFD_MAIN_PLANE,								
		0,											
		0, 0, 0										
	};
	
	if (!(hDC=GetDC(hWnd)))							
	{
		KillGLWindow();								
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	
	{
		KillGLWindow();								
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		
	{
		KillGLWindow();								
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if (!(hRC=wglCreateContext(hDC)))				
	{
		KillGLWindow();								
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if(!wglMakeCurrent(hDC,hRC))					
	{
		KillGLWindow();								
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	ShowWindow(hWnd,SW_SHOW);						
	SetForegroundWindow(hWnd);						
	SetFocus(hWnd);									
	ReSizeGLScene(width, height);					

    if (!InitGL())									
	{
		KillGLWindow();								
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	return TRUE;									
}


LRESULT CALLBACK WndProc(	HWND	hWnd,			
							UINT	uMsg,			
							WPARAM	wParam,			
							LPARAM	lParam)			
{
	switch (uMsg)									
	{
		case WM_ACTIVATE:							
		{
			if (!HIWORD(wParam))					
			{
				active=TRUE;						
			}
			else
			{
				active=FALSE;						
			}

			return 0;								
		}

		case WM_SYSCOMMAND:							
		{
			switch (wParam)							
			{
				case SC_SCREENSAVE:					
				case SC_MONITORPOWER:				
				return 0;							
			}
			break;									
		}

		case WM_CLOSE:								
		{
			PostQuitMessage(0);						
			return 0;								
		}

		case WM_KEYDOWN:							
		{
			keys[wParam] = TRUE;					
			return 0;								
		}

		case WM_KEYUP:								
		{
			keys[wParam] = FALSE;					
			return 0;								
		}

		case WM_SIZE:								
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam)); 
			return 0;								
		}
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,		
					HINSTANCE	hPrevInstance,	
					LPSTR		lpCmdLine,		
					int			nCmdShow)		
{
	MSG		msg;								
	BOOL	done=FALSE;							

	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							
	}

	InitVars();                                   

	if (!CreateGLWindow("Magic Room",640,480,16,fullscreen))
	{
		return 0;									
	}

	while(!done)									
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	
		{
			if (msg.message==WM_QUIT)				
			{
				done=TRUE;							
			}
			else									
			{
				TranslateMessage(&msg);				
				DispatchMessage(&msg);				
			}
		}
		else										
		    if (active)
			{
				if (keys[VK_ESCAPE])	
				{
					done=TRUE;					
				}
				else							
				{
					idle();                     
					DrawGLScene();              
					SwapBuffers(hDC);			
				}
	
				if (!ProcessKeys()) return 0;
			}
	}

	KillGLWindow();								
    glDeleteTextures(4,texture);
	return (msg.wParam);						
}



//�ж�������Ƿ��ཻ�����򷵻�1�����򷵻�0
int FindBallCol(TVector& point, double& TimePoint, double Time2, int& BallNr1, int& BallNr2)
{
	TVector RelativeV;
	TRay rays;
	double MyTime=0.0, Add=Time2/150.0, Timedummy=10000, Timedummy2=-1;
	TVector posi;
	
	//�ж�������Ƿ��ཻ
	for (int i=0;i<NrOfBalls-1;i++)
	{
	 for (int j=i+1;j<NrOfBalls;j++)
	 {	
		    RelativeV=ArrayVel[i]-ArrayVel[j];
			rays=TRay(OldPos[i],TVector::unit(RelativeV));
			MyTime=0.0;

			if ( (rays.dist(OldPos[j])) > 40) continue; 

			while (MyTime<Time2)
			{
			   MyTime+=Add;
			   posi=OldPos[i]+RelativeV*MyTime;
			   if (posi.dist(OldPos[j])<=40) {
										   point=posi;
										   if (Timedummy>(MyTime-Add)) Timedummy=MyTime-Add;
										   BallNr1=i;
										   BallNr2=j;
										   break;
										}
			
			}
	 }

	}

	if (Timedummy!=10000) { TimePoint=Timedummy;
	                        return 1;
	}

	return 0;
}

//ģ�⺯����������ײ��������ģ��
void idle()
{
  double rt,rt2,rt4,lamda=10000;
  TVector norm,uveloc;
  TVector normal,point,time;
  double RestTime,BallTime;
  TVector Pos2;
  int BallNr=0,dummy=0,BallColNr1,BallColNr2;
  TVector Nc;

  //���û�����������ϣ���ת�����
  if (!hook_toball1)
  {
	  camera_rotation+=0.1f;
	  if (camera_rotation>360)
		  camera_rotation=0;
  }
 
	  RestTime=Time;
	  lamda=1000;

	//�����������ٶ�
	for (int j=0;j<NrOfBalls;j++)
	  ArrayVel[j]+=accel*RestTime;

	//�����һ����ģ��ʱ����(������������㣬����������)
	while (RestTime>ZERO)
	{
	   lamda=10000;   
	
	   //����ÿ�����ҵ������������ײ��
   	   for (int i=0;i<NrOfBalls;i++)
	   {
		      //�����µ�λ�ú��ƶ��ľ���
			  OldPos[i]=ArrayPos[i];
			  TVector::unit(ArrayVel[i],uveloc);
			  ArrayPos[i]=ArrayPos[i]+ArrayVel[i]*RestTime;
			  rt2=OldPos[i].dist(ArrayPos[i]);

			  //�����Ƿ��ǽ����ײ
			  if (TestIntersionPlane(pl1,OldPos[i],uveloc,rt,norm))
			  {  
				  //������ײ��ʱ��
				  rt4=rt*RestTime/rt2;

				  //���С�ڵ�ǰ�������ײʱ�䣬�������
				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						 if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						  {
							normal=norm;
							point=OldPos[i]+uveloc*rt;
							lamda=rt4;
							BallNr=i;
						  }
				  }
			  }
			  
			  if (TestIntersionPlane(pl2,OldPos[i],uveloc,rt,norm))
			  {
				   rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=OldPos[i]+uveloc*rt;
							lamda=rt4;
							BallNr=i;
							dummy=1;
						 }
				  }
				 
			  }

			  if (TestIntersionPlane(pl3,OldPos[i],uveloc,rt,norm))
			  {
			      rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=OldPos[i]+uveloc*rt;
							lamda=rt4;
							BallNr=i;
						 }
				  }
			  }

			  if (TestIntersionPlane(pl4,OldPos[i],uveloc,rt,norm))
			  {
				  rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=OldPos[i]+uveloc*rt;
							lamda=rt4;
							BallNr=i;
						 }
				  }
			  }

			  if (TestIntersionPlane(pl5,OldPos[i],uveloc,rt,norm))
			  {
				  rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=OldPos[i]+uveloc*rt;
							lamda=rt4;
							BallNr=i;
						 }
				  }
			  }

              //�����Ƿ�������Բ������
			  if (TestIntersionCylinder(cyl1,OldPos[i],uveloc,rt,norm,Nc))
			  {
				  rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=Nc;
							lamda=rt4;
							BallNr=i;
						 }
				  }
				 
			  }
			  if (TestIntersionCylinder(cyl2,OldPos[i],uveloc,rt,norm,Nc))
			  {
				  rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=Nc;
							lamda=rt4;
							BallNr=i;
						 }
				  }
				 
			  }
			  if (TestIntersionCylinder(cyl3,OldPos[i],uveloc,rt,norm,Nc))
			  {
				  rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=Nc;
							lamda=rt4;
							BallNr=i;
						 }
				  }
				 
			  }
	   }


	   //����ÿ����֮�����ײ�������ײʱ��С�����������ײ�����滻����
	   if (FindBallCol(Pos2,BallTime,RestTime,BallColNr1,BallColNr2))
	   {
				  if (sounds)
					  PlaySound("Data/Explode.wav",NULL,SND_FILENAME|SND_ASYNC);
			      
				  if ( (lamda==10000) || (lamda>BallTime) )
				  {
					  RestTime=RestTime-BallTime;

					  TVector pb1,pb2,xaxis,U1x,U1y,U2x,U2y,V1x,V1y,V2x,V2y;
					  double a,b;

					  pb1=OldPos[BallColNr1]+ArrayVel[BallColNr1]*BallTime;
					  pb2=OldPos[BallColNr2]+ArrayVel[BallColNr2]*BallTime;
					  xaxis=(pb2-pb1).unit();

					  a=xaxis.dot(ArrayVel[BallColNr1]);
					  U1x=xaxis*a;
					  U1y=ArrayVel[BallColNr1]-U1x;

					  xaxis=(pb1-pb2).unit();
					  b=xaxis.dot(ArrayVel[BallColNr2]);
      				  U2x=xaxis*b;
					  U2y=ArrayVel[BallColNr2]-U2x;

					  V1x=(U1x+U2x-(U1x-U2x))*0.5;
					  V2x=(U1x+U2x-(U2x-U1x))*0.5;
					  V1y=U1y;
					  V2y=U2y;

					  for (j=0;j<NrOfBalls;j++)
					  ArrayPos[j]=OldPos[j]+ArrayVel[j]*BallTime;

					  ArrayVel[BallColNr1]=V1x+V1y;
					  ArrayVel[BallColNr2]=V2x+V2y;

					  //Update explosion array
                      for(j=0;j<20;j++)
					  {
						  if (ExplosionArray[j]._Alpha<=0)
						  {
							  ExplosionArray[j]._Alpha=1;
                              ExplosionArray[j]._Position=ArrayPos[BallColNr1];
							  ExplosionArray[j]._Scale=1;
							  break;
						  }
					  }

					  continue;
				  }
		}
  
	    //���Ĳ��ԣ��滻�´���ײ��ʱ�䣬�����±�ըЧ��������
		if (lamda!=10000)
		{		 
			RestTime-=lamda;

			for (j=0;j<NrOfBalls;j++)
			ArrayPos[j]=OldPos[j]+ArrayVel[j]*lamda;

			rt2=ArrayVel[BallNr].mag();
			ArrayVel[BallNr].unit();
			ArrayVel[BallNr]=TVector::unit( (normal*(2*normal.dot(-ArrayVel[BallNr]))) + ArrayVel[BallNr] );
			ArrayVel[BallNr]=ArrayVel[BallNr]*rt2;
				
			for(j=0;j<20;j++)
			{
			  if (ExplosionArray[j]._Alpha<=0)
			  {
				  ExplosionArray[j]._Alpha=1;
                    ExplosionArray[j]._Position=point;
				  ExplosionArray[j]._Scale=1;
				  break;
			  }
			}
		}
		else
			RestTime=0;

	}

}

/*************************************************************************************/
/*************************************************************************************/
/***        Init Variables                                                        ****/
/*************************************************************************************/
/*************************************************************************************/
void InitVars()
{
	 //create palnes
	pl1._Position=TVector(0,-300,0);
	pl1._Normal=TVector(0,1,0);
	pl2._Position=TVector(300,0,0);
	pl2._Normal=TVector(-1,0,0);
	pl3._Position=TVector(-300,0,0);
	pl3._Normal=TVector(1,0,0);
	pl4._Position=TVector(0,0,300);
	pl4._Normal=TVector(0,0,-1);
	pl5._Position=TVector(0,0,-300);
	pl5._Normal=TVector(0,0,1);


	//create cylinders
	cyl1._Position=TVector(0,0,0);
	cyl1._Axis=TVector(0,1,0);
	cyl1._Radius=60+20;
	cyl2._Position=TVector(200,-300,0);
	cyl2._Axis=TVector(0,0,1);
	cyl2._Radius=60+20;
	cyl3._Position=TVector(-200,0,0);
	cyl3._Axis=TVector(0,1,1);
    cyl3._Axis.unit();
	cyl3._Radius=30+20;
	//create quadratic object to render cylinders
	cylinder_obj= gluNewQuadric();
	gluQuadricTexture(cylinder_obj, GL_TRUE);

    //Set initial positions and velocities of balls
	//also initialize array which holds explosions
	NrOfBalls=10;
	ArrayVel[0]=veloc;
	ArrayPos[0]=TVector(199,180,10);
	ExplosionArray[0]._Alpha=0;
	ExplosionArray[0]._Scale=1;
	ArrayVel[1]=veloc;
	ArrayPos[1]=TVector(0,150,100);
	ExplosionArray[1]._Alpha=0;
	ExplosionArray[1]._Scale=1;
	ArrayVel[2]=veloc;
	ArrayPos[2]=TVector(-100,180,-100);
	ExplosionArray[2]._Alpha=0;
	ExplosionArray[2]._Scale=1;
	for (int i=3; i<10; i++)
	{
         ArrayVel[i]=veloc;
	     ArrayPos[i]=TVector(-500+i*75, 300, -500+i*50);
		 ExplosionArray[i]._Alpha=0;
	     ExplosionArray[i]._Scale=1;
	}
	for (i=10; i<20; i++)
	{
         ExplosionArray[i]._Alpha=0;
	     ExplosionArray[i]._Scale=1;
	}
}

//�ж������Ƿ��ƽ���ཻ�����򷵻�1�����򷵻�0
int TestIntersionPlane(const Plane& plane,const TVector& position,const TVector& direction, double& lamda, TVector& pNormal)
{

    double DotProduct=direction.dot(plane._Normal);
	double l2;

    //�ж��Ƿ�ƽ����ƽ��
    if ((DotProduct<ZERO)&&(DotProduct>-ZERO)) 
		return 0;

    l2=(plane._Normal.dot(plane._Position-position))/DotProduct;

    if (l2<-ZERO) 
		return 0;

    pNormal=plane._Normal;
	lamda=l2;
    return 1;
}

//�ж������Ƿ��Բ���ཻ�����򷵻�1�����򷵻�0
int TestIntersionCylinder(const Cylinder& cylinder,const TVector& position,const TVector& direction, double& lamda, TVector& pNormal,TVector& newposition)
{
	TVector RC;
	double d;
	double t,s;
	TVector n,D,O;
	double ln;
	double in,out;
	

	TVector::subtract(position,cylinder._Position,RC);
	TVector::cross(direction,cylinder._Axis,n);

    ln=n.mag();

	if ( (ln<ZERO)&&(ln>-ZERO) ) return 0;

	n.unit();

	d= fabs( RC.dot(n) );

    if (d<=cylinder._Radius)
	{
		TVector::cross(RC,cylinder._Axis,O);
		t= - O.dot(n)/ln;
		TVector::cross(n,cylinder._Axis,O);
		O.unit();
		s= fabs( sqrt(cylinder._Radius*cylinder._Radius - d*d) / direction.dot(O) );

		in=t-s;
		out=t+s;

		if (in<-ZERO){
			if (out<-ZERO) return 0;
			else lamda=out;
		}
		else
        if (out<-ZERO) {
			      lamda=in;
		}
		else
		if (in<out) lamda=in;
		else lamda=out;

    	newposition=position+direction*lamda;
		TVector HB=newposition-cylinder._Position;
		pNormal=HB - cylinder._Axis*(HB.dot(cylinder._Axis));
		pNormal.unit();

		return 1;
	}
    
	return 0;
}

//��������
void LoadGLTextures() 
{	
    //����ͼ��
    Image *image1, *image2, *image3, *image4;
    
    image1 = (Image *) malloc(sizeof(Image));
    if (image1 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }
	image2 = (Image *) malloc(sizeof(Image));
    if (image2 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }
	image3 = (Image *) malloc(sizeof(Image));
    if (image3 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }
	image4 = (Image *) malloc(sizeof(Image));
    if (image4 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }

    if (!ImageLoad("data/marble.bmp", image1)) {
	exit(1);
    } 
	if (!ImageLoad("data/spark.bmp", image2)) {
	exit(1);
    }
	if (!ImageLoad("data/boden.bmp", image3)) {
	exit(1);
    } 
	if (!ImageLoad("data/wand.bmp", image4)) {
	exit(1);
    }

    //��������
    glGenTextures(2, &texture[0]);

    glBindTexture(GL_TEXTURE_2D, texture[0]);   
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);

    glBindTexture(GL_TEXTURE_2D, texture[1]); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image2->sizeX, image2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image2->data);


    glGenTextures(2, &texture[2]);

    glBindTexture(GL_TEXTURE_2D, texture[2]); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image3->sizeX, image3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image3->data);

    glBindTexture(GL_TEXTURE_2D, texture[3]);  
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image4->sizeX, image4->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image4->data);

	free(image1->data);
	free(image1);
	free(image2->data);
	free(image2);
	free(image3->data);
	free(image3);
	free(image4->data);
	free(image4);
};

//ִ�а�������
int ProcessKeys()
{
	if (keys[VK_UP])    pos+=TVector(0,0,-10);
	if (keys[VK_UP])    pos+=TVector(0,0,10);
	if (keys[VK_LEFT])  camera_rotation+=10;
	if (keys[VK_RIGHT]) camera_rotation-=10;
	if (keys[VK_ADD])
	{
		Time+=0.1;
        keys[VK_ADD]=FALSE;
	}
	if (keys[VK_SUBTRACT])
	{
		Time-=0.1;
        keys[VK_SUBTRACT]=FALSE;
	}
	if (keys[VK_F3]) 
	{   
		sounds^=1;
        keys[VK_F3]=FALSE;
	}
	if (keys[VK_F2])
	{
	    hook_toball1^=1;
	    camera_rotation=0;
		keys[VK_F2]=FALSE;
	}
	if (keys[VK_F1])						
	{
		keys[VK_F1]=FALSE;					
		KillGLWindow();						
		fullscreen=!fullscreen;				
		if (!CreateGLWindow("Magic Room",640,480,16,fullscreen))
		{
			return 0;						
		}
	}

	return 1;
}

/********************************************************************************************************************************/