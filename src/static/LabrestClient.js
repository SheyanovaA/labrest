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
		       if (data.error == 0) {
		           tree();
		       } else {
			   error = 1;
			   jQuery("#res-lock-"+res_id).attr('checked', false);
			   alert("Данный ресурс уже используется!");
		       }
			data=0;
		   });
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
    s_lock.click(function() {ch_lock(res.id, (res.startTime == -1) ? false : true);});
    d.append(s_lock);

    var s_name = $('<span>');
    s_name.attr('id', 'res-name-' + res.id);
    s_name.html(res.name);
    d.append(s_name);

    var s_type_name = $('<span>');
    s_type_name.attr('id', 'res-type-name-' + res.id);
    s_type_name.html(res.typeName);
    d.append(s_type_name);

    var s_discr = $('<span>');
    s_discr.attr('id', 'res-discr-' + res.id);
    s_discr.html(res.discription);
    d.append(s_discr);

    return d;
}

var oldJson = null;

// функция постороения дерева ресурсов
function tree() {
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
			   alert('already tree is created!');
		       }
		       oldJson = json;
		       json = 0;
		   });
}
function userbox() {
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
		       json = 0;
		   }
		  );
}
var timer = setInterval(tree,30000);
jQuery(document).ready(function() {
    userbox();
    tree();
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
});
