<?PHP
$users = $sql->fetch_users();
$pages = $sql->fetch_pages();

echo header_text($page_uri, 'Admin');

$logged_in = true;
if(empty($_SESSION['user']) or ($_SESSION['user'] != $conf['default_admin'])) {
	$logged_in = false;
}

/*
echo '<h2>Users (change password)</h2>';
echo '<ul>';
foreach($users as $u) {
	echo '	<li><a href="/admin/user/'.$u['id'].'">'.$u['name'].'</a></li>';
}
echo '</ul>';
*/

echo "<h2>Pages</h2>\n";
echo "<ul>\n";
foreach($pages as $p) {
	echo '	<li>'.($logged_in?'<a href="/admin/page/'.$p['uri'].'">':'<strong>').'['.$p['title'].']</'.($logged_in?'a':'strong').'>'.
		'<a href="/'.$p['uri'].'">('.$p['uri'].')</a>'.
		($logged_in?'<a class="redlink autohide" href="/admin/forget/page/'.$p['uri'].'">[X]</a>':'').
	"</li>\n";
}
echo "</ul>\n";

if($logged_in) {
	echo "<p><a href=\"/admin/page\">New page</a></p>\n";
}

$hits = $sql->download_hits('first_update DESC');
echo "<h2>Download stats</h2>\n";
echo "<ul>\n";
foreach($hits as $h) {
	echo '	<li><a href="/download/'.$h['path'].'">'.$h['path'].'</a>:'.
		' <strong>'.$h['hits'].'</strong> hits since <strong>'.$h['first_update'].'</strong>. '.
		($logged_in?'<a class="redlink autohide" href="/admin/forget/download/'.$h['path'].'">[X]</a>':'').
		"</li>\n";
}
echo '</ul>';

echo '</div>';
echo sidebar_text($page_uri);
echo footer_text();
?>
