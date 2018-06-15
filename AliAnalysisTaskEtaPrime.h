#ifndef AliAnalysisTaskEtaPrime_cxx
#define AliAnalysisTaskEtaPrime_cxx

// example of analysis task

class TH1F;
class TH2F;
class TH3F;
class TH1I;
class AliVEvent;
class AliESDtrackCuts;
class TList;
class AliPIDResponse; // main class for PID analysis

#include "AliAnalysisTaskSE.h"

class AliAnalysisTaskEtaPrime : public AliAnalysisTaskSE {
public:
	AliAnalysisTaskEtaPrime();
	AliAnalysisTaskEtaPrime(const char *name);
	virtual ~AliAnalysisTaskEtaPrime();
    
	Double_t Psi_pair(AliESDtrack *neg, AliESDtrack *pos);
    void   UserCreateOutputObjects();
    void   UserExec(Option_t *option);
    void   Terminate(Option_t *);
    
    void SetTrackCuts(AliESDtrackCuts* const cuts) { fTrackCuts = cuts; }
    
private:
    // transient members are not streamed
    AliVEvent   *fEvent;          //! vEvent
    TList       *fOutputList;     //! Output list
    TList       *fOutputEvent;    //! Event list
    TList       *fOutputV0;       //! V0 list
    TList       *fOutputV0legneg; //! V0 negative leg
    TList       *fOutputV0legpos; //! V0 negative leg
    TList       *fOutputV0pair;   //! V0 pair list
    
    // Event histograms
    TH1I        *fEventStat;      //! Event statistics
    TH1F        *fNEvents;        //! n of events
    TH1F        *fVertexZ;        //! Vertex Z coordinate
    
    // V0 histograms
    TH1F        *fHistV0Pt;         //! V0's Pt spectrum
    TH1F        *fHistV0Eta;        //! V0's Eta distribution
    TH1F        *fHistV0Phi;        //! V0's Phi distribution
	TH1F        *fHistV0R;			//! V0's radius distribution
	TH1F        *fHistV0Z;          //! V0's Z coordinate distribution
	TH2F		*fHistV0RvsZ;		//! V0's R vs. Z distribution
	TH1F		*fHistV0CosPA;		//! V0's cos(pointing angle) distribution
	TH1F		*fHistV0Chi2;		//! V0's Chi2
	TH1F		*fHistV0Psi_pair;   //! V0's Psi_pair distribution
    TH1F        *fHistV0Mass;       //! V0's mass distribution
	TH1F		*fHistV0E;			//! V0's energy distribution using TLorentzvector
    TH2F        *fHistV0ArmPod;     //! Armenteros-Podolanski plot

    // V0 negative leg histograms
    TH1F        *fHistPt_neg;         //! Pt spectrum
    TH1F        *fHistEta_neg;        //! Eta distribution
    TH1F        *fHistPhi_neg;        //! Phi distribution
    TH1F        *fHistDCAxy_neg;      //! DCAxy distribution
    TH1F        *fHistDCAz_neg;       //! DCAz distribution
    TH1I        *fHistITSncls_neg;    //! N of clusters ITS
    TH1F        *fHistITSchi2_neg;    //! ITS chi2
    TH1I        *fHistTPCncls_neg;    //! N of clusters TPC
    TH1I        *fHistTPCncr_neg;     //! N of crossed rows TPC
    TH1F        *fHistTPCchi2_neg;    //! TPC chi2
    TH2F        *fHistTPCnSigmaEle_neg;    //! TPC n sigma ele vs momentum negative leg
    TH2F        *fHistTPCnSigmaPio_neg;    //! TPC n sigma pio vs momentum negative leg
    TH2F        *fHistdEdxneg;        //! dE/dx before PID cuts
    TH2F        *fHistdEdxnegfin;     //! dE/dx after PID cuts
    
    // V0 positive leg histograms
    TH1F        *fHistPt_pos;         //! Pt spectrum
    TH1F        *fHistEta_pos;        //! Eta distribution
    TH1F        *fHistPhi_pos;        //! Phi distribution
    TH1F        *fHistDCAxy_pos;      //! DCAxy distribution
    TH1F        *fHistDCAz_pos;       //! DCAz distribution
    TH1I        *fHistITSncls_pos;    //! N of clusters ITS
    TH1F        *fHistITSchi2_pos;    //! ITS chi2
    TH1I        *fHistTPCncls_pos;    //! N of clusters TPC
    TH1I        *fHistTPCncr_pos;     //! N of crossed rows TPC
    TH1F        *fHistTPCchi2_pos;    //! TPC chi2
    TH2F        *fHistTPCnSigmaEle_pos;    //! TPC n sigma ele vs momentum positive leg
    TH2F        *fHistTPCnSigmaPio_pos;    //! TPC n sigma pio vs momentum positive leg
    TH2F        *fHistdEdxpos;        //! dE/dx before PID cuts
    TH2F        *fHistdEdxposfin;     //! dE/dx after PID cuts
    
    // V0 pair histograms
    TH1F        *fHistV0InvMassini;				//! initial inv. mass of V0's pairs before pT cuts
	TH2F		*fHistV0InvMass_pTini;			//! initial mass of V0 vs pT before pT cuts
	TH1F		*fHistV0EnergyAsymmetryini;		//! initial V0's energy asymmetry before pT cuts
	TH1F            *fHistV0EnAscut;                        //! V0's energy asymmetry after pT and mass cut
	TH2F		*fHistV0InvMass_EnAsini;		//! initial mass of V0 vs energy asymmetry before pT cuts
	TH3F		*fHistV0Mass_pT12;				//! V0's mass vs. pT1 vs. pT2 before pT cuts
	TH2F		*fHistV0MassAngle;				//! VO's mass distribution vs. opening angle

	TH1F        *fHistV0InvMass1;			//! inv. mass of V0's pairs after 0.5 GeV/c pT cut

	TH1F        *fHistV0InvMass2;			//! inv. mass of V0's pairs after 0.7 GeV/c pT cut
	TH2F		*fHistV0InvMass_pT2;		//! mass of V0 vs pT after 0.7 GeV/c pT cut
	TH2F		*fHistV0InvMass_EnAs2;		//! mass of V0 vs energy asymmetry after 0.7 GeV/c pT cut

	TH1F        *fHistV0InvMass3;			//! inv. mass of V0's pairs after 0.5 GeV/c pT and 1.0 GeV/c cut
	TH2F		*fHistV0InvMass_pT3;		//! mass of V0 vs pT after after 0.5 GeV/c pT and 1.0 GeV/c cut
	
	TH1F        *fHistV0InvMass4;			//! inv. mass of V0's pairs after 1.0 GeV/c pT cut
	TH2F		*fHistV0InvMass_pT4;		//! mass of V0 vs pT after after 1.0 GeV/c pT cut

	TH1F        *fHistV0InvMass5;			//! inv. mass of V0's pairs after 1.5 GeV/c pT cut
	TH1F        *fHistV0InvMass6;			//! inv. mass of V0's pairs after 2.0 GeV/c pT cut
    
    AliPIDResponse *fPIDResponse;      //! PID response object
    
    // persistent members are streamed (copied/stored)
    AliESDtrackCuts *fTrackCuts; // Track cuts
    
    enum {kSelectedEvents=0, kVertexEvents, kVertexResDisp, kNbinsEvent};
    
	AliAnalysisTaskEtaPrime(const AliAnalysisTaskEtaPrime&); // not implemented
	AliAnalysisTaskEtaPrime& operator=(const AliAnalysisTaskEtaPrime&); // not implemented
    
	ClassDef(AliAnalysisTaskEtaPrime, 1);
};

#endif
