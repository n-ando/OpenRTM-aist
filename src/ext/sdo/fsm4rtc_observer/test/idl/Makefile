all:
	touch __init__.py
	omniidl -bpython -I. SDOPackage.idl
	omniidl -bpython -I. ComponentObserver.idl

clean:
	rm -f *.py *.pyc
	rm -rf SDOPackage SDOPackage__POA 
	rm -rf RTC RTC__POA

