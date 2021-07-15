#include "Constants.h"
#include "TGeoManager.h"


void aSideMacro() {


  // starting a manager
  TGeoManager *mgr = new TGeoManager("manager", "standalone");

  // material and medium
  TGeoMaterial *alMat = new TGeoMaterial("Al", 26.98,13,2.7);
  TGeoMedium   *alMed = new TGeoMedium("Al",1,alMat);

  TGeoMaterial *vacMat = new TGeoMaterial("Vacuum",0,0,0);
  TGeoMedium   *vacMed = new TGeoMedium("Vacuum",1,vacMat);

  // TGeoMaterial *airMat = new TGeoMaterial("Air",0,)

  Int_t isxfld = 2;     // magneticField->Integ();
  Float_t sxmgmx = 10.; // magneticField->Max();
  // FIXME: use o2::base::Detector::initFieldTrack to init mag field params

  //   Float_t a,z,d,radl,absl,buf[1];
  // Int_t nbuf;
  // AIR

  Float_t aAir[4] = {12.0107, 14.0067, 15.9994, 39.948};
  Float_t zAir[4] = {6., 7., 8., 18.};
  Float_t wAir[4] = {0.000124, 0.755267, 0.231781, 0.012827};
  Float_t dAir = 1.20479E-3;
  Float_t dAir1 = 1.20479E-11;
  // Radiator  glass SiO2
  Float_t aglass[2] = {28.0855, 15.9994};
  Float_t zglass[2] = {14., 8.};
  Float_t wglass[2] = {1., 2.};
  Float_t dglass = 2.65;
  // MCP glass SiO2
  Float_t dglass_mcp = 1.3;
  // Ceramic   97.2% Al2O3 , 2.8% SiO2
  Float_t aCeramic[2] = {26.981539, 15.9994};
  Float_t zCeramic[2] = {13., 8.};
  Float_t wCeramic[2] = {2., 3.};
  Float_t denscer = 3.6;
//   //*** Definition Of avaible FIT materials ***
//   Material(11, "Aliminium$", 26.98, 13.0, 2.7, 8.9, 999);
//   Mixture(1, "Vacuum$", aAir, zAir, dAir1, 4, wAir);
//   Mixture(2, "Air$", aAir, zAir, dAir, 4, wAir);
//   Mixture(4, "MCP glass   $", aglass, zglass, dglass_mcp, -2, wglass);
//   Mixture(24, "Radiator Optical glass$", aglass, zglass, dglass, -2, wglass);
//   Mixture(3, "Ceramic  $", aCeramic, zCeramic, denscer, -2, wCeramic);
//
//   Medium(1, "Air$", 2, 0, isxfld, sxmgmx, 10., .1, 1., .003, .003);
//   Medium(3, "Vacuum$", 1, 0, isxfld, sxmgmx, 10., .01, .1, .003, .003);
//   Medium(4, "Ceramic$", 3, 0, isxfld, sxmgmx, 10., .01, .1, .003, .003);
//   Medium(6, "Glass$", 4, 0, isxfld, sxmgmx, 10., .01, .1, .003, .003);
//   Medium(7, "OpAir$", 2, 0, isxfld, sxmgmx, 10., .1, 1., .003, .003);
//   Medium(18, "OpBlack$", 2, 0, isxfld, sxmgmx, 10., .1, 1., .003, .003);
//   Medium(15, "Aluminium$", 11, 0, isxfld, sxmgmx, 10., .01, 1., .003, .003);
//   Medium(17, "OptAluminium$", 11, 0, isxfld, sxmgmx, 10., .01, 1., .003, .003);
//   Medium(16, "OpticalGlass$", 24, 1, isxfld, sxmgmx, 10., .01, .1, .003, .01);
//   Medium(19, "OpticalGlassCathode$", 24, 1, isxfld, sxmgmx, 10., .01, .1, .003, .003);
//   Medium(22, "SensAir$", 2, 1, isxfld, sxmgmx, 10., .1, 1., .003, .003);



  Double_t x, y, z;

  Float_t pinstart[3] = {2.9491, 2.9491, 2.5};
  Float_t ptop[3] = {1.324, 1.324, 1.}; // Cherenkov radiator
  Float_t ptopblack[3] = {1.324, 1.324, 0.0002}; // black paper on the top on radiator
  Float_t ptopref[3] = {1.3241, 1.3241, 1.}; // Cherenkov radiator wrapped with reflector
  Double_t prfv[3] = {0.0002, 1.323, 1.};    // Vertical refracting layer bettwen radiators and between radiator and not optical Air
  Double_t prfh[3] = {1.323, 0.0002, 1.};    // Horizontal refracting layer bettwen radiators and ...
  Float_t pmcp[3] = {2.949, 2.949, 1.};      // MCP
  Float_t pmcpinner[3] = {2.749, 2.749, 0.1};
  Float_t pmcpside[3] = {0.1, 2.949, 1};
  Float_t pmcpbase[3] = {2.949, 2.949, 0.1};
  Float_t pmcptopglass[3] = {2.949, 2.949, 0.1}; // MCP top glass optical

  Float_t preg[3] = {1.324, 1.324, 0.005}; // Photcathode
  Double_t pal[3] = {2.648, 2.648, 0.25};  // 5mm Al on top of each radiator



  // // ConstructGeometry method
  Float_t zdetA = ZdetA + .5;
  //
  Int_t idrotm[999];
  // Double_t x, y, z;
  Float_t pstartC[3] = {20., 20, 5};
  Float_t pstartA[3] = {20, 20, 5};
  // Float_t pinstart[3] = {2.9491, 2.9491, 2.5};
  // Float_t pmcp[3] = {2.949, 2.949, 1.}; // MCP


  // A side construction

  // Float_t xa[NCellsA] = {-11.8, -5.9, 0, 5.9, 11.8, -11.8, -5.9, 0, 5.9, 11.8, -12.8, -6.9,
  //                   6.9, 12.8, -11.8, -5.9, 0, 5.9, 11.8, -11.8, -5.9, 0, 5.9, 11.8};
  //
  // Float_t ya[NCellsA] = {11.9, 11.9, 12.9, 11.9, 11.9, 6.0, 6.0, 7.0, 6.0, 6.0, -0., -0.,
  //                   0., 0., -6.0, -6.0, -7.0, -6.0, -6.0, -11.9, -11.9, -12.9, -11.9, -11.9};


  Float_t xa[NCellsA] = {-12.2, -6.1, 0, 6.1, 12.2, -12.2, -6.1, 0,
                                    6.1, 12.2, -13.3743, -7.274299999999999,
                                    7.274299999999999, 13.3743, -12.2, -6.1, 0,
                                    6.1, 12.2, -12.2, -6.1, 0, 6.1, 12.2};

  Float_t ya[NCellsA] = {12.2, 12.2, 13.53, 12.2, 12.2, 6.1, 6.1,
                                    7.43, 6.1, 6.1, 0, 0, 0, 0, -6.1, -6.1,
                                    -7.43, -6.1, -6.1, -12.2, -12.2, -13.53,
                                    -12.2, -12.2};

  TGeoVolumeAssembly* stlinA = new TGeoVolumeAssembly("0STL"); // A side mother

  // Here I set the top volume to the A side mother, I might regret this when we
  // need A and C side but for now it should work

  gGeoManager->SetTopVolume(stlinA);

  // // FIT Interior
  // TVirtualMC::GetMC()->Gsvolu("0INS", "BOX", getMediumID(kAir), pinstart, 3);
  // TGeoVolume* ins = gGeoManager->GetVolume("0INS");
  TGeoBBox* insBox = new TGeoBBox("insBox", pinstart[0], pinstart[1], pinstart[2]);
  TGeoVolume* ins = new TGeoVolume("0INS", insBox, vacMed);

  TGeoTranslation* tr[NCellsA + NCellsC];
  TString nameTr;

  // A side Translations
  for (Int_t itr = 0; itr < NCellsA; itr++) {
    nameTr = Form("0TR%i", itr + 1);
    z = -pstartA[2] + pinstart[2];
    tr[itr] = new TGeoTranslation(nameTr.Data(), xa[itr], ya[itr], z);
    tr[itr]->RegisterYourself();
    stlinA->AddNode(ins, itr, tr[itr]);
  }

// Note that for the purposes of the standalone code we will be simulating things
// of aluminum or vacuum to investigate overlaps


//   // Entry window (glass)
//   TVirtualMC::GetMC()->Gsvolu("0TOP", "BOX", getMediumID(kOpGlass), ptop, 3); // Glass radiator
//   TGeoVolume* top = gGeoManager->GetVolume("0TOP");

  TGeoBBox* topBox = new TGeoBBox("BOX", ptop[0], ptop[1], ptop[2]);
  TGeoVolume* top = new TGeoVolume("0TOP", topBox, alMed);

//   // TVirtualMC::GetMC()->Gsvolu("0TBL", "BOX", getMediumID(kOptBlack), ptopblack, 3); // Glass radiator
//   //  TGeoVolume* topblack = gGeoManager->GetVolume("0TBL");
  TGeoBBox* blackBox = new TGeoBBox("BOX", ptopblack[0], ptopblack[1], ptopblack[2]);
  TGeoVolume* topblack = new TGeoVolume("0TBL", blackBox, alMed);


//   TVirtualMC::GetMC()->Gsvolu("0TRE", "BOX", getMediumID(kAir), ptopref, 3); // Air: wrapped  radiator
//   TGeoVolume* topref = gGeoManager->GetVolume("0TRE");
  TGeoBBox* topRefBox = new TGeoBBox("BOX", ptopref[0], ptopref[1], ptopref[2]);
  TGeoVolume* topref = new TGeoVolume("0TRE", topRefBox, vacMed);

//   TVirtualMC::GetMC()->Gsvolu("0RFV", "BOX", getMediumID(kOptAl), prfv, 3); // Optical Air vertical
//   TGeoVolume* rfv = gGeoManager->GetVolume("0RFV");

  TGeoBBox* rfvBox = new TGeoBBox("BOX", prfv[0], prfv[1], prfv[2]);
  TGeoVolume* rfv = new TGeoVolume("0RFV", rfvBox, alMed);

//   TVirtualMC::GetMC()->Gsvolu("0RFH", "BOX", getMediumID(kOptAl), prfh, 3); // Optical Air horizontal
//   TGeoVolume* rfh = gGeoManager->GetVolume("0RFH");

  TGeoBBox* rfhBox = new TGeoBBox("BOX", prfh[0], prfh[1], prfh[2]);
  TGeoVolume* rfh = new TGeoVolume("0RFH", rfhBox, alMed);

//   TVirtualMC::GetMC()->Gsvolu("0PAL", "BOX", getMediumID(kAl), pal, 3); // 5mm Al on top of the radiator
//   TGeoVolume* altop = gGeoManager->GetVolume("0PAL");
  TGeoBBox* alTopBox = new TGeoBBox("BOX", pal[0], pal[1], pal[2]);
  TGeoVolume* altop = new TGeoVolume("0PAL", alTopBox, alMed);

//
//   TVirtualMC::GetMC()->Gsvolu("0REG", "BOX", getMediumID(kOpGlassCathode), preg, 3);
//   TGeoVolume* cat = gGeoManager->GetVolume("0REG");

  TGeoBBox* catBox = new TGeoBBox("BOX", preg[0], preg[1], preg[2]);
  TGeoVolume* cat = new TGeoVolume("0REG", catBox, alMed);

  //wrapped radiator +  reflecting layers

  Int_t ntops = 0, nrfvs = 0, nrfhs = 0;
  //  Float_t yin = 0, xinv = 0, yinv = 0;
  x = y = z = 0;
  topref->AddNode(top, 1, new TGeoTranslation(0, 0, 0));
  float xinv = -ptop[0] - prfv[0];
  topref->AddNode(rfv, 1, new TGeoTranslation(xinv, 0, 0));
  printf(" GEOGEO  refv %f ,  0,0 \n", xinv);
  xinv = ptop[0] + prfv[0];
  topref->AddNode(rfv, 2, new TGeoTranslation(xinv, 0, 0));
  printf(" GEOGEO  refv %f ,  0,0 \n", xinv);
  float yinv = -ptop[1] - prfh[1];
  topref->AddNode(rfh, 1, new TGeoTranslation(0, yinv, 0));
  printf(" GEOGEO  refh  ,  0, %f, 0 \n", yinv);
  yinv = ptop[1] + prfh[1];
  topref->AddNode(rfh, 2, new TGeoTranslation(0, yinv, 0));
  //  zin = -ptop[2] - ptopblack[2];
  //  printf(" GEOGEO  refh  ,  0, 0, %f \n", zin);
  //  topref->AddNode(topblack, 1, new TGeoTranslation(0, 0, zin));

  //container for radiator, cathode
  for (Int_t ix = 0; ix < 2; ix++) {
    float xin = -pinstart[0] + 0.3 + (ix + 0.5) * 2 * ptopref[0];
    for (Int_t iy = 0; iy < 2; iy++) {
      z = -pinstart[2] + 2 * pal[2] + ptopref[2];
      float yin = -pinstart[1] + 0.3 + (iy + 0.5) * 2 * ptopref[1];
      ntops++;
      ins->AddNode(topref, ntops, new TGeoTranslation(xin, yin, z));
      z += ptopref[2] + 2. * pmcptopglass[2] + preg[2];
      ins->AddNode(cat, ntops, new TGeoTranslation(xin, yin, z));
    }
  }
  //Al top
  z = -pinstart[2] + pal[2];
  ins->AddNode(altop, 1, new TGeoTranslation(0, 0, z));

  // MCP
//   TVirtualMC::GetMC()->Gsvolu("0MTO", "BOX", getMediumID(kOpGlass), pmcptopglass, 3); //Op  Glass
//   TGeoVolume* mcptop = gGeoManager->GetVolume("0MTO");

  TGeoBBox* mcptopBox = new TGeoBBox("BOX", pmcptopglass[0], pmcptopglass[1], pmcptopglass[2]);
  TGeoVolume* mcptop = new TGeoVolume("0MTO", mcptopBox, alMed);

  z = -pinstart[2] + 2 * pal[2] + 2 * ptopref[2] + pmcptopglass[2];
  ins->AddNode(mcptop, 1, new TGeoTranslation(0, 0, z));
//
  // TVirtualMC::GetMC()->Gsvolu("0MCP", "BOX", getMediumID(kAir), pmcp, 3); //glass
//   TGeoVolume* mcp = gGeoManager->GetVolume("0MCP");
  TGeoBBox* mcpBox = new TGeoBBox("BOX", pmcp[0], pmcp[1], pmcp[2]);
  TGeoVolume* mcp = new TGeoVolume("0MCP", mcpBox, alMed);

  z = -pinstart[2] + 2 * pal[2] + 2 * ptopref[2] + 2 * pmcptopglass[2] + 2 * preg[2] + pmcp[2];
  ins->AddNode(mcp, 1, new TGeoTranslation(0, 0, z));

//   TVirtualMC::GetMC()->Gsvolu("0MIN", "BOX", getMediumID(kGlass), pmcpinner, 3); //glass
//   TGeoVolume* mcpinner = gGeoManager->GetVolume("0MIN");
  TGeoBBox* mcpinnerBox = new TGeoBBox("BOX", pmcpinner[0], pmcpinner[1], pmcpinner[2]);
  TGeoVolume* mcpinner = new TGeoVolume("0MIN", mcpinnerBox, alMed);

  mcp->AddNode(mcpinner, 1, new TGeoTranslation(0, 0, 0));

//   TVirtualMC::GetMC()->Gsvolu("0MSI", "BOX", getMediumID(kGlass), pmcpside, 3); //glass
//   TGeoVolume* mcpside = gGeoManager->GetVolume("0MSI");
  TGeoBBox* mcpSideBox = new TGeoBBox("BOX", pmcpside[0], pmcpside[1], pmcpside[2]);
  TGeoVolume* mcpside = new TGeoVolume("0MSI", mcpSideBox, alMed);

  x = -pmcp[0] + pmcpside[0];
  y = -pmcp[1] + pmcpside[1];
  mcp->AddNode(mcpside, 1, new TGeoTranslation(x, y, 0));
  x = pmcp[0] - pmcpside[0];
  y = pmcp[1] - pmcpside[1];
  mcp->AddNode(mcpside, 2, new TGeoTranslation(x, y, 0));
  x = -pmcp[1] + pmcpside[1];
  y = -pmcp[0] + pmcpside[0];
  mcp->AddNode(mcpside, 3, new TGeoCombiTrans(x, y, 0, new TGeoRotation("R2", 90, 0, 0)));
  x = pmcp[1] - pmcpside[1];
  y = pmcp[0] - pmcpside[0];
  mcp->AddNode(mcpside, 4, new TGeoCombiTrans(x, y, 0, new TGeoRotation("R2", 90, 0, 0)));

//   TVirtualMC::GetMC()->Gsvolu("0MBA", "BOX", getMediumID(kCeramic), pmcpbase, 3); //glass
//   TGeoVolume* mcpbase = gGeoManager->GetVolume("0MBA");
  TGeoBBox* mcpBaseBox = new TGeoBBox("BOX", pmcpbase[0], pmcpbase[1], pmcpbase[2]);
  TGeoVolume* mcpbase = new TGeoVolume("0MBA", mcpBaseBox, alMed);

  z = -pinstart[2] + 2 * pal[2] + 2 * ptopref[2] + pmcptopglass[2] + 2 * pmcp[2] + pmcpbase[2];
  ins->AddNode(mcpbase, 1, new TGeoTranslation(0, 0, z));




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

  Float_t plate_zshift = -5;
  // define transformations for the plateGroups (6 basicPlates and 6 cablePlates)
  TGeoTranslation* plateGroupTr1 = new TGeoTranslation("plateGroupTr1", sPlateDisplacementX, sPlateDisplacementY - sYoffset, sPlateGroupZ + plate_zshift);
  plateGroupTr1->RegisterYourself();

  // TODO: 11/12 is this the place that the z-mismatch comes from?
  // TGeoCombiTrans* plateGroupTr2 = new TGeoCombiTrans("plateGroupTr2", 10.4358 + 1.5 * sPlateDisplacementDeltaY + sXoffset, -7.0747, sPlateGroupZ + sYoffset, new TGeoRotation("plateGroup2Rotation", -90, 0, 0));
  TGeoCombiTrans* plateGroupTr2 = new TGeoCombiTrans("plateGroupTr2", 10.4358 + 1.5 * sPlateDisplacementDeltaY, -7.0747 - sYoffset, sPlateGroupZ + plate_zshift, new TGeoRotation("plateGroup2Rotation", -90, 0, 0));
  plateGroupTr2->RegisterYourself();


  Float_t zShift = -5;

  // position of the two rectangles used to approximate the frame
  TGeoTranslation* frameTr1 = new TGeoTranslation("frameTr1", sFrame1PosX, sFrame1PosY, 0 + zShift);
  frameTr1->RegisterYourself();
  TGeoTranslation* frameTr2 = new TGeoTranslation("frameTr2", sFrame2PosX, sFrame2PosY, 0 + zShift);
  frameTr2->RegisterYourself();

  // remove the two smaller rectangles from the frame

  // TODO Jason 11/12: Do I need to add xOffset and yOffset here? I believe I may have forgetten it

  TGeoTranslation* rectTr1 = new TGeoTranslation("rectTr1", sFrame1PosX + sFrame1ExtraX1, sFrame1PosY + sFrame1ExtraY1, 0 + zShift);
  rectTr1->RegisterYourself();

  TGeoTranslation* rectTr2 = new TGeoTranslation("rectTr2", sFrame1PosX + sFrame1ExtraX2, sFrame1PosY + sFrame1ExtraY2, sMountZ / 2 + zShift);
  rectTr2->RegisterYourself();

  TGeoTranslation* rectTr3 = new TGeoTranslation("rectTr3", sFrame1PosX + sFrame1ExtraX3 - sRect3X / 2, sFrame1PosY + sFrame1ExtraY3 + sRect3Y / 2, 0 + zShift);
  rectTr3->RegisterYourself();

  TGeoTranslation* rectTr4 = new TGeoTranslation("rectTr4", sFrame1PosX + sFrame1ExtraX4, sFrame1PosY + sFrame1ExtraY4, 0 + zShift);
  rectTr4->RegisterYourself();

  TGeoTranslation* rectTr5 = new TGeoTranslation("rectTr5", sFrame2PosX + sFrame2ExtraX1 - sRect5X / 2, sFrame2PosY + sFrame2ExtraY1 - sRect5Y / 2, 0 + zShift);
  rectTr5->RegisterYourself();

  TGeoTranslation* rectTr6 = new TGeoTranslation("rectTr6", sFrame2PosX + sFrame2ExtraX2 - sRect6X / 2, sFrame2PosY + sFrame2ExtraY2 + sRect6Y / 2, 0 + zShift);
  rectTr6->RegisterYourself();

  TGeoTranslation* rectTr7 = new TGeoTranslation("rectTr7", sFrame2PosX + sFrame2ExtraX3 - sRect6X - sRect7X / 2, sFrame2PosY + sFrame2ExtraY3 + sRect7Y / 2, sMountZ / 2 + zShift);
  rectTr7->RegisterYourself();

  TGeoTranslation* rectTr8 = new TGeoTranslation("rectTr8", sFrame2PosX + sXoffset + sFrame2ExtraX4 - sRect8X / 2, sFrame2PosY + sYoffset + sFrame2ExtraY4 + sRect8Y / 2, 0 + zShift);
  rectTr8->RegisterYourself();

  // // old routine with hard-coded numbers
  // TGeoTranslation* rectTr1 = new TGeoTranslation("rectTr1", sFrame1PosX + 3.25, sFrame1PosY + 6.1875, 0);
  // rectTr1->RegisterYourself();
  //
  // TGeoTranslation* rectTr2 = new TGeoTranslation("rectTr2", sFrame1PosX + 9.3, sFrame1PosY - 0.5775, sMountZ / 2);
  // rectTr2->RegisterYourself();
  //
  // TGeoTranslation* rectTr3 = new TGeoTranslation("rectTr3", sFrame1PosX + 10.75 - sRect3X / 2, sFrame1PosY - 6.8525 + sRect3Y / 2, 0);
  // rectTr3->RegisterYourself();
  //
  // TGeoTranslation* rectTr4 = new TGeoTranslation("rectTr4", sFrame1PosX - 7.925, sFrame1PosY - 6.44, 0);
  // rectTr4->RegisterYourself();
  //
  // TGeoTranslation* rectTr5 = new TGeoTranslation("rectTr5", sFrame2PosX + 6.965 - sRect5X / 2, sFrame2PosY + 4.3625 - sRect5Y / 2, 0);
  // rectTr5->RegisterYourself();
  //
  // TGeoTranslation* rectTr6 = new TGeoTranslation("rectTr6", sFrame2PosX + 6.965 - sRect6X / 2, sFrame2PosY - 10.7375 + sRect6Y / 2, 0);
  // rectTr6->RegisterYourself();
  //
  // TGeoTranslation* rectTr7 = new TGeoTranslation("rectTr7", sFrame2PosX + 6.965 - sRect6X - sRect7X / 2, sFrame2PosY - 10.7375 + sRect7Y / 2, sMountZ / 2);
  // rectTr7->RegisterYourself();
  //
  // TGeoTranslation* rectTr8 = new TGeoTranslation("rectTr8", sFrame2PosX + sXoffset - 5.89 - sRect8X / 2, sFrame2PosY + sYoffset + 5.1125 + sRect8Y / 2, 0);
  // rectTr8->RegisterYourself();



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
  // frame1CompositeShapeBoolean += " ))";

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
  // frame2CompositeShapeBoolean += " )";

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
  // TGeoVolume *chamber = gGeoManager->MakeBox("TOP",vacMed,100,100,100);
  // gGeoManager->SetTopVolume(chamber);

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

  // Define a value to overcut the coincidence between the closure of the tube
  // and the edge of the rectangle to eliminate artifacts
  Double_t flopsErr = .00001; // cm
  Double_t extension = 5;

  TGeoBBox* pmtBox = new TGeoBBox("pmtBox", sPmtSide / 2 + sEps, sPmtSide / 2 + sEps, sPmtZ / 2 + sEps);
  // TGeoBBox* pmtCornerRect = new TGeoBBox("pmtCornerRect", sCornerRadius / 2 - flopsErr, sCornerRadius / 2 - flopsErr, sPmtZ / 2);
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


  std::vector rectTranslations = {rectCornerTr1, rectCornerTr2, rectCornerTr3, rectCornerTr4};
  std::vector pmtTranslations = {pmtCornerTr1, pmtCornerTr2, pmtCornerTr3, pmtCornerTr4};

  // // Define a value to overcut the coincidence between the closure of the tube
  // // and the edge of the rectangle to eliminate artifacts
  // Double_t flops = .00001; // cm

//   TGeoBBox* testBox = new TGeoBBox("testBox", sPmtSide/2. + sEps, sPmtSide/2. + sEps, sPmtZ/2. + sEps);
//   TGeoBBox* testRect = new TGeoBBox("testRect", sCornerRadius/2. - flops, sCornerRadius/2. - flops, sPmtZ/2.);
//   TGeoTube* testTube = new TGeoTube("testTube", 0, sCornerRadius, sPmtZ/2. + sEps);
//   TGeoTubeSeg* testTubeSeg = new TGeoTubeSeg("testTubeSeg", 0, sCornerRadius, sPmtZ/2. + sEps, -10, 100);
//
//   for (int i = 0; i<4; i++) {
//
//     TString cornerBool = Form("testRect - testTube:rectCornerTr%i", i + 1);
//     TGeoCompositeShape* cornerCompositeShape = new TGeoCompositeShape("cornerCompositeShape", cornerBool.Data());
//     TGeoVolume* cornerVol = new TGeoVolume("cornerVol", cornerCompositeShape, alMed);
//
//     chamber->AddNode(cornerVol, i, pmtTranslations[i]);
//
// }

// std::cout << "frame1 bool: " << frame1CompositeShapeBoolean.c_str() << std::endl;
// std::cout << "frame tot bool: " << frameCompositeShapeBoolean.c_str() << std::endl;

// Need to construct A-side sens elements
  // in Detector.cxx CreateMaterials() is called

  // am i good to do this - no
  // Float_t zdetA = Geometry::ZdetA + .5;


  // Definition of sensitive elements

  // from Geometry.h:
  TVector3 mMCP[52];
  static constexpr int NCellsA = 24;          // number of radiatiors on A side
  static constexpr int NCellsC = 28;          // number of radiatiors on C side
  static constexpr float ZdetA = 335;         // number of radiatiors on A side
  static constexpr float ZdetC = 82;          // number of radiatiors on C side
  static constexpr float ChannelWidth = 13.02;       // channel width in ps
  static constexpr float MV_2_Nchannels = 2.2857143; //amplitude channel 7 mV ->16channels




  TGeoVolume* frame = new TGeoVolume("frame", new TGeoCompositeShape("frame", frameCompositeShapeBoolean.c_str()), alMed);

  TGeoRotation* reflect = new TGeoRotation("reflect");
  reflect->ReflectX(true);
  reflect->ReflectY(true);
  reflect->RegisterYourself();


  TGeoVolume* tester1 = new TGeoVolume("tester1", frameRemovedPMTandRadiators1, alMed);
  TGeoVolume* tester2 = new TGeoVolume("tester2", frameRemovedPMTandRadiators2, alMed);
  // stlinA->AddNode(tester1, 1, frameTr1);
  // stlinA->AddNode(tester2, 2, frameTr2);
  //
  stlinA->AddNode(frame, 1);
  stlinA->AddNode(frame, 2, reflect);
  gGeoManager->CloseGeometry();
  gGeoManager->Export("standalone.root");

  // // make a canvas to draw on
  TCanvas *c = new TCanvas("c","c",0,0,1000,1000);
  gGeoManager->GetTopVolume()->Draw("ogle");

  TView *view = gPad->GetView();
  view->ShowAxis();

}
