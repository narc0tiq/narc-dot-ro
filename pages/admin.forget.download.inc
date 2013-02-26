<?PHP
unset($_ARGS[0]);
unset($_ARGS[1]);
unset($_ARGS[2]);
$download_path = implode('/', $_ARGS);

if(empty($download_path)) {
	die("What, forget nothing? That's a no-op!");
}

if(!empty($_POST['confirm']) || !empty($_POST['deny'])) {
	if(empty($_SESSION['token']) or ($_SESSION['token'] != $_POST['token']))
		redirect(PROG_URL.'/'.$page_uri, 302);

	if(!empty($_POST['confirm'])) {
		$sql->delete_download_hits($download_path);
	}

	redirect(PROG_URL.'/'.$page_uri, 302);
}

$_SESSION['token'] = strgen(32);
$confirm_query = "Really forget the download stats for \"${download_path}\"?";
require(PATH_PAGES.'/confirm.inc');

?>