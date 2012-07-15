<?
	include('includes/header.inc');
	if ($_SESSION['user']['adminyn'] == 'Y') {
		if ($_SERVER['REQUEST_METHOD'] == 'POST') {
			SaveDifficultyGroupPost();
		}
?>
<h1>Phat Lewtz!</h1>
<br />
<br />
<button id="addbutton" type="button" onclick="addzonerow()">Add Zone</button>
<form action="./zones.php" method="POST">
	<table class="tablesorter">
		<thead>
			<tr>
				<th style="width: 25px">del</th>
				<th style="width: 200px">Name</th>
				<th style="width: 200px">Color</th>
			</tr>
		</thead>
		<tbody id="zonelist">
			<? 
				GetZoneColors();
			?>
		</tbody>
	</table>

	<input type="submit" value="Save Zones" />
</form>
<?
	}
	else {
		print "No Access";
	}
	include('includes/footer.inc');
?>