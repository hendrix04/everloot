<?
	include('includes/header.inc');
	
	$difficultygroupquery = "select* from difficultygroup";
	
	$difficultygrouplist = RunQuery($difficultygroupquery);
?>
<h1>Phat Lewtz!</h1>
<br />
<br />
<h3>Add item difficulty group</h3>
<br />
<form id="addgroupform">
	Name:
	<br />
	<input type="text" name="name" />
	<br />
	color:
	<br />
	<input type="text" name="color" />
	<br />
	<button type="button" onclick="addgroup()">Add</button>
</form>

	<table class="tablesorter">
		<thead>
			<tr>
				<th style="width: 25px">del</th>
				<th style="width: 200px">Name</th>
				<th style="width: 150px">Color</th>
			</tr>
		</thead>
		<tbody id="lootlist">
			<? 
				foreach ($difficultygrouplist as $group) {
					
				}
			?>
		</tbody>
	</table>
</div>
<?
	include('includes/footer.inc');
?>