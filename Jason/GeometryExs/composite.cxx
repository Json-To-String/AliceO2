
void composite() {

	const Double_t sq2 = TMath::Sqrt(2.);
	gSystem->Load("libGeom");

	TGeoManager *mgr = new TGeoManager("Geom","composite shape example");
	TGeoMedium *medium = 0;
	TGeoVolume *top = mgr->MakeBox("TOP",medium,100,250,250);
	mgr->SetTopVolume(top);

	// Make shape components
	TGeoBBox *sbox = new TGeoBBox("B",100,125*sq2,125*sq2);
	TGeoTube *stub = new TGeoTube("T",0,100,250);
	TGeoPgon *spgon = new TGeoPgon("P",0.,360.,6,2);
	spgon->DefineSection(0,-250,0,80);
	spgon->DefineSection(1,250,0,80);

	// Define some rotations
	TGeoRotation *r1 = new TGeoRotation("r1",90,0,0,180,90,90);
	r1->RegisterYourself();
	
	TGeoRotation *r2 = new TGeoRotation("r2",90,0,45,90,45,270);
	r2->RegisterYourself();

	// create a composite
	TGeoCompositeShape *cs = new TGeoCompositeShape("cs", "((T+T:r1)-(P+P:r1))*B:r2");
	TGeoVolume *comp = new TGeoVolume("COMP",cs);
	comp->SetLineColor(5);

	// put it in the top volume
	top->AddNode(comp,1);
	mgr->CloseGeometry();

	// visualize with raytracing
	top->Raytrace();

}
	
	
