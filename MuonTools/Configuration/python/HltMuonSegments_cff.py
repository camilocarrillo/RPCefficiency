import FWCore.ParameterSet.Config as cms

from RecoMuon.Configuration.RecoMuon_cff import *

MuonSeed.DTSegmentLabel = cms.InputTag('hltDt4DSegments')
MuonSeed.CSCSegmentLabel = cms.InputTag('hltCscSegments')
ancientMuonSeed.DTRecSegmentLabel = cms.InputTag('hltDt4DSegments')
ancientMuonSeed.CSCRecSegmentLabel = cms.InputTag('hltCscSegments')
standAloneMuons.STATrajBuilderParameters.FilterParameters.RPCRecSegmentLabel = cms.InputTag("hltRpcRecHits")
standAloneMuons.STATrajBuilderParameters.FilterParameters.CSCRecSegmentLabel = cms.InputTag("hltCscSegments")
standAloneMuons.STATrajBuilderParameters.FilterParameters.DTRecSegmentLabel = cms.InputTag("hltDt4DSegments")
standAloneMuons.STATrajBuilderParameters.BWFilterParameters.CSCRecSegmentLabel = cms.InputTag("hltCscSegments")
standAloneMuons.STATrajBuilderParameters.BWFilterParameters.DTRecSegmentLabel = cms.InputTag("hltDt4DSegments")
standAloneMuons.STATrajBuilderParameters.BWFilterParameters.RPCRecSegmentLabel = cms.InputTag("hltRpcRecHits")
