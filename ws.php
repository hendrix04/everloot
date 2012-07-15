<?
	require('includes/functions.inc');
	require('includes/loginstuff.inc');
	
	//scrub input
	$_POST = si($_POST);
	
	switch($_GET['call']) {
		case 'searchtoons':
			$server = mysql_result(mysql_query("SELECT queryname FROM serverlist where serverlistid = " . $_POST['server']),0);

			SearchSonyForToons($_POST['name'], $server);
			break;
		case 'searchsonyloot':
			SearchSonyForLoot($_POST['name']);
			break;
		case 'addtoons':
			$sql = "insert into toon (userid, sonytoonid) values ";
			foreach ($_POST['toonstoadd'] as $sonytoonid) {
				$sql .= "('" . $_SESSION['user']['userid'] . "', '" . $sonytoonid . "'),";
			}
			$sql = substr_replace($sql ,"",-1);
			$result = mysql_query($sql);
			$affected = mysql_affected_rows();

			print json_encode(array('inserted' => $affected));
			break;
		case 'removetoon':
			if (isset($_POST['toonid']) && $_POST['toonid'] != '') {
				$sql = "delete from toon where toonid = " . $_POST['toonid'] . " and userid = " . $_SESSION['user']['userid'];
				
				$result = mysql_query($sql);
				$affected = mysql_affected_rows();
	
				print json_encode(array('inserted' => $affected));
			}
			break;
		case 'addloot':
			if (isset($_POST['sonylootid']) && $_POST['sonylootid'] != '') {
				$firstcheck = mysql_query('select * from loot where sonylootid = "' . $_POST['sonylootid'] . '" and userid = ' . $_SESSION['user']['userid']);
				
				if (mysql_num_rows($firstcheck) == 0) {
					mysql_query('insert into loot (userid, sonylootid) values ("' . $_SESSION['user']['userid'] . '", "' . $_POST['sonylootid'] . '")') or die(mysql_error());
				}
				
				$result = mysql_result(mysql_query('SELECT lootid FROM loot where sonylootid = "' . $_POST['sonylootid'] . '" and userid = "' . $_SESSION['user']['userid'] . '"'),0);
	
				print json_encode(array('inserted' => $result));
			}
			break;
		case 'removeloot':
			if (isset($_POST['loot']) && $_POST['loot'] != '') {
				$sql = "delete from loot where lootid = " . $_POST['loot'] . " and userid = " . $_SESSION['user']['userid'];
				
				$result = mysql_query($sql);
				$affected = mysql_affected_rows();
	
				print json_encode(array('inserted' => $affected));
			}
			break;
		case 'addgroup':
			if (isset($_POST['name']) && $_POST['name'] != '') {
				$firstcheck = mysql_query('select * from toongroup where name = "' . $_POST['name'] . '" and userid = ' . $_SESSION['user']['userid']);
				
				if (mysql_num_rows($firstcheck) == 0) {
					mysql_query('insert into toongroup (userid, name) values ("' . $_SESSION['user']['userid'] . '", "' . $_POST['name'] . '")') or die(mysql_error());
					
					$result = mysql_result(mysql_query('SELECT toongroupid FROM toongroup where name = "' . $_POST['name'] . '" and userid = "' . $_SESSION['user']['userid'] . '"'),0);
					
					$output = array(
						'name' => $_POST['name'],
						'value' => $result,
					);
				}
				else {
					$output = array(
						'name' => $_POST['name'],
						'value' => '-1',
					);
				}
			}
			else {
				$output = array(
						'name' => $_POST['name'],
						'value' => '-1',
					);
			}
			
			print json_encode($output);
			break;
		case 'removegroup':
			if (isset($_POST['group']) && $_POST['group'] != '') {
				$sql1 = "delete from toongroup where toongroupid = " . $_POST['group'] . " and userid = " . $_SESSION['user']['userid'];
				$sql2 = "delete from grouplink where toongroupid = " . $_POST['group'] . " and userid = " . $_SESSION['user']['userid'];
				
				$result = mysql_query($sql1);
				$result = mysql_query($sql2);
				$affected = mysql_affected_rows();
	
				print json_encode(array('inserted' => $affected));
			}
			break;
		case 'updategroup':
			if (isset($_POST)) {
				$sql = "delete from grouplink where userid = " . $_SESSION['user']['userid'];
				$query = "insert into grouplink (toonid, toongroupid, userid) values ";
				
				foreach ($_POST as $key => $toongroupidarray) {
					if (strpos($key, 'group_') !== false) {
						foreach ($toongroupidarray as $toongroupid) {
							$query .= '("' . substr($key, 6) . '", "' . $toongroupid . '", "' . $_SESSION['user']['userid'] . '"), ';
						}
					}
				}
			}
			mysql_query($sql);
			mysql_query(substr($query, 0, -2));
			break;
		case 'generatekey':
			if (isset($_POST['sonytoonid']) && $_POST['sonytoonid'] != '') {
				$hash = md5($_POST['sonytoonid']);
				$inky = 0;
				$foundyn = 'N';
				$shortcode = '';
				
				$firstcheck = mysql_query('select * from translation where sonytoonid = "' . $_POST['sonytoonid'] . '"');
				
				if (mysql_num_rows($firstcheck) == 0) {
					while (++$inky <= 32 && $foundyn == 'N') {
						$shortcode = substr($hash, 0, $inky);
						$result = mysql_query('select * from translation where shortcode = "' . $shortcode . '"');
						
						if (mysql_num_rows($result) == 0) {
							$foundyn = 'Y';
							mysql_query('insert into translation (shortcode, sonytoonid) values ("' . $shortcode . '", "' . $_POST['sonytoonid'] . '")');
							
						}
						
						mysql_free_result($result);
					}
				}
				else {
					$temp = $row = mysql_fetch_assoc($firstcheck);
					$shortcode = $temp['shortcode'];
					$foundyn = 'Y';
				}

				mysql_free_result($firstcheck);

				if ($foundyn == 'N') {
					//error, no valid url
				}
				else {
					print json_encode(array('shortcode' => $shortcode));
				}
			}
			break;
		case 'deletezone':
			mysql_query("delete from difficultygroup where difficultygroupid = " . $_POST['zone']);
			break;
		case 'getloot':
			print file_get_contents('http://data.soe.com/json/get/eq2/item/' . $_GET['item']);
			break;
		case 'updateitemzone':
			$sql  = 'insert into lootdifficulty (sonylootid, difficultygroupid) ';
			$sql .= 'values ("' . $_POST['sonylootid'] . '", "' . $_POST['zone']; 
			$sql .= '") on duplicate key update difficultygroupid = "' . $_POST['zone'] . '"';
			
			mysql_query($sql);
			break;
		default:
			//if we were actually error reporting, this is
			//where i would bitch at someone for trying to
			//hack the site.
			break;
	}

?>