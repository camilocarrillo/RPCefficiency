//
// Original Author:  Federica Primavera
//         Created:  Thu, 27 Nov 2014 13:58:57 GMT
//
//

#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/MuonReco/interface/Muon.h" 
#include "DataFormats/MuonReco/interface/MuonFwd.h" 
#include "DataFormats/MuonReco/interface/MuonTime.h"
#include "DataFormats/MuonReco/interface/MuonTimeExtra.h"
#include "DataFormats/MuonReco/interface/MuonTimeExtraMap.h"

#include "STASkim/ProducerTest/plugins/StandAloneTimingProducer.h"
#include "RecoMuon/MuonIdentification/interface/TimeMeasurementSequence.h"

namespace edm {
  class ParameterSet;
  class EventSetup;
  class InputTag;
  class Time;
}

// constructors
StandAloneTimingProducer::StandAloneTimingProducer(const edm::ParameterSet& iConfig){

  produces<reco::MuonTimeExtraMap>("combined");
  produces<reco::MuonTimeExtraMap>("dt");
  produces<reco::MuonTimeExtraMap>("csc");
  produces<reco::MuonTimeExtraMap>("rpc");

  m_muonCollection = iConfig.getParameter<edm::InputTag>("MuonCollection");
  muonToken_ = consumes<reco::TrackCollection>(m_muonCollection);
  // Load parameters for the TimingFiller
  edm::ParameterSet fillerParameters = iConfig.getParameter<edm::ParameterSet>("TimingFillerParameters");
  theTimingFiller_ = new Time(fillerParameters,consumesCollector());
}

// and destructor
StandAloneTimingProducer::~StandAloneTimingProducer(){
  if (theTimingFiller_) delete theTimingFiller_;
}


// ------------ method called to produce the data  ------------
void
StandAloneTimingProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup){
  //changed auto_ptr to auto 
  //std::auto_ptr<reco::MuonTimeExtraMap> muonTimeMap(new reco::MuonTimeExtraMap());
  auto muonTimeMap = std::make_unique<reco::MuonTimeExtraMap>();
  reco::MuonTimeExtraMap::Filler filler(*muonTimeMap);
  auto muonTimeMapDT = std::make_unique<reco::MuonTimeExtraMap>();
  reco::MuonTimeExtraMap::Filler fillerDT(*muonTimeMapDT);
  auto muonTimeMapCSC = std::make_unique<reco::MuonTimeExtraMap>();
  reco::MuonTimeExtraMap::Filler fillerCSC(*muonTimeMapCSC);
  
  auto muonTimeMapRPC = std::make_unique<reco::MuonTimeExtraMap>();
  reco::MuonTimeExtraMap::Filler fillerRPC(*muonTimeMapRPC);
  

  edm::Handle<reco::TrackCollection> muons; 
  iEvent.getByToken(muonToken_, muons);
  
  unsigned int nMuons = muons->size();
  

  std::vector<reco::MuonTimeExtra> dtTimeColl(nMuons);
  std::vector<reco::MuonTimeExtra> cscTimeColl(nMuons);
  std::vector<reco::MuonTimeExtra> combinedTimeColl(nMuons);
  std::vector<reco::MuonTimeExtra> rpcTimeColl(nMuons);
  

  for ( unsigned int i=0; i<nMuons; ++i ) {
    reco::MuonTimeExtra dtTime;
    reco::MuonTimeExtra cscTime;
    reco::MuonTimeExtra rpcTime;
    reco::MuonTimeExtra combinedTime;
    
    const reco::TrackRef muonref(muons,i);  
       
    theTimingFiller_->fillTime(muonref, dtTime, cscTime, rpcTime, combinedTime, iEvent, iSetup);

    dtTimeColl[i] = dtTime;
    cscTimeColl[i] = cscTime;
    combinedTimeColl[i] = combinedTime;
    rpcTimeColl[i] = rpcTime;
  }
  
  //muons 
  filler.insert(muons, combinedTimeColl.begin(), combinedTimeColl.end());
  filler.fill();
  fillerDT.insert(muons, dtTimeColl.begin(), dtTimeColl.end());
  fillerDT.fill();
  fillerCSC.insert(muons, cscTimeColl.begin(), cscTimeColl.end());
  fillerCSC.fill();
  fillerRPC.insert(muons, rpcTimeColl.begin(), rpcTimeColl.end());
  fillerRPC.fill();

  iEvent.put(std::move(muonTimeMap),"combined");
  iEvent.put(std::move(muonTimeMapDT),"dt");
  iEvent.put(std::move(muonTimeMapCSC),"csc");
  iEvent.put(std::move(muonTimeMapRPC),"rpc");
}     

DEFINE_FWK_MODULE(StandAloneTimingProducer);

