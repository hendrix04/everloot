<? 
	include('includes/header.inc');
	/*$toonList = array();
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
		. "and group.userid = " . $_SESSION['user']['userid'];
		
	$groupquery2 = "select * from toongroup where userid = " . $_SESSION['user']['userid'];
	
	$toonList = RunQuery($toonquery, 'toonid');
	$groupList1 = RunQuery($groupquery1);
	$groupList2 = RunQuery($groupquery2);
	
	if (count($groupList1) > 0) {
		foreach ($groupList1 as $group) {
			$toonList[$group['toonid']]['groups'][] = $group['toongroupid'];
		}
	}*/
	
	
//	PrintGroupGrid($_GET['group']);
//	die();
	
?>
<h1>Grid View</h1>
<br /><br/>
<div id="groupdiv" style="width: 1035px;">
	<table class="tablesorter">
		<thead>
			<tr>
				<th style="width: 45px"></th>
				<th style="width: 45px">Crit</th>
				<th style="width: 45px">Head</th>
				<th style="width: 45px">Shoulders</th>
				<th style="width: 45px">Chest</th>
				<th style="width: 45px">Forearms</th>
				<th style="width: 45px">Hands</th>
				<th style="width: 45px">Legs</th>
				<th style="width: 45px">Feet</th>
				<th style="width: 45px">Primary</th>
				<th style="width: 45px">Secondary</th>
				<th style="width: 45px">Ranged</th>
				<th style="width: 45px">Cloak</th>
				<th style="width: 45px">Charm 1</th>
				<th style="width: 45px">Charm 2</th>
				<th style="width: 45px">Left Ear</th>
				<th style="width: 45px">Right Ear</th>
				<th style="width: 45px">Neck</th>
				<th style="width: 45px">Left Finger</th>
				<th style="width: 45px">Right Finger</th>
				<th style="width: 45px">Left Wrist</th>
				<th style="width: 45px">Right Wrist</th>
				<th style="width: 45px">Waist</th>
			</tr>
		</thead>
		<tbody id="grouplist">
			<?
				PrintGroupGrid($_GET['group']);
			?>
		</tbody>
	</table>
</div>

<?
	include('includes/footer.inc');
?>