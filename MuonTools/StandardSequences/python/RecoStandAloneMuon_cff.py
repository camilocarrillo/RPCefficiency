import FWCore.ParameterSet.Config as cms

from RecoVertex.BeamSpotProducer.BeamSpot_cff import *
UpdaterService = cms.Service("UpdaterService")

from RecoLocalMuon.Configuration.RecoLocalMuon_cff import *
from RecoMuon.Configuration.RecoMuon_cff import *

from Configuration.StandardSequences.Geometry_cff import *
from Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff import *
from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *

# https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFrontierConditions
# GlobalTag.globaltag = 'GR_P_V17::All'

muonstandalonereco = cms.Sequence(offlineBeamSpot + standAloneMuonSeeds * standAloneMuons)
muonlocalstandalonereco = cms.Sequence(muonlocalreco * muonstandalonereco)
