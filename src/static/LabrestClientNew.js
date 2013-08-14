var oldJson = null;

var visible_na = false;


change_vis_na = function() {
    jQuery('input#na_button').val((visible_na) ? "Скрыть N/A Cards" : "Показать N/A Cards");
    jQuery("#leftcol div:contains('N/A')").css('display', (visible_na) ? "block":"none");
}


createTree = function(ress) {
    for (i in ress) {
	var res = ress[i];
	var line = createLine(res);
	jQuery('#leftcol').append(line);
    };
}


createLine = function(res) {
    var d = $('<div>');
    d.attr('id', 'res-' + res.id);
    d.css('margin-left', '' + (res.layer * 30) + 'px');

    var s_lock = $('<input>');
    s_lock.attr('type', 'checkbox');
    s_lock.attr('id', 'res-lock-' + res.id);
    s_lock.attr('checked', (res.startTime == -1) ? false : true);
    s_lock.attr('disabled', false );  
    s_lock.click(function() {ch_lock(res.id, (res.startTime == -1) ? false : true);});
    d.append(s_lock);

    var s_name = $('<span>');
    s_name.attr('id', 'res-name-' + res.id);
    s_name.html(" "+res.name);
    d.append(s_name);

    var s_type_name = $('<span>');
    s_type_name.attr('id', 'res-type-name-' + res.id);
    s_type_name.html(" "+res.typeName);
    d.append(s_type_name);

    var s_discr = $('<span>');
    s_discr.attr('id', 'res-discr-' + res.id);
    s_discr.html(" " + res.description);
    d.append(s_discr);

    var s_temp0 = $('<span>');
    s_temp0.attr('id', 'res-temp0-' + res.id);
    s_temp0.html(" зарезервировано ");
    s_temp0.css('display', (res.startTime == -1) ?'none':"inline")
    d.append(s_temp0);

    var s_time = $('<span>');
    s_time.attr('id', 'res-time-' + res.id);
    s_time.html((res.startTime == -1)?"":((res.duration == -1 || res.remainTime > 86400)? " c "+ createTimeStr(res.startTime):" на "+createTimeStr(res.remainTime)));
    d.append(s_time);

    var s_temp1 = $('<span>');
    s_temp1.attr('id', 'res-temp1-' + res.id);
    s_temp1.html(" пользователем:");
    s_temp1.css('display', (res.startTime == -1) ?'none':"inline");
    d.append(s_temp1);

    var s_user = $('<span>');
    s_user.attr('id', 'res-user-' + res.id);
    s_user.html((res.startTime == -1)? "" : " "+res.username);
    d.append(s_user);

    return d;
}


updateTree = function(oldTree, newTree) {
    var n = 0;
    for (i=0; i<oldTree.length; i++) {
        var ins_mas = [];
	var findInNew = false;
	for (j=n; j<newTree.length; j++) {
	    if (oldTree[i].id == newTree[j].id) {
		findInNew = true;
		updateLine(oldTree[i],newTree[j]);
	        break;
	    } else {
		ins_mas.push(newTree[j]);
	    };
	};
	n=(j==newTree.length-1) ? n : j+1;
	if (findInNew) {
	    for (j=0; j<ins_mas.length; j++) {
		insertBeforeLine(oldTree[i],ins_mas[j]);
	    }
	} else {
	    deleteLine(oldTree[i]);
	}
    }    
}

updateLine = function(old_res,new_res) {
    if (old_res.description != new_res.description) {jQuery("#res-discr-"+new_res.id).html(" "+new_res.description);}
    if (old_res.duration != new_res.duration) {}
    if (old_res.layer != new_res.layer) {jQuery("#res-"+new_res.id).css('margin-left', '' + (res.layer * 30) + 'px');}
    if (old_res.name != new_res.name) {jQuery("#res-name-"+new_res.id).html(" "+new_res.name);};
    if (old_res.startTime != new_res.startTime) { 
 	var s_lock = $('<input>');
    	s_lock.attr('type', 'checkbox');
    	s_lock.attr('id', 'res-lock-' + new_res.id);
    	s_lock.attr('checked', (new_res.startTime == -1) ? false : true);
    	s_lock.attr('disabled', true);
    	s_lock.click(function() {ch_lock(new_res.id, (new_res.startTime == -1) ? false : true);});
	jQuery("#res-lock-"+new_res.id).replaceWith(s_lock);    
    };
    jQuery("#res-temp0-"+new_res.id).css('display', (new_res.startTime == -1) ? "none" : "inline");
    jQuery("#res-time-"+new_res.id).html((new_res.startTime == -1)?"":((new_res.duration == -1 || new_res.remainTime > 86400)? " c "+ createTimeStr(new_res.startTime):" на "+createTimeStr(new_res.remainTime)));

    if (old_res.typeName != new_res.typeName) {jQuery("#res-type-name-"+new_res.id).html(" "+new_res.typeName);}
    if (old_res.username != new_res.username) {
	jQuery("#res-temp1-"+new_res.id).css('display', (new_res.startTime == -1) ? "none" : "inline");
	jQuery("#res-user-"+new_res.id).html(" "+ new_res.username);
    }
    
    jQuery("#"+old_res.id)
}

insertBeforeLine = function(old_res, new_res) { 
    //insert new line bafore old
    jQuery('#res-'+old_res.id).prepend(createLine(new_res));
}

deleteLine = function(old_res) {
    jQuery("#res-"+old_res.id).remove();
}

createTimeStr = function(seconds) {
    var time = new Date(seconds*1000);
    var day = time.getDate();
    var month = time.getMonth();
    var year = time.getFullYear();
    var hours = (seconds < 86400) ? time.getUTCHours() : time.getHours(); 
    var minutes = (seconds < 86400) ? time.getUTCMinutes() : time.getMinutes(); 
    var second =  (seconds < 86400) ? time.getUTCSeconds() :time.getSeconds();
    var time_str = (seconds < 86400) ? ''+to2digit(hours)+':'+to2digit(minutes)+':'+to2digit(second)+' ' : ''+to2digit(hours)+':'+to2digit(minutes)+':'+to2digit(second)+' ('+to2digit(day)+'.'+to2digit(month)+'.'+year+') ';
    return time_str;
}

to2digit = function(num) {
    if (num > 9 ) { return ''+num;}
    else {return '0'+num;}
}

tree = function() {
    jQuery.getJSON('/tree',
		   {})
                   .done(function(json) {
		       if (!oldJson) {
		           createTree(json.resources);
		       } else {
			   updateTree(oldJson.resources, json.resources);
		       }
		       oldJson = json;
                       access2lock(json.resources[0].logined_user);
		       updateUserInfo();
		       json = 0;
		   });
                  
}


login = function(user_name,user_auth) {
    jQuery.getJSON("/login", {username : user_name, authdata :user_auth},
		       function(json) {
			   if (json.error == 1) { alert ("Неверное имя пользователя или пароль!");}
			else { updateUser(json.user);};
		       });
}


updateUser = function(user) {
    if (user.name != 'guest') {
	jQuery("#user").html("Логин: " + user.name);
	if (user.group == 1) {
	    jQuery("#group").html("Администратор");
	} else {
	    jQuery("#group").html("Пользователь");
	}
	jQuery("form#loginbox").hide();
	jQuery("form#Userbox").show();
    } else {
	jQuery("form#loginbox").show();
	jQuery("form#Userbox").hide();
    };
    access2lock(user.name);
    json = 0;
}


updateUserInfo = function() {
    jQuery.getJSON('/userbox', 
		   {},
		   function(json) {
			updateUser(json.user);
                   });
}



access2lock =  function(user) {
	if (user=="guest") {
			   jQuery("#leftcol div input").attr('disabled', true);
		       } else {
		           jQuery("#leftcol div input").attr('disabled', false);
		       }
	change_vis_na();
};

ch_lock = function(res_id, sel_stat) {
    var error = 0;
    if (!sel_stat) {
        var d = prompt("Введите время, на которое вы резервируете данный ресурс: (время вводится в часах), пустое поле - для резервирования на бесконечный срок",2);
	if ( d == null) {
		
	    jQuery("#res-lock-"+res_id).attr('checked', false);
	    jQuery("#res-lock-"+res_id).prop('checked', false);
            return; 
	}
	if (d!="" || d <0 || d=="0") {
	    jQuery("#res-lock-"+res_id).attr('checked', false);
	    jQuery("#res-lock-"+res_id).prop('checked', false);
            return; 
	}
        if (d=="") { d = -1;} else {d=3600*d;};
        jQuery.getJSON("/lock/"+res_id+"/"+d,{},
		   function(data) {
		       if (data.error == 0) {
		           tree();
		       } else {
			   error = 1;
			   jQuery("#res-lock-"+res_id).attr('checked', false);
			   jQuery("#res-lock-"+res_id).prop('checked', false);
			   alert("Данный ресурс уже используется!");
		       }
			data=0;
		   });}
    else {
	jQuery.getJSON("/unlock/"+res_id,{}, 
		function(data) {
			if (data.error == 0) {
		           tree();
		       } else {
			   var s_lock = $('<input>');
    			   s_lock.attr('type', 'checkbox');
    			   s_lock.attr('id', 'res-lock-' + res_id);
    			   s_lock.attr('checked', true);
    			   s_lock.attr('disabled', false );  
    			   s_lock.click(function() {ch_lock(res_id, true);});
			   jQuery("#res-lock-"+res_id).attr('checked', true);
			   jQuery("#res-lock-"+res_id).replaceWith(s_lock); 
			   alert("Данный ресурс занят другим пользователем!");
		       }
			data=0;
		   });
    }
}


var timer = setInterval(tree,30000);

jQuery(document).ready(function() {
    tree();
    updateUserInfo();
    jQuery("#table").css('width',''+document.body.clientWidth);
    jQuery("input#login_button").click(function() {
	login(jQuery("input#username").val(),jQuery("input#authdata").val());
	return false;
    });
    jQuery("input#exit_button").click(function() {
	login("guest","guest");
    });
    jQuery("input#na_button").click(function() {
        visible_na = !visible_na;
	change_vis_na();
    });
});


