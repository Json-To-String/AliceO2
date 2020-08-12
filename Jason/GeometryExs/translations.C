#include "../temp/Constants.h"
#include "TGeoManager.h"

void translations() {

	// make a canvas to draw on
	TCanvas *c = new TCanvas("c", "c", 0, 0,600,600);

	// starting a manager
	TGeoManager *mgr = new TGeoManager("manager", "Detector-like macro");

	// material and medium
	TGeoMaterial *alMat = new TGeoMaterial("Al", 26.98,13,2.7);
	TGeoMedium   *alMed = new TGeoMedium("Al",1,alMat);

	TGeoMaterial *vacMat = new TGeoMaterial("Vacuum",0,0,0);
	TGeoMedium   *vacMed = new TGeoMedium("Vacuum",1,vacMat);

	TGeoVolume *chamber = gGeoManager->MakeBox("TOP",vacMed,100,100,100);
	gGeoManager->SetTopVolume(chamber);

	// // Documentation Shapes
	// TGeoVolume *al_box = gGeoManager->MakeBox("BOX",alMed,5,5,5);
	// TGeoVolume *al_sliver = gGeoManager->MakeBox("BOX2",alMed,4,4,1);

	// Detector-like shapes
	TGeoBBox* al_cube = new TGeoBBox("al_cube", 5,5,5);
	TGeoBBox* al_slab = new TGeoBBox("al_slab", 3,6,1);
	TGeoVolumeAssembly* Frame = new TGeoVolumeAssembly("Frame");

	TGeoTranslation* posXvar = new TGeoTranslation("posX",4,0,0);
	posXvar->RegisterYourself();
	TGeoTranslation* posYvar = new TGeoTranslation("posY",0,4,0);
	posYvar->RegisterYourself();

	TGeoRotation *r1 = new TGeoRotation("r1",90,0,0);
	r1->RegisterYourself();

	TGeoCombiTrans* combiTr = new TGeoCombiTrans("combiTr",4,0,0, r1);
	combiTr->RegisterYourself();

	// need to subtract different things from volume
	std::string compBool = "al_cube - al_slab";

	TGeoCompositeShape* compShape = new TGeoCompositeShape("compShape", compBool.c_str());
	TGeoVolume* test = new TGeoVolume("test", compShape, alMed);

	chamber->AddNode(test,1);

	gGeoManager->CloseGeometry();
	gGeoManager->SetNsegments(80);
	gGeoManager->Export("MyGeom.root");
	// chamber->Raytrace();
	gGeoManager->GetTopVolume()->Draw("ogle");
	// TGeoManager::Import("MyGeom.root");
	// chamber->Draw("ogl");

	TView *view = gPad->GetView();
	view->ShowAxis();


}
