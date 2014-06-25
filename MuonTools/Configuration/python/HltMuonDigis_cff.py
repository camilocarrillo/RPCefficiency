import FWCore.ParameterSet.Config as cms

from RecoLocalMuon.Configuration.RecoLocalMuon_cff import *

rpcRecHits.rpcDigiLabel = cms.InputTag("hltMuonRPCDigis")
dt1DRecHits.dtDigiLabel = cms.InputTag('hltMuonDTDigis')
dt4DSegments.dtDigiLabel = cms.InputTag('hltMuonDTDigis')
dt1DCosmicRecHits.dtDigiLabel = cms.InputTag('hltMuonDTDigis')
dt4DCosmicSegments.dtDigiLabel = cms.InputTag('hltMuonDTDigis')
csc2DRecHits.stripDigiTag = cms.InputTag('hltMuonCSCDigis','MuonCSCStripDigi')
csc2DRecHits.wireDigiTag = cms.InputTag('hltMuonCSCDigis','MuonCSCWireDigi')
