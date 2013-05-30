<?PHP

function header_text($page_name, $page_title) {
	$toplink = '<a href="/">'.PROG_NAME.'</a>';
	if($page_name == 'home')
		$toplink = PROG_NAME;

	return '<!DOCTYPE html>
<html>
<head>
	<link href="http://fonts.googleapis.com/css?family=PT+Sans+Caption" rel="stylesheet" type="text/css">
	<title>'.$page_title.' - '.PROG_NAME.'</title>
	<meta http-equiv="Content-Type" content="text/html;charset=utf-8" />
	<link rel="stylesheet" type="text/css" href="'.CSS_URL.'/page-style.css" />
	<link rel="stylesheet" type="text/css" href="'.CSS_URL.'/persona-buttons.css" />
	<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.8.3/jquery.min.js"></script>
	<script src="https://login.persona.org/include.js"></script>
	<script type="text/javascript">
	$(function() { // $().ready() handler
		// Support for Mozilla Persona
		var signinLink = document.getElementById("signin");
		if (signinLink) {
			signinLink.onclick = function(event) {
				navigator.id.request({
					siteName:"Narc Dot Ro",
					oncancel: function() { window.location = signinLink.href; }
				});
				event.preventDefault(); event.stopPropagation(); };
		}

		var signoutLink = document.getElementById("signout");
		if (signoutLink) {
			signoutLink.onclick = function(event) { navigator.id.logout(); event.preventDefault(); event.stopPropagation(); };
		}

		var currentUser = '.(empty($_SESSION['user'])?'null':'"'.$_SESSION['user'].'"').';
		var csrf_token = "'.$_SESSION['csrf_token'].'";

		navigator.id.watch({loggedInUser: currentUser,
			onlogin: function(assertion) {
				$.ajax({
					type: "POST",
					url: "/ajax-endpoint/login",
					data: {assertion: assertion, csrf: csrf_token},
					success: function(res, status, xhr) { window.location.reload(); },
					error: function(xhr, status, err) { alert("Login failure: " + err); }
				});
			},
			onlogout: function() {
				$.ajax({
					type: "POST",
					url: "/ajax-endpoint/logout",
					success: function(res, status, xhr) { window.location.reload(); },
					error: function(xhr, status, err) { alert("Logout failure: " + err); }
				});
			}
		});
	});
	</script>
</head>
<body>
	<div id="header">
		<h1 id="top">'.$toplink.'</h1>
	</div>
	<div id="column-mask">
		<div id="column-wrapper">
			<div id="content">
				<h2 id="title">'.$page_title.'</h2>
<!-- The stuff after this is no longer header stuff -->
';
}

function sidebar_text($page_name = '') {
	return '
<div id="sidebar">
	<p>Navigation</p>
	<ul>
		<li>'.($page_name == 'home' ? '<b>Home</b>' : '<a href="/">Home</a>').'</li>
		<li>'.($page_name == 'about' ? '<b>About Me</b>' : '<a href="/about">About Me</a>').'</li>
		<li>'.($page_name == 'contact' ? '<b>Contact Form</b>' : '<a href="/contact">Contact Form</a>').'</li>
		<li>'.($page_name == 'articles' ? '<b>Articles and Rants</b>' : '<a href="/articles">Articles and Rants</a>').'</li>
		<li>'.($page_name == 'projects' ? '<b>Projects</b>' : '<a href="/projects">Projects</a>').'</li>
		<li>'.($page_name == 'help-wanted' ? '<b>Help Wanted!</b>' : '<a href="/help-wanted">Help Wanted!</a>').'</li>
	</ul>

	<p>Related sites</p>
	<ul>
		<li><a href="http://wiki.narc.ro/">NarcWiki</a></li>
	</ul>

	<p>Internal stuff</p>
	<ul>
		<li>'.(empty($_SESSION['user'])?login_link():logout_text()).'</li>
		<li>'.($page_name == 'admin' ? '<b>Admin</b>' : '<a href="/admin">Admin</a>').'</li>
	</ul>
</div>
';
}

function login_link() {
	return '<a href="/admin/login" id="signin" class="persona-button dark"><span>Log In</span></a>';
}

function logout_text() {
	return 'Logged in as <b>'.$_SESSION['user'].'</b>.<br/><a href="/admin/logout" id="signout" class="persona-button dark"><span>Log Out</span></a>';
}

function footer_text() {
	global $page_timer_start;
	$page_timer_end = microtime();
	$pt_start = explode(' ', $page_timer_start);
	$pt_start = $pt_start[1].substr($pt_start[0], 1);
	$pt_stop = explode(' ', $page_timer_end);
	$pt_stop = $pt_stop[1].substr($pt_stop[0], 1);
	$page_timer = round(($pt_stop - $pt_start) * 1000, 2);

	return "

		</div> <!-- id=\"column-wrapper\" -->
	</div> <!-- id=\"column-mask\" -->
	<div id=\"footer\">
		<p>In completely unrelated news, it took ${page_timer} ms to display this page (more or less).</p>
	</div>

</body></html>
";
}

function strgen($len=8) {
	$chars = array('A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
		'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i',
		'j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2',
		'3','4','5','6','7','8','9','0');

	$len += 0;

	$resu = "";
	for ($i = 0; $i < $len; $i++) {
		$resu .= $chars[rand(0, count($chars)-1)];
	}

	return $resu;
}

?>
