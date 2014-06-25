import FWCore.ParameterSet.Config as cms


triggerFilter = cms.EDFilter('TriggerFilter',
                        gtDigis = cms.InputTag('hltGtDigis')
)




