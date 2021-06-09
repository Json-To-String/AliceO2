

void draw() {

	TGeoManager::Import("standalone.root"); gGeoManager->GetTopVolume()->Draw("ogl");

}
