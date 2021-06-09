#include <stdio.h>

void stringPrinter() {


  for (int i = 0; i<4; i++) {
    // char* cornerBool;
    TString cornerBool = Form("testRect - testTube:rectCornerTr%i", i + 1);
    std::cout << cornerBool.Data() << std::endl;
    // sprintf(var,"Tr%d", i+1);
    // std::cout << var << std::endl;

  }
}
