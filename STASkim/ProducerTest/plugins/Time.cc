//
// Original Author:  Federica Primavera
//         Created:  Thu, 27 Nov 2014 13:58:57 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/MuonReco/interface/MuonTimeExtra.h"
#include "DataFormats/MuonReco/interface/MuonTimeExtraMap.h"
#include "RecoMuon/MuonIdentification/interface/DTTimingExtractor.h"
#include "RecoMuon/MuonIdentification/interface/CSCTimingExtractor.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHit.h"

#include "RecoMuon/MuonIdentification/interface/TimeMeasurementSequence.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"

#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "STASkim/ProducerTest/plugins/Time.h"

namespace edm {
  class ParameterSet;
  class EventSetup;
  class InputTag;
  class CSCTimingExtractor;
  class DTTimingExtractor;
}

// constructors
Time::Time(const edm::ParameterSet& iConfig, edm::ConsumesCollector&& iC){

  // Load parameters for the DTTimingExtractor
  edm::ParameterSet dtTimingParameters = iConfig.getParameter<edm::ParameterSet>("DTTimingParameters");
  // theDTTimingExtractor_ = new DTTimingExtractor(dtTimingParameters,iC);
  
  // Load parameters for the CSCTimingExtractor
  edm::ParameterSet cscTimingParameters = iConfig.getParameter<edm::ParameterSet>("CSCTimingParameters");
  //theCSCTimingExtractor_ = new CSCTimingExtractor(cscTimingParameters,iC);

  // Fallback mechanism for old configs (there the segment matcher was built inside the timing extractors)
  edm::ParameterSet matchParameters;
  if (iConfig.existsAs<edm::ParameterSet>("MatchParameters")) 
    matchParameters = iConfig.getParameter<edm::ParameterSet>("MatchParameters");
  else 
    matchParameters = dtTimingParameters.getParameter<edm::ParameterSet>("MatchParameters");
  
  theMatcher_ = std::make_unique<MuonSegmentMatcher>(matchParameters, iC);
  theDTTimingExtractor_ = std::make_unique<DTTimingExtractor>(dtTimingParameters,theMatcher_.get());
  theCSCTimingExtractor_ = std::make_unique<CSCTimingExtractor>(cscTimingParameters,theMatcher_.get());
    
  useDT_ = iConfig.getParameter<bool>("UseDT");
  useCSC_ = iConfig.getParameter<bool>("UseCSC");
}

// and destructor
Time::~Time(){
  //if (theDTTimingExtractor_) delete theDTTimingExtractor_;
  //if (theCSCTimingExtractor_) delete theCSCTimingExtractor_;
}


////// working
void Time::fillTime(const reco::TrackRef& muon, 
		    reco::MuonTimeExtra& dtTime, 
		    reco::MuonTimeExtra& cscTime, 
		    reco::MuonTimeExtra& rpcTime,
		    // reco::MuonTime& rpcTime,
		    reco::MuonTimeExtra& combinedTime, 
		    edm::Event& iEvent, 
		    const edm::EventSetup& iSetup ){

  TimeMeasurementSequence dtTmSeq,cscTmSeq;
  
  if ( !(muon.isNull()) ) {
    theDTTimingExtractor_->fillTiming(dtTmSeq, muon, iEvent, iSetup);
    theCSCTimingExtractor_->fillTiming(cscTmSeq, muon, iEvent, iSetup);
  }
  
  // Fill DT-specific timing information block     
  fillTimeFromMeasurements(dtTmSeq, dtTime);
  // Fill CSC-specific timing information block     
  fillTimeFromMeasurements(cscTmSeq, cscTime);
  // Fill RPC-specific timing information block     
  fillRPCTime(muon, rpcTime, iEvent);

  // Combine the TimeMeasurementSequences from all subdetectors
  TimeMeasurementSequence combinedTmSeq;
  combineTMSequences(muon,dtTmSeq,cscTmSeq,combinedTmSeq);  // da riscrivere per le track
  
  // Fill the master timing block
  fillTimeFromMeasurements(combinedTmSeq, combinedTime);
     
  LogTrace("MuonTime") << "Global 1/beta: " << combinedTime.inverseBeta() << " +/- " << combinedTime.inverseBetaErr()<<std::endl;
  LogTrace("MuonTime") << "  Free 1/beta: " << combinedTime.freeInverseBeta() << " +/- " << combinedTime.freeInverseBetaErr()<<std::endl;
  LogTrace("MuonTime") << "  Vertex time (in-out): " << combinedTime.timeAtIpInOut() << " +/- " << combinedTime.timeAtIpInOutErr()
		       << "  # of points: " << combinedTime.nDof() <<std::endl;
  LogTrace("MuonTime") << "  Vertex time (out-in): " << combinedTime.timeAtIpOutIn() << " +/- " << combinedTime.timeAtIpOutInErr()<<std::endl;
  LogTrace("MuonTime") << "  direction: "   << combinedTime.direction() << std::endl;
  
 }

void Time::fillTimeFromMeasurements( const TimeMeasurementSequence& tmSeq, reco::MuonTimeExtra &muTime ) {
  
  std::vector <double> x,y;
  double invbeta=0, invbetaerr=0;
  double vertexTime=0, vertexTimeErr=0, vertexTimeR=0, vertexTimeRErr=0;    
  double freeBeta, freeBetaErr, freeTime, freeTimeErr;

  if (tmSeq.dstnc.size()<=1) return;
  
  for (unsigned int i=0;i<tmSeq.dstnc.size();i++) {
      invbeta+=(1.+tmSeq.local_t0.at(i)/tmSeq.dstnc.at(i)*30.)*tmSeq.weightInvbeta.at(i)/tmSeq.totalWeightInvbeta;
      x.push_back(tmSeq.dstnc.at(i)/30.);
      y.push_back(tmSeq.local_t0.at(i)+tmSeq.dstnc.at(i)/30.);
      vertexTime+=tmSeq.local_t0.at(i)*tmSeq.weightTimeVtx.at(i)/tmSeq.totalWeightTimeVtx;
      vertexTimeR+=(tmSeq.local_t0.at(i)+2*tmSeq.dstnc.at(i)/30.)*tmSeq.weightTimeVtx.at(i)/tmSeq.totalWeightTimeVtx;
  }
  
  double diff;
  for (unsigned int i=0;i<tmSeq.dstnc.size();i++) {
    diff=(1.+tmSeq.local_t0.at(i)/tmSeq.dstnc.at(i)*30.)-invbeta;
    invbetaerr+=diff*diff*tmSeq.weightInvbeta.at(i);
    diff=tmSeq.local_t0.at(i)-vertexTime;
    vertexTimeErr+=diff*diff*tmSeq.weightTimeVtx.at(i);
    diff=tmSeq.local_t0.at(i)+2*tmSeq.dstnc.at(i)/30.-vertexTimeR;
    vertexTimeRErr+=diff*diff*tmSeq.weightTimeVtx.at(i);
  }
  
  double cf = 1./(tmSeq.dstnc.size()-1);
  invbetaerr=sqrt(invbetaerr/tmSeq.totalWeightInvbeta*cf);
  vertexTimeErr=sqrt(vertexTimeErr/tmSeq.totalWeightTimeVtx*cf);
  vertexTimeRErr=sqrt(vertexTimeRErr/tmSeq.totalWeightTimeVtx*cf);
  
  muTime.setInverseBeta(invbeta);
  muTime.setInverseBetaErr(invbetaerr);
  muTime.setTimeAtIpInOut(vertexTime);
  muTime.setTimeAtIpInOutErr(vertexTimeErr);
  muTime.setTimeAtIpOutIn(vertexTimeR);
  muTime.setTimeAtIpOutInErr(vertexTimeRErr);
  
  rawFit(freeBeta, freeBetaErr, freeTime, freeTimeErr, x, y);
  
  muTime.setFreeInverseBeta(freeBeta);
  muTime.setFreeInverseBetaErr(freeBetaErr);
  muTime.setNDof(tmSeq.dstnc.size());
}


void Time::fillRPCTime(const reco::TrackRef& muonref, reco::MuonTimeExtra &rpcTime, edm::Event& iEvent ) {
  //MuonTimingFiller::fillRPCTime( const reco::Muon& muon, reco::MuonTime &rpcTime, edm::Event& iEvent ) {

  int nrpc=0;
  double trpc=0,trpc2=0,trpcerr=0;

  //  reco::TrackRef staTrack = muon.standAloneMuon();
  //if (staTrack.isNull()) return;

  std::vector<const RPCRecHit*> rpcHits = theMatcher_->matchRPC(*muonref,iEvent);
  for (std::vector<const RPCRecHit*>::const_iterator hitRPC = rpcHits.begin(); hitRPC != rpcHits.end(); hitRPC++) {
    //noi abbiamo direttamente gli hits delle rpc senza fare giri strani
    //for(RPCRecHitCollection::const_iterator recHit = rpcHits->begin(); recHit != rpcHits->end(); recHit++){ 
    nrpc++;
    // trpc+=recHit->BunchX();
    // trpc2+=recHit->BunchX()*recHit->BunchX();
    
    trpc+=(*hitRPC)->BunchX();
    trpc2+=(*hitRPC)->BunchX()*(*hitRPC)->BunchX();
  }
  
  if (nrpc==0) return;
  
  trpc2=trpc2/(double)nrpc*25.*25.;
  trpc=trpc/(double)nrpc*25.;
  trpcerr=sqrt(trpc2-trpc*trpc);

  // rpcTime.timeAtIpInOut=trpc;
  // rpcTime.timeAtIpInOutErr=trpcerr;
  // rpcTime.nDof=nrpc;
  
  // // currently unused
  // rpcTime.timeAtIpOutIn=0.;  
  // rpcTime.timeAtIpOutInErr=0.;

  rpcTime.setTimeAtIpInOut(trpc);
  rpcTime.setTimeAtIpInOutErr(trpcerr);
  rpcTime.setNDof(nrpc);
  
  // currently unused
  rpcTime.setTimeAtIpOutIn(0.);  
  rpcTime.setTimeAtIpOutInErr(0.);
}



void Time::combineTMSequences( const reco::TrackRef& muon, 
			       const TimeMeasurementSequence& dtSeq, 
			       const TimeMeasurementSequence& cscSeq, 
			       TimeMeasurementSequence &cmbSeq ) {
  
  if (useDT_) for (unsigned int i=0;i<dtSeq.dstnc.size();i++) {
      cmbSeq.dstnc.push_back(dtSeq.dstnc.at(i));
      cmbSeq.local_t0.push_back(dtSeq.local_t0.at(i));
      cmbSeq.weightTimeVtx.push_back(dtSeq.weightTimeVtx.at(i));
      cmbSeq.weightInvbeta.push_back(dtSeq.weightInvbeta.at(i));
      
      cmbSeq.totalWeightTimeVtx+=dtSeq.weightTimeVtx.at(i);
      cmbSeq.totalWeightInvbeta+=dtSeq.weightInvbeta.at(i);
    }
  
  if (useCSC_) for (unsigned int i=0;i<cscSeq.dstnc.size();i++) {
      cmbSeq.dstnc.push_back(cscSeq.dstnc.at(i));
      cmbSeq.local_t0.push_back(cscSeq.local_t0.at(i));
      cmbSeq.weightTimeVtx.push_back(cscSeq.weightTimeVtx.at(i));
      cmbSeq.weightInvbeta.push_back(cscSeq.weightInvbeta.at(i));

      cmbSeq.totalWeightTimeVtx+=cscSeq.weightTimeVtx.at(i);
      cmbSeq.totalWeightInvbeta+=cscSeq.weightInvbeta.at(i);
    }
} 

void Time::rawFit(double &a, double &da, double &b, double &db, const std::vector<double>& hitsx, const std::vector<double>& hitsy) {

  double s=0,sx=0,sy=0,x,y;
  double sxx=0,sxy=0;

  a=b=0;
  if (hitsx.size()==0) return;
  if (hitsx.size()==1) {
    b=hitsy[0];
  } else {
    for (unsigned int i = 0; i != hitsx.size(); i++) {
      x=hitsx[i];
      y=hitsy[i];
      sy += y;
      sxy+= x*y;
      s += 1.;
      sx += x;
      sxx += x*x;
    }
    
    double d = s*sxx - sx*sx;
    b = (sxx*sy- sx*sxy)/ d;
    a = (s*sxy - sx*sy) / d;
    da = sqrt(sxx/d);
    db = sqrt(s/d);
  }
}

