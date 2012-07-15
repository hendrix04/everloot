<?
	include('includes/header.inc');
?>
<h1>Search for your toon!</h1>
<br /><br />
<form id="findtoon">
	Toon Name (min 3 char):
	<br />
	<input type="text" name="name" class="required" minlength="3" />
	<br />
	Server:
	<br />
	<select name="server">
		<?
			foreach ($_SESSION['serverlist'] as $id => $name) {
				print '<option value="' . $id . '">' . $name . "</option>\n";
			}
		?>
	</select>
	<br />
	<button type="button" onclick="searchtoons()">Search</button>
</form>

<br /><br />
<div id="toonsection" style="width: 820px; display:none;">
	<button type="button" onclick="addtoons()">Add Selected</button>
	<form id="addtoons"> 
		<table class="tablesorter">
			<thead>
				<tr>
					<th style="width: 15px">&nbsp;</th>
					<th style="width: 200px">Name</th>
					<th style="width: 200px">Adventure (Level)</th>
					<th style="width: 200px">Tradeskill (Level)</th>
					<th style="width: 200px">Guild</th>
				</tr>
			</thead>
			<tbody id="toondata">
			</tbody>
		</table>
	</form>
</div>

<?
	include('includes/footer.inc');
?>