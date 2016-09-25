import FWCore.ParameterSet.Config as cms

from RecoVertex.BeamSpotProducer.BeamSpot_cff import *
# UpdaterService = cms.Service("UpdaterService")

from RecoLocalMuon.Configuration.RecoLocalMuon_cff import *
from RecoMuon.Configuration.RecoMuon_cff import *
# from RecoMuon.MuonSeedGenerator.standAloneMuonSeeds_cff import *   #piet 20141124
# from RecoMuon.StandAloneMuonProducer.standAloneMuons_cff import *  #piet 20141124


# from Configuration.StandardSequences.Geometry_cff import * --> dangerous guy. overwrites geometry of main file
from Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff import *
# from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import * --> dangerous guy. overwrites geometry of main file
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFrontierConditions
# GlobalTag.globaltag = 'GR_P_V17::All'


muonstandalonereco = cms.Sequence(offlineBeamSpot + standAloneMuonSeeds * standAloneMuons)
muonlocalstandalonereco = cms.Sequence(muonlocalreco * muonstandalonereco)
