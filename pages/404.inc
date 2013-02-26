<?PHP
header('HTTP/1.x 404 Not Found');

echo header_text($page_uri, '404 -- it doesn\'t exist!');
?>
<div style="text-align: center">
	<p>I'm sorry, I just can't seem to find what you're looking for here. Maybe it got deleted,
	maybe it just didn't make the transition to Linode, maybe I'm just having a bad day.</p>

	<p>Have a cute tumbeast <a href="http://theoatmeal.com/comics/state_web_summer#tumblr">courtesy
	of The Oatmeal</a> to make up for it:</p>

	<img src="/img/tb_sign1.png" style="height: 400px" />
</div>


<?PHP
echo '</div>';
echo sidebar_text();
echo footer_text();

?>