# all
all: do-test

# do tests
do-test:
	cp ../../../rtm_corba/idl/*.idl .
	omniidl -bpython *.idl

# Cleanup
clean:
	rm -rf OpenRTM RTC RTM SDOPackage
	rm -rf OpenRTM__POA RTC__POA RTM__POA SDOPackage__POA
	rm -f *.pyc
	rm -f *_idl.py
	rm -f *.idl
	rm -f *~

