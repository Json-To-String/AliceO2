

void draw() {

	TGeoManager::Import("PMTcornerRoutine.root"); gGeoManager->GetTopVolume()->Draw("ogl");

}
