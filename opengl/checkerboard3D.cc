#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#define DR (2*acos(0.0)/180)

static GLfloat vertices[]={
	-3.5,3.5,-0.25,
	3.5,3.5,-0.25,
	3.5,-3.5,-0.25,
	-3.5,-3.5,-0.25,
	-3.5,3.5,0.25,
	3.5,3.5,0.25,
	3.5,-3.5,0.25,
	-3.5,-3.5,0.25};
	static GLint indices[]={
	0,3,2,1,
	0,1,5,4,
	3,2,6,7,
	4,0,3,7,
	1,2,6,5,
	4,7,6,5};
	GLfloat mat_emission_white[]={1.0,1.0,1.0,1.0};
	GLfloat mat_emission_black[]={0.0,0.0,0.0,1.0};
	GLfloat mat_emission_red[]={1.0,0.0,0.0,1.0};
	GLfloat mat_emission_wood[]={0.87,0.723,0.53,1.0};
	GLfloat mat_emission_offwhite[]={0.8,0.8,0.8,1.0};
	GLfloat depth=0.0;
	int X=0,Y=0,Z=0;
	unsigned int WP=0xfff;
	unsigned int BP=(0xfff)<<20;
	unsigned int K=0;
void drawpieces(float x, float y, float radius, int row, int column)
{
	int i;
	int bit=31-(4*row+column/2);
	if(WP&((unsigned int)1<<bit))
	{
		glColor3f(1.0,1.0,1.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission_offwhite);
	}
	else if(BP&((unsigned int)1<<bit))
	{
		glColor3f(1.0,0.0,0.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission_red);
	}
	else
		return;
	glPushMatrix();
	glTranslatef(x,y,-0.375);
	glutSolidCylinder(radius,0.25,100,100);
	if(!((WP&K)&((unsigned int)1<<bit)) && !((BP&K)&((unsigned int)1<<bit)))
	{
		glPopMatrix();
		return;
	}
	glTranslatef(0,0,-0.125+radius/2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission_black);
	glutSolidSphere(radius/2,100,100);
	glPopMatrix();
}
void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
	GLfloat light_position[]={0.0,0.0,-9.0,1.0};
	GLfloat spot_direction[] = { 0.0, 0.0, 10.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}
void display(void)
{
	int i,j,color;
	glClear (GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt (0.0, 0.0,depth, 0.0, 0.0, 10.0, 0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0,0.0,9);
	glRotatef((GLfloat)X,1.0,0.0,0.0);
	glRotatef((GLfloat)Y,0.0,1.0,0.0);
	glRotatef((GLfloat)Z,0.0,0.0,1.0);
	glNormal3f(1.0,0.0,0.0);
	glNormal3f(-1.0,0.0,0.0);
	glNormal3f(0.0,1.0,0.0);
	glNormal3f(0.0,-1.0,0.0);
	glNormal3f(0.0,0.0,1.0);
	glNormal3f(0.0,0.0,-1.0);
	glColor3f(0.87,0.723,0.53);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission_wood);
	glBegin(GL_QUADS);
	for(i=0;i<6;i++)
	{
		glVertex3fv(&vertices[indices[i*4]*3]);
		glVertex3fv(&vertices[indices[i*4+1]*3]);
		glVertex3fv(&vertices[indices[i*4+2]*3]);
		glVertex3fv(&vertices[indices[i*4+3]*3]);
	}
	glEnd();
	glColor3f(1.0,1.0,1.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission_white);
	glBegin(GL_QUADS);
		glVertex3f(-3.3,-3.3,-0.251);
		glVertex3f(3.3,-3.3,-0.251);
		glVertex3f(3.3,3.3,-0.251);
		glVertex3f(-3.3,3.3,-0.251);
	glEnd();
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if((j%2==0 && i%2==0) || (j%2 && i%2))
			{
				glColor3f(1.0,1.0,1.0);
				glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission_white);
				color=1;
			}
			else
			{
				glColor3f(0.0,0.0,0.0);
				glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission_black);
				color=0;
			}
			glBegin(GL_POLYGON);
				glVertex3f(-3.3+0.825*j,3.3-0.825*i,-0.252);
				glVertex3f(-3.3+0.825*j,3.3-0.825*(i+1),-0.252);
				glVertex3f(-3.3+0.825*(j+1),3.3-0.825*(i+1),-0.252);
				glVertex3f(-3.3+0.825*(j+1),3.3-0.825*i,-0.252);
			glEnd();
		}
	}
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
			if(!((j%2==0 && i%2==0) || (j%2 && i%2)))
				drawpieces((2*(-3.3+0.825*j)+0.825)/2,(2*(3.3-0.825*i)-0.825)/2,0.3,i,j);
	glPopMatrix();
	glutSwapBuffers();
}
void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'a' : Y=(Y+10)%360;
			   glutPostRedisplay();
			   break;
		case 'd' : Y=(Y-10)%360;
			   glutPostRedisplay();
			   break;
		case 'w' : X=(X+10)%360;
			   glutPostRedisplay();
			   break;
		case 's' : X=(X-10)%360;
			   glutPostRedisplay();
			   break;
		case 'z' : depth+=0.2;
			   glutPostRedisplay();
			   break;
		case 'x' : depth-=0.2;
			   glutPostRedisplay();
			   break;
		case 'q' : Z=(Z+10)%360;
			   glutPostRedisplay();
			   break;
		case 'e' : Z=(Z-10)%360;
			   glutPostRedisplay();
			   break;
		default : break;
							   
	}
}
void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	//gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
	gluPerspective(60.0,1.0,1.5,20.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();            
	gluLookAt (0.0, 0.0,depth, 0.0, 0.0, 10.0, 0.0, 1.0, 0.0);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
