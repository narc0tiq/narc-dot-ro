<?PHP
$confirm_text = 'Confirm?';
if(!empty($confirm_query)) {
	$confirm_text = $confirm_query;
}

echo header_text($page_uri, "Confirm");
?>
<div style="text-align: center">
<p><?PHP echo $confirm_text; ?></p>
<form method="post">
	<input type="submit" name="confirm" value="Yes" accesskey="y" />
	<input type="submit" name="deny" value="No" accesskey="n" />
	<input type="hidden" name="token" value="<?PHP echo $_SESSION['token']; ?>" />
</form></div>
<?PHP
echo '</div>';
echo sidebar_text();
echo footer_text();

?>