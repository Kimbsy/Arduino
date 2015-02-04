class CopterModel {
  public float throttle =0, aileron =0, rudder =0, elevator =0 ;
  public float heading =0 , height=0;
  public float targetHeading=135, targetHeight =0;
    // Horizontal (in same plane as the camera/ground) position
  PVector pos, targetPos;
  boolean tracking = false;

  Serial port;
  PApplet parent;

  public CopterModel(PApplet parent) {
    this.parent = parent;
    targetPos = new PVector();
    targetPos.x = parent.width/2;
    targetPos.y = parent.height/2;
  }

  void sendData() {
    if (port != null) {
      throttle = clamp(throttle, 0, 1);
      rudder = clamp(rudder, -1, 1);
      aileron = clamp(aileron, -1, 1);
      elevator = clamp(elevator, -1, 1);

      byte[] data= {
        23, 
        (byte)map(throttle, 0, 1, 0, 255), 
        (byte)map(rudder, 1, -1, 0, 255), 
        (byte)map(aileron, 1, -1, 0, 255), 
        (byte)map(elevator, -1, 1, 0, 255)
        };
        port.write(data);
        println((byte)map(throttle, 0, 1, 0, 255));
    } 
    else {
      port = initSerial();
    }
  }

  Serial initSerial() {
    Serial port;
    try {
      if (Serial.list().length==0) {
        return null;
      }
      println(Serial.list()[0]);
      port = new Serial(parent, Serial.list()[0], 115200);  // make sure Arduino is talking serial at this baud rate
      port.clear();            // flush buffer
      port.bufferUntil('\n');  // set buffer full flag on receipt of carriage return
    } 
    catch (IllegalStateException e) {
      port=null;
    }
    return port;
  }
}

class CopterVisualisation {
  CopterModel copter;
  int posx, posy, h;

  public CopterVisualisation(CopterModel copter, int posx, int posy, int h) {
    this.copter = copter;
    this.posx = posx;
    this.posy = posy;
    this.h = h;
  }

  void update() {
    drawIndicator(posx+h/2, posy+h/2, h, copter.rudder, copter.throttle-1);
    drawIndicator(posx+4*h/2, posy+h/2, h, copter.aileron*2, copter.elevator*2);
    if (copter.tracking) {
      text("Height: " + nf(copter.height, 2, 3),posx+h*4,posy);
      text("Heading: " + nf(copter.heading, 2, 3),posx+h*4,posy+40);
    } else {
      text("Lost the copter", posx+h*4,posy);
    }
  }
  
  // range of posx and posy assumed to be -1 + 1
  void drawIndicator(int x, int y, int size, float posx, float posy) {
    PVector pos=new PVector(posx, posy);
    pos.mult(size/2);
    fill(0);
    stroke(255);
    ellipse(x, y, size, size);
    noFill();
    ellipse(x, y, size*0.75, size*0.75);
    ellipse(x, y, size*0.5, size*0.5);
    ellipse(x, y, size*0.25, size*0.25);
    fill(204, 102, 0);
    ellipse(x+pos.x, y-pos.y, size/5, size/5);
    noStroke();
    noFill();
  }
}

float clamp(float in, float min, float max) {
  if (in < min) return min;
  if (in > max) return max;
  return in;
}
