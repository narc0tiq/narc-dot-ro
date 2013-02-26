<?PHP
unset($_ARGS[0]);
$download_path = implode('/', $_ARGS);
$full_path = $conf['download_dir'].'/'.$download_path;
header('X-Download-Path: '.$download_path);

// Hax? No hax here.
if(strpos($download_path, '..') !== false) {
	redirect(PROG_URL.'/404', 302);
}

if(is_dir($full_path)) {
    $md = '';
    $hits = $sql->download_hits('first_update DESC', $download_path);
    foreach($hits as $h) {
        $md .= "  * [{$h['path']}](/download/{$h['path']}): **{$h['hits']}** hits since **{$h['first_update']}**\n";
    }

    if(empty($md)) {
        $md = "Sorry, nobody seems to have been downloading things starting with ${download_path}.";
    }
    else {
        $md = "People have been downloading:\n\n".$md;
    }

    echo header_text($page_uri, 'Downloads for '.$download_path);
    echo Markdown($md);
    echo '</div>';
    echo sidebar_text();
    echo footer_text();
    die();
}

$sql->add_download_hit($download_path);

redirect($conf['download_url'].'/'.$download_path, 302);
?>