#include "Constants.h"
#include "TGeoManager.h"

std::string pmtCompositeShapeBoolean();
std::string pmtCornerCompositeShapeBoolean();
std::string plateBoolean();
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
  Double_t rmag = sqrt(x*x + y*y + z*z);
	Double_t factor = (rmag +  (frameHeightC / 2.0) - (sPmtHeightC / 2)) / rmag;
	// Double_t factor = (rmag +  sQuartzRadiatorZC + (sPmtZC / 2)) / rmag;
  return factor;
}

Double_t qradPos(Double_t x, Double_t y, Double_t z){
  Double_t rmag = sqrt(x*x + y*y + z*z);
	Double_t factor = (rmag +  (frameHeightC / 2.0) - sPmtHeightC
                  - (sQuartzRadiatorZC / 2.0)) / rmag;

	// Double_t factor = (rmag + (sQuartzRadiatorZC/ 2.0)) / rmag;
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
	TGeoVolumeAssembly* ins = new TGeoVolumeAssembly("ins"); // sens elem mother

  TGeoTranslation* tr[NCellsA + NCellsC];
  TString nameTr;

  TGeoRotation* rot[NCellsC];
  TString nameRot;

  TGeoCombiTrans* com[NCellsC];
  TString nameCom;

	TGeoCombiTrans* plateCom[NCellsC];

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
	Float_t rMin = 81.9791;
	Float_t rMax = rMin + sFrameZC;
  Float_t tMin = 0;
  Float_t tMax = 35;
  Float_t pMin = 0;
  Float_t pMax = 180;

	Float_t backPlateZ = .5;

  TGeoSphere* sphere1 = new TGeoSphere("sphere1", rMin, rMax,
                                                  tMin, tMax,
                                                  pMin, pMax);

  TGeoSphere* sphere2 = new TGeoSphere("sphere2", rMin - sweep, rMax + sweep,
                                                  tMin, tMax,
                                                  pMin, pMax);

	TGeoSphere* sphere3 = new TGeoSphere("sphere3", rMin, rMin + backPlateZ,
                                                  tMin, tMax,
                                                  pMin, pMax);

  TGeoSphere* sphere4 = new TGeoSphere("sphere4", rMin - sweep,
																								  rMax + backPlateZ + sweep,
                                                  tMin, tMax,
                                                  pMin, pMax);

  // holepunch corners not implemented for quartzRadiatorSeat, rounded corners are
  // in place for PMT
  Double_t flopsErr = .00001;
  Double_t exag = 5;

	// highest overlap values
	Double_t errPMT = 10*sEps;
	Double_t errQrdZ = .143;

  TGeoBBox* insSeat = new TGeoBBox("insSeat", pinstart[0]*2, pinstart[1]*2, pinstart[2]*2);
  TGeoBBox* quartzRadiatorSeat = new TGeoBBox("quartzRadiatorSeat",
																					sQuartzRadiatorSide / 2 + sEps + errQrdZ,
																					sQuartzRadiatorSide / 2 + sEps + errQrdZ,
																					sQuartzRadiatorZC / 2 + sEps + errQrdZ);
																					// sQuartzRadiatorZC / 2 + 1.0);
																					// edited to peek out the back of the
																					// frame
	TGeoBBox* pmtBoxSeat = new TGeoBBox("pmtBoxSeat",
																	sPmtSide / 2 + sEps,
																	sPmtSide / 2 + sEps,
																	sPmtZ / 2 + sEps + errPMT);
  TGeoBBox* pmtCornerRect = new TGeoBBox("pmtCornerRect",
																					sCornerRadius / 2 - flopsErr,
																					sCornerRadius / 2 - flopsErr,
																					sPmtZ / 2);


	TGeoBBox* quartzRadiator = new TGeoBBox("quartzRadiator", sQuartzRadiatorSide / 2 - sEps, sQuartzRadiatorSide / 2 - sEps, sQuartzRadiatorZC / 2 + flopsErr - sEps);
	TGeoBBox* pmtBox = new TGeoBBox("pmtBox", sPmtSide / 2 - sEps, sPmtSide / 2 - sEps, sPmtZ / 2 - sEps);

  TGeoTube* pmtCornerTube = new TGeoTube("pmtCornerTube", 0, sCornerRadius, sPmtZ / 2 + sEps);
  TGeoVolume* PMTCorner = new TGeoVolume("PMTCorner", new TGeoCompositeShape("PMTCorner", pmtCornerCompositeShapeBoolean().c_str()), alMed);

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

  TGeoBBox* framecornerBox = new TGeoBBox("framecornerBox", 5, 5, 10);
  Double_t multCorn = 1.275;

	// begin sensitive elements
	TGeoVolume* pmtVol = new TGeoVolume("pmtVol", pmtBox, alMed);
	TGeoVolume* qrVol = new TGeoVolume("qrVol", quartzRadiator, alMed);

	TGeoTranslation* pmtTr = new TGeoTranslation("pmtTr", 0, 0, sPmtHeightC + sEps);
	// TGeoTranslation* pmtTr = new TGeoTranslation("pmtTr", 0, 0, sPmtHeightC - sQuartzHeightC/2 - sEps);
	pmtTr->RegisterYourself();

	TGeoTranslation* qrTr = new TGeoTranslation("qrTr", 0, 0, sQuartzHeightC - sEps);
	qrTr->RegisterYourself();



	std::string shellBoolean = "";
  shellBoolean += "sphere1"; // start with spherical shell - this will be reflected
  shellBoolean += "- sphere2:rotTr1"; // copy and combitrans a subtraction
  shellBoolean += "- sphere2:rotTr2"; // copy and combitrans a subtraction
  shellBoolean += "- sphere2:rotTr3"; // copy and combitrans a subtraction
  shellBoolean += "- insSeat:tr1"; // subtract the center hole
  shellBoolean += "- framecornerBox:comCorners"; // subtract the corners
  shellBoolean += "- framecornerBox:comCorners2"; // subtract the corners

	// backplate will take the same shape as the frame but with no cutouts and as
	// thin as a single plate
	std::string backPlateBool = "";
	backPlateBool += "sphere3"; // sphere3 should be defined to have the thickness
														  // of the single plate using backPlateZ
	backPlateBool += "- sphere4:rotTr1";
	backPlateBool += "- sphere4:rotTr2";
	backPlateBool += "- sphere4:rotTr3";
	backPlateBool += "- insSeat:tr1";
	backPlateBool += "- framecornerBox:comCorners";
	backPlateBool += "- framecornerBox:comCorners2";

	TGeoCompositeShape* plateCompositeShape = new TGeoCompositeShape("plateCompositeShape", plateBoolean().c_str());
	TGeoVolume* plateVol = new TGeoVolume("plateVol", plateCompositeShape, alMed);

	// C Side Transformations
  for (Int_t itr = NCellsA; itr < NCellsA + NCellsC; itr++) {
    nameTr = Form("0TR%i", itr + 1);
    nameRot = Form("0Rot%i", itr + 1);
    int ic = itr - NCellsA;
    nameCom = Form("0Com%i",itr+1);

    rot[ic] = new TGeoRotation(nameRot.Data(), ac[ic], bc[ic], gc[ic]);
    rot[ic]->RegisterYourself();

    // why is this 80 hardcoded -- if we change it to 82/the value of zDetC, what happens?
    // we think this might give overlaps in the future
    tr[itr] = new TGeoTranslation(nameTr.Data(), xc2[ic], yc2[ic], (zc2[ic] - 80.));
    tr[itr]->RegisterYourself();
    // tr[itr]->Print();

    //   com[itr-NCellsA] = new TGeoCombiTrans(tr[itr],rot[itr-NCellsA]);
		com[ic] = new TGeoCombiTrans(xc2[ic], yc2[ic], (zc2[ic] - 80), rot[ic]);
		plateCom[ic] = new TGeoCombiTrans(xc2[ic], yc2[ic], (zc2[ic] - 83), rot[ic]);
    // com[ic]->RegisterYourself();
    // std::cout << ic << " " << xc2[ic] << " " << yc2[ic] << std::endl;
    TGeoHMatrix hm = *com[ic];
    TGeoHMatrix* ph = new TGeoHMatrix(hm);

		TGeoHMatrix hmPlate = *plateCom[ic];
    TGeoHMatrix* phPlate = new TGeoHMatrix(hmPlate);

		// stlinC->AddNode(ins, itr, ph);
		// stlinC->AddNode(plateVol, itr + 1, phPlate);

  }

	ins->AddNode(pmtVol, 1, pmtTr);
	ins->AddNode(qrVol, 2, qrTr);

	// end sens elements

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


	// scaling the PMT/Qrads along the <x,y,z> vector that places the sens elems
  Double_t scalePMT = pmtPos(xc2[0], yc2[0], zc2[0]);
  Double_t scaleQrad = qradPos(xc2[0], yc2[0], zc2[0]);

	Double_t rmag = sqrt(x*x + y*y + z*z);


	Double_t xPMT[NCellsC]; Double_t yPMT[NCellsC]; Double_t zPMT[NCellsC];

	Double_t aPMT[NCellsC]; Double_t bPMT[NCellsC]; Double_t gPMT[NCellsC];

	Double_t xQrad[NCellsC]; Double_t yQrad[NCellsC]; Double_t zQrad[NCellsC];

	Double_t aQrad[NCellsC]; Double_t bQrad[NCellsC]; Double_t gQrad[NCellsC];

	Double_t rotC[NCellsC];
	Double_t comC[NCellsC];


  for (Int_t i = 0; i < NCellsC; i++) {
    // Double_t rsquared = xc2[i]*xc2[i] + yc2[i]*yc2[i] + zc2[i]*zc2[i];
    // Double_t invR = Q_rsqrt(rsquared);

		// PMT Transformations
		xPMT[i] = scalePMT * xc2[i];
		yPMT[i] = scalePMT * yc2[i];
		zPMT[i] = scalePMT * zc2[i];

	  aPMT[i] = TMath::ATan(yPMT[i] / xPMT[i]) - TMath::Pi() / 2 + 2 * TMath::Pi();
	  if (xPMT[i] < 0) {
			bPMT[i] = TMath::ACos(zPMT[i] / crad);
		} else {
			bPMT[i] = -1 * TMath::ACos(zPMT[i] / crad);
		}

	  aPMT[i] *= 180 / TMath::Pi();
    bPMT[i] *= 180 / TMath::Pi();
    gPMT[i] = -1 * aPMT[i];

		// Quartz radiator transformations
		xQrad[i] = scaleQrad * xc2[i];
		yQrad[i] = scaleQrad * yc2[i];
		zQrad[i] = scaleQrad * zc2[i];

		aQrad[i] = TMath::ATan(yQrad[i] / xQrad[i]) - TMath::Pi() / 2 + 2 * TMath::Pi();
		if (xQrad[i] < 0) {
			bQrad[i] = TMath::ACos(zQrad[i] / crad);
		} else {
			bQrad[i] = -1 * TMath::ACos(zQrad[i] / crad);
		}

		aQrad[i] *= 180 / TMath::Pi();
		bQrad[i] *= 180 / TMath::Pi();
		gQrad[i] = -1 * aQrad[i];

  }

  TString nameComPMT;
	TString nameComQuartz;
	TString nameComPlates;
	TString nameComC;
  for (Int_t itr = NCellsA; itr < NCellsA + NCellsC; itr++) {
    // nameTr = Form("0TR%i", itr + 1);
    nameRot = Form("0Rot%i", itr + 1);
    int ic = itr - NCellsA;
    nameComPMT = Form("0ComPMT%i", ic + 1);
    nameComQuartz = Form("0ComQuartz%i", ic + 1);

    // getting even indices to skip reflections -> reflections happen later in
    // frame construction
    if (ic%2==0){

			TGeoRotation* rotC = new TGeoRotation(nameRot.Data(), ac[ic], bc[ic], gc[ic]);
			rotC->RegisterYourself();

			TGeoCombiTrans* comC = new TGeoCombiTrans(nameComC.Data(),
																		xc2[ic], yc2[ic], zc2[ic], rotC);
			comC->RegisterYourself();


			TGeoRotation* rotPMT = new TGeoRotation(nameRot.Data(),
                                              ac[ic], bc[ic], gc[ic]);
      rotPMT->RegisterYourself();

      TGeoCombiTrans* comPMT = new TGeoCombiTrans(nameComPMT.Data(),
                                                  xPMT[ic], yPMT[ic],
																									// zPMT[ic] + 10*sEps,
																									zPMT[ic] + errPMT,
                                                  rotPMT);
      comPMT->RegisterYourself();



			TGeoRotation* rotQuartz = new TGeoRotation(nameRot.Data(),
                                                 ac[ic], bc[ic], gc[ic]);
      rotQuartz->RegisterYourself();

      TGeoCombiTrans* comQuartz = new TGeoCombiTrans(nameComQuartz.Data(),
                                                     xQrad[ic], yQrad[ic],
                                                     zQrad[ic] - (sQuartzRadiatorZC/2 + 3*sEps),
                                                     rotQuartz);
      comQuartz->RegisterYourself();

			TGeoRotation* rotPlates = new TGeoRotation(nameRot.Data(),
                                                 ac[ic], bc[ic], gc[ic]);
      rotPlates->RegisterYourself();

      TGeoCombiTrans* comPlates = new TGeoCombiTrans(nameComPlates.Data(),
                                                     xQrad[ic], yQrad[ic],
                                                     zQrad[ic],
                                                     rotPlates);
      comQuartz->RegisterYourself();


			// Subtract the PMTs from the frame
      std::string pmtCombiBool = "";
      pmtCombiBool += "- ";
      pmtCombiBool += "pmtBoxSeat:";
      pmtCombiBool += nameComPMT.Data();
      shellBoolean += pmtCombiBool;

			// Subtract the QuartzRadiators from the frame
      std::string quartzCombiBool = "";
      quartzCombiBool += "- ";
      quartzCombiBool += "quartzRadiatorSeat:";
			quartzCombiBool += nameComQuartz.Data();
			shellBoolean += quartzCombiBool;
    }
  }

  TGeoCompositeShape* shellCompShape = new TGeoCompositeShape("shellCompShape",
                                                          shellBoolean.c_str());
  TGeoCompositeShape* backPlateShape = new TGeoCompositeShape("backPlateShape", backPlateBool.c_str());

  TGeoVolume* shellVol = new TGeoVolume("shellVol", shellCompShape, alMed);

	TGeoVolume* backPlateVol = new TGeoVolume("backPlateVol", backPlateShape, alMed);

  // TGeoCombiTrans* shellTr1 = new TGeoCombiTrans("shellTr1", 0, 0, -80, rot1);
  TGeoTranslation* shellTr1 = new TGeoTranslation("shellTr1", 0, 0, -80);
  shellTr1->RegisterYourself();

  TGeoCombiTrans* shellTr2 = new TGeoCombiTrans("shellTr2", 0, 0, -80, reflectC1);
  shellTr2->RegisterYourself();

	TGeoTranslation* backPlateTr1 = new TGeoTranslation("backPlateTr1", 0, 0, -74);
	backPlateTr1->RegisterYourself();

	TGeoCombiTrans* backPlateTr2 = new TGeoCombiTrans("backPlateTr2", 0, 0, -74, reflectC1);
	backPlateTr2->RegisterYourself();

  stlinC->AddNode(shellVol, 29, shellTr1);
	stlinC->AddNode(shellVol, 30, shellTr2);

	stlinC->AddNode(backPlateVol, 31, backPlateTr1);
	stlinC->AddNode(backPlateVol, 32, backPlateTr2);

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
  pmtCompositeShapeBoolean += "pmtBoxSeat";
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


std::string plateBoolean() {
	Double_t prismHeight = .3895; //height of vertical edge of square prism part of base

	Double_t prismSide = 5.9; //width and length of square prism part of base

	Double_t radCurve = 81.9469; //radius of curvature of top part of base

	Double_t delHeight = radCurve*
		(1.0-TMath::Sqrt(1.0-0.5*TMath::Power(prismSide/radCurve,2.0)));
	//height from top of square prism to center of curved top surface of base

	Double_t heightBase = prismHeight + delHeight; //from center of bottom to center of top

	Double_t sliceSide = 5.3; //side lengths of slice's flat top

	Double_t heightBaseBox = 2 * heightBase;

	Double_t totalHeight = .5;

	Double_t sliceHeight = .5 - heightBase;


	//cable dimensions and distances
	Double_t cableHoleWidth = .3503;
	Double_t cableHoleLength = .9003;
	Double_t cableHoleDepth = 1; //really big just to punch a hole

	//sholes denotes "straight holes" and rholes denote "rotated holes"
	//all distances measured from edges of slice
	//up and down sholes
	Double_t sHolesBottomEdge = 1.585;
	Double_t sHolesTopEdge = .515;
	Double_t sHolesAvgTopBottom = (sHolesBottomEdge+sHolesTopEdge)/2.0;
	Double_t sHolesUpFromCenter = ( (sliceSide/2.0) - sHolesAvgTopBottom ); //amount up in x the sholes need to move.
	//left and right sholes
	Double_t sHolesFarEdge = 1.585;
	Double_t sHolesNearEdge = 1.065;
	Double_t sHolesAvgNearFar = (sHolesFarEdge+sHolesNearEdge)/2.0;
	Double_t sHolesLateralFromCenter = ( (sliceSide/2.0) - sHolesAvgNearFar );

	// Create Boxes

	TGeoBBox *box = new TGeoBBox("BASE", prismSide/2.0, heightBaseBox/2.0, prismSide/2.0);

	// Base raw box to be subtracted

	TGeoBBox *slice = new TGeoBBox("SLICE", sliceSide/2.0, heightBaseBox/2.0, sliceSide/2.0);

	TGeoBBox *cableHole = new TGeoBBox("CABLE", cableHoleLength/2.0, cableHoleDepth/2.0, cableHoleWidth/2.0);

	TGeoBBox *cableHole2 = new TGeoBBox("CABLE2", cableHoleWidth/2.0, cableHoleLength/2.0, cableHoleDepth/2.0);

	// Create Subtractions

	// TGeoVolume *vol = gGeoManager->MakeSphere("BASE_SUBTRACTION",med,
	// 	    radCurve, radCurve+5.0, 80, 100, 80, 100);

	TGeoSphere *baseShape = new TGeoSphere("BASE_SUBTRACTION", radCurve, radCurve+5.0, 80, 100, 80, 100);

	//TGeoVolume *vol2 = gGeoManager->MakeSphere("SPHERE2",med,
	//radCurve-5.0, radCurve, 80, 100, 80, 100);

	TGeoTranslation *rTrans= new TGeoTranslation("rTrans",0,radCurve,0);
	rTrans->RegisterYourself();

	TGeoTranslation *rBackTrans = new TGeoTranslation("rBackTrans",0,-1.0*radCurve,0);
	rBackTrans->RegisterYourself();

	TGeoTranslation *subSliceTrans = new TGeoTranslation("subSliceTrans",0,(heightBaseBox/2.0)+sliceHeight,0);
	subSliceTrans->RegisterYourself();

	TGeoTranslation *sHolesTopLeftTrans = new TGeoTranslation("sHolesTopLeftTrans",sHolesUpFromCenter,0,sHolesLateralFromCenter);
	sHolesTopLeftTrans->RegisterYourself();

	TGeoTranslation *sHolesTopRightTrans = new TGeoTranslation("sHolesTopRightTrans",sHolesUpFromCenter,0,-1.0*sHolesLateralFromCenter);
	sHolesTopRightTrans->RegisterYourself();




	TGeoTranslation *testTrans = new TGeoTranslation("testTrans",.1,.1,0);
	testTrans->RegisterYourself();

	TGeoRotation *switchToZ = new TGeoRotation("switchToZ",90,90,0);
	switchToZ->RegisterYourself();

	TGeoRotation *rotateHolesLeft = new TGeoRotation("rotateHolesLeft",345,0,0);
	rotateHolesLeft->RegisterYourself();

	TGeoRotation *rotateHolesRight = new TGeoRotation("rotatetHolesRight",15,0,0);
	rotateHolesRight->RegisterYourself();


	// Bottom holes rotation and translation with combitrans

	TGeoCombiTrans *rHolesBottomLeftTrans = new TGeoCombiTrans("rHolesBottomLeftTrans",-1.0*sHolesLateralFromCenter,-1.0*sHolesUpFromCenter,0,rotateHolesLeft);
	rHolesBottomLeftTrans->RegisterYourself();

	TGeoCombiTrans *rHolesBottomRightTrans = new TGeoCombiTrans("rHolesBottomRightTrans",sHolesLateralFromCenter,-1.0*sHolesUpFromCenter,0,rotateHolesRight);
	rHolesBottomRightTrans->RegisterYourself();



	std::string plateBoolean = " ";
	plateBoolean += "(((BASE:rTrans";
	plateBoolean += "- BASE_SUBTRACTION)";
	plateBoolean += "+ (SLICE:rTrans))";
	plateBoolean += ":rBackTrans";
	plateBoolean += "- BASE:subSliceTrans";
	plateBoolean += "- (CABLE:sHolesTopLeftTrans)";
	plateBoolean += "- (CABLE:sHolesTopRightTrans))";
	plateBoolean += ":switchToZ";
	plateBoolean += "- (CABLE2:rHolesBottomLeftTrans)";
	plateBoolean += "- (CABLE2:rHolesBottomRightTrans)";

	//
	// std::string plateBoolean = "BASE:rtrans - BASE_SUBTRACTION";
	return plateBoolean;
}


//Create rounded PMT socket corners
std::string pmtCornerCompositeShapeBoolean()
{
  // create a string for the boolean operations for the composite pmtCorner shape
  std::string pmtCornerCompositeShapeBoolean = "";
  pmtCornerCompositeShapeBoolean += "pmtCornerRect:pmtCornerRectTr";
  pmtCornerCompositeShapeBoolean += " - pmtCornerTube:pmtCornerTubeTr";

  return pmtCornerCompositeShapeBoolean;
}
