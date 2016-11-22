// -*- C++ -*-
//
// Class:      DTandCSCSegmentsinTracks
// 
/**\class DTandCSCSegmentsinTracks DTandCSCSegmentsinTracks.cc RecoLocalMuon/RPCRecHit/src/DTandCSCSegmentsinTracks.cc
   
Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//

#include "FWCore/Framework/interface/MakerMacros.h"
#include "DTandCSCSegmentsinTracks/DTandCSCSegmentsinTracks/interface/DTandCSCSegmentsinTracks.h"
#include "DataFormats/TrajectorySeed/interface/TrajectorySeedCollection.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"
#include "DataFormats/MuonDetId/interface/MuonSubdetId.h"
#include "DataFormats/MuonReco/interface/MuonTime.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/Common/interface/getRef.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment4D.h"
#include "DataFormats/TrackingRecHit/interface/RecSegment.h"

#include "DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h"
#include "DataFormats/CSCRecHit/interface/CSCSegmentCollection.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include "DataFormats/DTRecHit/interface/DTRecHitCollection.h"
#include "DataFormats/CSCRecHit/interface/CSCRecHit2DCollection.h"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"

#include <vector>


using namespace std;

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/EDGetToken.h"

DTandCSCSegmentsinTracks::DTandCSCSegmentsinTracks(const edm::ParameterSet& iConfig)
{
  dt4DSegments = consumes<DTRecSegment4DCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("dt4DSegments"));
  cscSegments = consumes<CSCSegmentCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("cscSegments"));
  tracks = consumes<reco::TrackCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("tracks"));
  
  staTimeToken=consumes<reco::MuonTimeExtraMap>(iConfig.getParameter<edm::InputTag>("MuonTimeMapLabel"));
  timingCut = iConfig.getUntrackedParameter<double>("timingCutValue");
  ptCut = iConfig.getUntrackedParameter<double>("ptCutValue");

  produces<DTRecSegment4DCollection>("SelectedDtSegments");
  produces<CSCSegmentCollection>("SelectedCscSegments");
}


DTandCSCSegmentsinTracks::~DTandCSCSegmentsinTracks(){
  
}

void DTandCSCSegmentsinTracks::produce(edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  edm::ESHandle<GlobalTrackingGeometry> theTrackingGeometry;
  iSetup.get<GlobalTrackingGeometryRecord>().get(theTrackingGeometry);
  
  edm::Handle<DTRecSegment4DCollection> all4DSegments;
  iEvent.getByToken(dt4DSegments, all4DSegments);	
  
  edm::Handle<CSCSegmentCollection> allCSCSegments;
  iEvent.getByToken(cscSegments, allCSCSegments);
  
  edm::Handle<reco::TrackCollection> alltracks;
  iEvent.getByToken(tracks,alltracks);
  
  edm::Handle<reco::MuonTimeExtraMap> timeMapCMB;
  iEvent.getByToken(staTimeToken,timeMapCMB); 
  
  reco::TrackCollection::const_iterator Track;
  DTRecSegment4DCollection::const_iterator segmentDT;
  CSCSegmentCollection::const_iterator segmentCSC;
  DTRecSegment4D segmentDTToStore;
  CSCSegment segmentCSCToStore;
  
  
  std::auto_ptr<DTRecSegment4DCollection> selectedDtSegments(new DTRecSegment4DCollection());
  std::auto_ptr<CSCSegmentCollection> selectedCscSegments(new CSCSegmentCollection());
   
  std::vector<CSCDetId> chamberIdCSC;
  std::vector<DTLayerId> chamberIdDT;
  
  //std::cout<<"nTracks: "<<alltracks->size()<<std::endl;
  for(unsigned int position = 0; position !=alltracks->size();   position++){
    if(alltracks->size()!=1) 
      continue;
   
    const reco::Track Track = alltracks->at(position); 
    double pt = Track.pt();
       
    if(pt<ptCut) 
      continue;  //Track Above 5GeV in pt
    
    //timing 
    reco::TrackRef staTrackRef(alltracks,position); 
    reco::MuonTimeExtra timec = timeMapCMB->get(staTrackRef.key());
    //reco::MuonTimeExtra timerpc = timeMapRPC->get(staTrackRef.key());
    // std::cout << "Time CMB = " << fabs(timec.timeAtIpInOut()) << " err = " << timec.timeAtIpInOutErr() << std::endl;
    //std::cout << "Time RPC = " << fabs(timerpc.timeAtIpInOut()) << " err = " << timerpc.timeAtIpInOutErr() << std::endl;
       
    if(fabs(timec.timeAtIpInOut()) > timingCut)
      continue;//take only intime muons 
    
    int hitsCounter = 0;
    for(trackingRecHit_iterator recHit2 = Track.recHitsBegin(); recHit2 != Track.recHitsEnd(); ++recHit2){
      hitsCounter++;
    }
    //std::cout<<"hitsCounter: "<<hitsCounter<<std::endl;
    
    for(trackingRecHit_iterator recHit = Track.recHitsBegin(); recHit != Track.recHitsEnd(); ++recHit){
      const GeomDet* geomDet = theTrackingGeometry->idToDet( (*recHit)->geographicalId() );
      if( geomDet->subDetector() == GeomDetEnumerators::DT ){
	edm::OwnVector<DTRecSegment4D> DTSegmentsVector;
	DTLayerId DTLayerIDfromRecHit( (*recHit)->geographicalId().rawId() );
	DTRecSegment4DCollection::range  range = all4DSegments->get(DTLayerIDfromRecHit);
	int counter=0;
	for (segmentDT = range.first; segmentDT!=range.second; ++segmentDT){
	  counter++;		  
	}
	if (counter==1){
	  bool isNewChamber = true;
	  for( std::vector<DTLayerId>::iterator chamberIdDTIt = chamberIdDT.begin(); chamberIdDTIt != chamberIdDT.end(); chamberIdDTIt++ ){
	    if( DTLayerIDfromRecHit.wheel() == (*chamberIdDTIt).wheel() &&  DTLayerIDfromRecHit.station() == (*chamberIdDTIt).station() && DTLayerIDfromRecHit.sector() == (*chamberIdDTIt).sector() ){
	      isNewChamber = false;
	    }
	  }
	  if (isNewChamber){
	    chamberIdDT.push_back(DTLayerIDfromRecHit);
	    DTSegmentsVector.push_back(*(range.first));
	    selectedDtSegments->put(DTLayerIDfromRecHit, DTSegmentsVector.begin(), DTSegmentsVector.end());
	  }
	}
      }	  
      
      if( geomDet->subDetector() == GeomDetEnumerators::CSC ){
	edm::OwnVector<CSCSegment> CSCSegmentsVector;
	CSCDetId CSCLayerIDfromRecHit( (*recHit)->geographicalId().rawId() );
	CSCSegmentCollection::range  range = allCSCSegments->get(CSCLayerIDfromRecHit);
	int counter=0;	
	for (segmentCSC = range.first; segmentCSC!=range.second; ++segmentCSC){
	  counter++;		  
	}
	if (counter==1){
	  bool isNewChamber = true;
	  for( std::vector<CSCDetId>::iterator chamberIdCSCIt = chamberIdCSC.begin(); chamberIdCSCIt != chamberIdCSC.end(); chamberIdCSCIt++ ){
	    if( CSCLayerIDfromRecHit.chamberId() == (*chamberIdCSCIt).chamberId() ){
	      isNewChamber = false;
	    }
	  }
	  if (isNewChamber){
	    chamberIdCSC.push_back(CSCLayerIDfromRecHit);
	    CSCSegmentsVector.push_back(*(range.first));
	    selectedCscSegments->put(CSCLayerIDfromRecHit, CSCSegmentsVector.begin(), CSCSegmentsVector.end());
	  }
	}
      }
    }
  }
 
  iEvent.put(selectedCscSegments,"SelectedCscSegments");
  iEvent.put(selectedDtSegments,"SelectedDtSegments");
}



// ------------ method called once each job just before starting event loop  ------------
void 
DTandCSCSegmentsinTracks::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DTandCSCSegmentsinTracks::endJob() {
}

DEFINE_FWK_MODULE(DTandCSCSegmentsinTracks);
