// -*- C++ -*-
//
// Package:    TriggerFilter
// Class:      TriggerFilter
// Gt
/**\class TriggerFilter TriggerFilter.cc TriggerFilter/TriggerFilter/src/TriggerFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Camilo Andres Carrillo Montoya,40 2-B15,+41227671625,
//         Created:  Tue Apr  5 10:35:59 CEST 2011
// $Id: TriggerFilter.cc,v 1.1.1.1 2012/07/17 01:17:51 jgomezca Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTCand.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTExtendedCand.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutCollection.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTCand.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutCollection.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTCand.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTExtendedCand.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuRegionalCand.h"


//
// class declaration
//

class TriggerFilter : public edm::EDFilter {
   public:
      explicit TriggerFilter(const edm::ParameterSet&);
      ~TriggerFilter();

   private:
      edm::InputTag gtDigis;
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TriggerFilter::TriggerFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
  gtDigis=iConfig.getParameter<edm::InputTag>("gtDigis");

}


TriggerFilter::~TriggerFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
TriggerFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<L1MuGMTReadoutCollection> gmtrc_handle;
  iEvent.getByLabel(gtDigis,gmtrc_handle);
  
  
  std::vector<L1MuGMTExtendedCand> gmt_candidates = (*gmtrc_handle).getRecord().getGMTCands();
  std::vector<L1MuGMTExtendedCand>::const_iterator candidate;
  
  //std::cout<<"The number of GMT Candidates in this event is "<<gmt_candidates.size()<<std::endl;

  bool atLeastOneDTorCSCTrigger = false;

  for(candidate=gmt_candidates.begin(); candidate!=gmt_candidates.end(); candidate++) {
    if(candidate->quality() == 6 || candidate->quality()==7) atLeastOneDTorCSCTrigger = true;
  }

  if(atLeastOneDTorCSCTrigger) return true;
  return false; 
}

// ------------ method called once each job just before starting event loop  ------------
void 
TriggerFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TriggerFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(TriggerFilter);
