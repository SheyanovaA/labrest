import Skype4Py as skype
import sys, traceback, Ice
import LabrestAPI
import mutex
from time import sleep
from threading import Thread



skypeClient = skype.Skype()
skypeClient.Attach()
status = 0
ic = None
session = None
t=None

class EventsQueue:
    ev_queue = []
    lock = mutex.mutex()

    def push(self,ev):
	while not self.lock.testandset():
	    pass
	self.ev_queue.append(ev)
	self.lock.unlock()

    def empty(self):
	emp = None
	while not self.lock.testandset():
	    pass
	if len(self.ev_queue) == 0:
	    emp = 1
	else:
	    emp = 0
	self.lock.unlock()
	return emp

    def pop(self):
	while not self.lock.testandset():
	    pass
	ev = self.ev_queue.pop(0)
	self.lock.unlock()
	return ev


events = EventsQueue()       

def call2skype():
    while 1:
	while not events.empty():
	    ev = events.pop();
	    res = res_info(ev.resourceId)
	    res_descr = ""
	    msg = "*** "+ev.username+ " "+res_dscr
	    print msg
	sleep(5)


def do_refresh():
    while 1:
	session.Refresh()
	print "refresh"
	sleep(15)

def res_info(res_id):
    res = session.getResourceManager().getResource(res_id)
    return res


class CallbackI(LabrestAPI.Callback):
    def doCallback(self, ev, current=None):
	print ev
	events.push(ev)
	


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
    cbThread = Thread(target = call2skype)
    cbThread.start()
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


