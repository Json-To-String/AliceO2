

void draw() {

	TGeoManager::Import("FT0C.root"); gGeoManager->GetTopVolume()->Draw("ogl");

}
