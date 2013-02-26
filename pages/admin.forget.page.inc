<?PHP
$uri = '';
if(!empty($_ARGS[3])) {
	$uri = $_ARGS[3];
}

if(empty($uri)) {
	die("What, forget nothing? That's a no-op!");
}
$page = $sql->fetch_page_meta($uri);

if(!empty($_POST['confirm']) || !empty($_POST['deny'])) {
	if(empty($_SESSION['token']) or ($_SESSION['token'] != $_POST['token']))
		redirect(PROG_URL.'/'.$page_uri, 302);

	if(!empty($_POST['confirm'])) {
		$sql->delete_page($uri);
	}

	redirect(PROG_URL.'/'.$page_uri, 302);
}

$_SESSION['token'] = strgen(32);
$confirm_query = "Really forget the page titled \"${page['title']}\" at ".PROG_URL."/${page['uri']}?";
require(PATH_PAGES.'/confirm.inc');

?>