#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>

#include "Graphics.h"  // Contains the definition of "Particule" and "Graphics"

enum  col_type {
  bottom,
  right,
  top,
  left,
  animation,
  particle
}; //different types of collision

typedef struct { // a structure describing each collision -- one might want an array of Events
  enum col_type type;
  int ia;
  double time;
} Event;

void initparticles( Particle *p, int np, double Lmin, double Lmax, double diameter){
  int i;
  for( i=0;i<np;i++){ // drand48() -- random double numbers uniform on (0 1)
    p[i].x = Lmin +diameter/2 + (Lmax-Lmin-diameter)*drand48(); //random positions for intial condition
    p[i].y = Lmin +diameter/2 + (Lmax-Lmin-diameter)*drand48();


    p[i].vx = 0;// choose random speeds too using drand48();
    p[i].vy = 0;
  }
}

int main(){
  double FPS=5.; //frames per second in animation
  int Np=2; //Number of particles
  double diameter=1;//particle size
  int Pix=600; //Number of pixels for window
  double Lmax=10, Lmin=0; //Physical dimensions of box
  Graphics gw(Np,Pix, Lmin ,Lmax,diameter);// Open a window to plot particles in
  srand48(1);//inititalize random numbers -- to find always the same value // you can replace "1" by time(NULL) 

  Particle *p= (Particle *) malloc( Np *sizeof( Particle)); //an array of particles
  initparticles(p,Np,Lmin, Lmax,diameter); //place particles in box
  Event *e = (Event *) malloc( 4*Np* sizeof(Event) ); // 4 Np possible collisions with walls
  
  gw.draw(p,FPS,0); //draw initial position and pause one second
  sleep(1);
  for (int l=0; l<10000;l++){//long loop animation...
    //find future collision using exact calculations of collision times
    e[0].type=right; //how to use the event array...
    e[0].time = 0.1234;
    e[0].ia = 27;
    // find the very first collision in the future by looking at e[].time
    // move particles
    gw.draw(p, FPS,l);
  }

  free(p);
  free(e);
  
  return 0;
}




