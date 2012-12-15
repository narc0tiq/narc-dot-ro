<?PHP
if(!empty($_POST['submit'])) {
	if(!$sql->add_page($_POST['uri'], $_POST['title'], $_POST['content']))
		die('Shit, shit, something went wrong!');

	redirect(PROG_URL.'/'.$page_uri, 303);
}

$uri = '';
$title = '';
$content = '';

if(!empty($_ARGS[2])) {
	$page = $sql->fetch_page($_ARGS[2]);
	$uri = $_ARGS[2];
	$title = $page['title'];
	$content = $page['content'];
}

echo header_text($page_uri, 'Edit page');

if(!empty($_POST['preview'])) {
	$uri = $_POST['uri'];
	$title = $_POST['title'];
	$content = $_POST['content'];

	echo '<div id="previewbox">'.Markdown("## $title ##\n$content").'</div>';

}
?>
<form method="post" id="editpage">
	<label for="uri">URI token: <?PHP echo PROG_URL; ?>/</label><input type="text" name="uri" value="<?PHP echo $uri; ?>" /><br/>
	<label for="title">Page title:</label> <input type="text" name="title" value="<?PHP echo $title; ?>" /><br/>
	<textarea name="content"><?PHP echo $content; ?></textarea><br/>
	<div style="text-align: center">
	<input class="button" type="submit" name="submit" accesskey="s" />
	<input class="button" type="submit" name="preview" value="Preview" accesskey="p" />
	</div>
</form>
<?PHP

echo '</div>';

echo sidebar_text();
echo footer_text();