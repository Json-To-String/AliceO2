void tubeSeg (){
   TCanvas *c = new TCanvas("c", "c",0,0,600,600);
   new TGeoManager("tubeseg", "poza3");
   TGeoMaterial *mat = new TGeoMaterial("Al", 26.98,13,2.7);
   TGeoMedium *med = new TGeoMedium("MED",1,mat);
   TGeoVolume *top = gGeoManager->MakeBox("TOP",med,100,100,100);
   gGeoManager->SetTopVolume(top);
   TGeoVolume *vol = gGeoManager->MakeTubs("TUBESEG",med, 0,30,40,180,270);
   vol->SetLineWidth(2);

   TGeoRotation *rot1 = new TGeoRotation("rot1", 90,0,0);
   TGeoRotation *rot2 = new TGeoRotation("rot2", 180,0,0);
   TGeoRotation *rot3 = new TGeoRotation("rot3", 270,0,0);

   top->AddNode(vol,1);
   top->AddNode(vol,2,rot1);
   top->AddNode(vol,3,rot2);
   top->AddNode(vol,4,rot3);

   gGeoManager->CloseGeometry();
   gGeoManager->SetNsegments(80);
   top->Draw();
   TView *view = gPad->GetView();
   view->ShowAxis();
}
