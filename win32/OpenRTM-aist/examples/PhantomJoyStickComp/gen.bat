rtc-template.py -bcxx -bvcproject^
 --module-name=PhantomJoystick --module-desc="PhantomJoystick component"^
 --module-version=0.1 --module-vendor=S.Kurihara --module-category=Generic^
 --module-comp-type=DataFlowComponent --module-act-type=SPORADIC^
 --module-max-inst=10^
 --config="force_gain:std::vector<double>:1.0,1.0,1.0"^
 --config="vel_gain:std::vector<double>:1.0,1.0,1.0"^
 --inport=force:TimedDoubleSeq --outport=vel:TimedDoubleSeq
