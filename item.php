<?
	include('includes/header.inc');
	
	$_GET = si($_GET);
	
	if (isset($_GET['loot']) && $_GET['loot'] != '') {
		$lootdivs = CreateLootDiv(GetSonyData("http://data.soe.com/json/get/eq2/item/?c:limit=1&id[]=" . $_GET['loot']));
		
		print_r($lootdivs[0]);
	}
	else {
		print "<br><br><br>Please enter a valid url";
		die();
	}

	include('includes/footer.inc');
?>