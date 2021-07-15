#include "Constants.h"
#include "TGeoManager.h"

std::string pmtCompositeShapeBoolean();
std::string pmtCornerCompositeShapeBoolean();
// std::string cornerCompositeShape();

	// Fast inverse sqrt algorithm from the internet
Double_t Q_rsqrt(Double_t number )
	{
		Double_t y = number;
		Double_t x2 = y * 0.5;
		std::int64_t i = *(std::int64_t *) &y;

		i = 0x5fe6eb50c7b537a9 - (i >> 1);
		y = *(Double_t *) &i;
		y = y * (1.5 - (x2 * y * y));
		y = y * (1.5 - (x2 * y * y));
		return y;
}

Double_t pmtPos(Double_t x, Double_t y, Double_t z){

  const Double_t sFrameZ = 5.700;
  const Double_t sPmtZ = 3.750;
  const Double_t sQuartzRadiatorZ = 1.950;

  Double_t sPmtHeight = sFrameZ / 2 - sPmtZ / 2;
  Double_t sQuartzHeight = -sFrameZ / 2 + sQuartzRadiatorZ / 2;
  Double_t frameHeight = 2.5;

  Double_t rmag = sqrt(x*x + y*y + z*z);
  Double_t factor = (rmag +  (frameHeight / 2.0) - (sPmtHeight / 2)) / rmag;

  return factor;
}

Double_t qradPos(Double_t x, Double_t y, Double_t z){

  const Double_t sFrameZ = 5.700;
  const Double_t sPmtZ = 3.750;
  const Double_t sQuartzRadiatorZ = 1.950;

  Double_t  sPmtHeight = sFrameZ / 2 - sPmtZ / 2;
  Double_t  sQuartzHeight = -sFrameZ / 2 + sQuartzRadiatorZ / 2;

  Double_t frameHeight = 2.5;

  Double_t rmag = sqrt(x*x+y*y+z*z);

  Double_t factor = (rmag +  (frameHeight / 2.0) - sPmtHeight
                  - (sQuartzRadiatorZ / 2.0)) / rmag;

  return factor;
}

void cSideMacro() {
  // main function

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

  // from Geometry.h:
  TVector3 mMCP[52];
  static constexpr int NCellsA = 24;          // number of radiatiors on A side
  static constexpr int NCellsC = 28;          // number of radiatiors on C side
  static constexpr float ZdetA = 335;         // number of radiatiors on A side
  static constexpr float ZdetC = 82;          // number of radiatiors on C side
  static constexpr float ChannelWidth = 13.02;       // channel width in ps
  static constexpr float MV_2_Nchannels = 2.2857143; //amplitude channel 7 mV ->16channels
  // LOG(DEBUG) << "Creating FT0 geometry\n";
  // CreateMaterials();

  Float_t zdetA = ZdetA + .5; // add by one to see if fixed overlap -- does!
                              // (should have been with FV0 I believe)
  Float_t zdetC = ZdetC;

  Int_t idrotm[999];
  Double_t x, y, z;
  Float_t pstartC[3] = {20., 20, 5};
  Float_t pstartA[3] = {20, 20, 5};
  Float_t pinstart[3] = {2.9491, 2.9491, 2.5};
  Float_t pmcp[3] = {2.949, 2.949, 1.}; // MCP

  int nCellsA = NCellsA;
  int nCellsC = NCellsC;


  // C side Concave Geometry

  Double_t crad = ZdetC; // define concave c-side radius here

  Double_t dP = pmcp[0]; // side length of mcp divided by 2

  // uniform angle between detector faces==
  Double_t btta = 2 * TMath::ATan(dP / crad);

  // get noncompensated translation data
  Double_t grdin[6] = {-3, -2, -1, 1, 2, 3};
  Double_t gridpoints[6];
  for (Int_t i = 0; i < 6; i++) {
    gridpoints[i] = crad * TMath::Sin((1 - 1 / (2 * TMath::Abs(grdin[i]))) * grdin[i] * btta);
  }

  // Double_t xi[NCellsC] = {gridpoints[1], gridpoints[2], gridpoints[3],
  //                         gridpoints[4], gridpoints[0], gridpoints[1],
  //                         gridpoints[2], gridpoints[3], gridpoints[4],
  //                         gridpoints[5], gridpoints[0], gridpoints[1],
  //                         gridpoints[4], gridpoints[5], gridpoints[0],
  //                         gridpoints[1], gridpoints[4], gridpoints[5],
  //                         gridpoints[0], gridpoints[1], gridpoints[2],
  //                         gridpoints[3], gridpoints[4], gridpoints[5],
  //                         gridpoints[1], gridpoints[2], gridpoints[3],
  //                         gridpoints[4]};
  //
  // Double_t yi[NCellsC] = {gridpoints[5], gridpoints[5], gridpoints[5],
  //                         gridpoints[5], gridpoints[4], gridpoints[4],
  //                         gridpoints[4], gridpoints[4], gridpoints[4],
  //                         gridpoints[4], gridpoints[3], gridpoints[3],
  //                         gridpoints[3], gridpoints[3], gridpoints[2],
  //                         gridpoints[2], gridpoints[2], gridpoints[2],
  //                         gridpoints[1], gridpoints[1], gridpoints[1],
  //                         gridpoints[1], gridpoints[1], gridpoints[1],
  //                         gridpoints[0], gridpoints[0], gridpoints[0],
  //                         gridpoints[0]};



  Double_t xi[NCellsC] = {-15.038271418735729, 15.038271418735729,
    -15.003757581112167, 15.003757581112167, -9.02690018974363,
    9.02690018974363, -9.026897413747076, 9.026897413747076,
    -9.026896531935773, 9.026896531935773, -3.0004568618531313,
    3.0004568618531313, -3.0270795197907225, 3.0270795197907225,
    3.0003978432927543, -3.0003978432927543, 3.0270569670429572,
    -3.0270569670429572, 9.026750365564254, -9.026750365564254,
    9.026837450695885, -9.026837450695885, 9.026849243816981,
    -9.026849243816981, 15.038129472387304, -15.038129472387304,
    15.003621961057961, -15.003621961057961};

Double_t yi[NCellsC] = {3.1599494336464455, -3.1599494336464455,
  9.165191680982874, -9.165191680982874, 3.1383331772537426,
  -3.1383331772537426, 9.165226363918643, -9.165226363918643,
  15.141616002932361, -15.141616002932361, 9.16517861649866,
  -9.16517861649866, 15.188854859073416, -15.188854859073416,
  9.165053319552113, -9.165053319552113, 15.188703787345304,
  -15.188703787345304, 3.138263189805292, -3.138263189805292,
  9.165104089644917, -9.165104089644917, 15.141494417823818,
  -15.141494417823818, 3.1599158563428644, -3.1599158563428644,
  9.165116302773846, -9.165116302773846};

  Double_t zi[NCellsC];
  for (Int_t i = 0; i < NCellsC; i++) {
    zi[i] = TMath::Sqrt(TMath::Power(crad, 2) - TMath::Power(xi[i], 2) - TMath::Power(yi[i], 2));
  }


  // get rotation data
  Double_t ac[NCellsC], bc[NCellsC], gc[NCellsC];
  for (Int_t i = 0; i < NCellsC; i++) {
    ac[i] = TMath::ATan(yi[i] / xi[i]) - TMath::Pi() / 2 + 2 * TMath::Pi();
    if (xi[i] < 0) {
      bc[i] = TMath::ACos(zi[i] / crad);
    } else {
      bc[i] = -1 * TMath::ACos(zi[i] / crad);
    }
  }
  Double_t xc2[NCellsC], yc2[NCellsC], zc2[NCellsC];

  // compensation based on node position within individual detector geometries
  // determine compensated radius
  Double_t rcomp = crad + pstartC[2] / 2.0; //
  for (Int_t i = 0; i < NCellsC; i++) {
    // Get compensated translation data
    xc2[i] = rcomp * TMath::Cos(ac[i] + TMath::Pi() / 2) * TMath::Sin(-1 * bc[i]);
    yc2[i] = rcomp * TMath::Sin(ac[i] + TMath::Pi() / 2) * TMath::Sin(-1 * bc[i]);
    zc2[i] = rcomp * TMath::Cos(bc[i]);

    // Convert angles to degrees
    ac[i] *= 180 / TMath::Pi();
    bc[i] *= 180 / TMath::Pi();
    gc[i] = -1 * ac[i];
  }

  TGeoVolumeAssembly* stlinC = new TGeoVolumeAssembly("0STR"); // C side mother
  gGeoManager->SetTopVolume(stlinC);

  // FIT interior
  // TVirtualMC::GetMC()->Gsvolu("0INS", "BOX", getMediumID(kAir), pinstart, 3);
  // TVirtualMC::GetMC()->Gsvolu("0INS", "BOX", vacMed, pinstart, 3);
  // TGeoVolume* ins = gGeoManager->GetVolume("0INS");

  // it seems as if these .C macros I've written cannot use the -> operation
  // use above. note this could be an inheritance problem due to my ignorance,
  // but the workaround is below:
  TGeoBBox* insBox = new TGeoBBox("insBox", pinstart[0], pinstart[1], pinstart[2]);
  TGeoVolume* ins = new TGeoVolume("0INS", insBox, vacMed);


  TGeoTranslation* tr[NCellsA + NCellsC];
  TString nameTr;

  TGeoRotation* rot[NCellsC];
  TString nameRot;

  TGeoCombiTrans* com[NCellsC];
  TString nameCom;

  // C Side Transformations
  for (Int_t itr = NCellsA; itr < NCellsA + NCellsC; itr++) {
    nameTr = Form("0TR%i", itr + 1);
    nameRot = Form("0Rot%i", itr + 1);
    int ic = itr - NCellsA;
    // nameCom = Form("0Com%i",itr+1);

    rot[ic] = new TGeoRotation(nameRot.Data(), ac[ic], bc[ic], gc[ic]);
    rot[ic]->RegisterYourself();

    // why is this 80 hardcoded -- if we change it to 82/the value of zDetC, what happens?
    // we think this might give overlaps in the future
    tr[itr] = new TGeoTranslation(nameTr.Data(), xc2[ic], yc2[ic], (zc2[ic] - 80.));
    tr[itr]->RegisterYourself();
    // tr[itr]->Print();

    //   com[itr-NCellsA] = new TGeoCombiTrans(tr[itr],rot[itr-NCellsA]);
    com[ic] = new TGeoCombiTrans(xc2[ic], yc2[ic], (zc2[ic] - 80), rot[ic]);
    // com[ic]->RegisterYourself();
    // std::cout << ic << " " << xc2[ic] << " " << yc2[ic] << std::endl;
    TGeoHMatrix hm = *com[ic];
    TGeoHMatrix* ph = new TGeoHMatrix(hm);
    // stlinC->AddNode(ins, itr, ph);
  }

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


  // c-side frame placement variables
  // defn of the shell that approximates frame

  Float_t sweep = 3.5*2;
  Float_t rMin = 81;
  Float_t rMax = 86.6;
  Float_t tMin = 0;
  Float_t tMax = 35;
  Float_t pMin = 0;
  Float_t pMax = 180;


  TGeoSphere* sphere1 = new TGeoSphere("sphere1", rMin, rMax,
                                                tMin, tMax,
                                                pMin, pMax);

  TGeoSphere* sphere2 = new TGeoSphere("sphere2", rMin-sweep, rMax+sweep,
                                                tMin, tMax,
                                                pMin, pMax);


  // holepunch corners not implemented for quartzRadiator, rounded corners are
  // in place for PMT
  Double_t flopsErr = .00001;
  Double_t exag = 5;
  TGeoBBox* insSeat = new TGeoBBox("insSeat", pinstart[0]*2, pinstart[1]*2, pinstart[2]*2);
  TGeoBBox* quartzRadiator = new TGeoBBox("quartzRadiator", sQuartzRadiatorSide / 2, sQuartzRadiatorSide / 2, sQuartzRadiatorZ / 2 + flopsErr);
	TGeoBBox* pmtBox = new TGeoBBox("pmtBox", sPmtSide / 2 + sEps, sPmtSide / 2 + sEps, sPmtZ / 2 + sEps);
	// TGeoBBox* pmtBox = new TGeoBBox("pmtBox", sPmtSide / 2 + sEps, sPmtSide / 2 + sEps, sPmtZ / 2 + sEps + exag/exag);
  TGeoBBox* pmtCornerRect = new TGeoBBox("pmtCornerRect", sCornerRadius / 2 - flopsErr, sCornerRadius / 2 - flopsErr, sPmtZ / 2);
  TGeoTube* pmtCornerTube = new TGeoTube("pmtCornerTube", 0, sCornerRadius, sPmtZ / 2 + sEps);
  TGeoVolume* PMTCorner = new TGeoVolume("PMTCorner", new TGeoCompositeShape("PMTCorner", pmtCornerCompositeShapeBoolean().c_str()), alMed);
  // TGeoVolume* PMT = gGeoManager->MakeBox("PMT", vacMed, sPmtSide / 2 + sEps, sPmtSide / 2 + sEps, sPmtZ / 2 + sEps);
  // TGeoBBox* PMT = new TGeoBBox("PMT", sPmtSide / 2 + sEps, sPmtSide / 2 + sEps, sPmtZ / 2 + sEps);
	// TGeoCompositeShape* PMT = new TGeoCompositeShape("PMT", cornerCompositeShape().c_str());
	TGeoCompositeShape* PMT = new TGeoCompositeShape("PMT", pmtCompositeShapeBoolean().c_str());
  TGeoRotation* rot1 = new TGeoRotation("rot1", 90, 0, 0);
  rot1->RegisterYourself();

  TGeoRotation* rot2 = new TGeoRotation("rot2", -90, 0, 0);
  rot2->RegisterYourself();

  TGeoRotation* rot3 = new TGeoRotation("rot3", 0, 0, 0);
  rot3->RegisterYourself();

  TGeoCombiTrans* rotTr1 = new TGeoCombiTrans("rotTr1", -20, -1, -5, rot1);
  rotTr1->RegisterYourself();

  TGeoCombiTrans* rotTr2 = new TGeoCombiTrans("rotTr2", 20, -1, -5, rot2);
  rotTr2->RegisterYourself();

  TGeoCombiTrans* rotTr3 = new TGeoCombiTrans("rotTr3", 0, 20, -5, rot3);
  rotTr3->RegisterYourself();

  TGeoRotation* reflectC1 = new TGeoRotation("reflectC1", 0, 0, 0);
  reflectC1->ReflectX(true);
  reflectC1->ReflectY(true);
  reflectC1->RegisterYourself();

  TGeoTranslation* tr1 = new TGeoTranslation("tr1", 0, 0, 85);
  tr1->RegisterYourself();

  TGeoBBox* framecornerBox = new TGeoBBox("framecornerBox", 5, 5, 5);
  Double_t multCorn = 1.275;

  Double_t xCorn = multCorn*(-14.75272569);
  Double_t yCorn = multCorn*(14.9043284);
  Double_t zCorn = 79.27306024;

  Double_t xCorn2 = -xCorn;
  Double_t yCorn2 = yCorn;
  Double_t zCorn2 = zCorn;

  Double_t acCorn;
  Double_t bcCorn;
  Double_t gcCorn;


  acCorn = TMath::ATan(yCorn / xCorn) - TMath::Pi() / 2 + 2 * TMath::Pi();

  bcCorn = /*(-1)**/ TMath::ACos(zCorn / crad);

  gcCorn = -1 * acCorn;

  TGeoRotation* rotCorners= new TGeoRotation("rotCorners", acCorn, bcCorn, gcCorn);
  rotCorners->RegisterYourself();

  TGeoCombiTrans* comCorners= new TGeoCombiTrans("comCorners", xCorn, yCorn, zCorn, rotCorners);
  comCorners->RegisterYourself();

  TGeoCombiTrans* comCorners2= new TGeoCombiTrans("comCorners2", xCorn2, yCorn2, zCorn2, rotCorners);
  comCorners2->RegisterYourself();


  std::string shellBoolean = "";
  shellBoolean += "sphere1";
  shellBoolean += "- sphere2:rotTr1";
  shellBoolean += "- sphere2:rotTr2";
  shellBoolean += "- sphere2:rotTr3";
  shellBoolean += "- insSeat:tr1";
  shellBoolean += "- framecornerBox:comCorners";
  shellBoolean += "- framecornerBox:comCorners2";


  //
  // Double_t aPMT[NCellsC], bPMT[NCellsC], gPMT[NCellsC];
  // for (Int_t i = 0; i < NCellsC; i++) {
  //   aPMT[i] = TMath::ATan(yi[i] / xi[i]) - TMath::Pi() / 2 + 2 * TMath::Pi();
  //   if (xi[i] < 0) {
  //     bPMT[i] = TMath::ACos(zi[i] / crad);
  //   } else {
  //     bPMT[i] = -1 * TMath::ACos(zi[i] / crad);
  //   }
  // }
  // Double_t xc2[NCellsC], yc2[NCellsC], zc2[NCellsC];
  //
  // // compensation based on node position within individual detector geometries
  // // determine compensated radius
  // Double_t rcomp = crad + pstartC[2] / 2.0; //
  // for (Int_t i = 0; i < NCellsC; i++) {
  //   // Get compensated translation data
  //   xc2[i] = rcomp * TMath::Cos(aPMT[i] + TMath::Pi() / 2) * TMath::Sin(-1 * bPMT[i]);
  //   yc2[i] = rcomp * TMath::Sin(aPMT[i] + TMath::Pi() / 2) * TMath::Sin(-1 * bPMT[i]);
  //   zc2[i] = rcomp * TMath::Cos(bPMT[i]);
  //
  //   // Convert angles to degrees
  //   aPMT[i] *= 180 / TMath::Pi();
  //   bPMT[i] *= 180 / TMath::Pi();
  //   gPMT[i] = -1 * aPMT[i];
  // }

	// only need one instance
  Double_t scalePMT = pmtPos(xc2[0], yc2[0], zc2[0]);
  Double_t scaleQrad = qradPos(xc2[0], yc2[0], zc2[0]);
	scaleQrad *= scaleQrad*scaleQrad; // just for me
	// scaleQrad -= .025; // just for me
	std::cout << "\nscaleQrad: " << scaleQrad << std::endl;

	Double_t xPMT[NCellsC];
	Double_t yPMT[NCellsC];
	Double_t zPMT[NCellsC];

	Double_t aPMT[NCellsC];
	Double_t bPMT[NCellsC];
	Double_t gPMT[NCellsC];

	Double_t xQrad[NCellsC];
	Double_t yQrad[NCellsC];
	Double_t zQrad[NCellsC];

	Double_t aQrad[NCellsC];
	Double_t bQrad[NCellsC];
	Double_t gQrad[NCellsC];


  for (Int_t i = 0; i < NCellsC; i++) {
    Double_t rsquared = xc2[i]*xc2[i] + yc2[i]*yc2[i] + zc2[i]*zc2[i];
    Double_t invR = Q_rsqrt(rsquared);


		// std::cout << xc2[i] << " " << yc2[i] << " " << zc2[i] << std::endl;

		// PMT Transformations
		xPMT[i] = scalePMT * xc2[i];
		yPMT[i] = scalePMT * yc2[i];
		zPMT[i] = scalePMT * zc2[i];
		// std::cout << xPMT[i] << " " << yPMT[i] << " " << zPMT[i] << std::endl;

	  aPMT[i] = TMath::ATan(yPMT[i] / xPMT[i]) - TMath::Pi() / 2 + 2 * TMath::Pi();
	  if (xPMT[i] < 0) {
			bPMT[i] = TMath::ACos(zPMT[i] / crad);
		} else {
			bPMT[i] = -1 * TMath::ACos(zPMT[i] / crad);
		}
		//
		// xPMT[i] = rcomp * TMath::Cos(aPMT[i] + TMath::Pi() / 2) * TMath::Sin(-1 * bPMT[i]);
    // yPMT[i] = rcomp * TMath::Sin(aPMT[i] + TMath::Pi() / 2) * TMath::Sin(-1 * bPMT[i]);
    // zPMT[i] = rcomp * TMath::Cos(bPMT[i]);

	  aPMT[i] *= 180 / TMath::Pi();
    bPMT[i] *= 180 / TMath::Pi();
    gPMT[i] = -1 * aPMT[i];
		//
		// Quart radiator transformations
		xQrad[i] = scaleQrad * xc2[i];
		yQrad[i] = scaleQrad * yc2[i];
		zQrad[i] = scaleQrad * zc2[i];

		aQrad[i] = TMath::ATan(yQrad[i] / xQrad[i]) - TMath::Pi() / 2 + 2 * TMath::Pi();
		if (xQrad[i] < 0) {
			bQrad[i] = TMath::ACos(zQrad[i] / crad);
		} else {
			bQrad[i] = -1 * TMath::ACos(zQrad[i] / crad);
		}
		//
		// xQrad[i] = rcomp * TMath::Cos(aQrad[i] + TMath::Pi() / 2) * TMath::Sin(-1 * bQrad[i]);
		// yQrad[i] = rcomp * TMath::Sin(aQrad[i] + TMath::Pi() / 2) * TMath::Sin(-1 * bQrad[i]);
		// zQrad[i] = rcomp * TMath::Cos(bQrad[i]);

		aQrad[i] *= 180 / TMath::Pi();
		bQrad[i] *= 180 / TMath::Pi();
		gQrad[i] = -1 * aQrad[i];


		// std::cout << xPMT[i] << " " << yPMT[i] << " " << zPMT[i] << std::endl;
		// std::cout << xQrad[i] << " " << yQrad[i] << " " << zQrad[i] << std::endl;
		// std::cout << aPMT[i] << " " << bPMT[i] << std::endl;
		// std::cout << aQrad[i] << " " << bQrad[i] << std::endl;

  }


  TString nameComPMT;
  TString nameComQuartz;
  for (Int_t itr = NCellsA; itr < NCellsA + NCellsC; itr++) {
    // nameTr = Form("0TR%i", itr + 1);
    nameRot = Form("0Rot%i", itr + 1);
    int ic = itr - NCellsA;
    nameComPMT = Form("0ComPMT%i", ic + 1);
    nameComQuartz = Form("0ComQuartz%i", ic + 1);

    // getting even indices to skip reflections -> reflections happen later in
    // frame construction
    if (ic%2==0){
      // std::cout << ic << std::endl;
      // TGeoRotation* rotPMT = new TGeoRotation(nameRot.Data(),
      //                                         aPMT[ic], bPMT[ic], gPMT[ic]);
      // rotPMT->RegisterYourself();
			//
      // TGeoCombiTrans* comPMT = new TGeoCombiTrans(nameComPMT.Data(),
      //                                             xPMT[ic], yPMT[ic],
      //                                             zPMT[ic],
      //                                             rotPMT);
      // comPMT->RegisterYourself();

			TGeoRotation* rotPMT = new TGeoRotation(nameRot.Data(),
                                              ac[ic], bc[ic], gc[ic]);
      rotPMT->RegisterYourself();

      TGeoCombiTrans* comPMT = new TGeoCombiTrans(nameComPMT.Data(),
                                                  xPMT[ic], yPMT[ic],
                                                  zPMT[ic],
                                                  rotPMT);
      comPMT->RegisterYourself();

      // TGeoRotation* rotQuartz = new TGeoRotation(nameRot.Data(),
      //                                            aQrad[ic], bQrad[ic], gQrad[ic]);
      // rotQuartz->RegisterYourself();
			//
      // TGeoCombiTrans* comQuartz = new TGeoCombiTrans(nameComQuartz.Data(),
      //                                                xQrad[ic], yQrad[ic],
      //                                                zQrad[ic],
      //                                                rotQuartz);
      // comQuartz->RegisterYourself();

			TGeoRotation* rotQuartz = new TGeoRotation(nameRot.Data(),
                                                 ac[ic], bc[ic], gc[ic]);
      rotQuartz->RegisterYourself();

      TGeoCombiTrans* comQuartz = new TGeoCombiTrans(nameComQuartz.Data(),
                                                     xQrad[ic], yQrad[ic],
                                                     zQrad[ic],
                                                     rotQuartz);
      comQuartz->RegisterYourself();

      std::string pmtCombiBool = "";
      pmtCombiBool += "- ";
      pmtCombiBool += "PMT:";
      pmtCombiBool += nameComPMT.Data();
      // std::cout << pmtCombiBool << std::endl;
      shellBoolean += pmtCombiBool;

      std::string quartzCombiBool = "";
      quartzCombiBool += "- ";
      quartzCombiBool += "quartzRadiator:";
      quartzCombiBool += nameComQuartz.Data();
      // std::cout << quartzCombiBool << std::endl;
      shellBoolean += quartzCombiBool;
    }
  }

  TGeoCompositeShape* shellCompShape = new TGeoCompositeShape("shellCompShape",
                                                          shellBoolean.c_str());

  TGeoVolume* shellVol = new TGeoVolume("shellVol", shellCompShape, alMed);

  // TGeoCombiTrans* shellTr1 = new TGeoCombiTrans("shellTr1", 0, 0, -80, rot1);
  TGeoTranslation* shellTr1 = new TGeoTranslation("shellTr1", 0, 0, -80);
  shellTr1->RegisterYourself();

  TGeoCombiTrans* shellTr2 = new TGeoCombiTrans("shellTr2", 0, 0, -80, reflectC1);
  shellTr2->RegisterYourself();
  //eulerAngles(xi, yi, zi);


  stlinC->AddNode(shellVol, 29, shellTr1);
  stlinC->AddNode(shellVol, 30, shellTr2);

  // Test Drawing the PMT
  // TGeoCompositeShape* tester = new TGeoCompositeShape("tester", pmtCompositeShapeBoolean().c_str());
  // TGeoVolume* testVol = new TGeoVolume("testVol", tester, alMed);
  // stlinC->AddNode(PMT, 31);

  gGeoManager->CloseGeometry();
  gGeoManager->Export("FT0C.root");

  // // make a canvas to draw on
  TCanvas *c = new TCanvas("c","c",0,0,1000,1000);
  gGeoManager->GetTopVolume()->Draw("ogle");

  TView *view = gPad->GetView();
  view->ShowAxis();
}

//Create PMT socket shape
std::string pmtCompositeShapeBoolean()
{
  // create a string for the boolean operations for the composite PMT shape
  std::string pmtCompositeShapeBoolean = "";
  pmtCompositeShapeBoolean += "pmtBox";
  pmtCompositeShapeBoolean += " - PMTCorner:PMTCornerTr1";
  pmtCompositeShapeBoolean += " - PMTCorner:PMTCornerTr2";
  pmtCompositeShapeBoolean += " - PMTCorner:PMTCornerTr3";
  pmtCompositeShapeBoolean += " - PMTCorner:PMTCornerTr4";

  return pmtCompositeShapeBoolean;
}

// // TODO 7/13/21 -> implement better corners to get rid of graphical artifacts
// // implementation comes from cornerRoutine.C by Jason Pruitt
// std::string cornerCompositeShape()
// {
//
// 	// tube goes to bottom left
// 	TGeoTranslation* rectCornerTr1 = new TGeoTranslation("rectCornerTr1", -sCornerRadius/2.,-sCornerRadius/2., 0.);
// 	rectCornerTr1->RegisterYourself();
//
// 	// tube goes to bottom right
// 	TGeoTranslation* rectCornerTr2 = new TGeoTranslation("rectCornerTr2", sCornerRadius/2.,-sCornerRadius/2., 0.);
// 	rectCornerTr2->RegisterYourself();
//
// 	// tube goes to top right
// 	TGeoTranslation* rectCornerTr3 = new TGeoTranslation("rectCornerTr3", sCornerRadius/2.,sCornerRadius/2., 0.);
// 	rectCornerTr3->RegisterYourself();
//
// 	// tube goes to top left
// 	TGeoTranslation* rectCornerTr4 = new TGeoTranslation("rectCornerTr4", -sCornerRadius/2.,sCornerRadius/2., 0.);
// 	rectCornerTr4->RegisterYourself();
//
// 	// Rounded corner goes to top right
// 	TGeoTranslation* pmtCornerTr1 = new TGeoTranslation("pmtCornerTr1", sPmtSide/2.,sPmtSide/2.,0.);
// 	pmtCornerTr1->RegisterYourself();
//
// 	// rounded corner goes to top left
// 	TGeoTranslation* pmtCornerTr2 = new TGeoTranslation("pmtCornerTr2", -sPmtSide/2.,sPmtSide/2.,0.);
// 	pmtCornerTr2->RegisterYourself();
//
// 	// rounded corner goes to bottom left
// 	TGeoTranslation* pmtCornerTr3 = new TGeoTranslation("pmtCornerTr3", -sPmtSide/2.,-sPmtSide/2.,0.);
// 	pmtCornerTr3->RegisterYourself();
//
// 	// rounded corner goes to bottom right
// 	TGeoTranslation* pmtCornerTr4 = new TGeoTranslation("pmtCornerTr4", sPmtSide/2.,-sPmtSide/2.,0.);
// 	pmtCornerTr4->RegisterYourself();
//
// 	TGeoBBox* testBox = new TGeoBBox("testBox", sPmtSide/2. + sEps, sPmtSide/2. + sEps, sPmtZ/2. + sEps);
// 	TGeoBBox* testRect = new TGeoBBox("testRect", sCornerRadius/2. - flops, sCornerRadius/2. - flops, sPmtZ/2.);
// 	TGeoTube* testTube = new TGeoTube("testTube", 0, sCornerRadius, sPmtZ/2. + sEps);
// 	TGeoTubeSeg* testTubeSeg = new TGeoTubeSeg("testTubeSeg", 0, sCornerRadius, sPmtZ/2. + sEps, -10, 100);
//
// 	for (int i = 0; i<4; i++) {
//
// 	TString cornerCompositeBool = Form("testRect - testTube:rectCornerTr%i", i + 1);
	// TGeoCompositeShape* cornerCompositeShape = new TGeoCompositeShape("cornerCompositeShape", cornerCompositeBool.Data());
	// TGeoVolume* cornerVol = new TGeoVolume("cornerVol", cornerCompositeShape, alMed);
// 	}
// 	return cornerCompositeBool;
//
// }

//Create rounded PMT socket corners
std::string pmtCornerCompositeShapeBoolean()
{
  // create a string for the boolean operations for the composite pmtCorner shape
  std::string pmtCornerCompositeShapeBoolean = "";
  pmtCornerCompositeShapeBoolean += "pmtCornerRect:pmtCornerRectTr";
  pmtCornerCompositeShapeBoolean += " - pmtCornerTube:pmtCornerTubeTr";

  return pmtCornerCompositeShapeBoolean;
}
