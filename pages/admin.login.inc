<?PHP
if(!empty($_SESSION['user']))
	unset($_SESSION['user']);

$error = false;

if(!empty($_POST['submit'])) {
	if($sql->login_user($_POST['user'], $_POST['pass'])) {
		$returnto = '';
		if(!empty($_SESSION['returnto_admin']) and $_SESSION['returnto_admin'] != 'login')
			$returnto = $_SESSION['returnto_admin'];

		$_SESSION['user'] = $_POST['user'];

		redirect(PROG_URL.'/'.$page_uri.'/'.$returnto, 303);
	}
	else
		$error = true;
}

echo header_text($page_uri, 'Login');

if(!empty($error))
	echo('<p class="error">Bad login, no cookie.</p>');
?>

<form method="post">
	<label for="user">Username:</label> <input type="text" name="user" /><br/>
	<label for="pass">Password:</label> <input type="password" name="pass" /><br/>
	<input type="submit" name="submit" />
</form>
<?PHP

echo '</div>';

echo sidebar_text();
echo footer_text();
?>