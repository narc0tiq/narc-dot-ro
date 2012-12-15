<?PHP

function redirect($uri,$type=302)
{
	$rr = '';
	switch($type) {
		case 301:   $rr = '301 Moved Permanently'; break;
		default: // just fall-through to:
		case 302:   $rr = '302 Found'; break;
		case 303:   $rr = '303 See Other'; break;
		case 307:   $rr = '307 Temporary Redirect'; break;
	}

	if(headers_sent())
		die('Cannot redirect automatically, please proceed manually to <a href="'.$uri.'">'.$uri.'</a>');

	while(ob_get_level() > 0)
		ob_end_clean();

	header('HTTP/1.1 '.$rr);
	header('Location: '.$uri);
	echo 'If you see this, please proceed manually to <a href="'.$uri.'">'.$uri.'</a>';
	exit;
}
?>