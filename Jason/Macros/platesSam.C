// TGeoSphere takes 6 parameters :
// inner and outer radius Rmin, Rmax
// the theta limits Tmin, Tmax
// the phi limits Pmin, Pmax
// (the sector in phi is considered
// starting from Pmin to Pmax counter-clockwise)

void platesSam()
{
  TCanvas *c = new TCanvas("c", "c",0,0,600,600);
  new TGeoManager("sphere", "poza7");
  TGeoMaterial *mat = new TGeoMaterial("Al", 26.98,13,2.7);
  TGeoMedium *med = new TGeoMedium("MED",1,mat);
  TGeoVolume *top = gGeoManager->MakeBox("TOP",med,100,100,100);
  gGeoManager->SetTopVolume(top);



  Double_t prismHeight = .3895; //height of vertical edge of square prism part of base
 
  Double_t prismSide = 5.9; //width and length of square prism part of base
  
  Double_t radCurve = 81.9469; //radius of curvature of top part of base
  
  Double_t delHeight = radCurve*
    (1.0-TMath::Sqrt(1.0-0.5*TMath::Power(prismSide/radCurve,2.0)));
  //height from top of square prism to center of curved top surface of base
  
  Double_t heightBase = prismHeight + delHeight; //from center of bottom to center of top

  Double_t sliceSide = 5.3; //side lengths of slice's flat top

  Double_t heightBaseBox = 2 * heightBase;

  Double_t totalHeight = .5;

  Double_t sliceHeight = .5 - heightBase;


  //cable dimensions and distances
  Double_t cableHoleWidth = .52;
  Double_t cableHoleLength = 1.07;
  Double_t cableHoleDepth = 1; //really big just to punch a hole

  //sholes denotes "straight holes" and rholes denote "rotated holes"
  //all distances measured from edges of slice
  //up and down sholes
  Double_t sHolesBottomEdge = 1.585;
  Double_t sHolesTopEdge = .515;
  Double_t sHolesAvgTopBottom = (sHolesBottomEdge+sHolesTopEdge)/2.0;
  Double_t sHolesUpFromCenter = ( (sliceSide/2.0) - sHolesAvgTopBottom ); //amount up in x the sholes need to move.
  //left and right sholes
  Double_t sHolesFarEdge = 1.585; 
  Double_t sHolesNearEdge = 1.065;
  Double_t sHolesAvgNearFar = (sHolesFarEdge+sHolesNearEdge)/2.0;
  Double_t sHolesLateralFromCenter = ( (sliceSide/2.0) - sHolesAvgNearFar );

  // Create Boxes

  TGeoBBox *box = new TGeoBBox("BASE", prismSide/2.0, heightBaseBox/2.0, prismSide/2.0);
  // Base raw box to be subtracted


  TGeoBBox *slice = new TGeoBBox("SLICE", sliceSide/2.0, heightBaseBox/2.0, sliceSide/2.0);
 
  TGeoBBox *cableHole = new TGeoBBox("CABLE", cableHoleLength/2.0, cableHoleDepth/2.0, cableHoleWidth/2.0);

  TGeoBBox *cableHole2 = new TGeoBBox("CABLE2", cableHoleWidth/2.0, cableHoleLength/2.0, cableHoleDepth/2.0);

  // Create Subtractions

  
  //spherical shell to shave off top of base
  TGeoVolume *vol = gGeoManager->MakeSphere("BASE_SUBTRACTION",med,
		    radCurve, radCurve+5.0, 80, 100, 80, 100);

  //Groove subtractions
  
  //1st from outside (this groove has multiple pieces and so the names will look like: lengthGroove1_[piece#]
  
  //segment1_1
  Double_t lengthGroove1_1 = 2.9;
  Double_t lengthGrooveBox1_1 = 2 * lengthGroove1_1;
  Double_t widthGroove1_1 = .2;
  Double_t depthGroove1_1 = .2;
  Double_t depthGrooveBox1_1 = 2.0*depthGroove1_1;

  TGeoBBox *groove1_1 = new TGeoBBox("groove1_1",widthGroove1_1/2.0,lengthGrooveBox1_1/2.0,depthGrooveBox1_1/2.0);

  //segment1_2 (to trapezoids combined to make one trapezoid)

  Double_t trapz1_2TopX=.2;
  Double_t trapz1_2BottomX=.3;
  Double_t trapz1_2TopY=.2;
  Double_t trapz1_2TopYBox = 2*trapz1_2TopY;;
  Double_t trapz1_2BottomY = .3;
  Double_t trapz1_2BottomYBox = 2*trapz1_2BottomY;
  Double_t trapz1_2Depth=std::sqrt((1.005)*(1.005)-(.1)*(.1));


  TGeoTrd2 *trapz1_2 = new TGeoTrd2("trapz1_2",trapz1_2TopX/2.0,trapz1_2BottomX/2.0,trapz1_2TopYBox/2.0,trapz1_2BottomYBox/2.0,trapz1_2Depth/2.0);  

  //segment 1_3

  Double_t lengthGroove1_3 = .6;
  Double_t widthGroove1_3 = .3;
  Double_t depthGroove1_3 = .3;
  Double_t depthGrooveBox1_3= 2*depthGroove1_3;

  TGeoBBox *groove1_3 = new TGeoBBox("groove1_3",widthGroove1_3/2.0,lengthGroove1_3/2.0,depthGrooveBox1_3/2.0);

  //segment 1_4

  Double_t trapz1_4TopX=.3;
  Double_t trapz1_4BottomX=.4;
  Double_t trapz1_4TopY=.3;
  Double_t trapz1_4TopYBox =2*trapz1_4TopY;
  Double_t trapz1_4BottomY =.3;
  Double_t trapz1_4BottomYBox =2*trapz1_4BottomY ;
  Double_t trapz1_4Depth=std::sqrt(1.0012*1.0012-.1*.1);


   TGeoTrd2 *trapz1_4 = new TGeoTrd2("trapz1_4",trapz1_4TopX/2.0,trapz1_4BottomX/2.0,trapz1_4TopYBox/2.0,trapz1_4BottomYBox/2.0,trapz1_4Depth/2.0);  
 

   //segment 1_5 

  Double_t lengthGroove1_5 = .4;
  Double_t lengthGrooveBox1_5 = 2 * lengthGroove1_5;
  Double_t widthGroove1_5 = .4;
  Double_t depthGroove1_5 = .3;
  Double_t depthGrooveBox1_5 = 2.0*depthGroove1_5;

  TGeoBBox *groove1_5 = new TGeoBBox("groove1_5",widthGroove1_5/2.0,lengthGrooveBox1_5/2.0,depthGrooveBox1_5/2.0);


  //2nd from outside
  Double_t lengthGroove2 = .815*1.5;
  Double_t widthGroove2 = .3;
  Double_t depthGroove2 = .4;
  Double_t depthGrooveBox2 = 2.0*depthGroove2;

  TGeoBBox *groove2 = new TGeoBBox("groove2",widthGroove2/2.0,lengthGroove2/2.0,depthGrooveBox2/2.0);


  //3rd from outside
  
  //segment 3_1

  Double_t lengthGroove3_1 = .5;
  Double_t lengthGrooveBox3_1 = 2*lengthGroove3_1;
  Double_t widthGroove3_1 = .3;
  Double_t depthGroove3_1 = .3;
  Double_t depthGrooveBox3_1 = 2*depthGroove3_1;
  
  TGeoBBox *groove3_1 = new TGeoBBox("groove3_1",widthGroove3_1/2.0,lengthGrooveBox3_1/2.0,depthGrooveBox3_1/2.0);
  

  //segment 3_2

  Double_t trapz3_2TopX=.3;
  Double_t trapz3_2BottomX=.3;
  Double_t trapz3_2TopY=.3;
  Double_t trapz3_2TopYBox = 2*trapz3_2TopY;;
  Double_t trapz3_2BottomY =.4;
  Double_t trapz3_2BottomYBox = 2*trapz3_2BottomY;
  Double_t trapz3_2Depth=std::sqrt((1.005)*(1.005)-(.1)*(.1));


  TGeoTrd2 *trapz3_2 = new TGeoTrd2("trapz3_2",trapz3_2TopX/2.0,trapz3_2BottomX/2.0,trapz3_2TopYBox/2.0,trapz3_2BottomYBox/2.0,trapz3_2Depth/2.0);  


  //segment 3_3

  
  Double_t lengthGroove3_3 = .8515;
  Double_t widthGroove3_3 = .3;
  Double_t depthGroove3_3 = .4;
  Double_t depthGrooveBox3_3 = 2*depthGroove3_3;
  
  TGeoBBox *groove3_3 = new TGeoBBox("groove3_3",widthGroove3_3/2.0,lengthGroove3_3/2.0,depthGrooveBox3_3/2.0);


  //segment 3 curvy bits

  //segment 3c_1

    
  Double_t lengthSlider3c_1 = 4.0;

  Double_t lengthGroove3c_1 = .05*lengthSlider3c_1;
  Double_t lengthGrooveBox3c_1 = 2 * lengthGroove3c_1;
  Double_t widthGroove3c_1 = .3;
  Double_t depthGroove3c_1 = .4;
  Double_t depthGrooveBox3c_1 = 2*depthGroove3c_1;
  
  TGeoBBox *groove3c_1 = new TGeoBBox("groove3c_1",widthGroove3c_1/2.0,lengthGrooveBox3c_1/2.0,depthGrooveBox3c_1/2.0);



  //segment 3c_2

  Double_t lengthSlider3c_2 = 1.35;

  Double_t lengthGroove3c_2 = .7 * lengthSlider3c_2;
  Double_t lengthGrooveBox3c_2 = 2* lengthGroove3c_2;
  Double_t widthGroove3c_2 = .3;
  Double_t depthGroove3c_2 = .4;
  Double_t depthGrooveBox3c_2 = 2 * depthGroove3c_2;

  TGeoBBox *groove3c_2 = new TGeoBBox("groove3c_2",widthGroove3c_2/2.0,lengthGrooveBox3c_2/2.0,depthGrooveBox3c_2/2.0);


  //4th from outside
 

  //segment 4_1

  Double_t lengthGroove4_1 = .5;
  Double_t lengthGrooveBox4_1 = 2*lengthGroove4_1;
  Double_t widthGroove4_1 = .2;
  Double_t depthGroove4_1 = .2;
  Double_t depthGrooveBox4_1 = 2*depthGroove4_1;

  TGeoBBox *groove4_1 = new TGeoBBox("groove4_1",widthGroove4_1/2.0,lengthGrooveBox4_1/2.0,depthGrooveBox4_1/2.0);


  //segment 4_2

  
  Double_t trapz4_2TopX=.2;
  Double_t trapz4_2BottomX=.3;
  Double_t trapz4_2TopY=.2;
  Double_t trapz4_2TopYBox = 2*trapz4_2TopY;;
  Double_t trapz4_2BottomY =.3;
  Double_t trapz4_2BottomYBox = 2*trapz4_2BottomY;
  Double_t trapz4_2Depth=std::sqrt((1.005)*(1.005)-(.1)*(.1));


  TGeoTrd2 *trapz4_2 = new TGeoTrd2("trapz4_2",trapz4_2TopX/2.0,trapz4_2BottomX/2.0,trapz4_2TopYBox/2.0,trapz4_2BottomYBox/2.0,trapz4_2Depth/2.0);  


  //segment 4_3

  
  Double_t lengthGroove4_3 = .9;
  Double_t widthGroove4_3 = .3;
  Double_t depthGroove4_3 = .3;
  Double_t depthGrooveBox4_3 = 2*depthGroove3_3;
  
  TGeoBBox *groove4_3 = new TGeoBBox("groove4_3",widthGroove4_3/2.0,lengthGroove4_3/2.0,depthGrooveBox4_3/2.0);


  //segment 4_4


  
  Double_t trapz4_4TopX=.3;
  Double_t trapz4_4BottomX=.3;
  Double_t trapz4_4TopY=.3;
  Double_t trapz4_4TopYBox = 2*trapz4_4TopY;;
  Double_t trapz4_4BottomY =.4;
  Double_t trapz4_4BottomYBox = 2*trapz4_4BottomY;
  Double_t trapz4_4Depth=std::sqrt((1.005)*(1.005)-(.1)*(.1));


  TGeoTrd2 *trapz4_4 = new TGeoTrd2("trapz4_4",trapz4_4TopX/2.0,trapz4_4BottomX/2.0,trapz4_4TopYBox/2.0,trapz4_4BottomYBox/2.0,trapz4_4Depth/2.0);  


  //segment 4 curvy bits

  //segment 4c_1

  Double_t lengthSlider4c_1 = 11.5;
    
  Double_t lengthGroove4c_1 = .05 * lengthSlider4c_1;
  Double_t widthGroove4c_1 = .3;
  Double_t depthGroove4c_1 = .4;
  Double_t depthGrooveBox4c_1 = 2*depthGroove4c_1;
  
  TGeoBBox *groove4c_1 = new TGeoBBox("groove4c_1",widthGroove4c_1/2.0,lengthGroove4c_1/2.0,depthGrooveBox4c_1/2.0);


  //segment 4c_2

  //trapz4c_2

  Double_t lengthSlider4c_2 = 10.0;
  Double_t gapSlider4c_2 = .5;

  
  Double_t trapz4c_2TopX=.3*gapSlider4c_2;
  Double_t trapz4c_2BottomX=.35;
  Double_t trapz4c_2BottomXBox=2.0*trapz4c_2BottomX;
  Double_t trapz4c_2TopY=.4;
  Double_t trapz4c_2TopYBox = 2*trapz4_4TopY;;
  Double_t trapz4c_2BottomY =.4;
  Double_t trapz4c_2BottomYBox = 2*trapz4c_2BottomY;
  Double_t trapz4c_2Depth=.05*lengthSlider4c_2;


  TGeoTrd2 *trapz4c_2 = new TGeoTrd2("trapz4c_2",trapz4c_2TopX/2.0,trapz4c_2BottomXBox/2.0,trapz4c_2TopYBox/2.0,trapz4c_2BottomYBox/2.0,trapz4c_2Depth/2.0);  


  //groove4c_2

  
  Double_t grooveSlider4c_2 = 10.0;

   
  Double_t lengthGroove4c_2 = .05 * grooveSlider4c_2;
  Double_t lengthGrooveBox4c_2 = 2* lengthGroove4c_2;
  Double_t widthGroove4c_2 = .35;
  Double_t depthGroove4c_2 = .4;
  Double_t depthGrooveBox4c_2 = 2*depthGroove4c_2;
  
  TGeoBBox *groove4c_2 = new TGeoBBox("groove4c_2",widthGroove4c_2/2.0,lengthGrooveBox4c_2/2.0,depthGrooveBox4c_2/2.0);


  //segment 4c_3

  Double_t lengthSlider4c_3 = 1.65;


   
  Double_t lengthGroove4c_3 = 1.1968 * lengthSlider4c_3;
  Double_t widthGroove4c_3 = .3;
  Double_t depthGroove4c_3 = .4;
  Double_t depthGrooveBox4c_3 = 2*depthGroove4c_3;
  
  TGeoBBox *groove4c_3 = new TGeoBBox("groove4c_3",widthGroove4c_3/2.0,lengthGroove4c_3/2.0,depthGrooveBox4c_3/2.0);





  //TGeoVolume *vol2 = gGeoManager->MakeSphere("SPHERE2",med,
  //radCurve-5.0, radCurve, 80, 100, 80, 100);

  TGeoTranslation *rTrans= new TGeoTranslation("rTrans",0,radCurve,0);
  rTrans->RegisterYourself();

  TGeoTranslation *rBackTrans = new TGeoTranslation("rBackTrans",0,-1.0*radCurve,0);
  rBackTrans->RegisterYourself();

  TGeoTranslation *subSliceTrans = new TGeoTranslation("subSliceTrans",0,(heightBaseBox/2.0)+sliceHeight,0);
  subSliceTrans->RegisterYourself();

  TGeoTranslation *sHolesTopLeftTrans = new TGeoTranslation("sHolesTopLeftTrans",sHolesUpFromCenter,0,sHolesLateralFromCenter);
  sHolesTopLeftTrans->RegisterYourself();

  TGeoTranslation *sHolesTopRightTrans = new TGeoTranslation("sHolesTopRightTrans",sHolesUpFromCenter,0,-1.0*sHolesLateralFromCenter);
  sHolesTopRightTrans->RegisterYourself();

  


  TGeoTranslation *testTrans = new TGeoTranslation("testTrans",.1,.1,0);
  testTrans->RegisterYourself();

  TGeoRotation *switchToZ = new TGeoRotation("switchToZ",90,90,0);
  switchToZ->RegisterYourself();

  TGeoRotation *rotateHolesLeft = new TGeoRotation("rotateHolesLeft",345,0,0);
  rotateHolesLeft->RegisterYourself();

  TGeoRotation *rotateHolesRight = new TGeoRotation("rotatetHolesRight",15,0,0);
  rotateHolesRight->RegisterYourself();


  // Bottom holes rotation and translation with combitrans

  Double_t rHolesDown = -1.0594;
  Double_t rHolesOut = 1.25385;

  TGeoCombiTrans *rHolesBottomLeftTrans = new TGeoCombiTrans("rHolesBottomLeftTrans",-1.0*rHolesOut,rHolesDown,0,rotateHolesLeft);
  rHolesBottomLeftTrans->RegisterYourself();

  TGeoCombiTrans *rHolesBottomRightTrans = new TGeoCombiTrans("rHolesBottomRightTrans",rHolesOut,rHolesDown,0,rotateHolesRight);
  rHolesBottomRightTrans->RegisterYourself();




  // Groove Translations and Rotations

  Double_t groovesDownToFloor = -1.0*heightBaseBox/2.0;

  //1st groove

  //segment 1_1
  Double_t groove1_1LateralShiftFromCableHole = widthGroove2/2.0 + .275 + widthGroove1_1/2.0;

  TGeoTranslation *groove1_1Trans = new TGeoTranslation("groove1_1Trans",sHolesLateralFromCenter+groove1_1LateralShiftFromCableHole,prismSide/2.0,groovesDownToFloor);
  groove1_1Trans->RegisterYourself();


  TGeoTranslation *groove1_1Trans2 = new TGeoTranslation("groove1_1Trans2",-1.0*(sHolesLateralFromCenter+groove1_1LateralShiftFromCableHole),prismSide/2.0,groovesDownToFloor);
  groove1_1Trans2->RegisterYourself();

  //segment 1_2

  Double_t correctionLength1_2 = 0.0001;

  TGeoRotation *flip1_2 = new TGeoRotation("flip1_2",0,90,0);
  flip1_2->RegisterYourself();

  TGeoCombiTrans *trapz1_2Trans1 = new TGeoCombiTrans("trapz1_2Trans1",sHolesLateralFromCenter+groove1_1LateralShiftFromCableHole,(prismSide/2.0-lengthGroove1_1)-(trapz1_2Depth/2.0)+correctionLength1_2,groovesDownToFloor,flip1_2);
  trapz1_2Trans1->RegisterYourself();

  TGeoCombiTrans *trapz1_2Trans2 = new TGeoCombiTrans("trapz1_2Trans2",-1.0*(sHolesLateralFromCenter+groove1_1LateralShiftFromCableHole),(prismSide/2.0-lengthGroove1_1)-(trapz1_2Depth/2.0)+correctionLength1_2,groovesDownToFloor,flip1_2);
  trapz1_2Trans2->RegisterYourself();

  //segment 1_3

  Double_t correctMe = .001;

  TGeoTranslation *groove1_3Trans1 = new TGeoTranslation("groove1_3Trans1",sHolesLateralFromCenter+groove1_1LateralShiftFromCableHole,(prismSide/2.0-lengthGroove1_1)-(trapz1_2Depth/2.0)+correctionLength1_2-trapz1_2Depth/2.0-lengthGroove1_3/2.0+correctMe,groovesDownToFloor);
  groove1_3Trans1->RegisterYourself();

  TGeoTranslation *groove1_3Trans2 = new TGeoTranslation("groove1_3Trans2",-1.0*(sHolesLateralFromCenter+groove1_1LateralShiftFromCableHole),(prismSide/2.0-lengthGroove1_1)-(trapz1_2Depth/2.0)+correctionLength1_2-trapz1_2Depth/2.0-lengthGroove1_3/2.0+correctMe,groovesDownToFloor);
  groove1_3Trans2->RegisterYourself();


  //segement 1_4 

  TGeoCombiTrans *trapz1_4Trans1 = new TGeoCombiTrans("trapz1_4Trans1",sHolesLateralFromCenter+groove1_1LateralShiftFromCableHole,(prismSide/2.0-lengthGroove1_1)-(trapz1_2Depth/2.0)+correctionLength1_2-trapz1_2Depth/2.0-lengthGroove1_3/2.0+correctMe-lengthGroove1_3/2.0-trapz1_4Depth/2.0,groovesDownToFloor,flip1_2);
  trapz1_4Trans1->RegisterYourself();

  TGeoCombiTrans *trapz1_4Trans2 = new TGeoCombiTrans("trapz1_4Trans2",-1.0*(sHolesLateralFromCenter+groove1_1LateralShiftFromCableHole),(prismSide/2.0-lengthGroove1_1)-(trapz1_2Depth/2.0)+correctionLength1_2-trapz1_2Depth/2.0-lengthGroove1_3/2.0+correctMe-lengthGroove1_3/2.0-trapz1_4Depth/2.0,groovesDownToFloor,flip1_2);
  trapz1_4Trans2->RegisterYourself();

  //segment 1_5

  Double_t correctMe1_5=.0001;

  TGeoTranslation *groove1_5Trans1 = new TGeoTranslation("groove1_5Trans1",sHolesLateralFromCenter+groove1_1LateralShiftFromCableHole,(prismSide/2.0-lengthGroove1_1)-(trapz1_2Depth/2.0)+correctionLength1_2-trapz1_2Depth/2.0-lengthGroove1_3/2.0+correctMe-lengthGroove1_3/2.0-trapz1_4Depth/2.0-trapz1_4Depth/2.0-lengthGrooveBox1_5/2.0+correctMe1_5,groovesDownToFloor);
  groove1_5Trans1->RegisterYourself();



  TGeoTranslation *groove1_5Trans2 = new TGeoTranslation("groove1_5Trans2",-1.0*(sHolesLateralFromCenter+groove1_1LateralShiftFromCableHole),(prismSide/2.0-lengthGroove1_1)-(trapz1_2Depth/2.0)+correctionLength1_2-trapz1_2Depth/2.0-lengthGroove1_3/2.0+correctMe-lengthGroove1_3/2.0-trapz1_4Depth/2.0-trapz1_4Depth/2.0-lengthGrooveBox1_5/2.0+correctMe1_5,groovesDownToFloor);
  groove1_5Trans2->RegisterYourself();


  //2nd groove


  TGeoTranslation *groove2Trans= new TGeoTranslation("groove2Trans",sHolesLateralFromCenter,sHolesUpFromCenter+lengthGroove2/2.0+cableHoleLength/2.0,groovesDownToFloor);
  groove2Trans->RegisterYourself();
  
  TGeoTranslation *groove2Trans2= new TGeoTranslation("groove2Trans2",-1.0*sHolesLateralFromCenter,sHolesUpFromCenter+lengthGroove2/2.0+cableHoleLength/2.0,groovesDownToFloor);
  groove2Trans2->RegisterYourself();

  //3rd groove

  //segment 3_1

  Double_t groove3_1LateralShiftFromCableHole = widthGroove2/2.0 + .15 + widthGroove3_1/2.0;

  TGeoTranslation *groove3_1Trans = new TGeoTranslation("groove3_1Trans",sHolesLateralFromCenter-groove3_1LateralShiftFromCableHole,prismSide/2.0,groovesDownToFloor);
  groove3_1Trans->RegisterYourself();

  TGeoTranslation *groove3_1Trans2 = new TGeoTranslation("groove3_1Trans2",-1.0*(sHolesLateralFromCenter-groove3_1LateralShiftFromCableHole),prismSide/2.0,groovesDownToFloor);
  groove3_1Trans2->RegisterYourself();


  //segment 3_2

  Double_t correctMe3_2=.0001;

  TGeoCombiTrans *trapz3_2Trans1 = new TGeoCombiTrans("trapz3_2Trans1",sHolesLateralFromCenter-groove3_1LateralShiftFromCableHole,prismSide/2.0-lengthGrooveBox3_1/2.0-trapz3_2Depth/2.0+correctMe3_2,groovesDownToFloor,flip1_2);
  trapz3_2Trans1->RegisterYourself();

  TGeoCombiTrans *trapz3_2Trans2 = new TGeoCombiTrans("trapz3_2Trans2",-1.0*(sHolesLateralFromCenter-groove3_1LateralShiftFromCableHole),prismSide/2.0-lengthGrooveBox3_1/2.0-trapz3_2Depth/2.0+correctMe3_2,groovesDownToFloor,flip1_2);
  trapz3_2Trans2->RegisterYourself();


  //segment 3_3


  Double_t correctMe3_3 = .0001;

  TGeoTranslation *groove3_3Trans1 = new TGeoTranslation("groove3_3Trans1",sHolesLateralFromCenter-groove3_1LateralShiftFromCableHole,prismSide/2.0-lengthGrooveBox3_1/2.0-trapz3_2Depth/2.0+correctMe3_2-trapz3_2Depth/2.0-lengthGroove3_3/2.0+correctMe3_3,groovesDownToFloor);
  groove3_3Trans1->RegisterYourself();

  TGeoTranslation *groove3_3Trans2 = new TGeoTranslation("groove3_3Trans2",-1.0*(sHolesLateralFromCenter-groove3_1LateralShiftFromCableHole),prismSide/2.0-lengthGrooveBox3_1/2.0-trapz3_2Depth/2.0+correctMe3_2-trapz3_2Depth/2.0-lengthGroove3_3/2.0+correctMe3_3,groovesDownToFloor);
  groove3_3Trans2->RegisterYourself();

  //segment 3 curvy bits

  //segment 3c_1

  TGeoTranslation *groove3c_1Trans1 = new TGeoTranslation("groove3c_1Trans1",sHolesLateralFromCenter-groove3_1LateralShiftFromCableHole,prismSide/2.0-lengthGrooveBox3_1/2.0-trapz3_2Depth/2.0+correctMe3_2-trapz3_2Depth/2.0-lengthGroove3_3/2.0+correctMe3_3-lengthGroove3_3/2.0-lengthGroove3c_1/2.0,groovesDownToFloor);
  groove3c_1Trans1->RegisterYourself();

  TGeoTranslation *groove3c_1Trans2 = new TGeoTranslation("groove3c_1Trans2",-1.0*(sHolesLateralFromCenter-groove3_1LateralShiftFromCableHole),prismSide/2.0-lengthGrooveBox3_1/2.0-trapz3_2Depth/2.0+correctMe3_2-trapz3_2Depth/2.0-lengthGroove3_3/2.0+correctMe3_3-lengthGroove3_3/2.0-lengthGroove3c_1/2.0,groovesDownToFloor);
  groove3c_1Trans2->RegisterYourself();

  //segment 3c_2

  Double_t intersectionX = 1.1155;
  Double_t intersectionY = -.5426;

  TGeoCombiTrans *groove3c_2Trans1 = new TGeoCombiTrans("groove3c_2Trans1",intersectionX,intersectionY,groovesDownToFloor,rotateHolesRight);
  groove3c_2Trans1->RegisterYourself();

  TGeoCombiTrans *groove3c_2Trans2 = new TGeoCombiTrans("groove3c_2Trans2",-1.0*intersectionX,intersectionY,groovesDownToFloor,rotateHolesLeft);
  groove3c_2Trans2->RegisterYourself();

  //4th groove

  //segment 4_1

  Double_t middleLength = .9;
  Double_t distanceToGroove4_1FromMiddleLength = middleLength/2.0;

  TGeoTranslation *groove4_1Trans = new TGeoTranslation("groove4_1Trans",distanceToGroove4_1FromMiddleLength,prismSide/2.0,groovesDownToFloor);
  groove4_1Trans->RegisterYourself();


  TGeoTranslation *groove4_1Trans2 = new TGeoTranslation("groove4_1Trans2",-1.0*distanceToGroove4_1FromMiddleLength,prismSide/2.0,groovesDownToFloor);
  groove4_1Trans2->RegisterYourself();


  //segment 4_2

  TGeoCombiTrans *trapz4_2Trans1 = new TGeoCombiTrans("trapz4_2Trans1",distanceToGroove4_1FromMiddleLength,prismSide/2.0-lengthGrooveBox4_1/2.0-trapz4_2Depth/2.0,groovesDownToFloor,flip1_2);
  trapz4_2Trans1->RegisterYourself();


  TGeoCombiTrans *trapz4_2Trans2 = new TGeoCombiTrans("trapz4_2Trans2",-1.0*distanceToGroove4_1FromMiddleLength,prismSide/2.0-lengthGrooveBox4_1/2.0-trapz4_2Depth/2.0,groovesDownToFloor,flip1_2);
  trapz4_2Trans2->RegisterYourself();


  //segement 4_3 

  TGeoTranslation *groove4_3Trans1 = new TGeoTranslation("groove4_3Trans1",distanceToGroove4_1FromMiddleLength,prismSide/2.0-lengthGrooveBox4_1/2.0-trapz4_2Depth/2.0-trapz4_2Depth/2.0-lengthGroove4_3/2.0,groovesDownToFloor);
  groove4_3Trans1->RegisterYourself();

  TGeoTranslation *groove4_3Trans2 = new TGeoTranslation("groove4_3Trans2",-1.0*distanceToGroove4_1FromMiddleLength,prismSide/2.0-lengthGrooveBox4_1/2.0-trapz4_2Depth/2.0-trapz4_2Depth/2.0-lengthGroove4_3/2.0,groovesDownToFloor);
  groove4_3Trans2->RegisterYourself();


  //segment 4_4

  TGeoCombiTrans *trapz4_4Trans1 = new TGeoCombiTrans("trapz4_4Trans1",distanceToGroove4_1FromMiddleLength,prismSide/2.0-lengthGrooveBox4_1/2.0-trapz4_2Depth/2.0-trapz4_2Depth/2.0-lengthGroove4_3/2.0-lengthGroove4_3/2.0-trapz4_4Depth/2.0,groovesDownToFloor,flip1_2);
  trapz4_4Trans1->RegisterYourself();

  TGeoCombiTrans *trapz4_4Trans2 = new TGeoCombiTrans("trapz4_4Trans2",-1.0*distanceToGroove4_1FromMiddleLength,prismSide/2.0-lengthGrooveBox4_1/2.0-trapz4_2Depth/2.0-trapz4_2Depth/2.0-lengthGroove4_3/2.0-lengthGroove4_3/2.0-trapz4_4Depth/2.0,groovesDownToFloor,flip1_2);
  trapz4_4Trans2->RegisterYourself();

  //segment 4_4 curvy bits

  //segment 4c_1

  TGeoTranslation *groove4c_1Trans1 = new TGeoTranslation("groove4c_1Trans1",distanceToGroove4_1FromMiddleLength,prismSide/2.0-lengthGrooveBox4_1/2.0-trapz4_2Depth/2.0-trapz4_2Depth/2.0-lengthGroove4_3/2.0-lengthGroove4_3/2.0-trapz4_4Depth/2.0-trapz4_4Depth/2.0-lengthGroove4c_1/2.0,groovesDownToFloor);
  groove4c_1Trans1->RegisterYourself();


TGeoTranslation *groove4c_1Trans2 = new TGeoTranslation("groove4c_1Trans2",-1.0*distanceToGroove4_1FromMiddleLength,prismSide/2.0-lengthGrooveBox4_1/2.0-trapz4_2Depth/2.0-trapz4_2Depth/2.0-lengthGroove4_3/2.0-lengthGroove4_3/2.0-trapz4_4Depth/2.0-trapz4_4Depth/2.0-lengthGroove4c_1/2.0,groovesDownToFloor);
  groove4c_1Trans2->RegisterYourself();

  //segement 4c_2
  
  //trapz

  Double_t lateralShift4c_2 = 2.3/2 + .35/2;

  TGeoCombiTrans *trapz4c_2Trans1 = new TGeoCombiTrans("trapz4c_2Trans1",lateralShift4c_2,-1.0*prismSide/2.0,groovesDownToFloor,flip1_2);
  trapz4c_2Trans1->RegisterYourself();

  //groove

  Double_t lateralSlider4c_2 = 1.0;

  TGeoTranslation *groove4c_2Trans1 = new TGeoTranslation("groove4c_2Trans1",lateralShift4c_2*lateralSlider4c_2,-1.0*prismSide/2.0,groovesDownToFloor);
  groove4c_2Trans1->RegisterYourself();


  TGeoTranslation *groove4c_2Trans2 = new TGeoTranslation("groove4c_2Trans2",-1.0*lateralShift4c_2*lateralSlider4c_2,-1.0*prismSide/2.0,groovesDownToFloor);
  groove4c_2Trans2->RegisterYourself();

  //segment 4c_3

  TGeoRotation *seg4RotRight = new TGeoRotation("seg4RotRight",25,0,0);
  seg4RotRight->RegisterYourself();


  TGeoRotation *seg4RotLeft = new TGeoRotation("seg4RotLeft",335,0,0);
  seg4RotLeft->RegisterYourself();




  TGeoCombiTrans *groove4c_3Trans1 = new TGeoCombiTrans("groove4c_3Trans1",(rHolesOut+distanceToGroove4_1FromMiddleLength)/2.0,rHolesDown-cableHoleLength*.75,groovesDownToFloor,seg4RotRight);
  groove4c_3Trans1->RegisterYourself();


  TGeoCombiTrans *groove4c_3Trans2 = new TGeoCombiTrans("groove4c_3Trans2",-1.0*(rHolesOut+distanceToGroove4_1FromMiddleLength)/2.0,rHolesDown-cableHoleLength*.75,groovesDownToFloor,seg4RotLeft);
  groove4c_3Trans2->RegisterYourself();


  std::string shellBoolean = " ";
  shellBoolean += "(((BASE:rTrans";
  shellBoolean += "- BASE_SUBTRACTION)";
  shellBoolean += "+ (SLICE:rTrans))";
  shellBoolean += ":rBackTrans";
  shellBoolean += "- BASE:subSliceTrans";
  shellBoolean += "- (CABLE:sHolesTopLeftTrans)";
  shellBoolean += "- (CABLE:sHolesTopRightTrans))";
  shellBoolean += ":switchToZ";
  shellBoolean += "- (CABLE2:rHolesBottomLeftTrans)";
  shellBoolean += "- (CABLE2:rHolesBottomRightTrans)";
  shellBoolean += "- (groove2:groove2Trans)";
  shellBoolean += "- (groove2:groove2Trans2)";
  shellBoolean += "- (groove1_1:groove1_1Trans)";
  shellBoolean += "- (groove1_1:groove1_1Trans2)";
  shellBoolean += "- (groove3_1:groove3_1Trans)";
  shellBoolean += "- (groove3_1:groove3_1Trans2)";
  shellBoolean += "- (groove4_1:groove4_1Trans)";
  shellBoolean += "- (groove4_1:groove4_1Trans2)";
  shellBoolean += "- (trapz1_2:trapz1_2Trans1)";
  shellBoolean += "- (trapz1_2:trapz1_2Trans2)";
  shellBoolean += "- (groove1_3:groove1_3Trans1)";
  shellBoolean += "- (groove1_3:groove1_3Trans2)";
  shellBoolean += "- (trapz1_4:trapz1_4Trans1)";
  shellBoolean += "- (trapz1_4:trapz1_4Trans2)";
  shellBoolean += "- (groove1_5:groove1_5Trans1)";
  shellBoolean += "- (groove1_5:groove1_5Trans2)";
  shellBoolean += "- (trapz3_2:trapz3_2Trans1)";
  shellBoolean += "- (trapz3_2:trapz3_2Trans2)";
  shellBoolean += "- (groove3_3:groove3_3Trans1)";
  shellBoolean += "- (groove3_3:groove3_3Trans2)";
  shellBoolean += "- (trapz4_2:trapz4_2Trans1)";
  shellBoolean += "- (trapz4_2:trapz4_2Trans2)";
  shellBoolean += "- (groove4_3:groove4_3Trans1)";
  shellBoolean += "- (groove4_3:groove4_3Trans2)";
  shellBoolean += "- (trapz4_4:trapz4_4Trans1)";
  shellBoolean += "- (trapz4_4:trapz4_4Trans2) ";
  shellBoolean += "- (groove4c_3:groove4c_3Trans1)";
  shellBoolean += "- (groove4c_1:groove4c_1Trans1)";
  shellBoolean += "- (groove4c_2:groove4c_2Trans1)";
  shellBoolean += "- (groove4c_3:groove4c_3Trans2)";
  shellBoolean += "- (groove4c_1:groove4c_1Trans2)";
  shellBoolean += "- (groove4c_2:groove4c_2Trans2)";
  shellBoolean += "- (groove3c_2:groove3c_2Trans1)";
  shellBoolean += "- (groove3c_1:groove3c_1Trans1)";
  shellBoolean += "- (groove3c_2:groove3c_2Trans2)";
  shellBoolean += "- (groove3c_1:groove3c_1Trans2)";


  // Create composite shape

  TGeoCompositeShape *thing = new TGeoCompositeShape("thing", shellBoolean.c_str());
  TGeoVolume *thingVol = new TGeoVolume("thingVol", thing, med);


  vol->SetLineWidth(2);
  top->AddNode(thingVol,1);
  gGeoManager->CloseGeometry();
  gGeoManager->SetNsegments(30);
  top->Draw("ogl");
  TView *view = gPad->GetView();
  view->ShowAxis();
};
