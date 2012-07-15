<?
	include('includes/header.inc');
	
	$_GET = si($_GET);
	
	if (isset($_GET['toon']) && $_GET['toon'] != '') {
		$character = GetCharacter($_GET['toon']);
		print '<h1>' . $character['displayname'] . ' (' . $character['type']['level'] . ')</h1><br><br><br><ul>';
		
		foreach ($character['equipmentslot_list'] as $slot) {
			print '<li><strong>' . $slot['displayname'] . ':</strong>&nbsp;<a href="http://u.eq2wire.com/item/index/' . $slot['item']['id'] . '">' . $slot['item']['displayname'] . '</a>';
		}
	}
	else {
		print "<br><br><br>Please enter a valid url";
		die();
	}
	
	include('includes/footer.inc');
?>