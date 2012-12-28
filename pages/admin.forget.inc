<?PHP
$forget_what = 'nothing';
if(!empty($_ARGS[2]))
	$forget_what = $_ARGS[2];

if(($forget_what != 'page') && ($forget_what != 'download')) {
	die("Can't forget ${forget_what}!");
}

if(!is_file(PATH_PAGES."/${page_uri}.${admin_page}.${forget_what}.inc"))
	die("Damn, that admin page doesn't exist.");

require(PATH_PAGES."/${page_uri}.${admin_page}.${forget_what}.inc");

?>