<?PHP
unset($_ARGS[0]);
$download_path = implode('/', $_ARGS);
$full_path = $conf['download_dir'].'/'.$download_path;

// Hax? No hax here.
if((strpos($download_path, '..') !== false) || (!is_file($full_path))) {
	redirect(PROG_URL.'/404', 302);
}

$sql->add_download_hit($download_path);

redirect($conf['download_url'].'/'.$download_path, 302);
?>