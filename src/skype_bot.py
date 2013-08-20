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
t=None

class Seeeion_ice:
    session = None
    lock = mutex.mutex()

    def write(self,sess):
	while not self.lock.testandset():
	    pass
	self.session = sess
	self.lock.unlock()

    def read(self):
	while not self.lock.testandset():
	    pass
	sess = self.session
	self.lock.unlock()
	return sess

session = Seeeion_ice()

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
	try:
	    while not events.empty():
	        ev = events.pop()
	        if ev.TypeEvent==4 or ev.TypeEvent==5:
	            res = session.read().getResourceManager().getResource(ev.resourceId)
                    res_d = []
	            while res.parentId != -1:
		        res_d.append("["+ res.name + " " + res.type.name+"] ")
		        res = session.read().getResourceManager().getResource(res.parentId)
 	    	    res_d.append("["+ res.name + " " + res.type.name+"] ")
	    	    res_descr = ""
	    	    while len(res_d) > 0:
		        res_descr = res_descr + res_d.pop()
	    	    lock_stat = ""
	    	    if ev.TypeEvent == 4:
		        lock_stat = "LOCK"
	    	    if ev.TypeEvent == 5:
		        lock_stat = "UNLOCK"
	    	    msg = "*** "+ev.userSrc+ " " + lock_stat +" "+res_descr+" ***"
	    	    print msg
	    	    skypeClient.SendMessage('alina_shejanova',msg)
#	    	    for chat in skypeClient.BookmarkedChats:
#                      chat.SendMessage(msg)
	except Ice.ConnectionRefusedException:
    	    print "connection refused"
	    do_refresh()
	except Ice.ObjectNotExistException:
	    print "session not exist"
	    xxx()
	sleep(5)


def do_refresh():
    while 1:
        try:
	    session.read().Refresh()
	except Ice.ConnectionRefusedException:
    	    print "connection refused"
	except Ice.ObjectNotExistException:
	    print "session not exist"
	    xxx()
	sleep(15)



class CallbackI(LabrestAPI.Callback):
    def doCallback(self, ev, current=None):
	events.push(ev)
	

def xxx():
	    print "create session"
	    ic = Ice.initialize(sys.argv)
	    base  = ic.stringToProxy("SimpleEntry:tcp -p 10000")
	    entry = LabrestAPI.EntryPrx.checkedCast(base)
	    if not entry:
		raise RuntimeError('Invalid proxy')
	    session.write(entry.login('guest','guest'))
	    adapter = ic.createObjectAdapter("")
	    ident = Ice.Identity()
	    ident.name = Ice.generateUUID()
	    ident.category = ""
	    print ident.name
	    cb = LabrestAPI.CallbackI()
	    adapter.add(cb, ident)
	    adapter.activate();
	    session.read().ice_getConnection().setAdapter(adapter)
	    session.read().getCallbackManager().registerCallback(ident)


LabrestAPI.CallbackI = CallbackI
try:
    ic = Ice.initialize(sys.argv)
    base  = ic.stringToProxy("SimpleEntry:tcp -p 10000")
    entry = LabrestAPI.EntryPrx.checkedCast(base)
    if not entry:
	raise RuntimeError('Invalid proxy')
    session.write(entry.login('guest','guest'))
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
    session.read().ice_getConnection().setAdapter(adapter)
    session.read().getCallbackManager().registerCallback(ident)
    cbThread = Thread(target = call2skype)
    cbThread.start()
    ic.waitForShutdown()
except Ice.ConnectionRefusedException:
    print "connection refused"
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


