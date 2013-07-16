import web
import json
import sys, traceback, Ice
import LabrestAPI

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



session_icl_map = {}
session_user_map = {}
User = {'username':'guest', 'authdata':'guest'}
		
def getIceSession(self,user):
    uslogin = self.getUser()
    icl = session_icl_map.get(self.session_id, None)
    if not icl or user != uslogin:
	print uslogin
	print user
        print 'create new Ice session'
	ic = Ice.initialize(sys.argv)
	base  = ic.stringToProxy("SimpleEntry:tcp -p 10000")
    	entry = LabrestAPI.EntryPrx.checkedCast(base)
	if not entry:
	    raise RuntimeError('Invalid proxy')
	icl = entry.login(uslogin['username'],uslogin['authdata'])
	session_icl_map[self.session_id] = icl
    return icl	

def setUser(self,new_user):
    session_user_map[self.session_id]=new_user;
    return None

def getUser(self):
    user = session_user_map.get(self.session_id, None)
    return user

web.session.Session.getIceSession = getIceSession
web.session.Session.setUser = setUser
web.session.Session.getUser = getUser
web.session.Session.__icl = None

session = web.session.Session(app,  web.session.DiskStore('sessions'))

class index:
    def GET(self):
	session.setUser(User)
	return render.guest_page(myform)

class login:
    def GET(self):
	s = session.getIceSession(session.getUser()).getUserManager().getUser(session.getUser()['username'])
	s = json.dumps({"user":s.__dict__})
	user_ = {}
	user_['name'] = s.name
	user_['auth'] = s.auth 
	user_['group'] = s.group
	print json.dumps(user_)
	return json.dumps(user_)

    def POST(self):
	form = myform()
        form.validates()
	user = {'username':form.value['username'], 'authdata':form.value['authdata']}
	session.getIceSession(user)
	session.setUser(user)
	return None

class tree:

    def ress2Tree(self,ress):
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

    def res2dict(self, res):
	result = {}
	result['logined_user'] = session.getUser()['username'];
	result['id'] = res['resource'].id
	result['name'] = res['resource'].name
	result['description'] = res['resource'].description
	result['parentId'] = res['resource'].parentId
	result['typeName'] = session.getIceSession(session.getUser()).getResourceManager().getResourceType(res['resource'].typeId).name
	result['startTime'] = res['resource'].resLockStatus.startTime
	result['duration'] = res['resource'].resLockStatus.duration
	result['username'] = res['resource'].resLockStatus.username
	return result

    def GET(self):
	ress = self.ress2Tree(session.getIceSession(session.getUser()).getResourceManager().getAllResources())
	res_list = []
	for res in ress:
            res_list.append(self.res2dict(res))
	w = {"resources":res_list}
	w = json.dumps(w)
	return w

class lock_res:
    def GET(self,res_id):
	session.getIceSession(session.getUser()).getResourceManager().lockResource(res_id,-1)
	raise web.seeother('/tree') 

class unlock_res:
    def GET(self,res_id):
	session.getIceSession(session.getUser()).getResourceManager().unlockResource(res_id)
	raise web.seeother('/tree')

if __name__ == '__main__':
    app.run()





