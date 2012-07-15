<?

session_start();

//a little checking to make sure we didn't go past index.php without loging in.
if (!isset($_SESSION['user']) && trim($_SERVER['PHP_SELF']) != '/index.php') {
	//if user isn't logged in, we should be on index.php
	die(header('Location: ./index.php'));
}

$conn = mysql_connect("localhost", "eq2anon_user", "42Wh1tm4NStr33T");

if (!$conn) {
	echo "Unable to connect to DB: " . mysql_error();
	exit;
}

if (!mysql_select_db("eq2anon_platform")) {
	echo "Unable to select mydbname: " . mysql_error();
	exit;
}


//This is our login logic
if (trim($_SERVER['PHP_SELF']) == '/index.php') {
	if (isset($_POST['username']) && $_POST['username'] != '' && isset($_POST['password']) && $_POST['password'] != '') {
		$_POST = si($_POST); //this calls si (scrub input) function in footer.inc
		$_POST['username'] = strtolower($_POST['username']);
		
		$_POST['password'] = EncryptPassword($_POST);
		
		$sql = "select userid, username, email, adminyn from user where username = '" . $_POST['username'] . "' and password = '" . $_POST['password'] . "'";
		
		$result = mysql_query($sql);

		if (!$result) {
			echo "Could not successfully run query ($sql) from DB: " . mysql_error();
			exit;
		}
		
		if (mysql_num_rows($result) == 0) {
			//invalid login case
			print "<h1 style=\"color:red;\">Invalid Login Attempt</h1>";
		}
		else {
			//got a login match
			$row = mysql_fetch_assoc($result);
			$_SESSION['user'] = $row;
			mysql_free_result($result);
			
			//store servers in session for easy access
			$result = mysql_query("select serverlistid, servername from serverlist order by servername asc");
			$serverlist = array();
			
			while ($row = mysql_fetch_assoc($result)) {
				$serverlist[$row['serverlistid']] = $row['servername'];
			}
			
			$_SESSION['serverlist'] = $serverlist;
			mysql_free_result($result);
			
			die(header('Location: ./home.php'));
		}
	}
	else {
		//If you come to index without trying to login, wipe session
		if (isset($_SESSION['user'])) {
			unset($_SESSION['user']);
		}
	}
}

//This is where we encrypt the password to what the DB expects
function EncryptPassword($userpass) {
	return hash("sha512", $userpass['username'] . $userpass['password'] . "Th3S4lT");
}


?>