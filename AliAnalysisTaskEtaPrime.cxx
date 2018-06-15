#include "TChain.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TCanvas.h"
#include "TMath.h"

#include <AliAnalysisTask.h>
#include <AliAnalysisManager.h>
#include <AliVEvent.h>
#include <AliInputEventHandler.h>
#include <AliESDVertex.h>
#include <AliESDEvent.h>
#include <AliESDInputHandler.h>
#include <AliESDtrackCuts.h>
#include <AliVVZERO.h>
#include "AliPIDResponse.h"
#include <TLorentzVector.h>

#include "AliAnalysisTaskEtaPrime.h"

class AliAnalysisTaskEtaPrime;
using namespace std;

ClassImp(AliAnalysisTaskEtaPrime)

//________________________________________________________________________
AliAnalysisTaskEtaPrime::AliAnalysisTaskEtaPrime()
: AliAnalysisTaskSE()
,fEvent(0)
,fOutputList(0)
,fOutputEvent(0)
,fOutputV0(0)
,fOutputV0legneg(0)
,fOutputV0legpos(0)
,fOutputV0pair(0)
,fEventStat(0)
,fNEvents(0)
,fVertexZ(0)
,fHistV0Pt(0)  
,fHistV0Eta(0) 
,fHistV0Phi(0)
,fHistV0R(0)
,fHistV0Z(0)
,fHistV0RvsZ(0)
,fHistV0CosPA(0)
,fHistV0Chi2(0)
,fHistV0Psi_pair(0)
,fHistV0Mass(0)
,fHistV0E(0)
,fHistV0ArmPod(0)
,fHistPt_neg(0)
,fHistEta_neg(0)
,fHistPhi_neg(0)
,fHistDCAxy_neg(0)
,fHistDCAz_neg(0)
,fHistITSncls_neg(0)
,fHistITSchi2_neg(0)
,fHistTPCncls_neg(0)
,fHistTPCncr_neg(0)
,fHistTPCchi2_neg(0)
,fHistTPCnSigmaEle_neg(0)
,fHistTPCnSigmaPio_neg(0)
,fHistdEdxneg(0)
,fHistdEdxnegfin(0)
,fHistPt_pos(0)
,fHistEta_pos(0)
,fHistPhi_pos(0)
,fHistDCAxy_pos(0)
,fHistDCAz_pos(0)
,fHistITSncls_pos(0)
,fHistITSchi2_pos(0)
,fHistTPCncls_pos(0)
,fHistTPCncr_pos(0)
,fHistTPCchi2_pos(0)
,fHistTPCnSigmaEle_pos(0)
,fHistTPCnSigmaPio_pos(0)
,fHistdEdxpos(0)
,fHistdEdxposfin(0)
,fHistV0InvMassini(0)
,fHistV0InvMass_pTini(0)
,fHistV0EnergyAsymmetryini(0)
,fHistV0EnAscut(0)
,fHistV0InvMass_EnAsini(0)
,fHistV0Mass_pT12(0)
,fHistV0MassAngle(0)
,fHistV0InvMass1(0)
,fHistV0InvMass2(0)
,fHistV0InvMass_pT2(0)
,fHistV0InvMass_EnAs2(0)
,fHistV0InvMass3(0)
,fHistV0InvMass_pT3(0)
,fHistV0InvMass4(0)
,fHistV0InvMass_pT4(0)
,fHistV0InvMass5(0)
,fHistV0InvMass6(0)
,fPIDResponse(0)
,fTrackCuts(0)
{
    // default constructor, don't allocate memory here!
    // this is used by root for IO purposes, it needs to remain empty
}

//________________________________________________________________________
AliAnalysisTaskEtaPrime::AliAnalysisTaskEtaPrime(const char* name)
: AliAnalysisTaskSE(name)
,fEvent(0)
,fOutputList(0)
,fOutputEvent(0)
,fOutputV0(0)
,fOutputV0legneg(0)
,fOutputV0legpos(0)
,fOutputV0pair(0)
,fEventStat(0)
,fNEvents(0)
,fVertexZ(0)
,fHistV0Pt(0)
,fHistV0Eta(0)
,fHistV0Phi(0)
,fHistV0R(0)
,fHistV0Z(0)
,fHistV0RvsZ(0)
,fHistV0CosPA(0)
,fHistV0Chi2(0)
,fHistV0Psi_pair(0)
,fHistV0Mass(0)
,fHistV0E(0)
,fHistV0ArmPod(0)
,fHistPt_neg(0)
,fHistEta_neg(0)
,fHistPhi_neg(0)
,fHistDCAxy_neg(0)
,fHistDCAz_neg(0)
,fHistITSncls_neg(0)
,fHistITSchi2_neg(0)
,fHistTPCncls_neg(0)
,fHistTPCncr_neg(0)
,fHistTPCchi2_neg(0)
,fHistTPCnSigmaEle_neg(0)
,fHistTPCnSigmaPio_neg(0)
,fHistdEdxneg(0)
,fHistdEdxnegfin(0)
,fHistPt_pos(0)
,fHistEta_pos(0)
,fHistPhi_pos(0)
,fHistDCAxy_pos(0)
,fHistDCAz_pos(0)
,fHistITSncls_pos(0)
,fHistITSchi2_pos(0)
,fHistTPCncls_pos(0)
,fHistTPCncr_pos(0)
,fHistTPCchi2_pos(0)
,fHistTPCnSigmaEle_pos(0)
,fHistTPCnSigmaPio_pos(0)
,fHistdEdxpos(0)
,fHistdEdxposfin(0)
,fHistV0InvMassini(0)
,fHistV0InvMass_pTini(0)
,fHistV0EnergyAsymmetryini(0)
,fHistV0EnAscut(0)
,fHistV0InvMass_EnAsini(0)
,fHistV0Mass_pT12(0)
,fHistV0MassAngle(0)
,fHistV0InvMass1(0)
,fHistV0InvMass2(0)
,fHistV0InvMass_pT2(0)
,fHistV0InvMass_EnAs2(0)
,fHistV0InvMass3(0)
,fHistV0InvMass_pT3(0)
,fHistV0InvMass4(0)
,fHistV0InvMass_pT4(0)
,fHistV0InvMass5(0)
,fHistV0InvMass6(0)
,fPIDResponse(0)
,fTrackCuts(0)
{
    // constructor
    DefineInput(0, TChain::Class());    // a 'chain' of events created by the analysis manager automatically
    DefineOutput(1, TList::Class());    // define the ouptut of the analysis: in this case it's a list of histograms
    // one can add more output objects by calling DefineOutput(2, classname::Class())
    // make sure to connect them properly in AddTask and to call PostData() for all of them!
    
}

//________________________________________________________________________
AliAnalysisTaskEtaPrime::~AliAnalysisTaskEtaPrime()
{
    // destructor
    if(fOutputList) {
        delete fOutputList;
    }
}

//________________________________________________________________________
Double_t AliAnalysisTaskEtaPrime::Psi_pair(AliESDtrack *neg, AliESDtrack *pos)
{
	if (!neg || !pos) return -1;
	Double_t x = TMath::ACos((neg->Px()*pos->Px() + neg->Py()*pos->Py() + neg->Pz()*pos->Pz()) / (neg->P()*pos->P()));
	Double_t t = neg->Eta() - pos->Eta();

	return TMath::ASin(t / x);
}

//________________________________________________________________________
void AliAnalysisTaskEtaPrime::UserCreateOutputObjects()
{
    // Called once at the start of the analysis
    
    // retrieve PID object from the input handler
    AliAnalysisManager *man=AliAnalysisManager::GetAnalysisManager();
    AliInputEventHandler* inputHandler = (AliInputEventHandler*) (man->GetInputEventHandler());
    fPIDResponse = inputHandler->GetPIDResponse();
    
    // create output lists
    
    fOutputList = new TList();
    fOutputList->SetName("Output");
    fOutputList->SetOwner(kTRUE); // the list is owner of all objects it contains and will delete them
    
    fOutputEvent = new TList();
    fOutputEvent->SetName("Event");
    fOutputEvent->SetOwner(kTRUE);
    
    fOutputV0 = new TList();
    fOutputV0->SetName("V0");
    fOutputV0->SetOwner(kTRUE);
    
    fOutputV0legneg = new TList();
    fOutputV0legneg->SetName("V0neg");
    fOutputV0legneg->SetOwner(kTRUE);
    
    fOutputV0legpos = new TList();
    fOutputV0legpos->SetName("V0pos");
    fOutputV0legpos->SetOwner(kTRUE);
    
    fOutputV0->Add(fOutputV0legneg);
    fOutputV0->Add(fOutputV0legpos);
    
    fOutputV0pair = new TList();
    fOutputV0pair->SetName("V0pair");
    fOutputV0pair->SetOwner(kTRUE);
    
    // create output histograms
    // event histos
    
    fEventStat = new TH1I("fEventStat", "Event statistics", kNbinsEvent, 0, kNbinsEvent);
    fEventStat->GetXaxis()->SetBinLabel(1,"After Phys. Sel. and trigger");
    fEventStat->GetXaxis()->SetBinLabel(2,"Vertex filter");
    fEventStat->GetXaxis()->SetBinLabel(3,"Vertex res. and disp.");
    fOutputEvent->Add(fEventStat);

    fNEvents = new TH1F("fNEvents", "N of events",1,0.,1.);
    fOutputEvent->Add(fNEvents);
    
    fVertexZ = new TH1F("fVertexZ", "Vertex Z distribution", 100, -15., 15.);
    fOutputEvent->Add(fVertexZ);
    
    // V0's track histos (negative leg)
    
    fHistPt_neg = new TH1F("fHistPt_neg", "P_{T} distribution", 100, 0., 10.);
    fHistPt_neg->GetXaxis()->SetTitle("P_{T} (GeV/c)");
    fHistPt_neg->GetYaxis()->SetTitle("dN/dP_{T} (c/GeV)");
    fOutputV0legneg->Add(fHistPt_neg);
    
    fHistEta_neg = new TH1F("fHistEta_neg", "#eta distribution", 200, -2., 2.);
    fHistEta_neg->GetXaxis()->SetTitle("#eta");
    fHistEta_neg->GetYaxis()->SetTitle("N of tracks");
    fOutputV0legneg->Add(fHistEta_neg);
    
    fHistPhi_neg = new TH1F("fHistPhi_neg", "#varphi distribution", 160, 0., 2*(TMath::Pi()));
    fHistPhi_neg->GetXaxis()->SetTitle("#varphi");
    fHistPhi_neg->GetYaxis()->SetTitle("N of tracks");
    fOutputV0legneg->Add(fHistPhi_neg);
    
    fHistDCAxy_neg = new TH1F("fHistDCAxy_neg","DCA_{xy} distribution",400, -2., 2.);
    fHistDCAxy_neg->GetXaxis()->SetTitle("DCA_{xy}");
    fHistDCAxy_neg->GetYaxis()->SetTitle("N of tracks");
    fOutputV0legneg->Add(fHistDCAxy_neg);
    
    fHistDCAz_neg = new TH1F("fHistDCAz_neg","DCA_{z} distribution",800, -4., 4.);
    fHistDCAz_neg->GetXaxis()->SetTitle("DCA_{z}");
    fHistDCAz_neg->GetYaxis()->SetTitle("N of tracks");
    fOutputV0legneg->Add(fHistDCAz_neg);
    
    fHistITSncls_neg = new TH1I("fHistITSncls_neg","N of clusters ITS",10, -0.5, 9.5);
    fHistITSncls_neg->GetXaxis()->SetTitle("N of clusters ITS");
    fHistITSncls_neg->GetYaxis()->SetTitle("N of tracks");
    fOutputV0legneg->Add(fHistITSncls_neg);
    
    fHistITSchi2_neg = new TH1F("fHistITSchi2_neg","ITS #chi^{2}",100, 0., 5.);
    fHistITSchi2_neg->GetXaxis()->SetTitle("ITS #chi^{2}");
    fHistITSchi2_neg->GetYaxis()->SetTitle("N of tracks");
    fOutputV0legneg->Add(fHistITSchi2_neg);
    
    fHistTPCncls_neg = new TH1I("fHistTPCncls_neg","N of clusters TPC",200, -0.5, 199.5);
    fHistTPCncls_neg->GetXaxis()->SetTitle("N of clusters TPC");
    fHistTPCncls_neg->GetYaxis()->SetTitle("N of tracks");
    fOutputV0legneg->Add(fHistTPCncls_neg);
    
    fHistTPCncr_neg = new TH1I("fHistTPCncr_neg","N of crossed rows TPC",200, -0.5, 199.5);
    fHistTPCncr_neg->GetXaxis()->SetTitle("N of crossed rows TPC");
    fHistTPCncr_neg->GetYaxis()->SetTitle("N of tracks");
    fOutputV0legneg->Add(fHistTPCncr_neg);
    
    fHistTPCchi2_neg = new TH1F("fHistTPCchi2_neg","TPC #chi^{2}",100, 0., 5.);
    fHistTPCchi2_neg->GetXaxis()->SetTitle("TPC #chi^{2}");
    fHistTPCchi2_neg->GetYaxis()->SetTitle("N of tracks");
    fOutputV0legneg->Add(fHistTPCchi2_neg);
    
    fHistTPCnSigmaEle_neg = new TH2F("fHistTPCnSigmaEle_neg","TPC n sigma ele neg leg", 500, 0., 10., 100, -5., 5.);
    fHistTPCnSigmaEle_neg->GetXaxis()->SetTitle("p (GeV/#it{c})");
    fHistTPCnSigmaEle_neg->GetYaxis()->SetTitle("TPCn#sigma_{ele}");
    fOutputV0legneg->Add(fHistTPCnSigmaEle_neg);
    
    fHistTPCnSigmaPio_neg = new TH2F("fHistTPCnSigmaPio_neg","TPC n sigma pio neg leg", 500, 0., 10., 150, 0., 15.);
    fHistTPCnSigmaPio_neg->GetXaxis()->SetTitle("p (GeV/#it{c})");
    fHistTPCnSigmaPio_neg->GetYaxis()->SetTitle("TPCn#sigma_{pio}");
    fOutputV0legneg->Add(fHistTPCnSigmaPio_neg);

    fHistdEdxneg = new TH2F("fHistdEdxneg", "dE/dx for negative leg before PID cuts", 1000,0,10, 400,0,200);
    fHistdEdxneg->GetXaxis()->SetTitle("p(GeV/c)");    
    fHistdEdxneg->GetYaxis()->SetTitle("TPC dE/dx (a.u.)");
    fOutputV0legneg->Add(fHistdEdxneg);

    fHistdEdxnegfin = new TH2F("fHistdEdxnegfin", "dE/dx for negative leg after PID cuts", 1000,0,10, 400,0,200);
    fHistdEdxnegfin->GetXaxis()->SetTitle("p(GeV/c)");    
    fHistdEdxnegfin->GetYaxis()->SetTitle("TPC dE/dx (a.u.)");
    fOutputV0legneg->Add(fHistdEdxnegfin);
    
    // V0's track histos (positive leg)
    
    fHistPt_pos = new TH1F("fHistPt_pos", "P_{T} distribution", 100, 0., 10.);
    fHistPt_pos->GetXaxis()->SetTitle("P_{T} (GeV/c)");
    fHistPt_pos->GetYaxis()->SetTitle("dN/dP_{T} (c/GeV)");
    fOutputV0legpos->Add(fHistPt_pos);
    
    fHistEta_pos = new TH1F("fHistEta_pos", "#eta distribution", 200, -2., 2.);
    fHistEta_pos->GetXaxis()->SetTitle("#eta");
    fHistEta_pos->GetYaxis()->SetTitle("N of tracks");
    fOutputV0legpos->Add(fHistEta_pos);
    
    fHistPhi_pos = new TH1F("fHistPhi_pos", "#varphi distribution", 160, 0., 2*(TMath::Pi()));
    fHistPhi_pos->GetXaxis()->SetTitle("#varphi");
    fHistPhi_pos->GetYaxis()->SetTitle("N of tracks");
    fOutputV0legpos->Add(fHistPhi_pos);
    
    fHistDCAxy_pos = new TH1F("fHistDCAxy_pos","DCA_{xy} distribution",400, -2., 2.);
    fHistDCAxy_pos->GetXaxis()->SetTitle("DCA_{xy}");
    fHistDCAxy_pos->GetYaxis()->SetTitle("N of tracks");
    fOutputV0legpos->Add(fHistDCAxy_pos);
    
    fHistDCAz_pos = new TH1F("fHistDCAz_pos","DCA_{z} distribution",800, -4., 4.);
    fHistDCAz_pos->GetXaxis()->SetTitle("DCA_{z}");
    fHistDCAz_pos->GetYaxis()->SetTitle("N of tracks");
    fOutputV0legpos->Add(fHistDCAz_pos);
    
    fHistITSncls_pos = new TH1I("fHistITSncls_pos","N of clusters ITS",10, -0.5, 9.5);
    fHistITSncls_pos->GetXaxis()->SetTitle("N of clusters ITS");
    fHistITSncls_pos->GetYaxis()->SetTitle("N of tracks");
    fOutputV0legpos->Add(fHistITSncls_pos);
    
    fHistITSchi2_pos = new TH1F("fHistITSchi2_pos","ITS #chi^{2}",100, 0., 5.);
    fHistITSchi2_pos->GetXaxis()->SetTitle("ITS #chi^{2}");
    fHistITSchi2_pos->GetYaxis()->SetTitle("N of tracks");
    fOutputV0legpos->Add(fHistITSchi2_pos);
    
    fHistTPCncls_pos = new TH1I("fHistTPCncls_pos","N of clusters TPC",200, -0.5, 199.5);
    fHistTPCncls_pos->GetXaxis()->SetTitle("N of clusters TPC");
    fHistTPCncls_pos->GetYaxis()->SetTitle("N of tracks");
    fOutputV0legpos->Add(fHistTPCncls_pos);
    
    fHistTPCncr_pos = new TH1I("fHistTPCncr_pos","N of crossed rows TPC",200, -0.5, 199.5);
    fHistTPCncr_pos->GetXaxis()->SetTitle("N of crossed rows TPC");
    fHistTPCncr_pos->GetYaxis()->SetTitle("N of tracks");
    fOutputV0legpos->Add(fHistTPCncr_pos);
    
    fHistTPCchi2_pos = new TH1F("fHistTPCchi2_pos","TPC #chi^{2}",100, 0., 5.);
    fHistTPCchi2_pos->GetXaxis()->SetTitle("TPC #chi^{2}");
    fHistTPCchi2_pos->GetYaxis()->SetTitle("N of tracks");
    fOutputV0legpos->Add(fHistTPCchi2_pos);
    
    fHistTPCnSigmaEle_pos = new TH2F("fHistTPCnSigmaEle_pos","TPC n sigma ele pos leg", 500, 0., 10., 100, -5., 5.);
    fHistTPCnSigmaEle_pos->GetXaxis()->SetTitle("p (GeV/#it{c})");
    fHistTPCnSigmaEle_pos->GetYaxis()->SetTitle("TPCn#sigma_{ele}");
    fOutputV0legpos->Add(fHistTPCnSigmaEle_pos);
    
    fHistTPCnSigmaPio_pos = new TH2F("fHistTPCnSigmaPio_pos","TPC n sigma pio pos leg", 500, 0., 10., 150, 0., 15.);
    fHistTPCnSigmaPio_pos->GetXaxis()->SetTitle("p (GeV/#it{c})");
    fHistTPCnSigmaPio_pos->GetYaxis()->SetTitle("TPCn#sigma_{pio}");
    fOutputV0legpos->Add(fHistTPCnSigmaPio_pos);

    fHistdEdxpos = new TH2F("fHistdEdxpos", "dE/dx for positive leg before PID cuts", 1000,0,10, 400,0,200);
    fHistdEdxpos->GetXaxis()->SetTitle("p(GeV/c)");    
    fHistdEdxpos->GetYaxis()->SetTitle("TPC dE/dx (a.u.)");
    fOutputV0legpos->Add(fHistdEdxpos);

    fHistdEdxposfin = new TH2F("fHistdEdxposfin", "dE/dx for positive leg after PID cuts", 1000,0,10, 400,0,200);
    fHistdEdxposfin->GetXaxis()->SetTitle("p(GeV/c)");    
    fHistdEdxposfin->GetYaxis()->SetTitle("TPC dE/dx (a.u.)");
    fOutputV0legpos->Add(fHistdEdxposfin);
    
    // V0s histos
    
    fHistV0Pt = new TH1F("fHistV0Pt", "V0 P_{T} distribution", 100, 0., 10.);
    fHistV0Pt->GetXaxis()->SetTitle("P_{T} (GeV/c)");
    fHistV0Pt->GetYaxis()->SetTitle("dN/dP_{T} (c/GeV)");
    fOutputV0->Add(fHistV0Pt);
    
    fHistV0Eta = new TH1F("fHistV0Eta", "V0 #eta distribution", 200, -2., 2.);
    fHistV0Eta->GetXaxis()->SetTitle("#eta");
    fHistV0Eta->GetYaxis()->SetTitle("N of V0s");
    fOutputV0->Add(fHistV0Eta);
    
    fHistV0Phi = new TH1F("fHistV0Phi", "V0 #varphi distribution", 320, 0, 2*(TMath::Pi()));
    fHistV0Phi->GetXaxis()->SetTitle("#varphi");
    fHistV0Phi->GetYaxis()->SetTitle("N of V0s");
    fOutputV0->Add(fHistV0Phi);

	fHistV0R = new TH1F("fHistV0R", "V0 radius distribution", 800, 0, 200);
	fHistV0R->GetXaxis()->SetTitle("R_{conv}(cm)");
	fHistV0R->GetYaxis()->SetTitle("N of V0s");
	fOutputV0->Add(fHistV0R);

	fHistV0Z = new TH1F("fHistV0Z", "V0 Z coordinate distribution", 1000, -250, 250);
	fHistV0Z->GetXaxis()->SetTitle("Z_{conv}(cm)");
	fHistV0Z->GetYaxis()->SetTitle("N of V0s");
	fOutputV0->Add(fHistV0Z);

	fHistV0RvsZ = new TH2F("fHistV0RvsZ", "V0 R vs. |Z| coordinate distribution", 1000, 0, 250, 800, 0, 200);
	fHistV0RvsZ->GetXaxis()->SetTitle("|Z_{conv}|(cm)");
	fHistV0RvsZ->GetYaxis()->SetTitle("R_{conv}(cm)");
	fOutputV0->Add(fHistV0RvsZ);

	fHistV0CosPA = new TH1F("fHistV0CosPA", "V0 cos(pointing angle) distribution", 100, 0.75, 1);
	fHistV0CosPA->GetXaxis()->SetTitle("cos(pointing angle)");
	fHistV0CosPA->GetYaxis()->SetTitle("N of V0s");
	fOutputV0->Add(fHistV0CosPA);

	fHistV0Chi2 = new TH1F("fHistV0Chi2", "V0 Chi2 distribution", 40, 0, 40);
	fHistV0Chi2->GetXaxis()->SetTitle("#chi^{2}");
	fHistV0Chi2->GetYaxis()->SetTitle("N of V0s");
	fOutputV0->Add(fHistV0Chi2);

	fHistV0Psi_pair = new TH1F("fHistPsi_pair", "V0 #Psi_{pair} distribution", 200, -1, 1);
	fHistV0Psi_pair->GetXaxis()->SetTitle("#Psi_{pair}");
	fHistV0Psi_pair->GetYaxis()->SetTitle("N of V0s");
	fOutputV0->Add(fHistV0Psi_pair);

    fHistV0Mass = new TH1F("fHistV0Mass", "V0 mass distribution", 5000, 0., 5.);
    fHistV0Mass->GetXaxis()->SetTitle("GeV/#it{c}^{2}");
    fHistV0Mass->GetYaxis()->SetTitle("N of V0s");
    fOutputV0->Add(fHistV0Mass);

    fHistV0E = new TH1F("fHistV0E", "V0 E distribution", 5000, 0., 5.);
    fHistV0E->GetXaxis()->SetTitle("GeV/#it{c}^{2}");
    fHistV0E->GetYaxis()->SetTitle("N of V0s");
    fOutputV0->Add(fHistV0E);
    
    fHistV0ArmPod = new TH2F("fHistV0ArmPod","Armenteros-Podolanski plot", 200, -1., 1., 250, 0., 0.25);
    fHistV0ArmPod->GetXaxis()->SetTitle("#alpha =  (p_{L}^{+} #minus p_{L}^{#minus}) / (p_{L}^{+} + p_{L}^{#minus})");
    fHistV0ArmPod->GetYaxis()->SetTitle("q_{T} (GeV/#it{c})");
    fOutputV0->Add(fHistV0ArmPod);
	

    // pair histos

	fHistV0InvMassini = new TH1F("fHistV0InvMassini", "Inv. mass before p_{T} cuts", 1200, 0., 1.2);
	fHistV0InvMassini->GetXaxis()->SetTitle("inv. mass, GeV/#it{c}^{2}");
	fHistV0InvMassini->GetYaxis()->SetTitle("N of pairs");
	fOutputV0pair->Add(fHistV0InvMassini);

	fHistV0InvMass_pTini = new TH2F("fHistV0InvMass_pTini", "Inv. mass vs P_{T} before p_{T} cuts", 1200, 0., 1.2, 1000, 0., 10.);
	fHistV0InvMass_pTini->GetXaxis()->SetTitle("inv. mass, GeV/#it{c}^{2}");
	fHistV0InvMass_pTini->GetYaxis()->SetTitle("P_{T} (GeV/#it{c})");
	fOutputV0pair->Add(fHistV0InvMass_pTini);

	fHistV0EnergyAsymmetryini = new TH1F("fHistV0EnergyAsymmetryini", "energy asymmetry #lambda before p_{T} cuts", 100, 0., 1.);
	fHistV0EnergyAsymmetryini->GetXaxis()->SetTitle("#lambda = |(E_{1} #minus E_{2}) / E_{1} + E_{2})|");
	fHistV0EnergyAsymmetryini->GetYaxis()->SetTitle("N of pairs");
	fOutputV0pair->Add(fHistV0EnergyAsymmetryini);

	fHistV0EnAscut = new TH1F("fHistV0EnAscut", "energy asymmetry #lambda after p_{T} = 3 GeV/c and m < 200 MeV/c^{2} cuts", 100, 0., 1.);
	fHistV0EnAscut->GetXaxis()->SetTitle("#lambda = |(E_{1} #minus E_{2}) / E_{1} + E_{2})|");
	fHistV0EnAscut->GetYaxis()->SetTitle("N of pairs");
	fOutputV0pair->Add(fHistV0EnAscut);

	fHistV0InvMass_EnAsini = new TH2F("fHistV0InvMass_EnAsini", "Inv. mass vs energy asymmetry #lambda before p_{T} cuts", 1200, 0., 1.2, 100, 0., 1.);
	fHistV0InvMass_EnAsini->GetXaxis()->SetTitle("inv. mass, GeV/#it{c}^{2}");
	fHistV0InvMass_EnAsini->GetYaxis()->SetTitle("#lambda = |(E_{1} #minus E_{2}) / E_{1} + E_{2})|");
	fOutputV0pair->Add(fHistV0InvMass_EnAsini);

	fHistV0Mass_pT12 = new TH3F("fHistV0Mass_pT12", "Inv. mass vs P_{T1} vs P_{T2} before p_{T} cuts", 800, 0., 1.2, 500, 0., 10., 500, 0., 10.);
	fHistV0Mass_pT12->GetXaxis()->SetTitle("inv. mass, GeV/#it{c}^{2}");
	fHistV0Mass_pT12->GetYaxis()->SetTitle("P_{T1} (GeV/#it{c})");
	fHistV0Mass_pT12->GetZaxis()->SetTitle("P_{T2} (GeV/#it{c})");
	fOutputV0pair->Add(fHistV0Mass_pT12);

	fHistV0MassAngle = new TH2F("fHistV0MassAngle", "Inv. mass vs angle #theta_{12} between paired VOs", 1200, 0., 1.2, 320, 0, TMath::Pi());
	fHistV0MassAngle->GetXaxis()->SetTitle("inv. mass, GeV/#it{c}^{2}");
	fHistV0MassAngle->GetYaxis()->SetTitle("#theta_{12}");
	fOutputV0pair->Add(fHistV0MassAngle);

	fHistV0InvMass1 = new TH1F("fHistV0InvMass1", "Inv. mass after p_{T} = 0.5 GeV/c cut", 1200, 0., 1.2);
	fHistV0InvMass1->GetXaxis()->SetTitle("inv. mass, GeV/#it{c}^{2}");
	fHistV0InvMass1->GetYaxis()->SetTitle("N of pairs");
	fOutputV0pair->Add(fHistV0InvMass1);

	fHistV0InvMass2 = new TH1F("fHistV0InvMass2", "Inv. mass after p_{T} = 0.7 GeV/c cut", 1200, 0., 1.2);
	fHistV0InvMass2->GetXaxis()->SetTitle("inv. mass, GeV/#it{c}^{2}");
	fHistV0InvMass2->GetYaxis()->SetTitle("N of pairs");
	fOutputV0pair->Add(fHistV0InvMass2);

	fHistV0InvMass_pT2 = new TH2F("fHistV0InvMass_pT2", "Inv. mass vs P_{T} after p_{T} = 0.7 GeV/c cut", 1200, 0., 1.2, 1000, 0., 10.);
	fHistV0InvMass_pT2->GetXaxis()->SetTitle("inv. mass, GeV/#it{c}^{2}");
	fHistV0InvMass_pT2->GetYaxis()->SetTitle("P_{T} (GeV/#it{c})");
	fOutputV0pair->Add(fHistV0InvMass_pT2);

	fHistV0InvMass_EnAs2 = new TH2F("fHistV0InvMass_EnAs2", "Inv. mass vs energy asymmetry #lambda after p_{T} = 0.7 GeV/c cut", 1200, 0., 1.2, 100, 0., 1.);
	fHistV0InvMass_EnAs2->GetXaxis()->SetTitle("inv. mass, GeV/#it{c}^{2}");
	fHistV0InvMass_EnAs2->GetYaxis()->SetTitle("#lambda = |(E_{1} #minus E_{2}) / E_{1} + E_{2})|");
	fOutputV0pair->Add(fHistV0InvMass_EnAs2);

	fHistV0InvMass3 = new TH1F("fHistV0InvMass3", "Inv. mass after p_{T} = 0.5 GeV/c and p_{T} = 1.0 GeV/c cut", 1200, 0., 1.2);
	fHistV0InvMass3->GetXaxis()->SetTitle("inv. mass, GeV/#it{c}^{2}");
	fHistV0InvMass3->GetYaxis()->SetTitle("N of pairs");
	fOutputV0pair->Add(fHistV0InvMass3);

	fHistV0InvMass_pT3 = new TH2F("fHistV0InvMass_pT3", "Inv. mass vs P_{T} after p_{T} = 0.5 GeV/c and p_{T} = 1.0 GeV/c cut", 1200, 0., 1.2, 1000, 0., 10.);
	fHistV0InvMass_pT3->GetXaxis()->SetTitle("inv. mass, GeV/#it{c}^{2}");
	fHistV0InvMass_pT3->GetYaxis()->SetTitle("P_{T} (GeV/#it{c})");
	fOutputV0pair->Add(fHistV0InvMass_pT3);

	fHistV0InvMass4 = new TH1F("fHistV0InvMass4", "Inv. mass after p_{T} = 1.0 GeV/c cut", 1200, 0., 1.2);
	fHistV0InvMass4->GetXaxis()->SetTitle("inv. mass, GeV/#it{c}^{2}");
	fHistV0InvMass4->GetYaxis()->SetTitle("N of pairs");
	fOutputV0pair->Add(fHistV0InvMass4);

	fHistV0InvMass_pT4 = new TH2F("fHistV0InvMass_pT4", "Inv. mass vs P_{T} after p_{T} = 1.0 GeV/c cut", 1200, 0., 1.2, 1000, 0., 10.);
	fHistV0InvMass_pT4->GetXaxis()->SetTitle("inv. mass, GeV/#it{c}^{2}");
	fHistV0InvMass_pT4->GetYaxis()->SetTitle("P_{T} (GeV/#it{c})");
	fOutputV0pair->Add(fHistV0InvMass_pT4);

	fHistV0InvMass5 = new TH1F("fHistV0InvMass5", "Inv. mass after p_{T} = 1.5 GeV/c cut", 600, 0., 1.2);
	fHistV0InvMass5->GetXaxis()->SetTitle("inv. mass, GeV/#it{c}^{2}");
	fHistV0InvMass5->GetYaxis()->SetTitle("N of pairs");
	fOutputV0pair->Add(fHistV0InvMass5);
	
	fHistV0InvMass6 = new TH1F("fHistV0InvMass6", "Inv. mass after p_{T} = 2.0 GeV/c cut", 600, 0., 1.2);
	fHistV0InvMass6->GetXaxis()->SetTitle("inv. mass, GeV/#it{c}^{2}");
	fHistV0InvMass6->GetYaxis()->SetTitle("N of pairs");
	fOutputV0pair->Add(fHistV0InvMass6);

    fOutputList->Add(fOutputEvent);
    fOutputList->Add(fOutputV0);
    fOutputList->Add(fOutputV0pair);
    
    PostData(1, fOutputList);           // postdata will notify the analysis manager of changes / updates to the
    // fOutputList object. the manager will in the end take care of writing your output to file
    // so it needs to know what's in the output
    
}

//________________________________________________________________________
void AliAnalysisTaskEtaPrime::UserExec(Option_t *)
{
    // Main loop
    // Called for each event
    
    fEvent = dynamic_cast<AliVEvent*>(InputEvent());
    if (!fEvent) {
        //printf("ERROR: fEvent not available\n");
        return;
    }
    
    AliESDEvent *esdevent = dynamic_cast<AliESDEvent *>(fEvent);
    if (!esdevent) return;
    
    // Was event selected?
    UInt_t maskIsSelected = ((AliInputEventHandler*)(AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler()))->IsEventSelected();
    
    if (maskIsSelected==0){
        PostData(1, fOutputList);
        return;
    }
    fEventStat->Fill(kSelectedEvents); // all events after trigger and physics selection
    
    // vertex filter
    const AliVVertex *vertex = fEvent->GetPrimaryVertex();
    Bool_t lVertexAcceptable = (TMath::Abs(vertex->GetZ()) <= 10. );
    
    // N of vertex contributors
    if (!(vertex->GetNContributors() > 0)){
        PostData(1, fOutputList);
        return;
    }
    
    if(!lVertexAcceptable){
        PostData(1, fOutputList);
        return;
    }
    fEventStat->Fill(kVertexEvents);
    
    
    // some further clean-up of events
    const AliESDVertex *lPrimaryVtxSPD    = NULL;
    const AliESDVertex *lPrimaryVtxTracks = NULL;
    lPrimaryVtxSPD    = esdevent->GetPrimaryVertexSPD   ();
    lPrimaryVtxTracks = esdevent->GetPrimaryVertexTracks();
    
    // inconsistency between SPD and track vertices
    if( lPrimaryVtxTracks->GetStatus() && lPrimaryVtxSPD->GetStatus() ) {
        // TODO value of displacement to be studied
        const Float_t maxDisplacement = 0.5;
        Double_t displacement = TMath::Abs(lPrimaryVtxSPD->GetZ() - lPrimaryVtxTracks->GetZ());
        
        if (displacement > maxDisplacement){
            PostData(1, fOutputList);
            return;
        }
    }
    
    // SPD VtxZ resolution and dispersion
    if (lPrimaryVtxSPD->IsFromVertexerZ() && !(lPrimaryVtxSPD->GetDispersion()<0.03 && lPrimaryVtxSPD->GetZRes()<0.25)){
        PostData(1, fOutputList);
        return;
    }
    
    fEventStat->Fill(kVertexResDisp);

    // fill event histograms after all filters

    fNEvents        ->Fill(0.5);
    fVertexZ        ->Fill(vertex->GetZ());
    

    // V0 loop
    
	for (int iV0 = 0; iV0 < esdevent->GetNumberOfV0s() - 1; ++iV0) {
		AliESDv0 *v0 = esdevent->GetV0(iV0);

		AliESDtrack *pos = dynamic_cast<AliESDtrack*>(esdevent->GetVTrack(v0->GetPindex()));
		AliESDtrack *neg = dynamic_cast<AliESDtrack*>(esdevent->GetVTrack(v0->GetNindex()));
		if (!pos || !neg) continue;

		if (pos->Charge() < 0) {
			pos = neg;
			neg = dynamic_cast<AliESDtrack*>(esdevent->GetVTrack(v0->GetPindex()));
		}

		// Track cuts (TPC only)
		if (!(fTrackCuts->AcceptTrack(pos)) || !(fTrackCuts->AcceptTrack(neg)))
		{
			continue; // rejected by track cuts
		}

		//V0 cuts
	     	if (neg->Charge() == pos->Charge()) continue;
		if (TMath::Abs(v0->Eta()) > 0.9) continue;
		if (v0->GetV0CosineOfPointingAngle() < 0.85) continue;
		if (v0->GetRr() < 5 || v0->GetRr() > 180) continue;
		if (v0->GetRr() < TMath::Abs(v0->Zv()) * TMath::Tan(2 * TMath::ATan(TMath::Exp(-0.9))) - 7 ) continue;            //line cut
		if (TMath::Abs(v0->Zv()) > 240) continue;
		if (TMath::Abs(Psi_pair(neg, pos)) > 0.1) continue;
		if (v0->GetKFInfo(1,1,2) > 30) continue;		//chi2 cut
		//if (!(v0->GetOnFlyStatus())) continue;

		//fill dE/dx histograms before PID cuts
		fHistdEdxneg->Fill(neg->P(),neg->GetTPCsignal());
		fHistdEdxpos->Fill(pos->P(),pos->GetTPCsignal());
		  

		// PID cuts (TPC only)
		Float_t nSigmaTPC_legpos = fPIDResponse->NumberOfSigmasTPC(pos, AliPID::kElectron);
		Float_t nSigmaTPC_legneg = fPIDResponse->NumberOfSigmasTPC(neg, AliPID::kElectron);
		Float_t nSigmaTPCpio_legpos = fPIDResponse->NumberOfSigmasTPC(pos, AliPID::kPion);
		Float_t nSigmaTPCpio_legneg = fPIDResponse->NumberOfSigmasTPC(neg, AliPID::kPion);

		if (pos->P() < 0.4 && nSigmaTPCpio_legpos < 0.5) continue;
		if (pos->P() > 0.4 && nSigmaTPCpio_legpos < 3) continue;
		if (neg->P() < 0.4 && nSigmaTPCpio_legneg < 0.5) continue;
		if (neg->P() > 0.4 && nSigmaTPCpio_legneg < 3) continue;
		if (TMath::Abs(nSigmaTPC_legpos) > 3) continue;
		if (TMath::Abs(nSigmaTPC_legneg) > 3) continue;

		//fill dE/dx histograms after PID cuts
		fHistdEdxnegfin->Fill(neg->P(),neg->GetTPCsignal());
		fHistdEdxposfin->Fill(pos->P(),pos->GetTPCsignal());

		// Armenteros Podolandski
		const float armAlpha = v0->AlphaV0();
		const float armQt = v0->PtArmV0();

		if (TMath::Abs(armAlpha) > 0.95) continue;
		if (armQt > 0.05 * TMath::Sqrt(1 - (armAlpha*armAlpha)/(0.95*0.95))) continue;		 //elliptic cut
		

		TLorentzVector lv1;
		lv1.SetPtEtaPhiM(v0->Pt(), v0->Eta(), v0->Phi(), 0.0);

		// second loop over V0s
		for (int iV02 = iV0 + 1; iV02 < esdevent->GetNumberOfV0s(); ++iV02) {

			AliESDv0 *v02 = esdevent->GetV0(iV02);

			AliESDtrack *pos2 = dynamic_cast<AliESDtrack*>(esdevent->GetVTrack(v02->GetPindex()));
			AliESDtrack *neg2 = dynamic_cast<AliESDtrack*>(esdevent->GetVTrack(v02->GetNindex()));
			if (!pos2 || !neg2) continue;

			if (pos2->Charge() < 0) {
				pos2 = neg2;
				neg2 = dynamic_cast<AliESDtrack*>(esdevent->GetVTrack(v02->GetPindex()));
			}

			// Track cuts (TPC only)
			if (!(fTrackCuts->AcceptTrack(pos2)) || !(fTrackCuts->AcceptTrack(neg2)))
			{
				continue; // rejected by track cuts
			}

			//V0 cuts
			if (neg2->Charge() == pos2->Charge()) continue;
			if (TMath::Abs(v02->Eta()) > 0.9) continue;
			if (v02->GetV0CosineOfPointingAngle() < 0.85) continue;
			if (v02->GetRr() < 5 || v02->GetRr() > 180) continue;
			if (v02->GetRr() < TMath::Abs(v0->Zv()) * TMath::Tan(2 * TMath::ATan(TMath::Exp(-0.9))) - 7) continue;            //line cut
			if (TMath::Abs(v02->Zv()) > 240) continue;
			if (TMath::Abs(Psi_pair(neg2,pos2)) > 0.1) continue;
			if (v02->GetKFInfo(1,1,2) > 30) continue;		//chi2 cut
			//if (!(v02->GetOnFlyStatus())) continue;
			

			// PID cuts (TPC only)

			Float_t nSigmaTPC_legpos2 = fPIDResponse->NumberOfSigmasTPC(pos2, AliPID::kElectron);
			Float_t nSigmaTPC_legneg2 = fPIDResponse->NumberOfSigmasTPC(neg2, AliPID::kElectron);
			Float_t nSigmaTPCpio_legpos2 = fPIDResponse->NumberOfSigmasTPC(pos2, AliPID::kPion);
			Float_t nSigmaTPCpio_legneg2 = fPIDResponse->NumberOfSigmasTPC(neg2, AliPID::kPion);

			if (pos2->P() < 0.4 && nSigmaTPCpio_legpos2 < 0.5) continue;
			if (pos2->P() > 0.4 && nSigmaTPCpio_legpos2 < 3) continue;
			if (neg2->P() < 0.4 && nSigmaTPCpio_legneg2 < 0.5) continue;
			if (neg2->P() > 0.4 && nSigmaTPCpio_legneg2 < 3) continue;
			if (TMath::Abs(nSigmaTPC_legpos2) > 3) continue;
			if (TMath::Abs(nSigmaTPC_legneg2) > 3) continue;

			// Armenteros Podolandski
			const float armAlpha2 = v02->AlphaV0();
			const float armQt2 = v02->PtArmV0();

			if (TMath::Abs(armAlpha2) > 0.95) continue;
			if (armQt2 > 0.05 * TMath::Sqrt(1 - (armAlpha2*armAlpha2) / (0.95*0.95))) continue;		 //elliptic cut
			

			TLorentzVector lv2;
			lv2.SetPtEtaPhiM(v02->Pt(), v02->Eta(), v02->Phi(), 0.0);

			double pt = (lv1 + lv2).Pt();
			double pt1 = lv1.Pt();
			double pt2 = lv2.Pt();
			double m = (lv1 + lv2).M();
			double en = (lv1 + lv2).E();
			double enas = TMath::Abs((lv1.E() - lv2.E()) / (lv1.E() + lv2.E()));
			double a = lv1.Angle(lv2.Vect());

			//fill energy asymmetry histogram for m < 0.2 Gev/c^2 and pt > 3 GeV/c
			if (m < 0.2 && pt > 3){
			  fHistV0EnAscut->Fill(enas);
			}

			fHistV0E->Fill(en);
			fHistV0InvMassini->Fill(m);
			fHistV0InvMass_pTini->Fill(m, pt);
			fHistV0EnergyAsymmetryini->Fill(enas);
			fHistV0InvMass_EnAsini->Fill(m, enas);
			fHistV0Mass_pT12->Fill(m, pt1, pt2);
			fHistV0MassAngle->Fill(m,a);

			if (pt1 < 0.5 || pt2 < 0.5) continue;
			fHistV0InvMass1->Fill(m);

			if (pt1 > 0.5 || pt2 > 1.){
				fHistV0InvMass3->Fill(m);
				fHistV0InvMass_pT3->Fill(m, pt);
			}

			if (pt1 < 0.7 || pt2 < 0.7) continue;
			fHistV0InvMass2->Fill(m);
			fHistV0InvMass_pT2->Fill(m, pt);
			fHistV0InvMass_EnAs2->Fill(m, enas);

			if (pt1 < 1. || pt2 < 1.) continue;
			fHistV0InvMass4->Fill(m);
			fHistV0InvMass_pT4->Fill(m, pt);
			
			if (pt1 < 1.5 || pt2 < 1.5) continue;
			fHistV0InvMass5->Fill(m);
			
			if (pt1 < 2. || pt2 < 2.) continue;
			fHistV0InvMass6->Fill(m);
		}
	}

	for (int iV0 = 0; iV0 < esdevent->GetNumberOfV0s(); ++iV0) {
		AliESDv0 *v0 = esdevent->GetV0(iV0);

		AliESDtrack *pos = dynamic_cast<AliESDtrack*>(esdevent->GetVTrack(v0->GetPindex()));
		AliESDtrack *neg = dynamic_cast<AliESDtrack*>(esdevent->GetVTrack(v0->GetNindex()));
		if (!pos || !neg) continue;

		if (pos->Charge() < 0) {
			pos = neg;
			neg = dynamic_cast<AliESDtrack*>(esdevent->GetVTrack(v0->GetPindex()));
		}
	
		// Track cuts (TPC only)
		if (!(fTrackCuts->AcceptTrack(pos)) || !(fTrackCuts->AcceptTrack(neg)))
		{
			continue; // rejected by track cuts
		}
		
		//V0 cuts
		if (neg->Charge() == pos->Charge()) continue;
		if (TMath::Abs(v0->Eta()) > 0.9) continue;
		if (v0->GetV0CosineOfPointingAngle() < 0.85) continue;
		if (v0->GetRr() < 5 || v0->GetRr() > 180) continue;
		if (v0->GetRr() < TMath::Abs(v0->Zv()) * TMath::Tan(2 * TMath::ATan(TMath::Exp(-0.9))) - 7 ) continue;            //line cut
		if (TMath::Abs(v0->Zv()) > 240) continue;
		if (TMath::Abs(Psi_pair(neg, pos)) > 0.1) continue;
		if (v0->GetKFInfo(1,1,2) > 30) continue;		//chi2 cut
		//if (!(v0->GetOnFlyStatus())) continue;
		

        // Armenteros Podolandski
        const float armAlpha = v0->AlphaV0();
        const float armQt = v0->PtArmV0();
		

		if (TMath::Abs(armAlpha) > 0.95) continue;
		if (armQt > 0.05 * TMath::Sqrt(1 - (armAlpha*armAlpha) / (0.95*0.95))) continue;		 //elliptic cut
		

		
		// PID cuts (TPC only)
		Float_t nSigmaTPC_legpos = fPIDResponse->NumberOfSigmasTPC(pos, AliPID::kElectron);
		Float_t nSigmaTPC_legneg = fPIDResponse->NumberOfSigmasTPC(neg, AliPID::kElectron);
		Float_t nSigmaTPCpio_legpos = fPIDResponse->NumberOfSigmasTPC(pos, AliPID::kPion);
		Float_t nSigmaTPCpio_legneg = fPIDResponse->NumberOfSigmasTPC(neg, AliPID::kPion);

		if (pos->P() < 0.4 && nSigmaTPCpio_legpos < 0.5) continue;
		if (pos->P() > 0.4 && nSigmaTPCpio_legpos < 3) continue;
		if (neg->P() < 0.4 && nSigmaTPCpio_legneg < 0.5) continue;
		if (neg->P() > 0.4 && nSigmaTPCpio_legneg < 3) continue;
        if (TMath::Abs(nSigmaTPC_legpos) > 3 ) continue;
		if (TMath::Abs(nSigmaTPC_legneg) > 3 ) continue;
		


        // fill histos for negative V0 leg
        // pt, eta, phi
        fHistPt_neg  ->Fill(neg->Pt());
        fHistEta_neg ->Fill(neg->Eta());
        fHistPhi_neg ->Fill(neg->Phi());
        
        // DCA
        Float_t impactParXY_neg, impactParZ_neg;
        neg->GetImpactParameters(impactParXY_neg, impactParZ_neg);
        fHistDCAxy_neg->Fill(impactParXY_neg);
        fHistDCAz_neg ->Fill(impactParZ_neg);
        
        // ITS tracking
        fHistITSncls_neg->Fill(neg->GetNcls(0));
        if (neg->GetNcls(0) > 0){
            fHistITSchi2_neg->Fill((neg->GetITSchi2())/(neg->GetNcls(0)));
        }
        
        // TPC tracking
        fHistTPCncls_neg->Fill(neg->GetTPCNcls());
        fHistTPCncr_neg ->Fill(neg->GetTPCCrossedRows());
        if (neg->GetTPCNcls() > 0){
            fHistTPCchi2_neg->Fill((neg->GetTPCchi2())/(neg->GetTPCNcls()));
        }
        
        // PID
        fHistTPCnSigmaEle_neg->Fill(neg->P(), nSigmaTPC_legneg);
        fHistTPCnSigmaPio_neg->Fill(neg->P(), nSigmaTPCpio_legneg);
        
        // fill histos for positive V0 leg
        // pt, eta, phi
        fHistPt_pos  ->Fill(pos->Pt());
        fHistEta_pos ->Fill(pos->Eta());
        fHistPhi_pos ->Fill(pos->Phi());
        
        // DCA
        Float_t impactParXY_pos, impactParZ_pos;
        pos->GetImpactParameters(impactParXY_pos, impactParZ_pos);
        fHistDCAxy_pos->Fill(impactParXY_pos);
        fHistDCAz_pos ->Fill(impactParZ_pos);
        
        // ITS tracking
        fHistITSncls_pos->Fill(pos->GetNcls(0));
        if (pos->GetNcls(0) > 0){
            fHistITSchi2_pos->Fill((pos->GetITSchi2())/(pos->GetNcls(0)));
        }
        
        // TPC tracking
        fHistTPCncls_pos->Fill(pos->GetTPCNcls());
        fHistTPCncr_pos ->Fill(pos->GetTPCCrossedRows());
        if (pos->GetTPCNcls() > 0){
            fHistTPCchi2_pos->Fill((pos->GetTPCchi2())/(pos->GetTPCNcls()));
        }
        
        // PID
        fHistTPCnSigmaEle_pos->Fill(pos->P(), nSigmaTPC_legpos);
        fHistTPCnSigmaPio_pos->Fill(pos->P(), nSigmaTPCpio_legpos);
        
        
        // fill V0 histograms
        fHistV0Pt		->Fill(v0->Pt());
        fHistV0Eta		->Fill(v0->Eta());
        fHistV0Phi		->Fill(v0->Phi());
		fHistV0Z		->Fill(v0->Zv());
		fHistV0R		->Fill(v0->GetRr());
		fHistV0RvsZ		->Fill(TMath::Abs(v0->Zv()), v0->GetRr());
		fHistV0CosPA	->Fill(v0->GetV0CosineOfPointingAngle());
		fHistV0Chi2		->Fill(v0->GetKFInfo(1,1,2));
		fHistV0Psi_pair	->Fill(Psi_pair(neg, pos));
		fHistV0ArmPod	->Fill(armAlpha, armQt);
		
		
		fHistV0Mass->Fill(v0->M()); // peak at 0.28 is due to wrong default assumption that decay products are pions
    }
    
    PostData(1, fOutputList);
}

//________________________________________________________________________
void AliAnalysisTaskEtaPrime::Terminate(Option_t *)
{
    // terminate
    // called at the END of the analysis (when all events are processed)
}
