<?PHP

final class SQLEngine {
    /** @var PDO */
	private $db = null;
	private $cache = array();

	public function __construct() {} // does nothing, is not supposed to.

	private function db_connect() {
		global $conf;

		if(!empty($conf['db_dsn']))
		{
			$this->db = new PDO($conf['db_dsn']);

			if(empty($this->db))
				die('Sorry, could not connect to database.');
		}

		if(empty($this->db))
			return false;

		// Activate foreign keys whenever we open the DB -- we really want them.
		$q = 'PRAGMA foreign_keys = ON';
		return $this->query_ignore_result($q);
	}

	private function fetch_tables() {
		if(empty($this->db) and !$this->db_connect())
			die('Unable to connect to database');

		$q = 'SELECT name FROM sqlite_master WHERE type="table"';
		$stmt = $this->db->query($q);

		if(empty($stmt))
			die('Unable to fetch existing table names');

		return $stmt->fetchAll(PDO::FETCH_COLUMN, 0);
	}

	public function table_exists($tablename) {
		if(empty($this->cache['tables']))
			$this->cache['tables'] = $this->fetch_tables();

		if(in_array($tablename, $this->cache['tables']))
			return true;
		else
			return false;
	}

	public function query_ignore_result($query) {
		if(empty($this->db) and !$this->db_connect())
			die('Unable to connect to database');

		$resu = $this->db->query($query);

		if(empty($resu))
			return false;

		return true;
	}

	public function create_users_table()
	{
		$q = 'CREATE TABLE users (
			id INTEGER PRIMARY KEY ASC,
			name TEXT NOT NULL UNIQUE,
			pass TEXT,
			salt TEXT
		)';

		return $this->query_ignore_result($q);
	}

	public function create_pages_table()
	{
		$q = 'CREATE TABLE pages (
			uri TEXT NOT NULL PRIMARY KEY,
			title TEXT NOT NULL,
			content TEXT NOT NULL,
			owner INTEGER DEFAULT NULL REFERENCES users(id)
				ON DELETE SET NULL
				ON UPDATE CASCADE
				DEFERRABLE INITIALLY DEFERRED
		)';

		if(!$this->query_ignore_result($q)) {
			return false;
		}

		$q = 'CREATE INDEX owner_index ON pages(owner)';
		return $this->query_ignore_result($q);
	}

	public function create_download_stats_table() {
		$q = 'CREATE TABLE download_stats (
			path TEXT NOT NULL PRIMARY KEY,
			hits INTEGER NOT NULL DEFAULT 0,
			first_update DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP
		)';

		return $this->query_ignore_result($q);
	}

	public function health_check() {
		if(empty($this->db) and !$this->db_connect())
			die('Unable to connect to database');

		if(!$this->table_exists('users') and !$this->create_users_table())
			return false;

		if(!$this->table_exists('pages') and !$this->create_pages_table())
			return false;

		if(!$this->table_exists('download_stats') and !$this->create_download_stats_table())
			return false;

		return true;
	}

	public function add_page($uri, $title, $text) {
		$q = 'INSERT INTO pages (uri, title, content) VALUES (?, ?, ?)';
		$sth = $this->db->prepare($q);
		$resu = $sth->execute(array($uri, $title, $text));

		if(!empty($resu))
			return true;

		$q = 'UPDATE pages SET title = ?, content = ? WHERE uri = ?';
		$sth = $this->db->prepare($q);

		$resu = $sth->execute(array($title, $text, $uri));

		if(!empty($resu))
			return true;

		die('Shit, adding pages don\'t work, what do?');
	}

	public function fetch_page($uri) {
		$q = 'SELECT uri, title, content FROM pages WHERE uri = ?';
		$sth = $this->db->prepare($q);

		$resu = $sth->execute(array($uri));

		if(empty($resu))
			return false;

		return $sth->fetch(PDO::FETCH_ASSOC);
	}

	public function fetch_page_meta($uri) {
		$q = 'SELECT uri, title FROM pages WHERE uri = ?';
		$sth = $this->db->prepare($q);

		$resu = $sth->execute(array($uri));

		if(empty($resu))
			return false;

		return $sth->fetch(PDO::FETCH_ASSOC);
	}

	public function delete_page($uri) {
		$q = 'DELETE FROM pages WHERE uri = ?';
		$sth = $this->db->prepare($q);

		$resu = $sth->execute(array($uri));

		if(empty($resu))
			return false;

		return true;
	}

	public function add_user($name, $pass, $salt) {
		$hash = crypt($pass, $salt);

		$q = 'INSERT INTO users (name, pass, salt) VALUES (?, ?, ?)';
		$sth = $this->db->prepare($q);
		$resu = $sth->execute(array($name, $hash, $salt));

		if(!empty($resu))
			return true;

		$q = 'UPDATE users SET pass = ?, salt = ? WHERE name = ?';
		$sth = $this->db->prepare($q);

		$resu = $sth->execute(array($hash, $salt, $name));

		if(!empty($resu))
			return true;

		die('Shit, adding users don\'t work, what do?');
	}

	public function login_user($name, $pass) {
		$q = 'SELECT salt FROM users WHERE name = ?';
		$sth = $this->db->prepare($q);

		$resu = $sth->execute(array($name));

		if(empty($resu))
			return false;

		$row = $sth->fetch(PDO::FETCH_ASSOC);
		$salt = $row['salt'];
		$hash = crypt($pass, $salt);

		$q = 'SELECT id, name FROM users WHERE name = ? AND pass = ?';
		$sth = $this->db->prepare($q);

		$resu = $sth->execute(array($name, $hash));

		if(empty($resu))
			return false;

		return $sth->fetch(PDO::FETCH_ASSOC);
	}

	public function fetch_users() {
		$q = 'SELECT id, name FROM users';
		$sth = $this->db->query($q);

		if(empty($sth))
			return array();

		return $sth->fetchAll(PDO::FETCH_ASSOC);
	}

	public function fetch_pages() {
		$q = 'SELECT uri, title FROM pages';
		$sth = $this->db->query($q);

		if(empty($sth))
			return array();

		return $sth->fetchAll(PDO::FETCH_ASSOC);
	}

	public function add_download_hit($path) {
		$q = 'INSERT INTO download_stats (path, hits) VALUES (?, 1)';
		$sth = $this->db->prepare($q);
		$resu = $sth->execute(array($path));

		if(!empty($resu))
			return true;

		$q = 'UPDATE download_stats SET hits = hits + 1 WHERE path = ?';
		$sth = $this->db->prepare($q);

		$resu = $sth->execute(array($path));

		if(!empty($resu))
			return true;
		else
			return false;
	}

	public function download_hits($order, $prefix = '') {
        $args = array();
		$q = 'SELECT path, hits, first_update FROM download_stats';
        if(!empty($prefix)) {
            $q .= ' WHERE path LIKE ?';
            $args[] = $prefix.'%';
        }
        $q .= ' ORDER BY '.$order;

        $sth = $this->db->prepare($q);
		$resu = $sth->execute($args);

		if(empty($resu))
			return array();

		return $sth->fetchAll(PDO::FETCH_ASSOC);
	}

	public function delete_download_hits($path) {
		$q = 'DELETE FROM download_stats WHERE path = ?';
		$sth = $this->db->prepare($q);

		$resu = $sth->execute(array($path));

		if(empty($resu))
			return false;

		return true;
	}
}

?>
