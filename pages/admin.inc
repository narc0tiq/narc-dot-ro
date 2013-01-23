<?PHP
$admin_page = 'main';
if(!empty($_ARGS[1]))
	$admin_page = $_ARGS[1];

if(empty($_SESSION['user'])) {
	require(PATH_PAGES.'/403.inc');
	die();
}

if(!is_file(PATH_PAGES.'/'.$page_uri.'.'.$admin_page.'.inc'))
	die('Damn, that admin page doesn\'t exist.');

require(PATH_PAGES.'/'.$page_uri.'.'.$admin_page.'.inc');

?>
