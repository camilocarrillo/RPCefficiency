// -*- C++ -*-
//
// Package:    RPCPointProducer
// Class:      RPCPointProducer
// 
/**\class RPCPointProducer RPCPointProducer.cc Analysis/RPCPointProducer/src/RPCPointProducer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Wed Sep 16 14:56:18 CEST 2009
// $Id: RPCPointProducer.cc,v 1.1.1.1 2012/07/17 01:17:51 jgomezca Exp $
//
//

#include "RecoLocalMuon/RPCRecHit/interface/RPCPointProducer.h"

// system include files

#include <memory>
#include <ctime>

// user include files

RPCPointProducer::RPCPointProducer(const edm::ParameterSet& iConfig)
{
    cscSegments = consumes<CSCSegmentCollection>(iConfig.getParameter<edm::InputTag>("cscSegments"));
    dt4DSegments = consumes<DTRecSegment4DCollection>(iConfig.getParameter<edm::InputTag>("dt4DSegments"));
    debug=iConfig.getUntrackedParameter<bool>("debug",false);
    incldt=iConfig.getUntrackedParameter<bool>("incldt",true);
    inclcsc=iConfig.getUntrackedParameter<bool>("inclcsc",true);
    MinCosAng=iConfig.getUntrackedParameter<double>("MinCosAng",0.95);
    MaxD=iConfig.getUntrackedParameter<double>("MaxD",80.);
    MaxDrb4=iConfig.getUntrackedParameter<double>("MaxDrb4",150.);
    ExtrapolatedRegion=iConfig.getUntrackedParameter<double>("ExtrapolatedRegion",0.5);
    
    produces<RPCRecHitCollection>("RPCDTExtrapolatedPoints");
    produces<RPCRecHitCollection>("RPCCSCExtrapolatedPoints");
}


RPCPointProducer::~RPCPointProducer(){

}

void RPCPointProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup){
  /*
  struct timespec start_time, stop_time;
  time_t fs;
  time_t fn;
  time_t ls;
  time_t ln;
  clock_gettime(CLOCK_REALTIME, &start_time);  
  */

  if(incldt){
    edm::Handle<DTRecSegment4DCollection> all4DSegments;
    iEvent.getByToken(dt4DSegments, all4DSegments);
    if(all4DSegments.isValid()){
	//DTSegtoRPC DTClass(all4DSegments,iSetup,iEvent,debug,ExtrapolatedRegion);
	//std::auto_ptr<RPCRecHitCollection> TheDTPoints(DTClass.thePoints());     
	//iEvent.put(TheDTPoints,"RPCDTExtrapolatedPoints"); 
	DTSegtoRPC DTClass(all4DSegments,iSetup,iEvent,debug,ExtrapolatedRegion);
	std::unique_ptr<RPCRecHitCollection>  TheDTPoints(DTClass.thePoints());
	iEvent.put(std::move(TheDTPoints), "RPCDTExtrapolatedPoints"); 
    }else{
      if(debug) std::cout<<"RPCHLT Invalid DTSegments collection"<<std::endl;
    }
  }

  if(inclcsc){
    edm::Handle<CSCSegmentCollection> allCSCSegments;
    iEvent.getByToken(cscSegments, allCSCSegments);
    if(allCSCSegments.isValid()){
	CSCSegtoRPC CSCClass(allCSCSegments, iSetup,iEvent,debug,ExtrapolatedRegion);
	std::unique_ptr<RPCRecHitCollection>  TheCSCPoints(CSCClass.thePoints());
	iEvent.put(std::move(TheCSCPoints), "RPCCSCExtrapolatedPoints"); 
    }else{
      if(debug) std::cout<<"RPCHLT Invalid CSCSegments collection"<<std::endl;
    }
  }
}

// ------------ method called once each job just before starting event loop  ------------
void 
RPCPointProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RPCPointProducer::endJob() {
}


