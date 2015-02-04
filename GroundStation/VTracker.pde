

// a track cursor can be assigned to a particular vTracker instance
// to show the position of the tracked object/colour area
// param s = size of the crosshair used
class TrackCursor {
  int sz;
  VTracker parent;

  TrackCursor (VTracker p, int s) {
    parent=p;
    sz=s;
  }

  void update() {
    stroke(255, 0, 0);
    float xx = parent.trackingX;
    float yy = parent.trackingY;
    line(xx-sz, yy, xx+sz, yy);
    line(xx, yy-sz, xx, yy+sz);
    noStroke();
  }
}


// VTracker class v1.04
// author: info@toxi.co.uk (based on code by robert@flight404.com)
// date:   08/09/03

class VTracker {

  // res = number of pixels skipped in x/y direction when analysing image
  // trackCol = packed colour integer, e.g. 0xffcc33 for some bright yellow
  // tolerance = value between [0..255] to control the tracking accuracy (values between 5..20 work best)
  // trk_follow = value between 0.0...1.0 used for interpolated movement of the tracking coordinates (values closer to 1.0 = more snappy)

  VTracker(Capture video, int rez, int trackCol, float tol, float trk_follow) {
    this.video = video;
    vWidth=video.width/rez;
    vHeight=video.height/rez;
    rowHeight=video.width*rez;
    similaritiesX=new int[vWidth];
    similaritiesY=new int[vHeight];
    res=rez;
    this.trackingNewColour(trackCol);
    tolerance=tol;
    trackFactor=trk_follow;
    this.reset();
  }

  // notify tracker about new video frame/data
  void newFrame() {
    if (!newFrame) newFrame=true;
  }

  PVector getVector() {
    return new PVector(trackingX, trackingY);
  }

  // set a new tracking colour for this instance
  void trackingNewColour(int c) {
    PVector oldColour = trackColour;
    int trackR=c>>16&0xff;
    int trackG=c>>8&0xff;
    int trackB=c&0xff;
    trackColour = calculateCI(trackR, trackG, trackB);
    println("tracking new colour: "+trackR+","+trackG+","+trackB);
    println("Invariant representation: "+trackColour);
    
    if (oldColour != null)
      println(trackColour.dist(oldColour));
  }

  // parse the current video image and try to find hotspot
  // needs to be called every frame, but will only fully execute if there's a new video frame present
  // boolean display is used to disable drawing the video image (important when using several instances)
  // see above example

  // note: quality of tracking will improve once the new imaging functions are implemented in P5
  // at the moment only single pixels instead of averaged pixelblocks are used for the analysis

  void analyse(boolean display) {

    if (!newFrame) {
      return;
    }

    int yoffset=0;
    int col;
    int xx=0;
    int yy=0;
    int r=0, g=0, b=0;

    // parse the video pixel buffer in the set (scaled down) resolution
    for (int y=0; y<vHeight; y++) {
      xx = 0;
      yy = y*res;
      for (int x=2; x<vWidth; x++) {
        col = video.pixels[yoffset+xx];
        r = col>>16&0xff;
        g = col>>8&0xff;
        ;
        b = col&0xff;

        PVector ci = calculateCI(r, g, b); 
        float d = trackColour.dist(ci);
        if (d<tolerance) {
          similaritiesX[x]++;
          similaritiesY[y]++;
          if (display) {
            fill(r,g,b);
            rect(xx, yy, res, res);
          }
        }    
        xx+=res;
      }
      yoffset+=rowHeight;
    }

    // now on to finding the peaks in horizontal and vertical direction
    // if no peak is found (or in other words, the tracked colour is not
    // present in the video image) the peak coodinates will be negative
    // (your code could check for that, for instance...)
    float peakXPos=-1, peakYPos=-1;

    peakXPos = findPeak(similaritiesX);
    peakYPos = findPeak(similaritiesY);

    // update the peak coordinates with the set interpolation speed
    trackingX -= (trackingX - ((peakXPos+0.5) * res)) * trackFactor;
    trackingY -= (trackingY - ((peakYPos+0.5) * res)) * trackFactor;

    this.reset();
  }

  // Find the location of the 'peak' of the data passed to us
  // This implementation works for round things, and some others, but its not clever.
  // The centre of the largest continuous span of non 0 data is returned.
  float findPeak(int[] data) {
    float current =0;
    float max = -1, peakPos = -1, segmentLeft=-1,  segmentSum=0;
    boolean segmentStarted = false;
    for (int x=0; x< data.length; x++) {
      current=data[x];
      if (current>0) {
        fill(current);
        if (data.length==width) 
          rect(x*res, 0, 1, 40); 
        else
          rect(0, x*res, 40, 1);
      }

      if (current > 0) {
        if (!segmentStarted) {
          segmentStarted = true;
          segmentLeft = x;
          segmentSum = 0;
        }
        segmentSum+=current;
      } 
      if (segmentStarted && (current == 0 || x == (data.length - 1))) {
        segmentStarted = false;
        float segmentSize = x - segmentLeft;
        if ((segmentSize+segmentSum) > max) {
          peakPos=x-segmentSize/2;
          max = segmentSize+segmentSum;
        }
      }
    }
    return peakPos;
  }

  // clear all values before processing a new frame
  void reset() {
    for (int x=0; x<vWidth; x++)  similaritiesX[x] = 0;
    for (int y=0; y<vHeight; y++) similaritiesY[y] = 0;
    newFrame=false;
  }

  // Return a vector representing a vector representing the colour in a form that
  // attempts not to vary according to lighting conditions and viewing angled...
  PVector calculateCI(int r, int g, int b) {
    if (invarianceFilters[invarianceFilter] == "rgbNorm") {
      return rgbNorm(r, g, b);
    }
    if (invarianceFilters[invarianceFilter] == "rgb") {
      return new PVector(r/255.0, g/255.0, b/255.0);
    }
    if (invarianceFilters[invarianceFilter] == "yuv") {
      return rgbToYuv(r,g,b);
    }
    throw new RuntimeException("CalculateCI no such filter");
  }

  String getFilter() {
    return invarianceFilters[invarianceFilter];
  }

  void switchFilter() {
    invarianceFilter = (invarianceFilter+1) % invarianceFilters.length;
  }
  
  // class fields...
  Capture video;
  int invarianceFilter=2;
  String invarianceFilters[] = {"rgb", "rgbNorm", "yuv"};
  float trackingX, trackingY;
  int vWidth;
  int vHeight;
  int rowHeight;
  int res;
  boolean newFrame;
  float trackFactor;
  PVector trackColour;

  float tolerance;
  int[] similaritiesX, similaritiesY;
}

PVector rgbToYuv(int r, int g, int b) {
  float R=r/255.0, G=g/255.0, B=b/255.0;
  PVector result = new PVector(0.299 * R + 0.587 * G + 0.114 * B, 
  -0.14713 * R - 0.28886 * G + 0.436 * B, 
  0.615 * R - 0.51499 * G - 0.10001 * B);
  // make very bright or very light things way out of bounds, as
  // these things are difficult to tell the colour of.aa
  if (result.x <0.1 || result.x > 0.8)
    result.x=10000;
  return result;
}

PVector rgbNorm(int r, int g, int b) {
  PVector result = new PVector((float)r/(r+g+b), (float)g/(r+g+b), (float)b/(r+g+b));
 if (abs(result.x/result.y-1) < 0.15)
   result.x=100000000;
 return result;
}
