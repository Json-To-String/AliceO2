
auto pi = TMath::Pi();

// function code in C
double single(double *x, double *par) {
	return pow(sin(pi*par[0]*x[0])/(pi*par[0]*x[0]),2);

}

double nslit0(double *x,double *par){
	return pow(sin(pi*par[1]*x[0])/sin(pi*x[0]),2);
}

double nslit(double *x, double *par){
	return single(x,par) * nslit0(x,par);
}

// main program
void slits() {
	float r,ns;

	// request user input
	cout << "slit width / g? ";
	scanf("%f",&r);
	cout << "# of slits? ";
	scanf("%f",&ns);
	cout <<"interference pattern for "<< ns <<" slits, width/distance: "
	<<r<<endl;

	// define function and set options
	TF1 *Fnslit = new TF1("Interference Pattern",nslit,-5.001,5.,2);
	Fnslit->SetNpx(500);

	// set parameters, as read in above
	Fnslit->SetParameter(0,r);
	Fnslit->SetParameter(1,ns);

	// Draw the interference patter for a grid with n slits
	Fnslit ->Draw();
}
