import sys, traceback, Ice
import LabrestAPI
from time import sleep
from threading import Thread



status = 0
ic = None
session = None
   
def do_refresh():
    while 1:
	session.Refresh()
	print "refresh"
	sleep(15)

class CallbackI(LabrestAPI.Callback):
    def doCallback(self, ev, current=None):
	print "!!!!"
	
LabrestAPI.CallbackI = CallbackI
try:
    ic = Ice.initialize(sys.argv)
    base  = ic.stringToProxy("SimpleEntry:tcp -p 10000")
    entry = LabrestAPI.EntryPrx.checkedCast(base)
    if not entry:
	raise RuntimeError('Invalid proxy')
    session = entry.login('guest','guest')
    t=Thread(target=do_refresh)
    t.start()
    adapter = ic.createObjectAdapter("")
    ident = Ice.Identity()
    ident.name = Ice.generateUUID()
    ident.category = ""
    print ident.name
    cb = LabrestAPI.CallbackI()
    adapter.add(cb, ident)
    adapter.activate();
    session.ice_getConnection().setAdapter(adapter)
    session.getCallbackManager().registerCallback(ident)
    print session.getResourceManager().getResource(5)
    ic.waitForShutdown()
except:
    traceback.print_exc()
    status = 1

if ic:
    # Clean up
    try:
        ic.destroy()
    except:
        traceback.print_exc()
        status = 1

sys.exit(status)


