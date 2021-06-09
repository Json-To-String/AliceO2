

{
	gSystem->Load("libGeom");
	
	new TGeoManager("world", "the simplest geometry");
	
	TGeoMaterial *mat = new TGeoMaterial("Vacuum",0,0,0);
	TGeoMedium   *med = new TGeoMedium("Vacuum",1,mat);
	
	TGeoVolume *top=gGeoManager->MakeBox("Top",med,10.,10.,10.);
	
	gGeoManager->SetTopVolume(top);
	
	gGeoManager->CloseGeometry();
	
	top->SetLineColor(kMagenta);
	gGeoManager->SetTopVisible(); // the TOP is invisible
	top->Draw();
	return 0;
}
