import web
import json
import sys, traceback, Ice
import LabrestAPI
import re

from web import form


urls = (
	'/', 'index',
	'/lock/(.*)', 'lock_res',
	'/unlock/(.*)', 'unlock_res',
	'/login', 'login',
	'/tree', 'tree'
)

web.config.debug = False
app = web.application(urls,globals())
render  = web.template.render('Web_templates')

myform = form.Form(
    form.Textbox('username',  value='Login', id="username", size="22", onfocus="if(this.value=='Login') this.value='';", onblur="if(this.value=='') this.value='Login'"),
    form.Password('authdata', value="Passwd", id='authdata', size ="22", onfocus="if(this.value=='Passwd') this.value='';", onblur="if(this.value=='') this.value='Passwd'")
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
		
def getIceSession(self):
    print 'getIceSession() called'
    ice_proxy_id = self.session_id + self.username
    icl = session_icl_map.get(ice_proxy_id, None)
    if not icl:
        print 'create new Ice session'
	base  = ic.stringToProxy("SimpleEntry:tcp -p 10000")
    	entry = LabrestAPI.EntryPrx.checkedCast(base)
	if not entry:
	    raise RuntimeError('Invalid proxy')
	icl = entry.login(self.username,self.authdata)
	session_icl_map[ice_proxy_id] = icl
    return icl	



web.session.Session.getIceSession = getIceSession
web.session.Session.username = 'guest'
web.session.Session.authdata = 'guest'
web.session.Session.__icl = None

session = web.session.Session(app,  web.session.DiskStore('sessions'))

class index:
    def GET(self):
	ress = ressToTree(session.getIceSession().getResourceManager().getAllResources())
	return render.guest_page(ress,myform)

class login:
    def GET(self):
	form = myform()
        form.validates()
	print form.value['username']
	session.username = form.value['username']
	session.authdata = form.value['authdata']
	print session.username
	s = session.getIceSession().getUserManager().getUser('admin')
	w = json.dumps(s.__dict__)
	print w
	return w

class tree:
    def res2dict(self, res):
	result = {};
	result = res.__dict__
	result['resLockStatus'] = res.resLockStatus.__dict__
	return result

    def GET(self):
	ress = session.getIceSession().getResourceManager().getAllResources()
	res_list = []
	for res in ress:
            res_list.append(self.res2dict(res))
	w = json.dumps(res_list)
	return w

class lock_res:
    def GET(self,res_id):
	session.getIceSession().getResourceManager().lockResource(res_id,-1)
	raise web.seeother('/') 

class unlock_res:
    def GET(self,res_id):
	session.getIceSession().getResourceManager().unlockResource(res_id)
	raise web.seeother('/')

if __name__ == '__main__':
    app.run()





