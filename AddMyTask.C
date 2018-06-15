AliAnalysisTaskEtaPrime* AddMyTask(TString name = "MyTaskEtaPrime")
{
    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr) {
        return 0x0;
    }
    if (!mgr->GetInputEventHandler()) {
        return 0x0;
    }

    // create an instance of the task
	AliAnalysisTaskEtaPrime *tasketaprime = new AliAnalysisTaskEtaPrime(name.Data());
    if(!tasketaprime) return 0x0;
    
    // event selection
    tasketaprime->SelectCollisionCandidates(AliVEvent::kINT7); // min. bias trigger for run2 data (V0AND)
    
    // track cuts
    AliESDtrackCuts* trackCuts=new AliESDtrackCuts();
    // pT and eta
     trackCuts->SetPtRange(0.05, 1e30);
     //trackCuts->SetEtaRange(-0.8, 0.8);
    //TPC
    trackCuts->SetRequireTPCRefit(kTRUE);
    //trackCuts->SetMinNCrossedRowsTPC(100);
    //trackCuts->SetMinNClustersTPC(80);
    trackCuts->SetMinRatioCrossedRowsOverFindableClustersTPC(0.6);
    //trackCuts->SetMaxChi2PerClusterTPC(4.0);
    //trackCuts->SetMaxFractionSharedTPCClusters(0.4);
//    //ITS
    //trackCuts->SetRequireITSRefit(kTRUE);
//    trackCuts->SetClusterRequirementITS(AliESDtrackCuts::kSPD,AliESDtrackCuts::kFirst);
//    trackCuts->SetMinNClustersITS(3);
//    trackCuts->SetMaxChi2PerClusterITS(4.5);
//    //primary selection
    trackCuts->SetAcceptKinkDaughters(kFALSE);
//    trackCuts->SetDCAToVertex2D(kFALSE);
//    trackCuts->SetRequireSigmaToVertex(kFALSE);
//    trackCuts->SetMaxDCAToVertexZ(3.0);
//    trackCuts->SetMaxDCAToVertexXY(1.0);
    //set track cuts to the task
    tasketaprime->SetTrackCuts(trackCuts);
    
    // add task to the manager
    mgr->AddTask(tasketaprime);
    // connect the manager to the task
    mgr->ConnectInput(tasketaprime,0,mgr->GetCommonInputContainer());
    mgr->ConnectOutput(tasketaprime,1,mgr->CreateContainer("Output", TList::Class(), AliAnalysisManager::kOutputContainer, "Output_MyTask.root"));
    return tasketaprime;
}
