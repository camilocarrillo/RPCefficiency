/** \class DTandCSCSegmentsinTracks
 *
 *  Producer which take as input a muon track and return two containers 
 *  with the DTSegments and CSCSegments (respectively) used to fit it
 *
 *  $Date: 2012/02/15 14:19:57 $
 *  
 *  \author Juan Pablo Gomez - Uniandes
 */
#include <vector>

//standard include
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/TransientTrackingRecHit/interface/TransientTrackingRecHit.h"
#include "TrackingTools/PatternTools/interface/TrajectoryMeasurement.h" 
#include "TrackingTools/DetLayers/interface/DetLayer.h"
#include "TrackingTools/PatternTools/interface/TrajMeasLessEstim.h"
#include "RecoMuon/TrackingTools/interface/MuonPatternRecoDumper.h"
#include "RecoMuon/TransientTrackingRecHit/interface/MuonTransientTrackingRecHit.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
///

#include "DataFormats/MuonReco/interface/MuonTrackLinks.h"
#include "DataFormats/TrackReco/interface/TrackToTrackMap.h"
#include "DataFormats/MuonReco/interface/MuonTimeExtra.h"
#include "DataFormats/MuonReco/interface/MuonTimeExtraMap.h"


#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EDProducer.h"
//#include<fstream>

#include "DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h"
#include "DataFormats/CSCRecHit/interface/CSCSegmentCollection.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/EDGetToken.h"


class DTandCSCSegmentsinTracks : public edm::EDProducer {
   public:
      explicit DTandCSCSegmentsinTracks(const edm::ParameterSet&);
      ~DTandCSCSegmentsinTracks();
     
   private:
//      edm::InputTag cscSegments;
//      edm::InputTag dt4DSegments;
//      edm::InputTag tracks;
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      // ----------member data ---------------------------

      edm::EDGetTokenT<DTRecSegment4DCollection> dt4DSegments;
      edm::EDGetTokenT<CSCSegmentCollection> cscSegments;
      edm::EDGetTokenT<reco::TrackCollection> tracks;
      edm::EDGetTokenT<reco::MuonTimeExtraMap> staTimeToken;
      //edm::EDGetTokenT<reco::MuonTimeExtraMap> staRpcTimeToken;
 
      double timingCut;
      double timingErrorCut;
      double ptCut;
};

