{
	TCanvas *c = new TCanvas("c", "c",0,0,600,600);

	new TGeoManager("box", "poza1");

	// Define materials
	TGeoMaterial *mat = new TGeoMaterial("Al", 26.98,13,2.7);
	
	// Define media
	TGeoMedium *med = new TGeoMedium("MED",1,mat);

	// I think this defines the container volume
	TGeoVolume *top = gGeoManager->MakeBox("TOP",med,100,100,100);
	gGeoManager->SetTopVolume(top);
	
	TGeoVolume *vol = gGeoManager->MakeBox("BOX",med,20,30,40);
	vol->SetLineWidth(2);
	top->AddNode(vol,1);
	
	gGeoManager->CloseGeometry();
	gGeoManager->SetNsegments(80);

	top->Draw();
	TView *view = gPad->GetView();
	view->ShowAxis();

}

