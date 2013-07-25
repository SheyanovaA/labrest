function ch_lock(res_id, sel_stat) {
    var error = 0;
    if (!sel_stat) {
        var d = prompt("Введите время, на которое вы резервируете данный ресурс: (время вводится в часах)");
        if (d=="") { d = -1;} else {d=3600*d;};
        jQuery.getJSON("/lock/"+res_id+"/"+d,{},
		   function(data) {
		       if (data.error == 0) {
		           tree();
		       } else {
			   error = 1;
			   jQuery("#res-lock-"+res_id).attr('checked', false);
			   alert("Данный ресурс уже используется!");
		       }
			data=0;
		   });}
    else {
	jQuery.getJSON("/unlock/"+res_id,{},
		   function(data) {
			   tree();
			data=0;
		   });
    }
}

insertBeforeLine = function(old_res, new_res) { //insert new line bafore old
    jQuery('#res-'+old_res.id).prepend(createLine(new_res));
}

var visible_na = true;

createTimeStr = function(seconds) {
    
}

change_vis_na = function() {
    jQuery("#leftcol div:contains('N/A')").css('display', (visible_na) ? "block":"none");
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
	jQuery("#res-temp0-"+new_res.id).css('display', (new_res.startTime == -1) ? "none" : "inline");
	var StartTime = new Date(new_res.startTime*1000);
        var remainTime = new Date(new_res.startTime*1000 + new_res.duration*1000 - new Date() - 1000*3*3600);
    jQuery("#res-time-"+new_res.id).html((new_res.startTime == -1)?"":((new_res.duration == -1)? " c "+ StartTime.toLocaleFormat('%H:%M:%S, (date %d.%m.%y) ' ):" на "+remainTime.toLocaleFormat('%H:%M:%S ')));
    };
    if (old_res.typeName != new_res.typeName) {jQuery("#res-type-name-"+new_res.id).html(" "+new_res.typeName);}
    if (old_res.username != new_res.username) {
	jQuery("#res-temp1-"+new_res.id).css('display', (new_res.startTime == -1) ? "none" : "inline");
	jQuery("#res-user-"+new_res.id).html(" "+ new_res.username);
    }
    
    jQuery("#"+old_res.id)
}

deleteLine = function(old_res) {
    jQuery("#res-"+old_res.id).remove();
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

	


createLine = function(res) {
    var d = $('<div>');
    d.attr('id', 'res-' + res.id);
    d.css('margin-left', '' + (res.layer * 30) + 'px');

    var s_lock = $('<input>');
    s_lock.attr('type', 'checkbox');
    s_lock.attr('id', 'res-lock-' + res.id);
    s_lock.attr('checked', (res.startTime == -1) ? false : true);
    s_lock.attr('disabled', true);
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

    var StartTime = new Date(res.startTime*1000);
    var remainTime = new Date(res.startTime*1000 + res.duration*1000 - new Date() - 1000*3*3600);

    var s_time = $('<span>');
    s_time.attr('id', 'res-time-' + res.id);
    s_time.html((res.startTime == -1)?"":((res.duration == -1)? " c "+ StartTime.toLocaleFormat('%H:%M:%S, (date %d.%m.%y)' ):" на "+remainTime.toLocaleFormat('%H:%M:%S')))
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

var oldJson = null;

// функция постороения дерева ресурсов
tree = function() {
    jQuery.getJSON('/tree',
		   {},
		   function(json) {
		       if (!oldJson) {
		       for (i in json.resources) {
			   var res = json.resources[i];
			   var line = createLine(res);
			   jQuery('#leftcol').append(line);
		       }
		       } else {
			   updateTree(oldJson.resources, json.resources);
		       }
		       access2lock(json.resources[0].logined_user);
		       oldJson = json;
		       json = 0;
		   });
}

access2lock =  function(user) {
	if (user=="guest") {
			   jQuery("#leftcol div input").attr('disabled', true);
		       } else {
		           jQuery("#leftcol div input").attr('disabled', false);
		       }
};

userbox = function() {
    jQuery.getJSON('/userbox', 
		   {},
		   function(json) {
		       if (json.user.name != 'guest') {
			   jQuery("#user").html("Логин: " + json.user.name);
			   if (json.user.group == 1) {
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
		       access2lock(json.user.name);
		       json = 0;
		   }
		  );
}
var timer = setInterval(tree,30000);
jQuery(document).ready(function() {
    tree();
    userbox();
    jQuery("input#login_button").click(function() {
	var user_name = jQuery("input#username").val();
	var user_auth = jQuery("input#authdata").val();
	jQuery.getJSON("/login", {username : user_name, authdata :user_auth},
		       function(json) {
			   if (json.error == 1) { alert ("Неверное имя пользователя или пароль!");}
			else { userbox();};
		       });
	return false;
    });
    jQuery("input#exit_button").click(function() {
	var user_name = "guest";
	var user_auth = "guest";
	jQuery.getJSON("/login", {username : user_name, authdata :user_auth},
		       function(data) {
			userbox();
			tree()
		       });
	return false;
    });
na_button
   jQuery("input#na_button").click(function() {
        visible_na = !visible_na;
	change_vis_na();
    });
});
