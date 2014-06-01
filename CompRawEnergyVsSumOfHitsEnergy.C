{

TFile* file = TFile::Open("ntuple_DYJets-Summer12-START53-HighEtaSkim-runDependent-Extra-V4-2012AB_10k.root");

TTree* tree = (TTree*)file->Get("selected");
TTree* extree = (TTree*)file->Get("extraCalibTree");

tree->AddFriend(extree, "extree");

//tree->Draw("rawEnergySCEle[0]:Sum$(extree.energyRecHitSCEle1)>>h(1000,0,1000,1000,0,1000)", "recoFlagsEle[0]>1", "colz");
tree->Draw("rawEnergySCEle[1]:Sum$(extree.energyRecHitSCEle2)>>h(1000,0,1000,1000,0,1000)", "(recoFlagsEle[1]>1&&ZStat==1)||(ZStat==2)", "colz");

}
