// TGeoSphere takes 6 parameters :
// inner and outer radius Rmin, Rmax
// the theta limits Tmin, Tmax
// the phi limits Pmin, Pmax
// (the sector in phi is considered
// starting from Pmin to Pmax counter-clockwise)


// #include "Constants.h" ------- why won't this include work???? causes segfault

void frameC()
{
  TCanvas *c = new TCanvas("c", "c",0,0,600,600);
  new TGeoManager("frameC", "poza7");
  TGeoMaterial *mat = new TGeoMaterial("Al", 26.98,13,2.7);
  TGeoMedium *med = new TGeoMedium("MED",1,mat);
  TGeoVolume *top = gGeoManager->MakeBox("TOP",med,100,100,100);
  gGeoManager->SetTopVolume(top);

  Float_t pmcp[3] = {2.949, 2.949, 1.}; // MCP

  Float_t sFrameZC = 5.5632;
  Float_t rMin = 81.9791;
  Float_t rMax = rMin + sFrameZC;


  // define some error to avoid overlaps
  Double_t sEps = 0.025;

  // both frame boxes are the same height
  Double_t sFrameZ = 5.700;
  Double_t sMountZ = 1.5;

  // PMT dimensions
  Double_t sPmtSide = 5.950;
  Double_t sPmtZ = 3.750;

  // quartz radiator dimensions
  Double_t sQuartzRadiatorSide = 5.350;
  Double_t sQuartzRadiatorZ = 1.950;

  // for the rounded corners
  Double_t sCornerRadius = .300;
  // quartz & PMT transformations
  Double_t sQuartzHeight = -sFrameZ / 2 + sQuartzRadiatorZ / 2;
  Double_t sPmtHeight = sFrameZ / 2 - sPmtZ / 2;
  Double_t sPmtCornerTubePos = -.15;
  Double_t sPmtCornerPos = 2.825;
  Double_t sEdgeCornerPos[2] = {-6.515, -.515};

  // quartz & PMT C-side transformations
  Double_t sensShift = .5;
	Double_t sQuartzRadiatorZC = 1.94360;   // Dimension variable (l_{q}
  Double_t sQuartzHeightC = (-sFrameZC / 2 + sQuartzRadiatorZC / 2); // placement variable )
  Double_t sPmtZC = 3.600; // Dimension variable (l_{p}
  Double_t sPmtHeightC = (sFrameZC / 2 - sPmtZC / 2); // placement variable
  Double_t flopsErr = .00001;


  TGeoBBox* quartzRadiator = new TGeoBBox("quartzRadiator", sQuartzRadiatorSide / 2, sQuartzRadiatorSide / 2, sQuartzRadiatorZC / 2 + flopsErr);
  TGeoBBox* pmtBox = new TGeoBBox("pmtBox", sPmtSide / 2, sPmtSide / 2, sPmtZ / 2);

  TGeoSphere* frameShape = new TGeoSphere("frameShape",rMin,rMax,0,35,0,180);
  // TGeoVolume* vol = gGeoManager->MakeSphere("SPHERE",med,rMin,rMax,0,35,0,180);
  TGeoVolume* frameVol = new TGeoVolume("frameVol", frameShape, med);

  TGeoVolume* pmtVol = new TGeoVolume("pmtVol", pmtBox, med);
  TGeoVolume* qrVol = new TGeoVolume("qrVol", quartzRadiator, med);

  // TGeoTranslation* pmtTr = new TGeoTranslation("pmtTr", 0, 0, sPmtHeightC + sEps);
  // pmtTr->RegisterYourself();
  //
  // TGeoTranslation* qrTr = new TGeoTranslation("qrTr", 0, 0, sQuartzHeightC - sEps);
  // qrTr->RegisterYourself();

  TGeoTranslation* pmtTr = new TGeoTranslation("pmtTr", 0, 0, sPmtZC/2 + sQuartzRadiatorZC/2 + 3*sEps);
  pmtTr->RegisterYourself();

  // TGeoTranslation* qrTr = new TGeoTranslation("qrTr", 0, 0, 0);
  // qrTr->RegisterYourself();


  TGeoVolumeAssembly* ins = new TGeoVolumeAssembly("ins"); // sens elem mother

  std::string insBool = "";
  insBool += "quartzRadiator";
  insBool += "+ pmtBox:pmtTr";

  TGeoCompositeShape* insComp = new TGeoCompositeShape("insComp", insBool.c_str());
  TGeoVolume* insVol = new TGeoVolume("insVol", insComp, med);

  std::string seatsRemovedBool = "";
  seatsRemovedBool += "frameShape - (";
  seatsRemovedBool += insBool;
  // adds combiTrans at each iterate
  seatsRemovedBool += ")";

  TGeoCompositeShape* seatsRemovedShape = new TGeoCompositeShape("seatsRemovedShape", seatsRemovedBool.c_str());
  TGeoVolume* seatsR = new TGeoVolume("seatsR", seatsRemovedShape, med);

  TGeoBBox* vacShape = new TGeoBBox("vacShape", )

  ins->AddNode(pmtVol, 2, pmtTr);
  ins->AddNode(qrVol, 3);

  top->AddNode(ins, 1);
  // top->AddNode(frameVol, 2);
  // top->AddNode(seatsR, 3);

  gGeoManager->CloseGeometry();
  gGeoManager->Export("insC.root");
  gGeoManager->SetNsegments(30);
  top->Draw("ogl");
  TView *view = gPad->GetView();
  view->ShowAxis();
};
