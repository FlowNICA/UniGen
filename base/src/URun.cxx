/**
 * UniGen - Common Format for Event Generators in High-energy and Nuclear
 * Physics Copyright (C) 2006 - 2019 GSI Helmholtzzentrum fuer
 * Schwerionenforschung GmbH
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>
using namespace std;

#include "TMath.h"

#include "URun.h"

//____________________________________________________________________
//
// URun
//
// Class for handling the run description.
// See the standard constructor and public accessors
//

//--------------------------------------------------------------------
URun::URun() : TNamed("run", "Run Header") {
  // Default constructor. Should not be used
  fGenerator = "";
  fComment = "";
  fDecayer = "";
  fAProj = fZProj = fATarg = fZTarg = fBWeight = fNEvents = 0;
  fPProj = fPTarg = fBMin = fBMax = fPhiMin = fPhiMax = fSigma = 0.;
  cout << "Warning: Default constructor of URun should not be used!" << endl;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
URun::URun(const char *generator, const char *comment, Int_t aProj, Int_t zProj,
           Double_t pProj, Int_t aTarg, Int_t zTarg, Double_t pTarg,
           Double_t bMin, Double_t bMax, Int_t bWeight, Double_t phiMin,
           Double_t phiMax, Double_t sigma, Int_t nEvents)
    : TNamed("run", "Run Header") {
  // Standard constructor
  fGenerator = generator;
  fComment = comment;
  fAProj = aProj;
  fZProj = zProj;
  fPProj = pProj;
  fATarg = aTarg;
  fZTarg = zTarg;
  fPTarg = pTarg;
  fBMin = bMin;
  fBMax = bMax;
  fBWeight = bWeight;
  fPhiMin = phiMin;
  fPhiMax = phiMax;
  fSigma = sigma;
  fNEvents = nEvents;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
URun::~URun() {
  // Destructor
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void URun::Print(Option_t *option) const {
  // Print all data members to the standard output
  cout << "--------------------------------------------------" << endl
       << "-I-                 Run Header                 -I-" << endl
       << "Generator                     : " << fGenerator << endl
       << "Comment                       : " << fComment << endl
       << "Decayer                       : " << fDecayer << endl
       << "Projectile mass               : " << fAProj << endl
       << "Projectile charge             : " << fZProj << endl
       << "Projectile momentum (AGeV/c)  : " << fPProj << endl
       << "Target mass                   : " << fATarg << endl
       << "Target charge                 : " << fZTarg << endl
       << "Target momentum (AGeV/c)      : " << fPTarg << endl
       << "Minimal impact parameter (fm) : " << fBMin << endl
       << "Maximal impact parameter (fm) : " << fBMax << endl
       << "Impact parameter weighting    : " << fBWeight << endl
       << "Minimal azimuthal angle (rad) : " << fPhiMin << endl
       << "Maximal azimuthal angle (rad) : " << fPhiMax << endl
       << "Cross-section (mb)            : " << fSigma << endl
       << "Requested number of events    : " << fNEvents << endl
       << "--------------------------------------------------" << endl;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
Double_t URun::GetProjectileEnergy() {
  // Get the projectile energy
  Double_t mProt = 0.938272029;
  Double_t mNeut = 0.939565360;
  Double_t mPion = 0.13957018;
  Double_t eProj = 0.;
  if (fAProj > 0) // nucleus
    eProj = fZProj * TMath::Sqrt(fPProj * fPProj + mProt * mProt) +
            (fAProj - fZProj) * TMath::Sqrt(fPProj * fPProj + mNeut * mNeut);
  else if (fAProj == 0) // photon
    eProj = fPProj;
  else if (fAProj == -1) // pion
    eProj = TMath::Sqrt(fPProj * fPProj + mPion * mPion);
  else
    cout << "Warning:: URun: Projectile mass " << fAProj << " not valid! "
         << endl;
  return eProj;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
Double_t URun::GetTargetEnergy() {
  // Get the target energy
  Double_t mProt = 0.938272029;
  Double_t mNeut = 0.939565360;
  Double_t mPion = 0.13957018;
  Double_t eTarg = 0.;
  if (fATarg > 0) // nucleus
    eTarg = fZTarg * TMath::Sqrt(fPTarg * fPTarg + mProt * mProt) +
            (fATarg - fZTarg) * TMath::Sqrt(fPTarg * fPTarg + mNeut * mNeut);
  else if (fAProj == 0) // photon
    eTarg = fPTarg;
  else if (fAProj == -1) // pion
    eTarg = TMath::Sqrt(fPTarg * fPTarg + mPion * mPion);
  else
    cout << "Warning:: URun: Target mass " << fATarg << " not valid! " << endl;
  return eTarg;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
Double_t URun::GetNNSqrtS() {
  // Get the cm energy
  Double_t eSum = TMath::Sqrt(fPTarg * fPTarg + 0.938272029 * 0.938272029) +
                  TMath::Sqrt(fPProj * fPProj + 0.938272029 * 0.938272029);
  Double_t pSum = Double_t(fPProj + fPTarg);
  Double_t ecm = TMath::Sqrt(eSum * eSum - pSum * pSum);
  return ecm;
}
//--------------------------------------------------------------------

Double_t URun::GetSqrtS() {
  // Get the cm energy
  Double_t eSum = GetProjectileEnergy() + GetTargetEnergy();
  Double_t pSum = Double_t(fAProj) * fPProj + Double_t(fATarg) * fPTarg;
  Double_t ecm = TMath::Sqrt(eSum * eSum - pSum * pSum);
  return ecm;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
Double_t URun::GetBetaCM() {
  // Get cm velocity
  Double_t eSum = GetProjectileEnergy() + GetTargetEnergy();
  Double_t pSum = Double_t(fAProj) * fPProj + Double_t(fATarg) * fPTarg;
  return pSum / eSum;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
Double_t URun::GetGammaCM() {
  // Get cm gamma factor
  Double_t betaCM = GetBetaCM();
  return 1. / TMath::Sqrt(1. - betaCM * betaCM);
}
//--------------------------------------------------------------------

ClassImp(URun);
