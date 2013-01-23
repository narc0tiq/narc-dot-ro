<?PHP
if(empty($_ARGS[1])) {
    header('HTTP/1.x 400 Bad Request');
    die('Nothing specified for the ajax endpoint to do!');
}

switch(strtolower($_ARGS[1])) {
    default:
        header('HTTP/1.x 400 Bad Request');
        die('No idea how to do "'.$_ARGS[1].'"!');
    break;
    case "login":
        verify_login();
    break;
    case "logout":
        teardown_session();
    break;
}


function verify_login() {
	if(empty($_POST['assertion'])) {
		header('HTTP/1.x 400 Bad Request');
		die('You failed to provide a login assertion!');
	}

	$url = 'https://verifier.login.persona.org/verify';
	$assert = filter_input(INPUT_POST, 'assertion', FILTER_UNSAFE_RAW, FILTER_FLAG_STRIP_LOW|FILTER_FLAG_STRIP_HIGH);
	$postdata = http_build_query(array(
		'assertion' => $assert,
		'audience' => 'http://www.narc.ro:80'
	));

	$ch = curl_init();
	$options = array(
		CURLOPT_URL => $url,
		CURLOPT_RETURNTRANSFER => true,
		CURLOPT_POST => 2,
		CURLOPT_POSTFIELDS => $postdata
	);
	curl_setopt_array($ch, $options);

	$result = curl_exec($ch);
	curl_close($ch);

	$verify = json_decode($result);

	if($verify === null) {
		header('HTTP/1.x 500 Internal Server Error');
		echo 'Persona authentication errored!';
		teardown_session();
		exit();
	}
	elseif($verify->status == 'failure') {
		header('HTTP/1.x 403 Forbidden');
		echo 'Persona reports authentication failure: '.$verify->reason;
		teardown_session();
		exit();
	}

	$_SESSION['user'] = $verify->email;
	echo 'Logged in '.$_SESSION['user'];
}

function teardown_session() {
	unset($_SESSION['user']);
}

?>
