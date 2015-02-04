import processing.serial.*;

/* video blob tracking based info@toxi.co.uk's code, based upon on rob hodgin's code (http://www.proce55ing.net/software/tracking/)
 *
 */

VTracker[] vTrackers;
TrackCursor[] cursors;
import processing.video.*;
boolean colour_pick=false, showVideo=false;
int     currTracker=0;
Capture video;
CopterModel copter;
CopterVisualisation visual;

void setup() {
  size(640, 600);
  noFill();
  ellipseMode(CENTER);
  noStroke();
  frameRate(30);

  PFont font = createFont("SansSerif", 30);      // font setup
  textFont(font);
  textAlign(CENTER, CENTER);


  String list[] = Capture.list();
  println(list);

  video = new Capture(this, 640,480, 30);//, 40*4, 30*4, 15);
  // Comment the following line if you use Processing 1.5
  video.start();
  video.width=640 ; 
  video.height=480;


  // new vTracker objects to track several instances
  vTrackers = new VTracker[2];
  // first tracker to track white areas with a tolerance of 15
  vTrackers[0] = new VTracker(video, 1, 0x007401, 0.24, 0.75); 
  vTrackers[1] = new VTracker(video, 1, 0xee3a64, 0.24, 0.75);   // another tracker to track bright red areas with a tolerance of 10
  //vTrackers[1] = new VTracker(1,0xff0000,10,0.3);
  // attach independent cursors to the trackers
  cursors = new TrackCursor[2];
  cursors[0] = new TrackCursor(vTrackers[0], 100);
  cursors[1] = new TrackCursor(vTrackers[1], 100);

  copter = new CopterModel((PApplet)this);
  visual = new CopterVisualisation(copter, 0, 490, 100);
}

boolean newframe=false;
void draw() {
  if (!video.available()) {
    return;
  }
  if (showVideo) {
    video.read();
    set(0, 0, video);
  } 
  else {
    background(0);
    video.read();
  }

  for (int i=0; i<vTrackers.length; i++) { 
    vTrackers[i].newFrame();
    vTrackers[i].analyse(true); 
    cursors[i].update();
  }

  updateModel(copter, vTrackers[0].getVector(), vTrackers[1].getVector());
  

  visual.update();

  // if mouse has been pressed, use new colour under mouse position for the next tracker
  if (colour_pick) {
    vTrackers[currTracker++].trackingNewColour(video.pixels[mouseY*width+mouseX]);
    currTracker%=vTrackers.length;
    colour_pick=false;
  }
  
  copter.sendData();
}

void updateModel(CopterModel copter, PVector p1, PVector p2) {
  if ((p1.x < 0 && p1.y < 0) || (p2.x < 0 && p2.y < 0)) {
    copter.tracking = false;
    copter.throttle*=0.95;
    copter.rudder=0;
    copter.aileron=0;
    copter.elevator=0;
    return;
  }
  copter.tracking = true;
  
  float distanceBetweenPoints= p1.dist(p2);
  copter.height=100 / distanceBetweenPoints;
  copter.pos = p1.get();
  copter.pos.add(p2);
  copter.pos.div(2);
  PVector heading = p2.get();
  heading.sub(p1);
  copter.heading=degrees(PVector.angleBetween(new PVector(0,1), heading));
  updateAileron(copter); 
  updateElevator(copter); 
  updateRudder(copter);
  if (copter.aileron ==0 && copter.elevator==0) {
    copter.rudder*=0.5;
  } 

  stroke(200);
  ellipse(copter.pos.x, copter.pos.y, 20, 20);

}

void updateElevator(CopterModel copter) {
  float y = copter.pos.y -copter.targetPos.y;
  if ( abs(y) < 15) { 
    copter.elevator=0;
    return;
  }

  if (y <0) {
    copter.elevator=-0.1;
  }
  if (y >0) {
    copter.elevator=+0.1;
  }
}

void updateAileron(CopterModel copter) {
  float x = copter.pos.x -copter.targetPos.x;
  if ( abs(x) < 15) { 
    copter.aileron=0;
    return;
  }
  if (x <0) {
    copter.aileron=-0.1;
  }
  if (x >0) {
    copter.aileron=+0.1;
  }
}

void updateRudder(CopterModel copter) {
  if (abs(copter.targetHeading-copter.heading) < 5) {
    copter.rudder = 0; 
   return; 
  }  
  if ( (copter.targetHeading-copter.heading) < 0) {
    copter.rudder= + 0.07;
  } 
  if ( (copter.targetHeading-copter.heading) > 0) {
    copter.rudder= - 0.07;
  } 
}

void mousePressed() {
  colour_pick=true;
}

void keyPressed() {
  if (key == 's') {
    for (int i=0; i<vTrackers.length; i++) { 
      vTrackers[i].tolerance -= 0.01;
    }
  }
  if (key == 'S') {
    for (int i=0; i<vTrackers.length; i++) { 
      vTrackers[i].tolerance += 0.01;
    }
  }
  if (key == 'v') {
    showVideo = !showVideo;
  }
  if (key == 'f') {
    for (int i=0; i<vTrackers.length; i++) { 
      vTrackers[i].switchFilter();
    }
  }
  float stepSize=0.06;
  if (key == 'a') {
    copter.throttle += stepSize;
  }
  if (key == 'z') {
    copter.throttle -= stepSize;
  }
  if (key == 'A' || key == 'Z') {
    copter.throttle = 0;
  }

  if (key == CODED) {
    if (keyCode == UP) {
      copter.elevator+=stepSize;
    } 
    else if (keyCode == DOWN) {
      copter.elevator-=stepSize;
    } else    if (keyCode == RIGHT) {
      copter.aileron+=stepSize;
    } 
    else if (keyCode == LEFT) {
      copter.aileron-=stepSize;
    }  }
  println("Tolerance: " + vTrackers[0].tolerance);
  println("Showing Video: " + showVideo+copter.throttle);
  println("Invariance Filter: " + vTrackers[0].getFilter());
}
