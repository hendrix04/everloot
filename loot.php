<?
	include('includes/header.inc');
	
	$lootquery = "select lootid, sonylootid from loot where userid = " . $_SESSION['user']['userid'];
	
	$lootlist = RunQuery($lootquery);
?>
<script type="text/javascript">

$(document).ready(function() {
	var  inputbox = $('#' + inputid);
    var code =null;
    inputbox.keypress(function(e)
    {
        code= (e.keyCode ? e.keyCode : e.which);
        if (code == 13 || code == 10) {
        	searchsonyloot();
        	e.preventDefault();
        }
        
    });	
});

</script>
<h1>Phat Lewtz!</h1>
<br />
<br />

<button id="addbutton" type="button" onclick="$(this).hide(); $('#adddiv').slideDown('slow');">Add Items</button>
<div id="adddiv" style="width: 600px; display:none">
	<button type="button" onclick="$('#adddiv').slideUp('slow', function(){$('#addbutton').show();});">Close Add Items</button>
	<br /><br />

	<form id="findsonyloot">
		Item Name (min 3 char):
		<br />
		<input type="text" name="name" class="required" minlength="3" />
		<br /><br />
		<button type="button" onclick="searchsonyloot()">Search</button>
	</form>
	
	<br /><br />
	<div id="lootsection" style="width: 820px; display:none;">
		
		<form id="lootresults"> 
			<table class="tablesorter">
				<thead>
					<tr>
						<th style="width: 200px">Name</th>
						<th style="width: 50px">Level</th>
						<th style="width: 50px">&nbsp;</th>
					</tr>
				</thead>
				<tbody id="lootdata">
				</tbody>
			</table>
		</form>
	</div>
</div>

<?
	if (count($lootlist) > 0) {
		print '<div id="listdiv" style="width: 750px">';
	}
	else {
		print '<div id="listdiv" style="width: 750px; display:none;">';
	}
?>

	<table class="tablesorter">
		<thead>
			<tr>
				<th style="width: 25px">del</th>
				<th style="width: 200px">Name</th>
				<th style="width: 50px">Level</th>
				<th style="width: 150px">Difficulty</th>
				<th style="width: 150px">&nbsp;</th>
			</tr>
		</thead>
		<tbody id="lootlist">
			<? 
				if (count($lootlist) > 0) {
					GetLootFromSony($lootlist);
				}
			?>
		</tbody>
	</table>
</div>
<?
	include('includes/footer.inc');
?>