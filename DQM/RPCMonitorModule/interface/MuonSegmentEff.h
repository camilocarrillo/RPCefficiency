/** \class RPCEfficiency
 *
 * Class for RPC Monitoring using RPCDigi and DT and CSC Segments.
 *
 *  $Date: 2012/07/17 01:17:51 $
 *  $Revision: 1.1.1.1 $
 *
 * \author Camilo Carrillo (Uniandes)
 *
 */

#include <FWCore/Framework/interface/Frameworkfwd.h>
#include <FWCore/Framework/interface/EDAnalyzer.h>
#include <FWCore/Framework/interface/Event.h>
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"

#include <DataFormats/MuonDetId/interface/RPCDetId.h>
#include "FWCore/Framework/interface/ESHandle.h"
#include <Geometry/RPCGeometry/interface/RPCGeometry.h>
#include <Geometry/DTGeometry/interface/DTGeometry.h>
#include <Geometry/CSCGeometry/interface/CSCGeometry.h>

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include <DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h>
#include <DataFormats/CSCRecHit/interface/CSCSegmentCollection.h>

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/MuonReco/interface/MuonTrackLinks.h"
#include "DataFormats/TrackReco/interface/TrackToTrackMap.h"
#include "DataFormats/MuonReco/interface/MuonTimeExtra.h"
#include "DataFormats/MuonReco/interface/MuonTimeExtraMap.h"

#include<string>
#include<map>
#include<fstream>

class RPCDetId;
class TFile;
class TH1F;
class TFile;
class TCanvas;
class TH2F;
class TString;


class MuonSegmentEff : public edm::EDAnalyzer {
   public:
      explicit MuonSegmentEff(const edm::ParameterSet&);
      ~MuonSegmentEff();
      bool firstbook;
      virtual void beginJob() ;
      virtual void beginRun(const edm::Run&, const edm::EventSetup&);
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      std::map<std::string, MonitorElement*> bookDetUnitSeg(RPCDetId & detId,int nstrips,float stripw,float stripl);
      virtual void endRun(const edm::Run& r, const edm::EventSetup& iSetup);
      std::map<int,float> alignmentinfo;
      
      edm::ESHandle<RPCGeometry> rpcGeo;
      edm::ESHandle<DTGeometry> dtGeo;
      edm::ESHandle<CSCGeometry> cscGeo;

      MonitorElement * statistics;
      MonitorElement * selectedstatistics;
      MonitorElement * CosAngMB3MB4Whm2;
      MonitorElement * CosAngMB3MB4Whm1;
      MonitorElement * CosAngMB3MB4Wh0;
      MonitorElement * CosAngMB3MB4Wh1;
      MonitorElement * CosAngMB3MB4Wh2;
      MonitorElement * bxVsy;
   
      //Distance Strip
      MonitorElement * DistBorderClu1La1;
      MonitorElement * DistBorderClu1La2;
      MonitorElement * DistBorderClu1La3;
      MonitorElement * DistBorderClu1La4;
      MonitorElement * DistBorderClu1La5;
      MonitorElement * DistBorderClu1La6;

      MonitorElement * DistBorderClu2La1;
      MonitorElement * DistBorderClu2La2;
      MonitorElement * DistBorderClu2La3;
      MonitorElement * DistBorderClu2La4;
      MonitorElement * DistBorderClu2La5;
      MonitorElement * DistBorderClu2La6;

      MonitorElement * DistBorderClu3La1;
      MonitorElement * DistBorderClu3La2;
      MonitorElement * DistBorderClu3La3;
      MonitorElement * DistBorderClu3La4;
      MonitorElement * DistBorderClu3La5;
      MonitorElement * DistBorderClu3La6;
      
      //Ang Dependence

      MonitorElement * ScatterPlotAlphaCLSLa1;
      MonitorElement * ScatterPlotAlphaCLSLa2;
      MonitorElement * ScatterPlotAlphaCLSLa3;
      MonitorElement * ScatterPlotAlphaCLSLa4;
      MonitorElement * ScatterPlotAlphaCLSLa5;
      MonitorElement * ScatterPlotAlphaCLSLa6;

      MonitorElement * ScatterPlotAlphaPCLSLa1;
      MonitorElement * ScatterPlotAlphaPCLSLa2;
      MonitorElement * ScatterPlotAlphaPCLSLa3;
      MonitorElement * ScatterPlotAlphaPCLSLa4;
      MonitorElement * ScatterPlotAlphaPCLSLa5;
      MonitorElement * ScatterPlotAlphaPCLSLa6;

      MonitorElement * AngClu1La1;
      MonitorElement * AngClu1La2;
      MonitorElement * AngClu1La3;
      MonitorElement * AngClu1La4;
      MonitorElement * AngClu1La5;
      MonitorElement * AngClu1La6;

      MonitorElement * AngClu2La1;
      MonitorElement * AngClu2La2;
      MonitorElement * AngClu2La3;
      MonitorElement * AngClu2La4;
      MonitorElement * AngClu2La5;
      MonitorElement * AngClu2La6;

      MonitorElement * AngClu3La1;
      MonitorElement * AngClu3La2;
      MonitorElement * AngClu3La3;
      MonitorElement * AngClu3La4;
      MonitorElement * AngClu3La5;
      MonitorElement * AngClu3La6;
      
      //Residuals

      MonitorElement * hGlobalResClu1La1;
      MonitorElement * hGlobalResClu1La2;
      MonitorElement * hGlobalResClu1La3;
      MonitorElement * hGlobalResClu1La4;
      MonitorElement * hGlobalResClu1La5;
      MonitorElement * hGlobalResClu1La6;

      MonitorElement * hGlobalResClu2La1;
      MonitorElement * hGlobalResClu2La2;
      MonitorElement * hGlobalResClu2La3;
      MonitorElement * hGlobalResClu2La4;
      MonitorElement * hGlobalResClu2La5;
      MonitorElement * hGlobalResClu2La6;

      MonitorElement * hGlobalResClu3La1;
      MonitorElement * hGlobalResClu3La2;
      MonitorElement * hGlobalResClu3La3;
      MonitorElement * hGlobalResClu3La4;
      MonitorElement * hGlobalResClu3La5;
      MonitorElement * hGlobalResClu3La6;

      //Endcap  
      MonitorElement * hGlobalResClu1R3C;
      MonitorElement * hGlobalResClu1R3B;
      MonitorElement * hGlobalResClu1R3A;
      MonitorElement * hGlobalResClu1R2C;
      MonitorElement * hGlobalResClu1R2B; 
      MonitorElement * hGlobalResClu1R2A;

      MonitorElement * hGlobalResClu2R3C;
      MonitorElement * hGlobalResClu2R3B;
      MonitorElement * hGlobalResClu2R3A;
      MonitorElement * hGlobalResClu2R2C;
      MonitorElement * hGlobalResClu2R2B;
      MonitorElement * hGlobalResClu2R2A;

      MonitorElement * hGlobalResClu3R3C;
      MonitorElement * hGlobalResClu3R3B;
      MonitorElement * hGlobalResClu3R3A;

      MonitorElement * hGlobalResClu3R2C;
      MonitorElement * hGlobalResClu3R2B;
      MonitorElement * hGlobalResClu3R2A;

      //Residuals


      MonitorElement * hQResidualsRE1r3A;
      MonitorElement * hQResidualsRE1r3B;
      MonitorElement * hQResidualsRE1r3C;

      MonitorElement * hQResidualsRE1r2A;
      MonitorElement * hQResidualsRE1r2B;
      MonitorElement * hQResidualsRE1r2C;

      MonitorElement * hQResidualsRE2r3A;
      MonitorElement * hQResidualsRE2r3B;
      MonitorElement * hQResidualsRE2r3C;

      MonitorElement * hQResidualsRE2r2A;
      MonitorElement * hQResidualsRE2r2B;
      MonitorElement * hQResidualsRE2r2C;

      MonitorElement * hQResidualsRE3r3A;
      MonitorElement * hQResidualsRE3r3B;
      MonitorElement * hQResidualsRE3r3C;

      MonitorElement * hQResidualsRE3r2A;
      MonitorElement * hQResidualsRE3r2B;
      MonitorElement * hQResidualsRE3r2C;

      MonitorElement * hQResidualsRE4r3A;
      MonitorElement * hQResidualsRE4r3B;
      MonitorElement * hQResidualsRE4r3C;

      MonitorElement * hQResidualsRE4r2A;
      MonitorElement * hQResidualsRE4r2B;
      MonitorElement * hQResidualsRE4r2C;

      MonitorElement * hQResidualsODDRE1r3A;
      MonitorElement * hQResidualsODDRE1r3B;
      MonitorElement * hQResidualsODDRE1r3C;

      MonitorElement * hQResidualsODDRE1r2A;
      MonitorElement * hQResidualsODDRE1r2B;
      MonitorElement * hQResidualsODDRE1r2C;

      MonitorElement * hQResidualsODDRE2r3A;
      MonitorElement * hQResidualsODDRE2r3B;
      MonitorElement * hQResidualsODDRE2r3C;

      MonitorElement * hQResidualsODDRE2r2A;
      MonitorElement * hQResidualsODDRE2r2B;
      MonitorElement * hQResidualsODDRE2r2C;

      MonitorElement * hQResidualsODDRE3r3A;
      MonitorElement * hQResidualsODDRE3r3B;
      MonitorElement * hQResidualsODDRE3r3C;

      MonitorElement * hQResidualsODDRE3r2A;
      MonitorElement * hQResidualsODDRE3r2B;
      MonitorElement * hQResidualsODDRE3r2C;

      MonitorElement * hQResidualsODDRE4r3A;
      MonitorElement * hQResidualsODDRE4r3B;
      MonitorElement * hQResidualsODDRE4r3C;

      MonitorElement * hQResidualsODDRE4r2A;
      MonitorElement * hQResidualsODDRE4r2B;
      MonitorElement * hQResidualsODDRE4r2C;
      
 private:
      //timing 
      edm::InputTag theSTACollectionLabel;
      edm::EDGetTokenT<reco::TrackCollection> staMuonsToken;
      edm::EDGetTokenT<reco::MuonTimeExtraMap> staTimeToken;
      edm::EDGetTokenT<reco::MuonTimeExtraMap> staRpcTimeToken;
      edm::EDGetTokenT<reco::MuonTimeExtraMap> staDtTimeToken;
      edm::EDGetTokenT<reco::MuonTimeExtraMap> staCscTimeToken;
 
      MonitorElement *hTimeCombined;
      MonitorElement *hTimeRPC;
      MonitorElement *hTimeDT;
      MonitorElement *hTimeCSC;

      MonitorElement *hNTracks;

      MonitorElement *hInTimeMuons;
      MonitorElement *hInTimeMuons_eta;
      MonitorElement *hInTimeMuons_pt;
      MonitorElement *hInTimeMuons_charge;

      MonitorElement *hOutOfTimeMuons;
      MonitorElement *hOutOfTimeMuons_eta;
      MonitorElement *hOutOfTimeMuons_pt;
      MonitorElement *hOutOfTimeMuons_charge;

      double timingCut;
      int clsCut;
      
      std::vector<std::map<RPCDetId, int> > counter;
      std::vector<int> totalcounter;
      std::ofstream ofrej;
      bool debug;
      bool paper;
      bool inves;
      bool manualalignment;
      double rangestrips;
      int dupli;
      int charge;
      int pT;
      
      edm::EDGetTokenT<DTRecSegment4DCollection> dt4DSegments;
      edm::EDGetTokenT<CSCSegmentCollection> cscSegments;

      edm::EDGetTokenT<DTRecSegment4DCollection> selecteddt4DSegments;
      edm::EDGetTokenT<CSCSegmentCollection> selectedcscSegments;

      edm::EDGetTokenT<RPCRecHitCollection> rpcRecHitsLabel;
      edm::EDGetTokenT<RPCRecHitCollection> rpcDTPointsLabel;
      edm::EDGetTokenT<RPCRecHitCollection> rpcCSCPointsLabel;

      std::string rejected;
      std::string rollseff;
      
      std::map<std::string, std::map<std::string, MonitorElement*> >  meCollection;
      
      bool EffSaveRootFile;
      std::string EffRootFileName;
      std::string AlignmentinfoFile;
      std::string nameInLog;

      DQMStore * dbe;
};
