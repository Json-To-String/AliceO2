void rotations() {

	gSystem->Load("libGeom");

	TGeoManager *mgr = new TGeoManager("Geom", "composite shape example");
	TGeoMedium *medium = 0;
	TGeoVolume *top = mgr->MakeBox("TOP",medium,100,250,250);
	mgr->SetTopVolume(top);
	
	TGeoTube *stub = new TGeoTube("T",0,100,250);
	
	TGeoRotation *r1 = new TGeoRotation("r1",90,0,0,180,90,90);
	r1->RegisterYourself();

	TGeoRotation *r2 = new TGeoRotation("r2",90,0,45,90,45,270);
	r2->RegisterYourself();

	TGeoCompositeShape *cs = new TGeoCompositeShape("cs", "(T+T:r1)");
	
	TGeoVolume *comp = new TGeoVolume("COMP",cs);
	comp->SetLineColor(5);

	top->AddNode(comp,1);
	mgr->CloseGeometry();

	top->Raytrace();
}		
