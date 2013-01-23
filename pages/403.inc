<?PHP
header('HTTP/1.x 403 Forbidden');

echo header_text($page_uri, '403 -- not allowed!');
?>
<div style="text-align: center">
	<p>I'm sorry, what you're trying to do is forbidden by security policy.</p>

	<img src="/img/padlock.png" style="height: 300px" />

	<p>Please check whether you are logged in and should have permission for this action, 
	and contact the administrator if you feel a mistake has been made.</p>
</div>


<?PHP
echo '</div>';
echo sidebar_text();
echo footer_text();

?>
