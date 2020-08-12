#include "../temp/Constants.h"
#include "TGeoManager.h"

void standalone() {

  // starting a manager
  TGeoManager *mgr = new TGeoManager("manager", "standalone");

  // material and medium
  TGeoMaterial *alMat = new TGeoMaterial("Al", 26.98,13,2.7);
  TGeoMedium   *alMed = new TGeoMedium("Al",1,alMat);

  TGeoMaterial *vacMat = new TGeoMaterial("Vacuum",0,0,0);
  TGeoMedium   *vacMed = new TGeoMedium("Vacuum",1,vacMat);

  // Beginning of translations
  // translations for quartz radiators in frame 1
  TGeoTranslation* quartzRadiatorTr1 = new TGeoTranslation("quartzRadiatorTr1", sPos1X[0], sPos1Y[0], sQuartzHeight);
  quartzRadiatorTr1->RegisterYourself();
  TGeoTranslation* quartzRadiatorTr2 = new TGeoTranslation("quartzRadiatorTr2", sPos1X[0], sPos1Y[1], sQuartzHeight);
  quartzRadiatorTr2->RegisterYourself();
  TGeoTranslation* quartzRadiatorTr3 = new TGeoTranslation("quartzRadiatorTr3", sPos1X[1], sPos1Y[2], sQuartzHeight);
  quartzRadiatorTr3->RegisterYourself();
  TGeoTranslation* quartzRadiatorTr4 = new TGeoTranslation("quartzRadiatorTr4", sPos1X[1], sPos1Y[3], sQuartzHeight);
  quartzRadiatorTr4->RegisterYourself();
  TGeoTranslation* quartzRadiatorTr5 = new TGeoTranslation("quartzRadiatorTr5", sPos1X[2], sPos1Y[2], sQuartzHeight);
  quartzRadiatorTr5->RegisterYourself();
  TGeoTranslation* quartzRadiatorTr6 = new TGeoTranslation("quartzRadiatorTr6", sPos1X[2], sPos1Y[3], sQuartzHeight);
  quartzRadiatorTr6->RegisterYourself();

  // translations for quartz radiators in frame 2
  TGeoTranslation* quartzRadiatorTr7 = new TGeoTranslation("quartzRadiatorTr7", sPos2X[0], sPos2Y[0], sQuartzHeight);
  quartzRadiatorTr7->RegisterYourself();
  TGeoTranslation* quartzRadiatorTr8 = new TGeoTranslation("quartzRadiatorTr8", sPos2X[1], sPos2Y[0], sQuartzHeight);
  quartzRadiatorTr8->RegisterYourself();
  TGeoTranslation* quartzRadiatorTr9 = new TGeoTranslation("quartzRadiatorTr9", sPos2X[2], sPos2Y[1], sQuartzHeight);
  quartzRadiatorTr9->RegisterYourself();
  TGeoTranslation* quartzRadiatorTr10 = new TGeoTranslation("quartzRadiatorTr10", sPos2X[3], sPos2Y[1], sQuartzHeight);
  quartzRadiatorTr10->RegisterYourself();
  TGeoTranslation* quartzRadiatorTr11 = new TGeoTranslation("quartzRadiatorTr11", sPos2X[2], sPos2Y[2], sQuartzHeight);
  quartzRadiatorTr11->RegisterYourself();
  TGeoTranslation* quartzRadiatorTr12 = new TGeoTranslation("quartzRadiatorTr12", sPos2X[3], sPos2Y[2], sQuartzHeight);
  quartzRadiatorTr12->RegisterYourself();

  // translations for PMTs in frame 1
  TGeoTranslation* PMTTr1 = new TGeoTranslation("PMTTr1", sPos1X[0], sPos1Y[0], sPmtHeight);
  PMTTr1->RegisterYourself();
  TGeoTranslation* PMTTr2 = new TGeoTranslation("PMTTr2", sPos1X[0], sPos1Y[1], sPmtHeight);
  PMTTr2->RegisterYourself();
  TGeoTranslation* PMTTr3 = new TGeoTranslation("PMTTr3", sPos1X[1], sPos1Y[2], sPmtHeight);
  PMTTr3->RegisterYourself();
  TGeoTranslation* PMTTr4 = new TGeoTranslation("PMTTr4", sPos1X[1], sPos1Y[3], sPmtHeight);
  PMTTr4->RegisterYourself();
  TGeoTranslation* PMTTr5 = new TGeoTranslation("PMTTr5", sPos1X[2], sPos1Y[2], sPmtHeight);
  PMTTr5->RegisterYourself();
  TGeoTranslation* PMTTr6 = new TGeoTranslation("PMTTr6", sPos1X[2], sPos1Y[3], sPmtHeight);
  PMTTr6->RegisterYourself();

  // translations for PMTs in frame 2
  TGeoTranslation* PMTTr7 = new TGeoTranslation("PMTTr7", sPos2X[0], sPos2Y[0], sPmtHeight);
  PMTTr7->RegisterYourself();
  TGeoTranslation* PMTTr8 = new TGeoTranslation("PMTTr8", sPos2X[1], sPos2Y[0], sPmtHeight);
  PMTTr8->RegisterYourself();
  TGeoTranslation* PMTTr9 = new TGeoTranslation("PMTTr9", sPos2X[2], sPos2Y[1], sPmtHeight);
  PMTTr9->RegisterYourself();
  TGeoTranslation* PMTTr10 = new TGeoTranslation("PMTTr10", sPos2X[3], sPos2Y[1], sPmtHeight);
  PMTTr10->RegisterYourself();
  TGeoTranslation* PMTTr11 = new TGeoTranslation("PMTTr11", sPos2X[2], sPos2Y[2], sPmtHeight);
  PMTTr11->RegisterYourself();
  TGeoTranslation* PMTTr12 = new TGeoTranslation("PMTTr12", sPos2X[3], sPos2Y[2], sPmtHeight);
  PMTTr12->RegisterYourself();

  // define pmtCorner transformations
  TGeoTranslation* pmtCornerTubeTr = new TGeoTranslation("pmtCornerTubeTr", sPmtCornerTubePos, sPmtCornerTubePos, 0);
  pmtCornerTubeTr->RegisterYourself();
  TGeoTranslation* pmtCornerRectTr = new TGeoTranslation("pmtCornerRectTr", 0, 0, 0);
  pmtCornerRectTr->RegisterYourself();
  TGeoTranslation* PMTCornerTr1 = new TGeoTranslation("PMTCornerTr1", sPmtCornerPos, sPmtCornerPos, 0);
  PMTCornerTr1->RegisterYourself();
  TGeoRotation* reflect2 = new TGeoRotation();
  reflect2->ReflectX(true);
  reflect2->RegisterYourself();
  TGeoCombiTrans* PMTCornerTr2 = new TGeoCombiTrans("PMTCornerTr2", -sPmtCornerPos, sPmtCornerPos, 0, reflect2);
  PMTCornerTr2->RegisterYourself();
  TGeoRotation* reflect3 = new TGeoRotation();
  reflect3->ReflectX(true);
  reflect3->ReflectY(true);
  reflect3->RegisterYourself();
  TGeoCombiTrans* PMTCornerTr3 = new TGeoCombiTrans("PMTCornerTr3", -sPmtCornerPos, -sPmtCornerPos, 0, reflect3);
  PMTCornerTr3->RegisterYourself();
  TGeoRotation* reflect4 = new TGeoRotation();
  reflect4->ReflectY(true);
  reflect4->RegisterYourself();
  TGeoCombiTrans* PMTCornerTr4 = new TGeoCombiTrans("PMTCornerTr4", sPmtCornerPos, -sPmtCornerPos, 0, reflect4);
  PMTCornerTr4->RegisterYourself();
  TGeoRotation* reflect5 = new TGeoRotation();
  reflect5->ReflectX(true);
  reflect5->ReflectY(true);
  reflect5->RegisterYourself();
  TGeoCombiTrans* edgeCornerTr = new TGeoCombiTrans("edgeCornerTr", sEdgeCornerPos[0], sEdgeCornerPos[1], 0, reflect5);
  edgeCornerTr->RegisterYourself();
  // define transformations for the fiber heads in opticalFiberPlate1
  TGeoTranslation* opticalFiberHeadTr1 = new TGeoTranslation("opticalFiberHeadTr1", 1.7384, 1.36, 0);
  opticalFiberHeadTr1->RegisterYourself();
  TGeoTranslation* opticalFiberHeadTr2 = new TGeoTranslation("opticalFiberHeadTr2", 1.7384, -1.36, 0);
  opticalFiberHeadTr2->RegisterYourself();
  TGeoCombiTrans* opticalFiberHeadTr3 = new TGeoCombiTrans("opticalFiberHeadTr3", -0.9252, -.9375, 0, new TGeoRotation("rot3", 15, 0, 0));
  opticalFiberHeadTr3->RegisterYourself();
  TGeoCombiTrans* opticalFiberHeadTr4 = new TGeoCombiTrans("opticalFiberHeadTr4", -0.9252, .9375, 0, new TGeoRotation("rot4", -15, 0, 0));
  opticalFiberHeadTr4->RegisterYourself();

  // make the transformations for the fiber heads in opticalFiberPlate2
  TGeoCombiTrans* opticalFiberHeadTr5 = new TGeoCombiTrans("opticalFiberHeadTr5", 1.6714, 1.525, 0, new TGeoRotation("rot5", 30, 0, 0));
  opticalFiberHeadTr5->RegisterYourself();
  TGeoCombiTrans* opticalFiberHeadTr6 = new TGeoCombiTrans("opticalFiberHeadTr6", 1.6714, -1.525, 0, new TGeoRotation("rot6", -30, 0, 0));
  opticalFiberHeadTr6->RegisterYourself();
  TGeoCombiTrans* opticalFiberHeadTr7 = new TGeoCombiTrans("opticalFiberHeadTr7", -0.9786, -1.125, 0, new TGeoRotation("rot7", 30, 0, 0));
  opticalFiberHeadTr7->RegisterYourself();
  TGeoCombiTrans* opticalFiberHeadTr8 = new TGeoCombiTrans("opticalFiberHeadTr8", -0.9786, 1.125, 0, new TGeoRotation("rot8", -30, 0, 0));
  opticalFiberHeadTr8->RegisterYourself();

  // define transformations to form a plateBox (2 basicPlates and 2 cablePlates)
  TGeoCombiTrans* basicPlateTr = new TGeoCombiTrans("basicPlateTr", 0, -sPlateSpacing, 0, new TGeoRotation("basicPlateRot", 90, 0, 0));
  basicPlateTr->RegisterYourself();
  TGeoCombiTrans* opticalFiberPlateTr1 = new TGeoCombiTrans("opticalFiberPlateTr1", 0, 0, sOpticalFiberPlateZ, new TGeoRotation("opticalFiberPlateRot1", 90, 0, 0));
  opticalFiberPlateTr1->RegisterYourself();
  TGeoCombiTrans* opticalFiberPlateTr2 = new TGeoCombiTrans("opticalFiberPlateTr2", 0, -sPlateSpacing, sOpticalFiberPlateZ, new TGeoRotation("opticalFiberPlateRot2", 90, 0, 0));
  opticalFiberPlateTr2->RegisterYourself();

  // define transformations to form a plateGroup
  TGeoTranslation* plateTr1 = new TGeoTranslation("plateTr1", -sPlateSpacing, sPlateDisplacementDeltaY, 0);
  plateTr1->RegisterYourself();
  TGeoTranslation* plateTr2 = new TGeoTranslation("plateTr2", 0, 0, 0);
  plateTr2->RegisterYourself();
  TGeoTranslation* plateTr3 = new TGeoTranslation("plateTr3", sPlateSpacing, 0, 0);
  plateTr3->RegisterYourself();

  // TODO: fix plateGroupTr2
  // define transformations for the plateGroups (6 basicPlates and 6 cablePlates)
  TGeoTranslation* plateGroupTr1 = new TGeoTranslation("plateGroupTr1", sPlateDisplacementX, sPlateDisplacementY, sPlateGroupZ);
  plateGroupTr1->RegisterYourself();
  TGeoCombiTrans* plateGroupTr2 = new TGeoCombiTrans("plateGroupTr2", 10.4358 + 1.5 * sPlateDisplacementDeltaY, -7.0747, sPlateGroupZ, new TGeoRotation("plateGroup2Rotation", -90, 0, 0));
  plateGroupTr2->RegisterYourself();

  // position of the two rectangles used to approximate the frame
  TGeoTranslation* frameTr1 = new TGeoTranslation("frameTr1", sFrame1PosX, sFrame1PosY, 0);
  frameTr1->RegisterYourself();
  TGeoTranslation* frameTr2 = new TGeoTranslation("frameTr2", sFrame2PosX, sFrame2PosY, 0);
  frameTr2->RegisterYourself();

  // remove the two smaller rectangles from the frame
  TGeoTranslation* rectTr1 = new TGeoTranslation("rectTr1", sFrame1PosX + 3.25, sFrame1PosY + 6.1875, 0);
  rectTr1->RegisterYourself();

  TGeoTranslation* rectTr2 = new TGeoTranslation("rectTr2", sFrame1PosX + 9.3, sFrame1PosY - 0.5775, sMountZ / 2);
  rectTr2->RegisterYourself();

  TGeoTranslation* rectTr3 = new TGeoTranslation("rectTr3", sFrame1PosX + 10.75 - sRect3X / 2, sFrame1PosY - 6.8525 + sRect3Y / 2, 0);
  rectTr3->RegisterYourself();

  TGeoTranslation* rectTr4 = new TGeoTranslation("rectTr4", sFrame1PosX - 7.925, sFrame1PosY - 6.44, 0);
  rectTr4->RegisterYourself();

  TGeoTranslation* rectTr5 = new TGeoTranslation("rectTr5", sFrame2PosX + 6.965 - sRect5X / 2, sFrame2PosY + 4.3625 - sRect5Y / 2, 0);
  rectTr5->RegisterYourself();

  TGeoTranslation* rectTr6 = new TGeoTranslation("rectTr6", sFrame2PosX + 6.965 - sRect6X / 2, sFrame2PosY - 10.7375 + sRect6Y / 2, 0);
  rectTr6->RegisterYourself();

  TGeoTranslation* rectTr7 = new TGeoTranslation("rectTr7", sFrame2PosX + 6.965 - sRect6X - sRect7X / 2, sFrame2PosY - 10.7375 + sRect7Y / 2, sMountZ / 2);
  rectTr7->RegisterYourself();

  TGeoTranslation* rectTr8 = new TGeoTranslation("rectTr8", sFrame2PosX - 5.89 - sRect8X / 2, sFrame2PosY + 5.1125 + sRect8Y / 2, 0);
  rectTr8->RegisterYourself();

  // Beginning of booleans:
  std::string frame1CompositeShapeBoolean = "";
  frame1CompositeShapeBoolean += "((frame1";

  // remove the radiators
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

  // remove the PMTs
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



  // end of booleans


  // Beginning of Shapes
  TGeoVolume *chamber = gGeoManager->MakeBox("TOP",vacMed,100,100,100);
  gGeoManager->SetTopVolume(chamber);

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
  TGeoTube* pmtCornerTube = new TGeoTube("pmtCornerTube", 0, sCornerRadius + sEps, sPmtZ / 2 + sEps);
  TGeoVolume* PMTCorner = new TGeoVolume("PMTCorner", new TGeoCompositeShape("PMTCorner", pmtCornerCompositeShapeBoolean.c_str()), alMed);
  TGeoVolume* PMT = new TGeoVolume("PMT", new TGeoCompositeShape("PMT", pmtCompositeShapeBoolean.c_str()), vacMed);

  // add the plates on the bottom of the frame
  TGeoBBox* basicPlate = new TGeoBBox("basicPlate", sPlateSide / 2, sPlateSide / 2, sBasicPlateZ / 2);
  TGeoBBox* cablePlate = new TGeoBBox("cablePlate", sPlateSide / 2, sPlateSide / 2, sCablePlateZ  / 2);
  TGeoBBox* opticalFiberHead = new TGeoBBox("opticalFiberHead", sFiberHeadX / 2, sFiberHeadY / 2, sCablePlateZ  / 2);
  TGeoCompositeShape* opticalFiberPlate1 = new TGeoCompositeShape("opticalFiberPlate1", opticalFiberPlateCompositeShapeBoolean1.c_str());
  TGeoCompositeShape* opticalFiberPlate2 = new TGeoCompositeShape("opticalFiberPlate2", opticalFiberPlateCompositeShapeBoolean2.c_str());
  TGeoCompositeShape* plateBox = new TGeoCompositeShape("plateBox", plateBoxCompositeShapeBoolean.c_str());                                 // holds 2 basic plates and 2 cable plates
  TGeoVolume* plateGroup = new TGeoVolume("plateGroup", new TGeoCompositeShape("plateGroup", plateGroupCompositeShapeBoolean.c_str()), alMed); // holds 3 plate boxes

  // remove the quartz radiators and PMTs from the frame
  TGeoCompositeShape* frameRemovedPMTandRadiators1 = new TGeoCompositeShape("frameRemovedPMTandRadiators1", frame1CompositeShapeBoolean.c_str());
  TGeoCompositeShape* frameRemovedPMTandRadiators2 = new TGeoCompositeShape("frameRemovedPMTandRadiators2", frame2CompositeShapeBoolean.c_str());


  // end of old shapes
  // New shapes here:

  // std::cout << frame1CompositeShapeBoolean.c_str() << std::endl;

  // tube goes to bottom left
  TGeoTranslation* rectCornerTr1 = new TGeoTranslation("rectCornerTr1", -sCornerRadius/2.,-sCornerRadius/2., 0.);
  rectCornerTr1->RegisterYourself();

  // tube goes to bottom right
  TGeoTranslation* rectCornerTr2 = new TGeoTranslation("rectCornerTr2", sCornerRadius/2.,-sCornerRadius/2., 0.);
  rectCornerTr2->RegisterYourself();

  // tube goes to top right
  TGeoTranslation* rectCornerTr3 = new TGeoTranslation("rectCornerTr3", sCornerRadius/2.,sCornerRadius/2., 0.);
  rectCornerTr3->RegisterYourself();

  // tube goes to top left
  TGeoTranslation* rectCornerTr4 = new TGeoTranslation("rectCornerTr4", -sCornerRadius/2.,sCornerRadius/2., 0.);
  rectCornerTr4->RegisterYourself();

  // Rounded corner goes to top right
  TGeoTranslation* pmtCornerTr1 = new TGeoTranslation("pmtCornerTr1", sPmtSide/2.,sPmtSide/2.,0.);
  pmtCornerTr1->RegisterYourself();

  // rounded corner goes to top left
  TGeoTranslation* pmtCornerTr2 = new TGeoTranslation("pmtCornerTr2", -sPmtSide/2.,sPmtSide/2.,0.);
  pmtCornerTr2->RegisterYourself();

  // rounded corner goes to bottom left
  TGeoTranslation* pmtCornerTr3 = new TGeoTranslation("pmtCornerTr3", -sPmtSide/2.,-sPmtSide/2.,0.);
  pmtCornerTr3->RegisterYourself();

  // rounded corner goes to bottom right
  TGeoTranslation* pmtCornerTr4 = new TGeoTranslation("pmtCornerTr4", sPmtSide/2.,-sPmtSide/2.,0.);
  pmtCornerTr4->RegisterYourself();

  // TGeoRotation* reflectX = new TGeoRotation("reflectX");
  // reflectX->ReflectX(true);
  // reflectX->RegisterYourself();
  //
  // TGeoRotation* reflectY = new TGeoRotation("reflectY");
  // reflectY->ReflectY(true);
  // reflectY->RegisterYourself();
  //
  // TGeoRotation* reflectXY = new TGeoRotation("reflectXY");
  // reflectXY->ReflectX(true);
  // reflectXY->ReflectY(true);
  // reflectXY->RegisterYourself();
  //
  // TGeoCombiTrans* cornerRefTr2 = new TGeoCombiTrans("cornerRefTr2",  sCornerRadius/2.,-sCornerRadius/2., 0., reflectX);
  // cornerRefTr2->RegisterYourself();
  //
  // TGeoCombiTrans* cornerRefTr3 = new TGeoCombiTrans("cornerRefTr3", sCornerRadius/2.,sCornerRadius/2., 0., reflectXY);
  // cornerRefTr3->RegisterYourself();
  //
  // TGeoCombiTrans* cornerRefTr4 = new TGeoCombiTrans("cornerRefTr4", -sCornerRadius/2.,sCornerRadius/2., 0., reflectY);
  // cornerRefTr4->RegisterYourself();

  std::vector rectTranslations = {rectCornerTr1, rectCornerTr2, rectCornerTr3, rectCornerTr4};
  std::vector pmtTranslations = {pmtCornerTr1, pmtCornerTr2, pmtCornerTr3, pmtCornerTr4};

  // Define a value to overcut the coincidence between the closure of the tube
  // and the edge of the rectangle to eliminate artifacts
  Double_t flops = .00001; // cm

  TGeoBBox* testBox = new TGeoBBox("testBox", sPmtSide/2. + sEps, sPmtSide/2. + sEps, sPmtZ/2. + sEps);
  TGeoBBox* testRect = new TGeoBBox("testRect", sCornerRadius/2. - flops, sCornerRadius/2. - flops, sPmtZ/2.);
  TGeoTube* testTube = new TGeoTube("testTube", 0, sCornerRadius, sPmtZ/2. + sEps);
  TGeoTubeSeg* testTubeSeg = new TGeoTubeSeg("testTubeSeg", 0, sCornerRadius, sPmtZ/2. + sEps, -10, 100);

  for (int i = 0; i<4; i++) {

    TString cornerBool = Form("testRect - testTube:rectCornerTr%i", i + 1);
    TGeoCompositeShape* cornerCompositeShape = new TGeoCompositeShape("cornerCompositeShape", cornerBool.Data());
    TGeoVolume* cornerVol = new TGeoVolume("cornerVol", cornerCompositeShape, alMed);

    chamber->AddNode(cornerVol, i, pmtTranslations[i]);

}


  gGeoManager->CloseGeometry();
  gGeoManager->Export("standalone.root");

  // // make a canvas to draw on
  TCanvas *c = new TCanvas("c","c",0,0,1000,1000);
  gGeoManager->GetTopVolume()->Draw("ogle");

  TView *view = gPad->GetView();
  view->ShowAxis();

}
