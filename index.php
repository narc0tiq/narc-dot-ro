<?PHP
header('Content-Type: text/html; charset=UTF-8');
$page_timer_start = microtime();

define('PROG_NAME',  'Narc Dot Ro');
define('PROG_VER',   '3.0');
define('PROG_FULL',  PROG_NAME.'/'.PROG_VER);

define('PATH_BASE',  dirname(__FILE__));
define('PATH_INC',   PATH_BASE.'/inc');
define('PATH_TPL',   PATH_BASE.'/tpl');
define('PATH_PAGES', PATH_BASE.'/pages');

define('PROG_URL',   'http://www.narc.ro');
define('CSS_URL',    PROG_URL.'/css');
define('JS_URL',     PROG_URL.'/js');

define('DEBUG_LOG',  PATH_BASE.'/debug.log');

include(PATH_INC.'/conf.inc');
include(PATH_INC.'/sql.inc');
include(PATH_INC.'/strings.inc');
include(PATH_INC.'/ua.inc');
include(PATH_INC.'/markdown.php');

$sql = new SQLEngine();

if(!$sql->health_check())
	die('Damn, something went horrifically wrong!');

$_ARGS = array();
if(empty($_REQUEST['args']))
	$_ARGS[0] = 'home';
else
	$_ARGS = explode('/', $_REQUEST['args']);

$page_uri = $_ARGS[0];

session_set_cookie_params(24 * 3600);
session_name('narcdotrosessid');
session_start();


if(is_file(PATH_PAGES.'/'.$page_uri.'.inc')) {
	require(PATH_PAGES.'/'.$page_uri.'.inc');
	die();
}

$page = $sql->fetch_page($page_uri);
if(empty($page)) {
	require(PATH_PAGES.'/404.inc');
	die();
}
echo header_text($page_uri, $page['title']);
echo Markdown($page['content']);
echo '<!-- End of the markdown stuff --></div>';

echo sidebar_text($page_uri);
echo footer_text();

?>
