from STASkim.ProducerTest.standAloneTiming_cfi import*

standAloneTiming = cms.Sequence(staUpdAtVtx + staRegular)
#standAloneTiming = cms.Sequence(staRegular)
#standAloneTiming = cms.Sequence(staUpdAtVtx)
