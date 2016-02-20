//#include <GL/gl.h>
//#include <GL/glu.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#define DR (2*acos(0.0)/180)
static GLfloat vertices[]={
	-3.5,3.5,2.0,
	3.5,3.5,2.0,
	3.5,-3.5,2.0,
	-3.5,-3.5,2.0,
	-3.5,3.5,3.0,
	3.5,3.5,3.0,
	3.5,-3.5,3.0,
	-3.5,-3.5,3.0};
static GLint indices[]={
	0,1,2,3,
	0,4,5,1,
	3,7,6,2,
	4,0,3,7,
	1,5,6,2,
	4,5,6,7};

float X=0.0,Y=0.0;
unsigned int WP=0xfff;
unsigned int BP=(0xfff)<<20;
void drawpieces(float x, float y, float radius, int row, int column)
{
	int i;
	int bit=31-(4*row+column/2);
	if(WP&((unsigned int)1<<bit))
		glColor3f(1.0,1.0,1.0);
	else if(BP&((unsigned int)1<<bit))
		glColor3f(1.0,0.0,0.0);
	else
		return;
	/*glBegin(GL_POLYGON);
	for(i=0;i<360;i++)
	{
		float degInRad=i*Deg2Rad;
		glVertex3f(radius*cos(degInRad)+x,radius*sin(degInRad)+y,2.0);
	}
	glEnd();*/
	glPushMatrix();
	glTranslatef(x,y,1.875);
	glutSolidCylinder(radius,0.25,100,100);
	glPopMatrix();
}
void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}
void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
	glTranslatef(0.0,0.0,7);
	glRotatef(X,1.0,0.0,0.0);
	glRotatef(Y,0.0,1.0,0.0);
	//glutWireCube(1.0);
	int i,j,color;
	glColor3f(0.87,0.723,0.53);
	glBegin(GL_QUADS);
	for(i=0;i<6;i++)
	{
		glVertex3fv(&vertices[indices[i*4]*3]);
		glVertex3fv(&vertices[indices[i*4+1]*3]);
		glVertex3fv(&vertices[indices[i*4+2]*3]);
		glVertex3fv(&vertices[indices[i*4+3]*3]);
	}
	glEnd();
	/*glBegin(GL_POLYGON);
	  	glVertex3f(-3.5,3.5,2);
		glVertex3f(3.5,3.5,2);
		glVertex3f(3.5,-3.5,2);
		glVertex3f(-3.5,-3.5,2;
	glEnd();*/
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_QUADS);
		glVertex3f(-3.3,-3.3,2);
		glVertex3f(3.3,-3.3,2);
		glVertex3f(3.3,3.3,2);
		glVertex3f(-3.3,3.3,2);
	glEnd();
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if((j%2==0 && i%2==0) || (j%2 && i%2))
			{
				glColor3f(1.0,1.0,1.0);
				color=1;
			}
			else
			{
				glColor3f(0.0,0.0,0.0);
				color=0;
			}
			glBegin(GL_POLYGON);
				glVertex3f(-3.3+0.825*j,3.3-0.825*i,2.0);
				glVertex3f(-3.3+0.825*j,3.3-0.825*(i+1),2.0);
				glVertex3f(-3.3+0.825*(j+1),3.3-0.825*(i+1),2.0);
				glVertex3f(-3.3+0.825*(j+1),3.3-0.825*i,2.0);
			glEnd();
			/*if(!color && i!=3 && i!=4)
				drawpieces((2*(-3.3+0.825*j)+0.825)/2,(2*(3.3-0.825*i)-0.825)/2,0.3,i);*/
		}
	}
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
			if(!((j%2==0 && i%2==0) || (j%2 && i%2)))
				drawpieces((2*(-3.3+0.825*j)+0.825)/2,(2*(3.3-0.825*i)-0.825)/2,0.3,i,j);
	glPopMatrix();
	glutSwapBuffers();
}
void ChangeCam()
{
	glLoadIdentity ();            
	printf("FLAG!!!\n");
	gluLookAt (0.0, 9.0,9.0, 0.0, 0.0, 10.0, 0.0, 1.0, 0.0);
}
void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'a' : Y+=5;
			   glutPostRedisplay();
			   break;
		case 'd' : Y-=5;
			   glutPostRedisplay();
			   break;
		case 'w' : X+=5;
			   glutPostRedisplay();
			   break;
		case 's' : X-=5;
			   glutPostRedisplay();
			   break;
		case 'c' : ChangeCam();
			   break;
							   
	}
}
void reshape (int w, int h)
{
	printf("FLAG RESHAPE!\n");
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0,1.0,1.5,20.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();            
	gluLookAt (0.0, 0.0,0.0, 0.0, 0.0, 10.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500,500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("BlackPearl Checkers v1.0");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
