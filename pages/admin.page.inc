<?PHP
if(!empty($_POST['submit'])) {
	if(empty($_SESSION['user']) || $_SESSION['user'] != $conf['default_admin']) {
		require(PATH_PAGES.'/403.inc');
		die();
	}

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

$logged_in = true;
if(empty($_SESSION['user']) || $_SESSION['user'] != $conf['default_admin']) {
	$logged_in = false;
?>
	<p><strong>Warning</strong>: you are not the administrator, therefore you may not submit a new version of this page. You are free to read its source below, however.</p>
<?PHP
}
?>
<form method="post" id="editpage">
	<label for="uri">URI token: <?PHP echo PROG_URL; ?>/</label><input type="text" name="uri" value="<?PHP echo $uri; ?>" <?PHP if(!$logged_in) { echo 'readonly="readonly"'; } ?> /><br/>
	<label for="title">Page title:</label> <input type="text" name="title" value="<?PHP echo $title; ?>" <?PHP if(!$logged_in) { echo 'readonly="readonly"'; } ?> /><br/>
	<textarea name="content" <?PHP if(!$logged_in) { echo 'readonly="readonly"'; } ?> ><?PHP echo $content; ?></textarea><br/>
	<div style="text-align: center">
	<?PHP if($logged_in) { ?>
		<input class="button" type="submit" name="submit" accesskey="s" />
	<?PHP } ?>
	<input class="button" type="submit" name="preview" value="Preview" accesskey="p" />
	</div>
</form>
<?PHP

echo '</div>';

echo sidebar_text();
echo footer_text();
