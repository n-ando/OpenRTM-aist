all: clean omniidl omniidlpy idlj rtorb orbitidl

IDLFILES = \
	BasicDataType.idl      \
	DataPort.idl           \
	ExtendedDataTypes.idl  \
	InterfaceDataTypes.idl \
	Manager.idl            \
	OpenRTM.idl            \
	RTC.idl                \
	SDOPackage.idl         \
	ManipulatorCommonInterface_DataTypes.idl  \
	ManipulatorCommonInterface_Common.idl     \
	ManipulatorCommonInterface_Middle.idl     \
	Img.idl

omniidl:
	rm  -rf omniidl
	mkdir omniidl
	for f in $(IDLFILES) ; do \
		omniidl -bcxx -I.. -Comniidl ../$$f ; \
	done
	
omniidlpy:
	rm -rf omniidlpy
	mkdir omniidlpy
	for f in $(IDLFILES) ; do \
		omniidl -bpython -I.. -Comniidlpy ../$$f ; \
	done
	
idlj:
	rm -rf java
	mkdir java
	for f in $(IDLFILES) ; do \
		idlj -DIDLJ -i ../ -td java ../$$f ; \
	done
	
rtorb:
	rm  -rf rtorb
	mkdir rtorb
	cd rtorb
	for f in $(IDLFILES) ; do \
		(cd rtorb ; rtorb-idl --skeleton-impl ../../$$f;) \
	done
	cd ..
	
orbitidl:
	rm  -rf orbitidl
	mkdir orbitidl
	for f in $(IDLFILES) ; do \
		orbit-idl-2 --showcpperrors --idlwarnlevel=4 --output-dir=orbitidl ../$$f;\
	done
	cd ..
	
clean:
	rm -rf omniidl
	rm -rf omniidlpy
	rm -rf java
	rm -rf rtorb
	rm -rf orbitidl
	rm -rf cxx python java
	rm -rf _SDOPackage