function lock(res_id) {
    var d = prompt("Введите время, на которое вы резервируете данный ресурс: (время вводится в часах)");
    if (d=="") { d = -1;} else {d=3600*d;};
    jQuery.getJSON("/lock/"+res_id+"/"+d,{},
		   function(data) {
		       tree();
		   });
}
// функция постороения дерева ресурсов
function tree() {
    jQuery.getJSON('/tree',
		   {},
		   function(json) {
		       jQuery('#leftcol').html("");
		       jQuery('#leftcol').append("<h4>Доступные ресурсы:</h4>"); 
		       jQuery('#leftcol').append("<ul id=-1>");
		       for (i in json.resources) {
			   var res = json.resources[i];
			   var startTime = new Date(res.startTime*1000);
			   jQuery("ul#"+res.parentId).append("<li><ul id="+res.id+"><span><div>" + res.name + " " + res.typeName + " " + res.description);
			   if (res.logined_user=="guest") {
			       if (res.startTime ==-1) {
				   jQuery("ul#"+res.id+" span div").append(" [_]");
			       } else {
				   jQuery("ul#"+res.id+" span div").append(" [x] использует: "+ res.username + ",  с " + startTime.toLocaleFormat('%H:%M:%S %d.%m.%y,')); 
			       }} else {
				   if (res.startTime ==-1) {
				       jQuery("ul#"+res.id+" span div").append("<a onclick=lock("+res.id+")> [_] </a>");
				   } else {
				       jQuery("ul#"+res.id+" span div").append("<a id="+res.id+" href=/unlock/"+res.id+"> [x] </a> использует: "+ res.username + ",  с " + startTime.toLocaleFormat('%H:%M:%S %d.%m.%y,'));  
				   }}
			   if (res.duration != -1 && res.startTime !=-1) {
			       var remain =new Date(new Date(res.startTime*1000+res.duration*1000) - new Date() -new Date(3600*3*1000));
			       jQuery("ul#"+res.id+" span div").append("осталось: " + (remain.toLocaleFormat('%H:%M:%S')));
			   }
		       };
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
    $$("input#login_button").click(function() {
	var user_name = $$("input#username").val();
	var user_auth = $$("input#authdata").val();
	jQuery.getJSON("/login", {username : user_name, authdata :user_auth},
		       function(data) {
			   userbox();
			   tree();
		       });
	return false;
    });
    $$("input#exit_button").click(function() {
	var user_name = "guest";
	var user_auth = "guest";
	jQuery.getJSON("/login", {username : user_name, authdata :user_auth},
		       function(data) {
			   userbox();
			   tree();
		       });
	return false;
    });
});