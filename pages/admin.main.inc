<?PHP
$users = $sql->fetch_users();
$pages = $sql->fetch_pages();

echo header_text($page_uri, 'Admin');

echo '<h2>Users (change password)</h2>';
echo '<ul>';
foreach($users as $u) {
	echo '	<li><a href="/admin/user/'.$u['id'].'">'.$u['name'].'</a></li>';
}
echo '</ul>';

echo '<h2>Pages (edit)</h2>';
echo '<ul>';
foreach($pages as $p) {
	echo '	<li><a href="/admin/page/'.$p['uri'].'">['.$p['title'].']</a><a href="/'.$p['uri'].'":>('.$p['uri'].')</a></li>';
}
echo '</ul>';

echo '<p><a href="/admin/page">New page</a></p>';

echo '<h2>Download stats</h2>';
$hits = $sql->download_hits('first_update DESC');
echo '<ul>';
foreach($hits as $h) {
	echo '	<li><a href="/download/'.$h['path'].'">'.$h['path'].'</a>: <strong>'.$h['hits'].'</strong> hits since <strong>'.$h['first_update'].'</strong>.</li>';
}
echo '</ul>';

echo '</div>';
echo sidebar_text($page_uri);
echo footer_text();
?>