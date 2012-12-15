<?PHP
session_name('narcdotrosessid');
session_start();

if(!empty($_POST['submit'])) {
	if(empty($_POST['content']))
		redirect(PROG_URL.'/', 302);

	if(empty($_SESSION['token']) or ($_SESSION['token'] != $_POST['token']))
		redirect(PROG_URL.'/', 302);

	$mailto = 'contact-form@narc.ro';
	$subj = 'Contact form message from narc.ro';
	$message = $_POST['content'];
	$extra_headers = array('From: Narc.ro Contact Form <noreply@narc.ro>',
		'X-Mailer: '.str_replace(' ', '', PROG_FULL).' (PHP/'.phpversion().')');

	if(!empty($_POST['return_addr'])) {
		$_POST['return_addr'] = str_replace("\n", '', $_POST['return_addr']); // guard against mail headers injection
		$extra_headers[] = 'Reply-To: '.$_POST['return_addr'];
	}

	mail($mailto, $subj, $message, implode("\r\n", $extra_headers));
	redirect(PROG_URL.'/', 303);
}

$_SESSION['token'] = strgen(32);

echo header_text($page_uri, 'Contact Narc');
?>
<p>So, I take it you need to reach me for some reason. Well, I can guarantee this form
will get your message to me... eventually. See, what it does is it sends me an email, and
when I read my mail, I'll be able to see it. Except that I do sometimes go a day or two
without reading my mail. So, you might not get a response quickly. But if that's okay,
then go right ahead!</p>

<form method="post" id="mailform">
	<label for="return_addr">If you want me to email you back, type in your address here (optional):</label><br/>
	<input type="text" name="return_addr" value="" /><br/>
	<label for="content">Now your message:</label><br/>
	<textarea name="content"></textarea><br/>
	<div>When you're done, just hit the Submit button below, or hit Alt+S (or Alt+Shift+S in some browsers).</div>
	<div style="text-align: center"><input type="submit" accesskey="s" name="submit" /></div>
	<input type="hidden" name="token" value="<?PHP echo $_SESSION['token']; ?>" />
</form>
<?
echo '</div>';
echo sidebar_text($page_uri);
echo footer_text();
?>