#include <iostream>
#include <cmath>


//give position of general sensitive element block
Double_t pmtPos(x,y,z){


  const Double_t sFrameZ = 5.700;
  const Double_t sPmtZ = 3.750;
  const Double_t sQuartzRadiatorZ = 1.950;

  Double_t  sPmtHeight = sFrameZ / 2 - sPmtZ / 2;
  Double_t  sQuartzHeight = -sFrameZ / 2 + sQuartzRadiatorZ / 2;

  Double_t frameHeight = 2.5;

  Double_t rmag=sqrt(x*x+y*y+z*z);

  Double_t factor = (rmag +  (frameHeight / 2.0) - (sPmtHeight / 2)) / rmag;


  return factor;


}
