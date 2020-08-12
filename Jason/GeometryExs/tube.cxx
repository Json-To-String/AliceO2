void tube() {

	// make a canvas to draw on
	TCanvas *c = new TCanvas("c", "c", 0, 0,600,600);

	// starting a manager
	new TGeoManager("tube", "poza2");

	// material and medium
	TGeoMaterial *alMat = new TGeoMaterial("Al", 26.98,13,2.7);
	TGeoMedium   *alMed = new TGeoMedium("Al",1,alMat);

	TGeoMaterial *vacMat = new TGeoMaterial("Vacuum",0,0,0);
	TGeoMedium   *vacMed = new TGeoMedium("Vacuum",1,vacMat);

	// make a box for tube to live in
	TGeoVolume *top = gGeoManager->MakeBox("TOP",vacMed,100,100,100);
	gGeoManager->SetTopVolume(top);

	TGeoVolume *vol = gGeoManager->MakeTube("TUBE",alMed,20,30,40);

	vol->SetLineWidth(2);
	top->AddNode(vol,1);

	gGeoManager->CloseGeometry();
	gGeoManager->SetNsegments(80);

	top->Draw();
}
