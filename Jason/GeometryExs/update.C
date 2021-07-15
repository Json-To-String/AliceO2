// TGeoSphere takes 6 parameters :
// inner and outer radius Rmin, Rmax
// the theta limits Tmin, Tmax
// the phi limits Pmin, Pmax
// (the sector in phi is considered
// starting from Pmin to Pmax counter-clockwise)

void update()
{
  TCanvas *c = new TCanvas("c", "c",0,0,600,600);
  new TGeoManager("sphere", "poza7");
  TGeoMaterial *mat = new TGeoMaterial("Al", 26.98,13,2.7);
  TGeoMedium *med = new TGeoMedium("MED",1,mat);
  TGeoVolume *top = gGeoManager->MakeBox("TOP",med,100,100,100);
  gGeoManager->SetTopVolume(top);

  Float_t pmcp[3] = {2.949, 2.949, 1.}; // MCP


  TGeoVolume *vol = gGeoManager->MakeSphere("SPHERE",med,
  										                      82, 87.6,0,35,0,180);


  vol->SetLineWidth(2);
  top->AddNode(vol, 1);

  gGeoManager->CloseGeometry();
  gGeoManager->SetNsegments(30);
  top->Draw("ogl");
  TView *view = gPad->GetView();
  view->ShowAxis();
};
