<?
	include('includes/header.inc');
	$toonList = array();
	$groupList1 = array();
	$groupList2 = array();
	
	$toonquery = "select toon.toonid, toon.sonytoonid, translation.shortcode "
		. "from toon left join translation "
		. "on toon.sonytoonid = translation.sonytoonid "
		. "where toon.userid = " . $_SESSION['user']['userid'];
		
	$groupquery1 = "select toongroup.toongroupid, toongroup.name, grouplink.toonid "
		. "from toongroup left join grouplink "
		. "on toongroup.toongroupid = grouplink.toongroupid "
		. "where toongroup.userid = " . $_SESSION['user']['userid'];
		
	/*$groupquery1 =  "select group.groupid, group.name, grouplink.toonid "
		. "from group, grouplink "
		. "where group.groupid = grouplink.groupid "
		. "and group.userid = " . $_SESSION['user']['userid'];*/
		
	$groupquery2 = "select * from toongroup where userid = " . $_SESSION['user']['userid'];
	
	$toonList = RunQuery($toonquery, 'toonid');
	$groupList1 = RunQuery($groupquery1);
	$groupList2 = RunQuery($groupquery2);
	
	if (count($toonList) > 0 && count($groupList1) > 0) {
		foreach ($groupList1 as $group) {
			$toonList[$group['toonid']]['groups'][] = $group['toongroupid'];
		}
	}
	
	/*print "<pre>";
	print_r($toonList);
	print "</pre>";*/
	
?>
<div id="item1"></div>
<h1>List of possible toons</h1>
<br />
<br />
<input type="checkbox" name="grouptoggle" id="grouptoggle" onclick="$('#groupdiv').toggle()"> <label for="grouptoggle">Add/View Groups (access grid view)</label>
<div id="groupdiv" style="width: 180px; display: none;">
	<h3>Add a group</h3>
	<br />
	<form id="addgroupform">
		Name:
		<br />
		<input type="text" name="name" />
		<br />
		<button type="button" onclick="addgroup()">Add</button>
	</form>
	<table class="tablesorter">
		<thead>
			<tr>
				<th style="width: 30px">del</th>
				<th style="width: 150px">Name</th>
				<th style="width: 150px">Grid</th>
			</tr>
		</thead>
		<tbody id="grouplist">
			<?
				if (count($groupList2) > 0) {
					foreach ($groupList2 as $group) {
						print '<tr><td><a href="#" onclick="removegroup(this, \'' . $group['toongroupid'] . '\');return false;">X</a></td>';
						print '<td>' . $group['name'] . '</td><td><a href="./grid.php?group=' . $group['toongroupid'] . '">View Grid</a></td></tr>';
					}
				}
			?>
		</tbody>
	</table>
</div>

<br />
<div style="width: 990px">
	<button type="button" style="float: right;" onclick="updatetoongroups()">Update Groups</button>
	<br />
	<form id="updategroupform">
	<?
		if (count($toonList) > 0) {
			print '<table class="tablesorter">'
				.'<thead>'
				.	'<tr>'
				.		'<th style="width: 30px">del</th>'
				.		'<th style="width: 100px">Name</th>'
				.		'<th style="width: 125px">Adventure (Level)</th>'
				.		'<th style="width: 125px">Tradeskill (Level)</th>'
				.		'<th style="width: 200px">Guild</th>'
				.		'<th style="width: 100px">Server</th>'
				.		'<th style="width: 200px">Groups</th>'
				.		'<th style="width: 110px">Anonymizer URL</th>'
				.	'</tr>'
				.'</thead>'
				.'<tbody>';
					GetMyToonsFromSony($toonList, $groupList2);
			print	'</tbody>' 
			.'</table>';
		}
		else {
			print '<a href="./findtoon.php">Add a toon</a>';
		}
	?>
	</form>
</div>
<?
	include('includes/footer.inc');
?>