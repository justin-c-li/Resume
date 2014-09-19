//#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>

using namespace std;
/*============================================================================
 *Name        : CSCI-3010U Project.cpp
 *Author      : Justin Li
 *Version     :
 *Copyright   : Your copyright notice
 *Description : Simulation Project
 *============================================================================*/

/* units
 * front door: 3'
 * inside doors: 2.5'
 * outer walls: 6"
 * inner walls: 4"
 * ##############
 */

/*
 * x=in-out of screen
 * y=left-right
 * z=height
 */

int window;
double state[7];
double rate[7];

/*Play around with the values from here*/
//##########################################//
double d=1200;//distance from house
double dt=0.05;
double r=12;
double theta=60;
double lambda=3; //recommended to go between -5 to 5 degrees for lambda and the lambda angle is restricted between -45 to 45 in main
double drag=0.1; //drag co-efficient
double mass=1;
double g=9.81;
double v=7000;
//##########################################//

double meterToInches(double meter){
	double inch=meter*39.3701;
	return inch;
}

double toRadian(double degree){
	double rad=degree/180*M_PI;
	return rad;
}

bool collision(){
	if(state[2]<=84+r){//check with every rectangle in the house
		//outside bottom wall
		if(state[0]>=0+d-r && state[0]<=600+d+r && state[1]>=0-r && state[1]<=6+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//outside top-left wall
		else if(state[0]>=0+d-r && state[0]<=210+d+r && state[1]>=354-r && state[1]<=360+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//outside top-right wall
		else if(state[0]>=246+d-r && state[0]<=600+d+r && state[1]>=354-r && state[1]<=360+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//outside left wall
		else if(state[0]>=0+d-r && state[0]<=6+d+r && state[1]>=0-r && state[1]<=360+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//outside right wall
		else if(state[0]>=594+d-r && state[0]<=600+d+r && state[1]>=0-r && state[1]<=360+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//living room top-right wall
		else if(state[0]>=200+d-r && state[0]<=204+d+r && state[1]>=274-r && state[1]<=354+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//living room bottom-right-right wall
		else if(state[0]>=200+d-r && state[0]<=204+d+r && state[1]>=160-r && state[1]<=244+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//living room bottom-right-left wall
		else if(state[0]>=118+d-r && state[0]<=204+d+r && state[1]>=160-r && state[1]<=164+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//living room bottom-left wall
		else if(state[0]>=6+d-r && state[0]<=88+d+r && state[1]>=160-r && state[1]<=164+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//bathroom top-left wall
		else if(state[0]>=6+d-r && state[0]<=18+d+r && state[1]>=108-r && state[1]<=112+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//bathroom/laundry wall
		else if(state[0]>=48+d-r && state[0]<=94+d+r && state[1]>=108-r && state[1]<=112+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//bathroom right wall
		else if(state[0]>=78+d-r && state[0]<=82+d+r && state[1]>=6-r && state[1]<=108+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//laundry right wall
		else if(state[0]>=200+d-r && state[0]<=204+d+r && state[1]>=6-r && state[1]<=112+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//laundry top-right wall
		else if(state[0]>=124+d-r && state[0]<=204+d+r && state[1]>=108-r && state[1]<=112+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//SE Bedroom bottom-left wall
		else if(state[0]>=420+d-r && state[0]<=424+d+r && state[1]>=6-r && state[1]<=88+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//SE Bedroom top-left-left wall to NE Bedroom bottom-left-left wall
		else if(state[0]>=420+d-r && state[0]<=424+d+r && state[1]>=118-r && state[1]<=240+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//SE Bedroom top-left-top wall
		else if(state[0]>=424+d-r && state[0]<=552+d+r && state[1]>=134-r && state[1]<=138+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//SE Bedroom top-right-top wall
		else if(state[0]>=582+d-r && state[0]<=594+d+r && state[1]>=134-r && state[1]<=138+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//NE Bedroom bottom-left-down wall
		else if(state[0]>=424+d-r && state[0]<=552+d+r && state[1]>=224-r && state[1]<=228+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//NE Bedroom bottom-right-down wall
		else if(state[0]>=582+d-r && state[0]<=594+d+r && state[1]>=224-r && state[1]<=228+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//NE Bedtoom top-left-left wall
		else if(state[0]>=420+d-r && state[0]<=424+d+r && state[1]>=270-r && state[1]<=354+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//Closest bottom-right
		else if(state[0]>=414+d-r && state[0]<=420+d+r && state[1]>=294-r && state[1]<=298+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//Closest bottom-left
		else if(state[0]>=372+d-r && state[0]<=378+d+r && state[1]>=294-r && state[1]<=298+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//Kitchen/Dining right wall
		else if(state[0]>=368+d-r && state[0]<=372+d+r && state[1]>=54-r && state[1]<=354+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//Dining bottom wall
		else if(state[0]>=252+d-r && state[0]<=372+d+r && state[1]>=54-r && state[1]<=58+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//kitchen top-left-top wall
		else if(state[0]>=252+d-r && state[0]<=256+d+r && state[1]>=272-r && state[1]<=354+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//kitchen bottom-left-left wall to dining top-left-left wall
		else if(state[0]>=252+d-r && state[0]<=256+d+r && state[1]>=157-r && state[1]<=242+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//kitchen bottom-left-bottom wall/Dining room top-left wall
		else if(state[0]>=256+d-r && state[0]<=297+d+r && state[1]>=226-r && state[1]<=230+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//kitchen bottom-right-bottom wall/Dining room top-right wall
		else if(state[0]>=327+d-r && state[0]<=368+d+r && state[1]>=226-r && state[1]<=230+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		//Dining bottom-left wall
		else if(state[0]>=252+d-r && state[0]<=256+d+r && state[1]>=58-r && state[1]<=127+r){
			cout<<"hit wall"<<endl;
			return true;
		}
		else if(state[2]<=r){
			cout<<"hit floor"<<endl;
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

void house(){
	int list;
	list=glGenLists(1);
	glNewList(list,GL_COMPILE);
	glBegin(GL_LINES);
	glColor3f(1,1,1);
	//front door
	/*glVertex3f(246,355,0);//
		glVertex3f(210,355,0);
		glVertex3f(246,359,0);//
		glVertex3f(210,359,0);

		glVertex3f(246,355,0);//
		glVertex3f(246,355,84);
		glVertex3f(210,355,0);//
		glVertex3f(210,355,84);
		glVertex3f(246,359,0);//
		glVertex3f(246,359,84);
		glVertex3f(210,359,0);//
		glVertex3f(210,359,84);

		glVertex3f(246,355,84);//
		glVertex3f(210,355,84);
		glVertex3f(246,359,84);//
		glVertex3f(210,359,84);*/

	/*outer wall of house*/
	//bottom
	glVertex3f(0,0,0);//
	glVertex3f(600,0,0);
	glVertex3f(600,0,0);//
	glVertex3f(600,360,0);
	glVertex3f(0,0,0);//
	glVertex3f(0,360,0);
	glVertex3f(0,360,0);//
	glVertex3f(210,360,0);
	glVertex3f(246,360,0);//
	glVertex3f(600,360,0);
	//up
	glVertex3f(0,0,0);//
	glVertex3f(0,0,84);
	glVertex3f(600,0,0);//
	glVertex3f(600,0,84);
	glVertex3f(600,360,0);//
	glVertex3f(600,360,84);
	glVertex3f(0,360,0);//
	glVertex3f(0,360,84);
	glVertex3f(210,360,0);//
	glVertex3f(210,360,84);
	glVertex3f(246,360,0);//
	glVertex3f(246,360,84);
	//top
	glVertex3f(0,0,84);//
	glVertex3f(600,0,84);
	glVertex3f(600,0,84);//
	glVertex3f(600,360,84);
	glVertex3f(0,0,84);//
	glVertex3f(0,360,84);
	glVertex3f(0,360,84);//
	glVertex3f(210,360,84);
	glVertex3f(246,360,84);//
	glVertex3f(600,360,84);

	/*front entrance*/
	//bottom
	glVertex3f(210,360,0);//
	glVertex3f(210,354,0);
	glVertex3f(210,354,0);//
	glVertex3f(204,354,0);
	glVertex3f(246,360,0);//
	glVertex3f(246,354,0);
	glVertex3f(246,354,0);//
	glVertex3f(252,354,0);
	//up
	glVertex3f(210,360,0);//
	glVertex3f(210,360,84);
	glVertex3f(210,354,0);//
	glVertex3f(210,354,84);
	glVertex3f(204,354,0);//
	glVertex3f(204,354,84);
	glVertex3f(246,360,0);//
	glVertex3f(246,360,84);
	glVertex3f(246,354,0);//
	glVertex3f(246,354,84);
	glVertex3f(252,354,0);//
	glVertex3f(252,354,84);
	//top
	glVertex3f(210,360,84);//
	glVertex3f(210,354,84);
	glVertex3f(210,354,84);//
	glVertex3f(204,354,84);
	glVertex3f(246,360,84);//
	glVertex3f(246,354,84);
	glVertex3f(246,354,84);//
	glVertex3f(252,354,84);

	/*living room*/
	//bottom
	glVertex3f(204,354,0);//
	glVertex3f(204,274,0);
	glVertex3f(204,274,0);//
	glVertex3f(200,274,0);
	glVertex3f(200,274,0);//
	glVertex3f(200,354,0);
	glVertex3f(200,354,0);//
	glVertex3f(6,354,0);
	glVertex3f(6,354,0);//
	glVertex3f(6,164,0);
	glVertex3f(6,164,0);//
	glVertex3f(88,164,0);
	glVertex3f(88,164,0);//
	glVertex3f(88,160,0);
	glVertex3f(88,160,0);//
	glVertex3f(6,160,0);
	glVertex3f(118,164,0);//
	glVertex3f(200,164,0);
	glVertex3f(200,164,0);//
	glVertex3f(200,244,0);
	glVertex3f(200,244,0);//
	glVertex3f(204,244,0);
	glVertex3f(204,244,0);//
	glVertex3f(204,160,0);
	glVertex3f(204,160,0);//
	glVertex3f(118,160,0);
	glVertex3f(118,160,0);//
	glVertex3f(118,164,0);
	//up
	glVertex3f(204,354,0);//
	glVertex3f(204,354,84);
	glVertex3f(204,274,0);//
	glVertex3f(204,274,84);
	glVertex3f(200,274,0);//
	glVertex3f(200,274,84);
	glVertex3f(200,354,0);//
	glVertex3f(200,354,84);
	glVertex3f(6,354,0);//
	glVertex3f(6,354,84);
	glVertex3f(6,164,0);//
	glVertex3f(6,164,84);
	glVertex3f(88,164,0);//
	glVertex3f(88,164,84);
	glVertex3f(88,160,0);//
	glVertex3f(88,160,84);
	glVertex3f(6,164,0);
	glVertex3f(6,164,84);//
	glVertex3f(118,164,0);//
	glVertex3f(118,164,84);
	glVertex3f(200,164,0);//
	glVertex3f(200,164,84);
	glVertex3f(200,244,0);//
	glVertex3f(200,244,84);
	glVertex3f(204,244,0);//
	glVertex3f(204,244,84);
	glVertex3f(204,160,0);//
	glVertex3f(204,160,84);
	glVertex3f(118,160,0);//
	glVertex3f(118,160,84);
	//top
	glVertex3f(204,354,84);//
	glVertex3f(204,274,84);
	glVertex3f(204,274,84);//
	glVertex3f(200,274,84);
	glVertex3f(200,274,84);//
	glVertex3f(200,354,84);
	glVertex3f(200,354,84);//
	glVertex3f(6,354,84);
	glVertex3f(6,354,84);//
	glVertex3f(6,164,84);
	glVertex3f(6,164,84);//
	glVertex3f(88,164,84);
	glVertex3f(88,164,84);//
	glVertex3f(88,160,84);
	glVertex3f(88,160,84);//
	glVertex3f(6,160,84);
	glVertex3f(118,164,84);//
	glVertex3f(200,164,84);
	glVertex3f(200,164,84);//
	glVertex3f(200,244,84);
	glVertex3f(200,244,84);//
	glVertex3f(204,244,84);
	glVertex3f(204,244,84);//
	glVertex3f(204,160,84);
	glVertex3f(204,160,84);//
	glVertex3f(118,160,84);
	glVertex3f(118,160,84);//
	glVertex3f(118,164,84);

	/*between wall bathroom & living room*/
	//bottom
	glVertex3f(6,160,0);//
	glVertex3f(6,112,0);
	//up
	glVertex3f(6,160,0);//
	glVertex3f(6,160,84);
	glVertex3f(6,112,0);//
	glVertex3f(6,112,84);
	//top
	glVertex3f(6,160,84);//
	glVertex3f(6,112,84);

	/*bathroom*/
	//bottom
	glVertex3f(6,6,0);//
	glVertex3f(78,6,0);
	glVertex3f(78,6,0);//
	glVertex3f(78,108,0);
	glVertex3f(6,6,0);//
	glVertex3f(6,108,0);
	glVertex3f(6,108,0);//
	glVertex3f(18,108,0);
	glVertex3f(18,108,0);//
	glVertex3f(18,112,0);
	glVertex3f(18,112,0);//
	glVertex3f(6,112,0);
	glVertex3f(48,108,0);//
	glVertex3f(78,108,0);
	glVertex3f(48,108,0);//
	glVertex3f(48,112,0);
	glVertex3f(48,112,0);//
	glVertex3f(78,112,0);
	//up
	glVertex3f(6,6,0);//
	glVertex3f(6,6,84);
	glVertex3f(78,6,0);//
	glVertex3f(78,6,84);
	glVertex3f(78,108,0);//
	glVertex3f(78,108,84);
	glVertex3f(6,108,0);//
	glVertex3f(6,108,84);
	glVertex3f(18,108,0);//
	glVertex3f(18,108,84);
	glVertex3f(18,112,0);//
	glVertex3f(18,112,84);
	glVertex3f(6,112,0);//
	glVertex3f(6,112,84);
	glVertex3f(48,108,0);//
	glVertex3f(48,108,84);
	glVertex3f(48,112,0);//
	glVertex3f(48,112,84);
	//top
	glVertex3f(6,6,84);//
	glVertex3f(78,6,84);
	glVertex3f(78,6,84);//
	glVertex3f(78,108,84);
	glVertex3f(6,6,84);//
	glVertex3f(6,108,84);
	glVertex3f(6,108,84);//
	glVertex3f(18,108,84);
	glVertex3f(18,108,84);//
	glVertex3f(18,112,84);
	glVertex3f(18,112,84);//
	glVertex3f(6,112,84);
	glVertex3f(48,108,84);//
	glVertex3f(78,108,84);
	glVertex3f(48,108,84);//
	glVertex3f(48,112,84);
	glVertex3f(48,112,84);//
	glVertex3f(78,112,84);

	/*laundry room*/
	//bottom
	glVertex3f(82,6,0);//
	glVertex3f(82,108,0);
	glVertex3f(82,6,0);//
	glVertex3f(200,6,0);
	glVertex3f(200,6,0);//
	glVertex3f(200,108,0);
	glVertex3f(82,108,0);//
	glVertex3f(94,108,0);
	glVertex3f(94,108,0);//
	glVertex3f(94,112,0);
	glVertex3f(124,112,0);//
	glVertex3f(204,112,0);
	glVertex3f(204,112,0);//
	glVertex3f(204,6,0);
	glVertex3f(124,112,0);//
	glVertex3f(124,108,0);
	glVertex3f(124,108,0);//
	glVertex3f(200,108,0);
	glVertex3f(78,112,0);//
	glVertex3f(94,112,0);
	//up
	glVertex3f(200,6,0);//
	glVertex3f(200,6,84);
	glVertex3f(200,108,0);
	glVertex3f(200,108,84);
	glVertex3f(94,108,0);//
	glVertex3f(94,108,84);
	glVertex3f(94,112,0);//
	glVertex3f(94,112,84);
	glVertex3f(124,112,0);//
	glVertex3f(124,112,84);
	glVertex3f(204,112,0);//
	glVertex3f(204,112,84);
	glVertex3f(204,6,0);//
	glVertex3f(204,6,84);
	glVertex3f(124,108,0);//
	glVertex3f(124,108,84);
	//top
	glVertex3f(82,6,84);//
	glVertex3f(82,108,84);
	glVertex3f(82,6,84);//
	glVertex3f(200,6,84);
	glVertex3f(200,6,84);//
	glVertex3f(200,108,84);
	glVertex3f(82,108,84);//
	glVertex3f(94,108,84);
	glVertex3f(94,108,84);//
	glVertex3f(94,112,84);
	glVertex3f(124,112,84);//
	glVertex3f(204,112,84);
	glVertex3f(204,112,84);//
	glVertex3f(204,6,84);
	glVertex3f(124,112,84);//
	glVertex3f(124,108,84);
	glVertex3f(124,108,84);//
	glVertex3f(200,108,84);
	glVertex3f(78,112,84);//
	glVertex3f(94,112,84);

	/*hallway*/
	//bottom
	glVertex3f(204,6,0);//
	glVertex3f(420,6,0);
	//up
	glVertex3f(204,6,0);//
	glVertex3f(204,6,84);
	glVertex3f(420,6,0);//
	glVertex3f(420,6,84);
	//top
	glVertex3f(204,6,84);//
	glVertex3f(420,6,84);

	/*Bedroom by dining room*/
	//bottom
	glVertex3f(420,6,0);//
	glVertex3f(420,88,0);
	glVertex3f(420,122,0);//
	glVertex3f(420,134,0);
	glVertex3f(420,122,0);//
	glVertex3f(424,122,0);
	glVertex3f(424,122,0);//
	glVertex3f(424,134,0);
	glVertex3f(420,88,0);//
	glVertex3f(424,88,0);
	glVertex3f(424,88,0);//
	glVertex3f(424,6,0);
	glVertex3f(424,6,0);//
	glVertex3f(594,6,0);
	glVertex3f(594,6,0);//
	glVertex3f(594,134,0);
	glVertex3f(594,134,0);//
	glVertex3f(582,134,0);
	glVertex3f(552,134,0);//
	glVertex3f(424,134,0);
	//up
	glVertex3f(420,6,0);//
	glVertex3f(420,6,84);
	glVertex3f(420,88,0);//
	glVertex3f(420,88,84);
	glVertex3f(420,122,0);//
	glVertex3f(420,122,84);
	glVertex3f(424,122,0);//
	glVertex3f(424,122,84);
	glVertex3f(424,134,0);//
	glVertex3f(424,134,84);
	glVertex3f(424,88,0);//
	glVertex3f(424,88,84);
	glVertex3f(424,6,0);//
	glVertex3f(424,6,84);
	glVertex3f(594,6,0);//
	glVertex3f(594,6,84);
	glVertex3f(594,134,0);//
	glVertex3f(594,134,84);
	glVertex3f(582,134,0);//
	glVertex3f(582,134,84);
	glVertex3f(552,134,0);//
	glVertex3f(552,134,84);
	glVertex3f(424,134,0);//
	glVertex3f(424,134,84);
	//top
	glVertex3f(420,6,84);//
	glVertex3f(420,88,84);
	glVertex3f(420,122,84);//
	glVertex3f(420,134,84);
	glVertex3f(420,122,84);//
	glVertex3f(424,122,84);
	glVertex3f(424,122,84);//
	glVertex3f(424,134,84);
	glVertex3f(420,88,84);//
	glVertex3f(424,88,84);
	glVertex3f(424,88,84);//
	glVertex3f(424,6,84);
	glVertex3f(424,6,84);//
	glVertex3f(594,6,84);
	glVertex3f(594,6,84);//
	glVertex3f(594,134,84);
	glVertex3f(594,134,84);//
	glVertex3f(582,134,84);
	glVertex3f(552,134,84);//
	glVertex3f(424,134,84);

	/*bedroom bathroom*/
	//bottom
	glVertex3f(420,134,0);//
	glVertex3f(420,228,0);
	glVertex3f(424,138,0);//
	glVertex3f(424,224,0);
	glVertex3f(594,138,0);//
	glVertex3f(582,138,0);
	glVertex3f(552,138,0);//
	glVertex3f(424,138,0);
	glVertex3f(582,138,0);//
	glVertex3f(582,134,0);
	glVertex3f(552,138,0);//
	glVertex3f(552,134,0);
	glVertex3f(424,224,0);//
	glVertex3f(552,224,0);
	glVertex3f(582,224,0);//
	glVertex3f(594,224,0);
	glVertex3f(594,224,0);//
	glVertex3f(594,138,0);
	glVertex3f(582,224,0);//
	glVertex3f(582,228,0);
	glVertex3f(582,228,0);//
	glVertex3f(594,228,0);
	glVertex3f(552,224,0);//
	glVertex3f(552,228,0);
	glVertex3f(552,228,0);//
	glVertex3f(424,228,0);
	//up
	glVertex3f(424,138,0);//
	glVertex3f(424,138,84);
	glVertex3f(424,224,0);//
	glVertex3f(424,224,84);
	glVertex3f(594,138,0);//
	glVertex3f(594,138,84);
	glVertex3f(582,138,0);//
	glVertex3f(582,138,84);
	glVertex3f(552,138,0);//
	glVertex3f(552,138,84);
	glVertex3f(582,134,0);//
	glVertex3f(582,134,84);
	glVertex3f(552,134,0);//
	glVertex3f(552,134,84);
	glVertex3f(582,224,0);//
	glVertex3f(582,224,84);
	glVertex3f(552,224,0);//
	glVertex3f(552,224,84);
	glVertex3f(594,224,0);//
	glVertex3f(594,224,84);
	glVertex3f(582,228,0);//
	glVertex3f(582,228,84);
	glVertex3f(594,228,0);//
	glVertex3f(594,228,84);
	glVertex3f(552,228,0);//
	glVertex3f(552,228,84);
	glVertex3f(424,228,0);//
	glVertex3f(424,228,84);
	//top
	glVertex3f(420,134,84);//
	glVertex3f(420,228,84);
	glVertex3f(424,138,84);//
	glVertex3f(424,224,84);
	glVertex3f(594,138,84);//
	glVertex3f(582,138,84);
	glVertex3f(552,138,84);//
	glVertex3f(424,138,84);
	glVertex3f(582,138,84);//
	glVertex3f(582,134,84);
	glVertex3f(552,138,84);//
	glVertex3f(552,134,84);
	glVertex3f(424,224,84);//
	glVertex3f(552,224,84);
	glVertex3f(582,224,84);//
	glVertex3f(594,224,84);
	glVertex3f(594,224,84);//
	glVertex3f(594,138,84);
	glVertex3f(582,224,84);//
	glVertex3f(582,228,84);
	glVertex3f(582,228,84);//
	glVertex3f(594,228,84);
	glVertex3f(552,224,84);//
	glVertex3f(552,228,84);
	glVertex3f(552,228,84);//
	glVertex3f(424,228,84);

	/*Bedroom E of closet*/
	//bottom
	glVertex3f(424,228,0);//
	glVertex3f(424,240,0);
	glVertex3f(424,270,0);//
	glVertex3f(424,354,0);
	glVertex3f(424,354,0);//
	glVertex3f(594,354,0);
	glVertex3f(594,354,0);//
	glVertex3f(594,228,0);
	glVertex3f(420,228,0);//
	glVertex3f(420,240,0);
	glVertex3f(420,240,0);//
	glVertex3f(424,240,0);
	glVertex3f(424,270,0);//
	glVertex3f(420,270,0);
	//up
	glVertex3f(424,228,0);//
	glVertex3f(424,228,84);
	glVertex3f(424,240,0);//
	glVertex3f(424,240,84);
	glVertex3f(424,270,0);//
	glVertex3f(424,270,84);
	glVertex3f(424,354,0);//
	glVertex3f(424,354,84);
	glVertex3f(594,354,0);//
	glVertex3f(594,354,84);
	glVertex3f(594,228,0);//
	glVertex3f(594,228,84);
	glVertex3f(420,240,0);//
	glVertex3f(420,240,84);
	glVertex3f(424,270,0);//
	glVertex3f(420,270,0);
	//top
	glVertex3f(424,228,84);//
	glVertex3f(424,240,84);
	glVertex3f(424,270,84);//
	glVertex3f(424,354,84);
	glVertex3f(424,354,84);//
	glVertex3f(594,354,84);
	glVertex3f(594,354,84);//
	glVertex3f(594,228,84);
	glVertex3f(420,228,84);//
	glVertex3f(420,240,84);
	glVertex3f(420,240,84);//
	glVertex3f(424,240,84);
	glVertex3f(424,270,84);//
	glVertex3f(420,270,84);

	/*closet*/
	//bottom
	glVertex3f(420,270,0);//
	glVertex3f(420,294,0);
	glVertex3f(420,294,0);//
	glVertex3f(414,294,0);
	glVertex3f(378,294,0);//
	glVertex3f(372,294,0);
	glVertex3f(378,294,0);//
	glVertex3f(378,298,0);
	glVertex3f(378,298,0);//
	glVertex3f(372,298,0);
	glVertex3f(372,298,0);//
	glVertex3f(372,354,0);
	glVertex3f(372,354,0);//
	glVertex3f(420,354,0);
	glVertex3f(420,354,0);//
	glVertex3f(420,298,0);
	glVertex3f(420,298,0);//
	glVertex3f(414,298,0);
	glVertex3f(414,298,0);//
	glVertex3f(414,294,0);
	//up
	glVertex3f(420,270,0);//
	glVertex3f(420,270,84);
	glVertex3f(420,294,0);//
	glVertex3f(420,294,84);
	glVertex3f(414,294,0);//
	glVertex3f(414,294,84);
	glVertex3f(378,294,0);//
	glVertex3f(378,294,84);
	glVertex3f(372,294,0);//
	glVertex3f(372,294,84);
	glVertex3f(378,294,0);//
	glVertex3f(378,294,84);
	glVertex3f(378,298,0);//
	glVertex3f(378,298,84);
	glVertex3f(372,298,0);//
	glVertex3f(372,298,84);
	glVertex3f(372,354,0);//
	glVertex3f(372,354,84);
	glVertex3f(420,354,0);//
	glVertex3f(420,354,84);
	glVertex3f(420,298,0);//
	glVertex3f(420,298,84);
	glVertex3f(414,298,0);//
	glVertex3f(414,298,84);
	//top
	glVertex3f(420,270,84);//
	glVertex3f(420,294,84);
	glVertex3f(420,294,84);//
	glVertex3f(414,294,84);
	glVertex3f(378,294,84);//
	glVertex3f(372,294,84);
	glVertex3f(378,294,84);//
	glVertex3f(378,298,84);
	glVertex3f(378,298,84);//
	glVertex3f(372,298,84);
	glVertex3f(372,298,84);//
	glVertex3f(372,354,84);
	glVertex3f(372,354,84);//
	glVertex3f(420,354,84);
	glVertex3f(420,354,84);//
	glVertex3f(420,298,84);
	glVertex3f(420,298,84);//
	glVertex3f(414,298,84);
	glVertex3f(414,298,84);//
	glVertex3f(414,294,84);

	/*kitchen*/
	//bottom
	glVertex3f(372,300,0);//
	glVertex3f(372,226,0);
	glVertex3f(368,226,0);//
	glVertex3f(327,226,0);
	glVertex3f(327,226,0);//
	glVertex3f(327,230,0);
	glVertex3f(327,230,0);//
	glVertex3f(368,230,0);
	glVertex3f(368,230,0);//
	glVertex3f(368,354,0);
	glVertex3f(368,354,0);//
	glVertex3f(256,354,0);
	glVertex3f(256,354,0);//
	glVertex3f(256,272,0);
	glVertex3f(256,272,0);//
	glVertex3f(252,272,0);
	glVertex3f(252,272,0);//
	glVertex3f(252,354,0);
	glVertex3f(256,242,0);//
	glVertex3f(256,230,0);
	glVertex3f(256,242,0);//
	glVertex3f(252,242,0);
	glVertex3f(252,242,0);//
	glVertex3f(252,226,0);
	glVertex3f(256,230,0);//
	glVertex3f(293,230,0);
	glVertex3f(293,230,0);//
	glVertex3f(293,226,0);
	glVertex3f(293,226,0);//
	glVertex3f(256,226,0);
	//up
	glVertex3f(372,300,0);//
	glVertex3f(372,300,84);
	glVertex3f(368,226,0);//
	glVertex3f(368,226,84);
	glVertex3f(327,226,0);//
	glVertex3f(327,226,84);
	glVertex3f(327,230,0);//
	glVertex3f(327,230,84);
	glVertex3f(368,230,0);//
	glVertex3f(368,230,84);
	glVertex3f(368,354,0);//
	glVertex3f(368,354,84);
	glVertex3f(256,354,0);//
	glVertex3f(256,354,84);
	glVertex3f(256,272,0);//
	glVertex3f(256,272,84);
	glVertex3f(252,272,0);//
	glVertex3f(252,272,84);
	glVertex3f(252,354,0);//
	glVertex3f(252,354,84);
	glVertex3f(256,242,0);//
	glVertex3f(256,242,84);
	glVertex3f(256,230,0);//
	glVertex3f(256,230,84);
	glVertex3f(256,242,0);//
	glVertex3f(256,242,84);
	glVertex3f(252,242,0);//
	glVertex3f(252,242,84);
	glVertex3f(293,230,0);//
	glVertex3f(293,230,84);
	glVertex3f(293,226,0);//
	glVertex3f(293,226,84);
	glVertex3f(256,226,0);//
	glVertex3f(256,226,84);
	//top
	glVertex3f(372,300,84);//
	glVertex3f(372,226,84);
	glVertex3f(368,226,84);//
	glVertex3f(327,226,84);
	glVertex3f(327,226,84);//
	glVertex3f(327,230,84);
	glVertex3f(327,230,84);//
	glVertex3f(368,230,84);
	glVertex3f(368,230,84);//
	glVertex3f(368,354,84);
	glVertex3f(368,354,84);//
	glVertex3f(256,354,84);
	glVertex3f(256,354,84);//
	glVertex3f(256,272,84);
	glVertex3f(256,272,84);//
	glVertex3f(252,272,84);
	glVertex3f(252,272,84);//
	glVertex3f(252,354,84);
	glVertex3f(256,242,84);//
	glVertex3f(256,230,84);
	glVertex3f(256,242,84);//
	glVertex3f(252,242,84);
	glVertex3f(252,242,84);//
	glVertex3f(252,226,84);
	glVertex3f(256,230,84);//
	glVertex3f(293,230,84);
	glVertex3f(293,230,84);//
	glVertex3f(293,226,84);
	glVertex3f(293,226,84);//
	glVertex3f(256,226,84);

	/*dining room*/
	//bottom
	glVertex3f(252,54,0);//
	glVertex3f(372,54,0);
	glVertex3f(372,54,0);//
	glVertex3f(372,226,0);
	glVertex3f(368,226,0);//
	glVertex3f(368,58,0);
	glVertex3f(368,58,0);//
	glVertex3f(256,58,0);
	glVertex3f(256,58,0);//
	glVertex3f(256,127,0);
	glVertex3f(256,127,0);//
	glVertex3f(252,127,0);
	glVertex3f(252,127,0);//
	glVertex3f(252,54,0);
	glVertex3f(256,157,0);//
	glVertex3f(252,157,0);
	glVertex3f(252,157,0);//
	glVertex3f(252,226,0);
	glVertex3f(256,157,0);//
	glVertex3f(256,226,0);
	//up
	glVertex3f(252,54,0);//
	glVertex3f(252,54,84);
	glVertex3f(372,54,0);//
	glVertex3f(372,54,84);
	glVertex3f(368,226,0);//
	glVertex3f(368,226,84);
	glVertex3f(368,58,0);//
	glVertex3f(368,58,84);
	glVertex3f(256,58,0);//
	glVertex3f(256,58,84);
	glVertex3f(256,127,0);//
	glVertex3f(256,127,84);
	glVertex3f(252,127,0);//
	glVertex3f(252,127,84);
	glVertex3f(256,157,0);//
	glVertex3f(256,157,84);
	glVertex3f(252,157,0);//
	glVertex3f(252,157,84);
	glVertex3f(256,157,0);//
	glVertex3f(256,157,84);
	glVertex3f(256,226,0);//
	glVertex3f(256,226,84);
	//top
	glVertex3f(252,54,84);//
	glVertex3f(372,54,84);
	glVertex3f(372,54,84);//
	glVertex3f(372,226,84);
	glVertex3f(368,226,84);//
	glVertex3f(368,58,84);
	glVertex3f(368,58,84);//
	glVertex3f(256,58,84);
	glVertex3f(256,58,84);//
	glVertex3f(256,127,84);
	glVertex3f(256,127,84);//
	glVertex3f(252,127,84);
	glVertex3f(252,127,84);//
	glVertex3f(252,54,84);
	glVertex3f(256,157,84);//
	glVertex3f(252,157,84);
	glVertex3f(252,157,84);//
	glVertex3f(252,226,84);
	glVertex3f(256,157,84);//
	glVertex3f(256,226,84);
	glEnd();

	//floor
	glBegin(GL_QUADS);
	glColor3f(207/255.0, 207/255.0, 207/255.0);
	glVertex3f(0,0,0);
	glVertex3f(0,360,0);
	glVertex3f(600,360,0);
	glVertex3f(600,0,0);
	glEnd();

	//front door
	/*glBegin(GL_QUADS);
	glColor3f(173/255.0, 216/255.0, 230/255.0);
	glVertex3f(210,355,0);
	glVertex3f(210,355,84);
	glVertex3f(246,355,84);
	glVertex3f(246,355,0);

	glVertex3f(210,359,0);
	glVertex3f(210,359,84);
	glVertex3f(246,359,84);
	glVertex3f(246,359,0);
	glEnd();*/


	/*##############outside walls##############*/
	glBegin(GL_QUADS);
	glColor3f(247/255.0, 247/255.0, 247/255.0);

	//bottom wall
	glVertex3f(0,0,0);
	glVertex3f(0,0,84);
	glVertex3f(0,360,84);
	glVertex3f(0,360,0);

	//right wall
	glVertex3f(600,0,0);
	glVertex3f(600,0,84);
	glVertex3f(600,360,84);
	glVertex3f(600,360,0);

	//left wall
	glVertex3f(0,0,0);
	glVertex3f(0,0,84);
	glVertex3f(600,0,84);
	glVertex3f(600,0,0);

	//top-left wall
	glVertex3f(0,360,0);
	glVertex3f(0,360,84);
	glVertex3f(210,360,84);
	glVertex3f(210,360,0);

	//top-right wall
	glVertex3f(600,360,0);
	glVertex3f(600,360,84);
	glVertex3f(246,360,84);
	glVertex3f(246,360,0);

	/*##############living room##############*/
	//top-inner wall
	glVertex3f(6,354,0);
	glVertex3f(6,354,84);
	glVertex3f(200,354,84);
	glVertex3f(200,354,0);

	//top-right inner wall
	glVertex3f(200,354,0);
	glVertex3f(200,354,84);
	glVertex3f(200,274,84);
	glVertex3f(200,274,0);

	//top-right inner-outer wall
	glVertex3f(200,274,0);
	glVertex3f(200,274,84);
	glVertex3f(204,274,84);
	glVertex3f(204,274,0);

	//top-right outer wall
	glVertex3f(204,274,0);
	glVertex3f(204,274,84);
	glVertex3f(204,354,84);
	glVertex3f(204,354,0);

	//left door corner
	glVertex3f(204,354,0);
	glVertex3f(204,354,84);
	glVertex3f(210,354,84);
	glVertex3f(210,354,0);

	//left  door inner-outer corner
	glVertex3f(210,354,0);
	glVertex3f(210,354,84);
	glVertex3f(210,360,84);
	glVertex3f(210,360,0);


	//left inner wall
	glVertex3f(6,354,0);
	glVertex3f(6,354,84);
	glVertex3f(6,164,84);
	glVertex3f(6,164,0);

	//bottom-left inner wall
	glVertex3f(6,164,0);
	glVertex3f(6,164,84);
	glVertex3f(88,164,84);
	glVertex3f(88,164,0);

	//bottom-left inner-outer wall
	glVertex3f(88,164,0);
	glVertex3f(88,164,84);
	glVertex3f(88,160,84);
	glVertex3f(88,160,0);

	//bottom-left outer wall
	glVertex3f(88,160,0);
	glVertex3f(88,160,84);
	glVertex3f(6,160,84);
	glVertex3f(6,160,0);

	//bottom-right-down inner wall
	glVertex3f(118,164,0);
	glVertex3f(118,164,84);
	glVertex3f(200,164,84);
	glVertex3f(200,164,0);

	//bottom-right-right inner wall
	glVertex3f(200,164,0);
	glVertex3f(200,164,84);
	glVertex3f(200,244,84);
	glVertex3f(200,244,0);

	//bottom-right-right inner-outer wall
	glVertex3f(200,244,0);
	glVertex3f(200,244,84);
	glVertex3f(204,244,84);
	glVertex3f(204,244,0);

	//bottom-right-down inner-outer wall
	glVertex3f(118,164,0);
	glVertex3f(118,164,84);
	glVertex3f(118,160,84);
	glVertex3f(118,160,0);

	//bottom-right-down outer wall
	glVertex3f(118,160,0);
	glVertex3f(118,160,84);
	glVertex3f(204,160,84);
	glVertex3f(204,160,0);

	//bottom-right-right outer wall
	glVertex3f(204,160,0);
	glVertex3f(204,160,84);
	glVertex3f(204,244,84);
	glVertex3f(204,244,0);

	/*##############left hallway wall##############*/
	glVertex3f(6,160,0);
	glVertex3f(6,160,84);
	glVertex3f(6,112,84);
	glVertex3f(6,112,0);

	/*##############bathroom in hallway##############*/
	//top-left outer wall
	glVertex3f(6,112,0);
	glVertex3f(6,112,84);
	glVertex3f(18,112,84);
	glVertex3f(18,112,0);

	//top-left outer-inner wall
	glVertex3f(18,112,0);
	glVertex3f(18,112,84);
	glVertex3f(18,108,84);
	glVertex3f(18,108,0);

	//top-left inner wall
	glVertex3f(18,108,0);
	glVertex3f(18,108,84);
	glVertex3f(6,108,84);
	glVertex3f(6,108,0);

	//top-right inner-outer wall
	glVertex3f(48,108,0);
	glVertex3f(48,108,84);
	glVertex3f(48,112,84);
	glVertex3f(48,112,0);

	//top-right inner wall
	glVertex3f(48,108,0);
	glVertex3f(48,108,84);
	glVertex3f(78,108,84);
	glVertex3f(78,108,0);

	//right wall inner
	glVertex3f(78,108,0);
	glVertex3f(78,108,84);
	glVertex3f(78,6,84);
	glVertex3f(78,6,0);

	//bottom wall inner
	glVertex3f(78,6,0);
	glVertex3f(78,6,84);
	glVertex3f(6,6,84);
	glVertex3f(6,6,0);

	//left wall inner
	glVertex3f(6,6,0);
	glVertex3f(6,6,84);
	glVertex3f(6,108,84);
	glVertex3f(6,108,0);

	//top-right outer wall
	glVertex3f(48,112,0);
	glVertex3f(48,112,84);
	glVertex3f(80,112,84);
	glVertex3f(80,112,0);

	/*##############laundry room##############*/
	//top-left outer wall
	glVertex3f(80,112,0);
	glVertex3f(80,112,84);
	glVertex3f(94,112,84);
	glVertex3f(94,112,0);

	//top-left outer-inner wall
	glVertex3f(94,112,0);
	glVertex3f(94,112,84);
	glVertex3f(94,108,84);
	glVertex3f(94,108,0);

	//top-left inner wall
	glVertex3f(94,108,0);
	glVertex3f(94,108,84);
	glVertex3f(82,108,84);
	glVertex3f(82,108,0);

	//left inner wall
	glVertex3f(82,108,0);
	glVertex3f(82,108,84);
	glVertex3f(82,6,84);
	glVertex3f(82,6,0);

	//bottom inner wall
	glVertex3f(82,6,0);
	glVertex3f(82,6,84);
	glVertex3f(200,6,84);
	glVertex3f(200,6,0);

	//right inner wall
	glVertex3f(200,6,0);
	glVertex3f(200,6,84);
	glVertex3f(200,108,84);
	glVertex3f(200,108,0);

	//top-right inner wall
	glVertex3f(200,108,0);
	glVertex3f(200,108,84);
	glVertex3f(124,108,84);
	glVertex3f(124,108,0);

	//top-right inner-outer wall
	glVertex3f(124,108,0);
	glVertex3f(124,108,84);
	glVertex3f(124,112,84);
	glVertex3f(124,112,0);

	//top-right outer wall
	glVertex3f(124,112,0);
	glVertex3f(124,112,84);
	glVertex3f(204,112,84);
	glVertex3f(204,112,0);

	//right outer wall
	glVertex3f(204,112,0);
	glVertex3f(204,112,84);
	glVertex3f(204,6,84);
	glVertex3f(204,6,0);

	/*hallway bottom wall*/
	glVertex3f(204,6,0);
	glVertex3f(204,6,84);
	glVertex3f(420,6,84);
	glVertex3f(420,6,0);

	/*##############Bedroom SE of dining room##############*/
	//left outer wall
	glVertex3f(420,6,0);
	glVertex3f(420,6,84);
	glVertex3f(420,88,84);
	glVertex3f(420,88,0);

	//left outer-inner wall
	glVertex3f(420,88,0);
	glVertex3f(420,88,84);
	glVertex3f(424,88,84);
	glVertex3f(424,88,0);

	//left inner wall
	glVertex3f(424,88,0);
	glVertex3f(424,88,84);
	glVertex3f(424,6,84);
	glVertex3f(424,6,0);

	//bottom inner wall
	glVertex3f(424,6,0);
	glVertex3f(424,6,84);
	glVertex3f(594,6,84);
	glVertex3f(594,6,0);

	//right inner wall
	glVertex3f(594,6,0);
	glVertex3f(594,6,84);
	glVertex3f(594,134,84);
	glVertex3f(594,134,0);

	//top-right inner wall
	glVertex3f(594,134,0);
	glVertex3f(594,134,84);
	glVertex3f(582,134,84);
	glVertex3f(582,134,0);

	//top-left-top inner wall
	glVertex3f(552,134,0);
	glVertex3f(552,134,84);
	glVertex3f(424,134,84);
	glVertex3f(424,134,0);

	//top-left-left inner wall
	glVertex3f(424,134,0);
	glVertex3f(424,134,84);
	glVertex3f(424,122,84);
	glVertex3f(424,122,0);

	//top-left-left inner-outer wall
	glVertex3f(424,122,0);
	glVertex3f(424,122,84);
	glVertex3f(420,122,84);
	glVertex3f(420,122,0);

	//top-left-left outer wall
	glVertex3f(420,122,0);
	glVertex3f(420,122,84);
	glVertex3f(420,134,84);
	glVertex3f(420,134,0);

	/*##############Bedroom bathroom##############*/
	//left outer wall
	glVertex3f(420,134,0);
	glVertex3f(420,134,84);
	glVertex3f(420,228,84);
	glVertex3f(420,228,0);

	//bottom-right outer-inner wall
	glVertex3f(582,134,0);
	glVertex3f(582,134,84);
	glVertex3f(582,138,84);
	glVertex3f(582,138,0);

	//bottom-right inner wall
	glVertex3f(582,138,0);
	glVertex3f(582,138,84);
	glVertex3f(594,138,84);
	glVertex3f(594,138,0);

	//right inner wall
	glVertex3f(594,138,0);
	glVertex3f(594,138,84);
	glVertex3f(594,224,84);
	glVertex3f(594,224,0);

	//bottom-left inner-outer wall
	glVertex3f(552,138,0);
	glVertex3f(552,138,84);
	glVertex3f(552,134,84);
	glVertex3f(552,134,0);

	//bottom-left inner wall
	glVertex3f(552,138,0);
	glVertex3f(552,138,84);
	glVertex3f(424,138,84);
	glVertex3f(424,138,0);

	//left inner wall
	glVertex3f(424,138,0);
	glVertex3f(424,138,84);
	glVertex3f(424,224,84);
	glVertex3f(424,224,0);

	//top-left inner wall
	glVertex3f(424,224,0);
	glVertex3f(424,224,84);
	glVertex3f(552,224,84);
	glVertex3f(552,224,0);

	//top-left inner-outer wall
	glVertex3f(552,224,0);
	glVertex3f(552,224,84);
	glVertex3f(552,228,84);
	glVertex3f(552,228,0);

	//top-right inner wall
	glVertex3f(582,224,0);
	glVertex3f(582,224,84);
	glVertex3f(594,224,84);
	glVertex3f(594,224,0);

	//top-right inner-outer wall
	glVertex3f(582,224,0);
	glVertex3f(582,224,84);
	glVertex3f(582,228,0);
	glVertex3f(582,228,0);

	/*##############Bedroom E of closest##############*/
	//bottom-right inner wall
	glVertex3f(582,228,0);
	glVertex3f(582,228,84);
	glVertex3f(594,228,84);
	glVertex3f(594,228,0);

	//right inner wall
	glVertex3f(594,228,0);
	glVertex3f(594,228,84);
	glVertex3f(594,354,84);
	glVertex3f(594,354,0);

	//top inner wall
	glVertex3f(594,354,0);
	glVertex3f(594,354,84);
	glVertex3f(424,354,84);
	glVertex3f(424,354,0);

	//top-left inner wall
	glVertex3f(424,354,0);
	glVertex3f(424,354,84);
	glVertex3f(424,270,84);
	glVertex3f(424,270,0);

	//top-left inner-outer wall
	glVertex3f(424,270,0);
	glVertex3f(424,270,84);
	glVertex3f(420,270,84);
	glVertex3f(420,270,0);

	//top-left outer wall
	glVertex3f(420,270,0);
	glVertex3f(420,270,84);
	glVertex3f(420,294,84);
	glVertex3f(420,294,0);

	//bottom-left-left inner wall
	glVertex3f(424,240,0);
	glVertex3f(424,240,84);
	glVertex3f(424,228,84);
	glVertex3f(424,228,0);

	//bottom-left-down inner wall
	glVertex3f(424,228,0);
	glVertex3f(424,228,84);
	glVertex3f(552,228,84);
	glVertex3f(552,228,0);

	//bottom-left inner-outer wall
	glVertex3f(424,240,0);
	glVertex3f(424,240,84);
	glVertex3f(420,240,84);
	glVertex3f(420,240,0);

	//bottom-left outer wall
	glVertex3f(420,240,0);
	glVertex3f(420,240,84);
	glVertex3f(420,224,84);
	glVertex3f(420,224,0);

	/*##############closet##############*/
	//bottom-right outer wall
	glVertex3f(420,294,0);
	glVertex3f(420,294,84);
	glVertex3f(414,294,84);
	glVertex3f(414,294,0);

	//bottom-right outer-inner wall
	glVertex3f(414,294,0);
	glVertex3f(414,294,84);
	glVertex3f(414,298,84);
	glVertex3f(414,298,0);

	//bottom-right inner wall
	glVertex3f(414,298,0);
	glVertex3f(414,298,84);
	glVertex3f(420,298,84);
	glVertex3f(420,298,0);

	//right inner wall
	glVertex3f(420,298,0);
	glVertex3f(420,298,84);
	glVertex3f(420,354,84);
	glVertex3f(420,354,0);

	//top inner wall
	glVertex3f(420,354,0);
	glVertex3f(420,354,84);
	glVertex3f(372,354,84);
	glVertex3f(372,354,0);

	//left inner wall
	glVertex3f(372,354,0);
	glVertex3f(372,354,84);
	glVertex3f(372,298,84);
	glVertex3f(372,298,0);

	//bottom-left inner wall
	glVertex3f(372,298,0);
	glVertex3f(372,298,84);
	glVertex3f(378,298,84);
	glVertex3f(378,298,0);

	//bottom-left inner-outer wall
	glVertex3f(378,298,0);
	glVertex3f(378,298,84);
	glVertex3f(378,294,84);
	glVertex3f(378,294,0);

	//bottom-left outer wall
	glVertex3f(378,294,0);
	glVertex3f(378,294,84);
	glVertex3f(372,294,84);
	glVertex3f(372,294,0);

	/*##############kitchen##############*/
	//right outer wall
	glVertex3f(372,294,0);
	glVertex3f(372,294,84);
	glVertex3f(372,226,84);
	glVertex3f(372,226,0);

	//bottom-right inner-outer wall
	glVertex3f(327,226,0);
	glVertex3f(327,226,84);
	glVertex3f(327,230,84);
	glVertex3f(327,230,0);

	//bottom-right inner wall
	glVertex3f(327,230,0);
	glVertex3f(327,230,84);
	glVertex3f(368,230,84);
	glVertex3f(368,230,0);

	//right inner wall
	glVertex3f(368,230,0);
	glVertex3f(368,230,84);
	glVertex3f(368,354,84);
	glVertex3f(368,354,0);

	//top inner wall
	glVertex3f(368,354,0);
	glVertex3f(368,354,84);
	glVertex3f(256,354,84);
	glVertex3f(256,354,0);

	//top-left inner wall
	glVertex3f(256,354,0);
	glVertex3f(256,354,84);
	glVertex3f(256,272,84);
	glVertex3f(256,272,0);

	//top-left inner-outer wall
	glVertex3f(256,272,0);
	glVertex3f(256,272,84);
	glVertex3f(252,272,84);
	glVertex3f(252,272,0);

	//top-left outer wall
	glVertex3f(252,272,0);
	glVertex3f(252,272,84);
	glVertex3f(252,354,84);
	glVertex3f(252,354,0);

	/*###*/
	//bottom-right inner door
	glVertex3f(252,354,0);
	glVertex3f(252,354,84);
	glVertex3f(246,354,84);
	glVertex3f(246,354,0);

	//bottom-right inner-outer door
	glVertex3f(246,354,0);
	glVertex3f(246,354,84);
	glVertex3f(246,360,84);
	glVertex3f(246,360,0);
	/*###*/

	//bottom-left-left outer wall
	glVertex3f(252,242,0);
	glVertex3f(252,242,84);
	glVertex3f(252,226,84);
	glVertex3f(252,226,0);

	//bottom-left-left outer-inner wall
	glVertex3f(252,242,0);
	glVertex3f(252,242,84);
	glVertex3f(256,242,84);
	glVertex3f(256,242,0);

	//bottom-left-left inner wall
	glVertex3f(256,242,0);
	glVertex3f(256,242,84);
	glVertex3f(256,230,84);
	glVertex3f(256,230,0);

	//bottom-left-down inner wall
	glVertex3f(256,230,0);
	glVertex3f(256,230,84);
	glVertex3f(297,230,84);
	glVertex3f(297,230,0);

	//bottom-left-down inner-outer wall
	glVertex3f(297,230,0);
	glVertex3f(297,230,84);
	glVertex3f(297,226,84);
	glVertex3f(297,226,0);

	/*##############Dining Room##############*/
	//top-right inner wall
	glVertex3f(327,226,0);
	glVertex3f(327,226,84);
	glVertex3f(368,226,84);
	glVertex3f(368,226,0);

	//right inner wall
	glVertex3f(368,226,0);
	glVertex3f(368,226,84);
	glVertex3f(368,58,84);
	glVertex3f(368,58,0);

	//bottom inner wall
	glVertex3f(368,58,0);
	glVertex3f(368,58,84);
	glVertex3f(256,58,84);
	glVertex3f(256,58,0);

	//bottom-left inner wall
	glVertex3f(256,58,0);
	glVertex3f(256,58,84);
	glVertex3f(256,127,84);
	glVertex3f(256,127,0);

	//bottom-left inner-outer wall
	glVertex3f(256,127,0);
	glVertex3f(256,127,84);
	glVertex3f(252,127,84);
	glVertex3f(252,127,0);

	//bottom-left outer wall
	glVertex3f(252,127,0);
	glVertex3f(252,127,84);
	glVertex3f(252,54,84);
	glVertex3f(252,54,0);

	//bottom outer wall
	glVertex3f(252,54,0);
	glVertex3f(252,54,84);
	glVertex3f(372,54,84);
	glVertex3f(372,54,0);

	//right outer wall
	glVertex3f(372,54,0);
	glVertex3f(372,54,84);
	glVertex3f(372,226,84);
	glVertex3f(372,226,0);

	//top-left-top inner wall
	glVertex3f(297,226,0);
	glVertex3f(297,226,84);
	glVertex3f(256,226,84);
	glVertex3f(256,226,0);

	//top-left-left inner wall
	glVertex3f(256,226,0);
	glVertex3f(256,226,84);
	glVertex3f(256,157,84);
	glVertex3f(256,157,0);

	//top-left inner-outer wall
	glVertex3f(256,157,0);
	glVertex3f(256,157,84);
	glVertex3f(252,157,84);
	glVertex3f(252,157,0);

	//top-left outer wall
	glVertex3f(252,157,0);
	glVertex3f(252,157,84);
	glVertex3f(252,226,84);
	glVertex3f(252,226,0);

	glEnd();
	glEndList();
}

void display() {
	GLfloat ambient[4] = { 0.0, 0.0, 0.4, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(d,-180,0);
	glCallList(1);
	glPopMatrix();
	house();

	glPushMatrix();
	glColor3f(1.0,0.0,0.0);
	glTranslatef(state[0],state[1],state[2]);
	glutSolidSphere(r, 1000.0, 1000.0);
	glPopMatrix();

	glutSwapBuffers();

}

void animate() {
	cout<<"("<<state[0]<<","<<state[1]<<","<<state[2]<<"), time"<<state[6]<<endl;
	state[0]+=rate[0];
	state[1]+=rate[1];
	state[2]+=rate[2];
	state[3]+=rate[3];
	state[4]+=rate[4];
	state[5]+=rate[5];
	state[6]+=rate[6];
	rate[0]=state[3];
	rate[1]=state[4];
	rate[2]=state[5];
	rate[3]=-drag/mass*state[3];
	rate[4]=-drag/mass*state[4];
	rate[5]=-g-drag*state[5]/mass;
	if(state[0]>=d && state[0]<=600+d && state[1]<=180 && state[1]>=-180){
		if(collision()){
			cout<<"position:"<<"("<<state[0]<<","<<state[1]<<","<<state[2]<<")"<<",time:"<<state[6]<<endl;
			double pause;
			cout<<"type anything to exit"<<endl;
			cin>>pause;
			exit(1);
		}
	}
	else if(state[2]<=r && state[6]>0.02){
		double pause;
		cout<<"miss"<<endl;
		cin>>pause;
		exit(1);
	}
	glutSetWindow(window);
	glutPostRedisplay();
}

void gfxinit() {
	double view=d*.5;
	double dist=d;
	if(view<700){
		view=700;
	}
	if(dist<1100){
		dist+=300;
	}
	v*=dt;
	//g=meterToInches(g)*dt;
	//Restricts lambda to -45 to 45
	if(lambda>45){
		lambda=45;
	}
	else if(lambda<-45){
		lambda=-45;
	}
	lambda*=-1; //make positive right side and negative left
	state[0]=0;
	state[1]=0;
	state[2]=0;
	state[3]=v*cos(toRadian(theta));
	state[4]=state[3]*tan(toRadian(lambda));
	state[5]=v*sin(toRadian(theta));
	state[6]=0;
	rate[0]=state[3];
	rate[1]=state[4];
	rate[2]=state[5];
	rate[3]=-drag/mass*state[3];
	rate[4]=-drag/mass*state[4];
	rate[5]=-g-drag/mass*state[5];
	rate[6]=dt;
	GLfloat lightamb[4] = { 0.8, 0.8, 0.8, 1.0 };
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	//glOrtho(-350, 350, -350, 350, 1, 4800);
	gluPerspective(30.0, 1.0, 1.0, 4800.0);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	gluLookAt(0.0, 0.0, view, dist, 0.0, 0.0, 0.0, 0.0, 1.0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightamb);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

}

int main(int argc, char **argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	window = glutCreateWindow("Projectile Motion");
	glutDisplayFunc(display);
	glutIdleFunc(animate);
	gfxinit();
	glutMainLoop();
	return 0;
}
