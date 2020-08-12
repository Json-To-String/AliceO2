#include "Constants.h"

//TGeoVolume* Detector::
void constructFrameGeometry()
{
//std::cout << sFrame1X << endl;

//
//  // define the media
 // TGeoMedium* Vacuum = gGeoManager->GetMedium("FT0_Vacuum$");
//  TGeoMedium* Al = gGeoManager->GetMedium("FT0_Aluminium$");

  // material and medium
  TGeoMaterial *alMat = new TGeoMaterial("Al", 26.98,13,2.7);
  TGeoMedium   *alMed = new TGeoMedium("Al",1,alMat);

  TGeoMaterial *vacMat = new TGeoMaterial("Vacuum",0,0,0);
  TGeoMedium   *vacMed = new TGeoMedium("Vacuum",1,vacMat);
// make a volume assembly for the frame
  TGeoVolumeAssembly* FT0_Frame = new TGeoVolumeAssembly("FT0_Frame");
//
//  // define translations for the quartz radiators and PMTs
//  defineTransformations();
//
  // cout<<frame1CompositeShapeBoolean<<endl;

  // remove the radiators
  std::string frame1CompositeShapeBoolean = "";
  frame1CompositeShapeBoolean += "((frame1";
  frame1CompositeShapeBoolean += " - quartzRadiator:quartzRadiatorTr1";
  frame1CompositeShapeBoolean += " - quartzRadiator:quartzRadiatorTr2";
  frame1CompositeShapeBoolean += " - quartzRadiator:quartzRadiatorTr3";
  frame1CompositeShapeBoolean += " - quartzRadiator:quartzRadiatorTr4";
  frame1CompositeShapeBoolean += " - quartzRadiator:quartzRadiatorTr5";
  frame1CompositeShapeBoolean += " - quartzRadiator:quartzRadiatorTr6)";

  // remove the PMTs
  frame1CompositeShapeBoolean += " - PMT:PMTTr1";
  frame1CompositeShapeBoolean += " - PMT:PMTTr2";
  frame1CompositeShapeBoolean += " - PMT:PMTTr3";
  frame1CompositeShapeBoolean += " - PMT:PMTTr4";
  frame1CompositeShapeBoolean += " - PMT:PMTTr5";
  frame1CompositeShapeBoolean += " - PMT:PMTTr6)";

  std::string frame2CompositeShapeBoolean = "";
  frame2CompositeShapeBoolean += "((frame2";

  // remove the radiators
  frame2CompositeShapeBoolean += " - quartzRadiator:quartzRadiatorTr7";
  frame2CompositeShapeBoolean += " - quartzRadiator:quartzRadiatorTr8";
  frame2CompositeShapeBoolean += " - quartzRadiator:quartzRadiatorTr9";
  frame2CompositeShapeBoolean += " - quartzRadiator:quartzRadiatorTr10";
  frame2CompositeShapeBoolean += " - quartzRadiator:quartzRadiatorTr11";
  frame2CompositeShapeBoolean += " - quartzRadiator:quartzRadiatorTr12)";

  //// remove the PMTs
  frame2CompositeShapeBoolean += " - PMT:PMTTr7";
  frame2CompositeShapeBoolean += " - PMT:PMTTr8";
  frame2CompositeShapeBoolean += " - PMT:PMTTr9";
  frame2CompositeShapeBoolean += " - PMT:PMTTr10";
  frame2CompositeShapeBoolean += " - PMT:PMTTr11";
  frame2CompositeShapeBoolean += " - PMT:PMTTr12)";

  // create a string for the boolean operations for the composite plateGroup shape
  std::string frameCompositeShapeBoolean = "";

  // add frames 1 and 2
  frameCompositeShapeBoolean += "frameRemovedPMTandRadiators1:frameTr1";
  frameCompositeShapeBoolean += " + frameRemovedPMTandRadiators2:frameTr2";

  // add the plateGroups
  frameCompositeShapeBoolean += " + plateGroup:plateGroupTr1";
  frameCompositeShapeBoolean += " + plateGroup:plateGroupTr2";

  // subtract the extra Al
  frameCompositeShapeBoolean += " - rect1:rectTr1";
  frameCompositeShapeBoolean += " - rect2:rectTr2";
  frameCompositeShapeBoolean += " - rect3:rectTr3";
  frameCompositeShapeBoolean += " - rect4:rectTr4";
  frameCompositeShapeBoolean += " - rect5:rectTr5";
  frameCompositeShapeBoolean += " - rect6:rectTr6";
  frameCompositeShapeBoolean += " - rect7:rectTr7";
  frameCompositeShapeBoolean += " - rect8:rectTr8";

  // create a string for the boolean operations for the composite plateGroup shape
  std::string plateGroupCompositeShapeBoolean = "";

  // add the plateBoxes to the plateGroup
  plateGroupCompositeShapeBoolean += "plateBox:plateTr1";
  plateGroupCompositeShapeBoolean += " + plateBox:plateTr2";
  plateGroupCompositeShapeBoolean += " + plateBox:plateTr3";


  // create a string for the boolean operations for the composite opticalFiberPlate1 shape
  std::string opticalFiberPlateCompositeShapeBoolean1 = "";
  opticalFiberPlateCompositeShapeBoolean1 += "cablePlate";
  opticalFiberPlateCompositeShapeBoolean1 += " - opticalFiberHead:opticalFiberHeadTr1";
  opticalFiberPlateCompositeShapeBoolean1 += " - opticalFiberHead:opticalFiberHeadTr2";
  opticalFiberPlateCompositeShapeBoolean1 += " - opticalFiberHead:opticalFiberHeadTr3";
  opticalFiberPlateCompositeShapeBoolean1 += " - opticalFiberHead:opticalFiberHeadTr4";

  // create a string for the boolean operations for the composite opticalFiberPlate2 shape
  std::string opticalFiberPlateCompositeShapeBoolean2 = "";

  // remove the opticalFiberHeads from the cablePlate
  opticalFiberPlateCompositeShapeBoolean2 += "cablePlate";
  opticalFiberPlateCompositeShapeBoolean2 += " - opticalFiberHead:opticalFiberHeadTr5";
  opticalFiberPlateCompositeShapeBoolean2 += " - opticalFiberHead:opticalFiberHeadTr6";
  opticalFiberPlateCompositeShapeBoolean2 += " - opticalFiberHead:opticalFiberHeadTr7";
  opticalFiberPlateCompositeShapeBoolean2 += " - opticalFiberHead:opticalFiberHeadTr8";


  // create a string for the boolean operations for the composite pmtCorner shape
  std::string pmtCornerCompositeShapeBoolean = "";
  pmtCornerCompositeShapeBoolean += "pmtCornerRect:pmtCornerRectTr";
  pmtCornerCompositeShapeBoolean += " - pmtCornerTube:pmtCornerTubeTr";


  // create a string for the boolean operations for the composite PMT shape
  std::string pmtCompositeShapeBoolean = "";
  pmtCompositeShapeBoolean += "pmtBox";
  pmtCompositeShapeBoolean += " - PMTCorner:PMTCornerTr1";
  pmtCompositeShapeBoolean += " - PMTCorner:PMTCornerTr2";
  pmtCompositeShapeBoolean += " - PMTCorner:PMTCornerTr3";
  pmtCompositeShapeBoolean += " - PMTCorner:PMTCornerTr4";


  // create a string for the boolean operations for the composite plateBox shape
  std::string plateBoxCompositeShapeBoolean = "";
  plateBoxCompositeShapeBoolean += "basicPlate";
  plateBoxCompositeShapeBoolean += " + basicPlate:basicPlateTr";
  plateBoxCompositeShapeBoolean += " + opticalFiberPlate1:opticalFiberPlateTr1";
  plateBoxCompositeShapeBoolean += " + opticalFiberPlate2:opticalFiberPlateTr2";


  //
  // cout<<frame1CompositeShapeBoolean<<endl;
  // cout<<frame2CompositeShapeBoolean<<endl;
  // cout<<frameCompositeShapeBoolean<<endl;

  // approximate the frame with some rectangles
  TGeoBBox* frame1 = new TGeoBBox("frame1", sFrame1X / 2, sFrame1Y / 2, sFrameZ / 2);
  TGeoBBox* frame2 = new TGeoBBox("frame2", sFrame2X / 2, sFrame2Y / 2, sFrameZ / 2);
  TGeoBBox* quartzRadiator = new TGeoBBox("quartzRadiator", sQuartzRadiatorSide / 2, sQuartzRadiatorSide / 2, sQuartzRadiatorZ / 2);
  TGeoBBox* rect1 = new TGeoBBox("rect1", sRect1X / 2, sRect1Y / 2, sFrameZ / 2);
  TGeoBBox* rect2 = new TGeoBBox("rect2", sRect2X / 2, sRect2Y / 2 + sEps, sFrameZ / 2 - sMountZ / 2);
  TGeoBBox* rect3 = new TGeoBBox("rect3", sRect3X / 2, sRect3Y / 2, sFrameZ / 2);
  TGeoBBox* rect4 = new TGeoBBox("rect4", sRect4X / 2, sRect4Y / 2, sFrameZ / 2);
  TGeoBBox* rect5 = new TGeoBBox("rect5", sRect5X / 2 + sEps, sRect5Y / 2 + sEps, sFrameZ / 2 + sEps);
  TGeoBBox* rect6 = new TGeoBBox("rect6", sRect6X / 2 + sEps, sRect6Y / 2 + sEps, sFrameZ / 2 + sEps);
  TGeoBBox* rect7 = new TGeoBBox("rect7", sRect7X / 2 + sEps, sRect7Y / 2 + sEps, sFrameZ / 2 - sMountZ / 2 + sEps);
  TGeoBBox* rect8 = new TGeoBBox("rect8", sRect8X / 2 + sEps, sRect8Y / 2 + sEps, sFrameZ / 2 + sEps);

 // PMT needs round edges
 TGeoBBox* pmtBox = new TGeoBBox("pmtBox", sPmtSide / 2 + sEps, sPmtSide / 2 + sEps, sPmtZ / 2 + sEps);
 TGeoBBox* pmtCornerRect = new TGeoBBox("pmtCornerRect", sCornerRadius / 2, sCornerRadius / 2, sPmtZ / 2);
 TGeoTube* pmtCornerTube = new TGeoTube("pmtCornerTube", 0, sCornerRadius, sPmtZ / 2);


 TGeoVolume* PMTCorner = new TGeoVolume("PMTCorner", new TGeoCompositeShape("PMTCorner", pmtCornerCompositeShapeBoolean, alMed));
 // TGeoVolume* PMT = new TGeoVolume("PMT", new TGeoCompositeShape("PMT", pmtCompositeShapeBoolean().c_str()), Vacuum);

 // // add the plates on the bottom of the frame
 // TGeoBBox* basicPlate = new TGeoBBox("basicPlate", sPlateSide / 2, sPlateSide / 2, sBasicPlateZ / 2);
 // TGeoBBox* cablePlate = new TGeoBBox("cablePlate", sPlateSide / 2, sPlateSide / 2, sCablePlateZ  / 2);
 // TGeoBBox* opticalFiberHead = new TGeoBBox("opticalFiberHead", sFiberHeadX / 2, sFiberHeadY / 2, sCablePlateZ  / 2);
 // TGeoCompositeShape* opticalFiberPlate1 = new TGeoCompositeShape("opticalFiberPlate1", opticalFiberPlateCompositeShapeBoolean1().c_str());
 // TGeoCompositeShape* opticalFiberPlate2 = new TGeoCompositeShape("opticalFiberPlate2", opticalFiberPlateCompositeShapeBoolean2().c_str());
 // TGeoCompositeShape* plateBox = new TGeoCompositeShape("plateBox", plateBoxCompositeShapeBoolean().c_str());                                 // holds 2 basic plates and 2 cable plates
 // TGeoVolume* plateGroup = new TGeoVolume("plateGroup", new TGeoCompositeShape("plateGroup", plateGroupCompositeShapeBoolean().c_str()), Al); // holds 3 plate boxes
 //
 // // remove the quartz radiators and PMTs from the frame
 // TGeoCompositeShape* frameRemovedPMTandRadiators1 = new TGeoCompositeShape("frameRemovedPMTandRadiators1", frame1CompositeShapeBoolean().c_str());
 // TGeoCompositeShape* frameRemovedPMTandRadiators2 = new TGeoCompositeShape("frameRemovedPMTandRadiators2", frame2CompositeShapeBoolean().c_str());
 //
 // // make the right side frame
 // TGeoVolume* frame = new TGeoVolume("frame", new TGeoCompositeShape("frame", frameCompositeShapeBoolean().c_str()), Al);
 //
 // // reflection for the left side of the frame
 // TGeoRotation* reflect = new TGeoRotation("reflect");
 // reflect->ReflectX(true);
 // reflect->ReflectY(true);
 // reflect->RegisterYourself();
 //
 // // add the right and left sides to top volume
 // FT0_Frame->AddNode(frame, 1);          // right side
 // FT0_Frame->AddNode(frame, 2, reflect); // left side
 //
 // return FT0_Frame;
}
