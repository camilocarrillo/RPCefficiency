import FWCore.ParameterSet.Config as cms

#from RecoMuon.MuonIdentification.standAloneTimingFiller_cfi import *
from RecoMuon.MuonIdentification.DTTimingExtractor_cfi import *
from RecoMuon.MuonIdentification.CSCTimingExtractor_cfi import *
from RecoMuon.TrackingTools.MuonSegmentMatcher_cff import *

MuonSegmentMatcher_ = MuonSegmentMatcher.clone(MatchParameters = cms.PSet(DTsegments = cms.InputTag("hltDt4DSegments"),
                                                                          DTradius = cms.double(0.01),
                                                                          CSCsegments = cms.InputTag("hltCscSegments"),
                                                                          RPChits = cms.InputTag("hltRpcRecHits"),
                                                                          TightMatchDT = cms.bool(False),
                                                                          TightMatchCSC = cms.bool(True)
                                                                          
                                                                          )
                                               )

staUpdAtVtx = cms.EDProducer(
    'StandAloneTimingProducer',
    #TimingFillerBlock,
    TimingFillerParameters = cms.PSet(DTTimingExtractorBlock,
                                      CSCTimingExtractorBlock,
                                      MuonSegmentMatcher_,
                                      # On/off switches for combined time measurement
                                      UseDT  = cms.bool(True),
                                      UseCSC = cms.bool(True)
                                      ),
    MuonCollection = cms.InputTag("standAloneMuons","UpdatedAtVtx")
    )

staRegular = staUpdAtVtx.clone(
    MuonCollection = cms.InputTag("standAloneMuons"))

staSETUpdAtVtx = staUpdAtVtx.clone(
    MuonCollection = cms.InputTag("standAloneSETMuons"))

staSETRegular = staUpdAtVtx.clone(
    MuonCollection = cms.InputTag("standAloneSETMuons"))

