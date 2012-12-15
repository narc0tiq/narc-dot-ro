<?PHP
session_name('narcdotrosessid');
session_start();

$admin_page = 'main';
if(!empty($_ARGS[1]))
	$admin_page = $_ARGS[1];

if($admin_page != 'login') {
	if(empty($_SESSION['user'])) {
		$_SESSION['returnto_admin'] = $admin_page;
		redirect(PROG_URL.'/'.$page_uri.'/login', 307);
	}

	if(!empty($_SESSION['returnto_admin']))
		unset($_SESSION['returnto_admin']);
}

if(!is_file(PATH_PAGES.'/'.$page_uri.'.'.$admin_page.'.inc'))
	die('Damn, that admin page doesn\'t exist.');

require(PATH_PAGES.'/'.$page_uri.'.'.$admin_page.'.inc');

?>