import web
import sys, traceback, Ice
import LabrestAPI

from web import form

urls = (
	'/', 'index',
	'/lock/(.*)', 'lock_res',
	'/unlock/(.*)', 'unlock_res'
)

web.config.debug = False
app = web.application(urls,globals())
render  = web.template.render('Web_templates')

myform = form.Form(
    form.Textbox('username'),
    form.Textbox('authdata')
)

ic = Ice.initialize(sys.argv)

session_icl_map = {}

def ressToTree(ress):
    lres = []
    l = len(ress)
    stk = []
    stk.append(-1)
    while l>len(lres):
	p_id = stk.pop()
	for res in ress:
	    if res.parentId == p_id:
	        r = {'layer':len(stk), 'resource':res}
		if r not in lres:
		    stk.append(p_id)
		    stk.append(res.id)
	            del res
		    lres.append(r)
	            break
    return lres
		
def getIceSession(self,username,authdate):
    print 'getIceSession() called'
    icl = session_icl_map.get(self.session_id, None)
    if not icl:
        print 'create new Ice session'
	base  = ic.stringToProxy("SimpleEntry:tcp -p 10000")
    	entry = LabrestAPI.EntryPrx.checkedCast(base)
	if not entry:
	    raise RuntimeError('Invalid proxy')
	icl = entry.login(username,authdate)
	session_icl_map[self.session_id] = icl
    return icl	

web.session.Session.getIceSession = getIceSession
web.session.Session.__icl = None

session = web.session.Session(app,  web.session.DiskStore('sessions'))

class index:
    def GET(self):
	ress = ressToTree(session.getIceSession('us','1').getResourceManager().getAllResources())
	return render.page(ress,myform)

class lock_res:
    def GET(self,res_id):
#	return res_id
	session.getIceSession('us','1').getResourceManager().lockResource(res_id,-1)
	raise web.seeother('/') 

class unlock_res:
    def GET(self,res_id):
#	return res_id
	session.getIceSession('us','1').getResourceManager().unlockResource(res_id)
	raise web.seeother('/')

if __name__ == '__main__':
    app.run()





