/*
Program Name: AHU Fault Diagnosis
Author: Khaled ELKarazle
Date: 26-03-2019
Description: This program is to find and fix AHU flaws & faulties by taking 
*/

//importing all the necessary libraries
#include "pch.h"
#include <iostream> 
#include <math.h>

  using namespace std;
//function below to get the users value
double getValues(double & tsa, double & prf, double & psf, double & nrf, double & nsf, double & ucc, double & toa, double & tma, double & fsa) {

  do {
    cout << "Please Input the Supply Air Temperature(C):";

    cin >> tsa;
  } while (tsa > 50.0 || tsa < -30.0);

  do {
    cout << "Please Input the Returned Fan Power(W):";
    cin >> prf;
  } while (prf < 0.0);

  do {
    cout << "Please Input the Fan Power (W):";
    cin >> psf;
  } while (psf < 0.0);

  do {
    cout << "Please Input the Returned Fan Speed Control Signal(%):";
    cin >> nrf;
  } while (nrf < 0.0 || nrf > 100.0);

  do {
    cout << "Please Input the Fan Speed Control Signal (%):";
    cin >> nsf;
  } while (nsf < 0.0 || nsf > 100.0);

  do {
    cout << "Please Input the Cooling Coil Valve Control Signal (%):";
    cin >> ucc;
  } while (ucc < 0.0 || ucc > 100.0);

  do {
    cout << "Please Input the Outdoor Air Temperature (C):";
    cin >> toa;
  } while (toa > 58.0 || toa < -30.0);

  do {
    cout << "Please Input the Mixed Air Temperature(C):";
    cin >> tma;
  } while (tma > 58.0 || tma < -30.0);

  do {
    cout << "Please Input the Air Flow Rate(m^3/min):";
    cin >> fsa;
  } while (fsa < 0.0 || fsa > 1000.0);

  return tsa, prf, psf, nrf, nsf, ucc, toa, tma, fsa;
}

//function below to determine the condition of the AHU according to the user input
//all outputs are following the decision tree provided

double getAHUCondition(double & Tsa, double & Prf, double & Psf, double & Nrf, double & Nsf, double & Ucc, double & Toa, double & Tma, double & Fsa) {
  if (isgreaterequal(Tsa, 19.2)) {
    cout << "CCVSFC 474 / 474 Normal" << endl;
  } else if (isgreaterequal(Prf, 182.0)) {
    if (isgreaterequal(Ucc, 64.3)) {
      if (isless(Ucc, 65.0)) {
        if (isgreaterequal(Ucc, 65.0)) {
          cout << "CCVS65% 335 / 335 Cooling Coil Valve Stuck at 65% Opening" << endl;
        } else {
          cout << "HCVL 11/24 Heating Coil Valv Leakage" << endl;
        }
      } else if (isgreaterequal(Toa, 27.2)) {
        if (isless(Psf, 1466.0)) {
          cout << "CCVS65% 12/12 Cooling Coil Valve Stuck at 65% Opening" << endl;
        } else if (isgreaterequal(Ucc, 66.5)) {
          cout << "EADSFC 141/142 Exhaust air damper stuck at fully closed " << endl;
        } else {
          if (isless(Prf, 391)) {
            cout << "EADSFC 13/13 Exhaust air damper stuck at fully closed " << endl;
          } else {
            cout << "Normal 22/22 Fault Free" << endl;
          }
        }
      } else if (isgreaterequal(Tsa, 13.2)) {
        cout << "CCVS65% 17/26 Cooling coil valve stuck at 65% opening" << endl;
      } else {
        cout << "HCVL 204/217 Heating coil valve leakage" << endl;
      }
    } else if (isless(Nsf, 80.4)) {
      if (isless(Tma, 22.9)) {
        if (isless(Nsf, 71.2)) {
          if (islessequal(Fsa, 54.7)) {
            cout << "DLBSF 303 / 303 AHU duct leakage before supply fan" << endl;
          } else if (isless(Nsf, 66.0)) {
            if (isgreaterequal(Ucc, 33.6)) {
              cout << "HCVL 27/28 Heating coil valve leakage" << endl;
            } else {
              cout << "Normal 40/40 Fault Free" << endl;
            }
          }
        } else if (isgreaterequal(Ucc, 51.2)) {
          cout << "HCVL 45/50 Heating coil valve leakage" << endl;
        } else {
          cout << "Normal 66/76 Fault Free" << endl;
        }
      } else if (isgreaterequal(Toa, 30.2)) {
        cout << "EADSFC 55/55 Exhaust air damper stuck at fully closed" << endl;
      } else if (isless(Tma, 23.3)) {
        if (isgreaterequal(Tma, 23.1)) {
          if (isgreaterequal(Ucc, 42.4)) {
            cout << "EADSFC 60/74 Exhaust air damper stuck at fully closed" << endl;
          } else if (isless(Toa, 23.4)) {
            cout << "EADSFC 12/12 Exhaust air damper stuck at fully closed" << endl;
          } else {
            cout << "Normal 35/35 Fault Free" << endl;
          }
        } else {
          cout << "Normal 31/40 Fault Free" << endl;
        }
      } else if (isgreaterequal(Toa, 24.5)) {
        if (isgreaterequal(Ucc, 59.0)) {
          if (isless(Nrf, 61.6)) {
            cout << "HCVL 24/24 Heating coil valve leakage" << endl;
          } else {
            cout << "Normal 107/113 Fault Free" << endl;
          }
        } else {
          cout << "Normal 371/376 Fault Free" << endl;
        }
      } else {
        cout << "OADSFC 12/19 Outdoor air damper stuck at fully closed" << endl;
      }
    } else {
      cout << "OADSFC 233/233 Outdoor air damper stuck at fully closed" << endl;
    }
  } else if (isless(Prf, 77.9)) {
    cout << "RFCF 285 / 285 Return fan completely failed " << endl;
  } else {
    cout << "RFF30% 261 / 261 Return fan fixed at 30% speed" << endl;
  }
  return 0;
}

int main() {
  //declare input variables
  double tsa, prf, psf, nrf, nsf, ucc, toa, tma, fsa;
  //welcoming message
  cout << "Air Handling Unit Fault Diagnosis System" << endl;
  //get user values which will be sent to getValues() function
  getValues(tsa, prf, psf, nrf, nsf, ucc, toa, tma, fsa);
  //determine the condition according to user input using getAHUCondition() function
  getAHUCondition(tsa, prf, psf, nrf, nsf, ucc, toa, tma, fsa);
  system("Pause");
}