import FWCore.ParameterSet.Config as cms

from RecoMuon.Configuration.RecoMuon_cff import *

standAloneMuons.STATrajBuilderParameters.FilterParameters.EnableRPCMeasurement = cms.bool(False)
standAloneMuons.STATrajBuilderParameters.BWFilterParameters.EnableRPCMeasurement = cms.bool(False)
