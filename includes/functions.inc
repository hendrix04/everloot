<?php

$itemholder = '';

function si($input) {
	if (is_array($input)) {
		foreach ($input as $key => $value) {
			$output[$key] = si($value);
		}
	}
	else {
		$output = trim(htmlentities(strip_tags($input)));
	}
	
	return $output;
}

function RunQuery($sql, $key='N') {
	$result = mysql_query($sql) or die(mysql_error());
	$ouput = array();
	
	if (mysql_num_rows($result) > 0) {
		while($row = mysql_fetch_assoc($result)) {
			if ($key == 'N') {
				$output[] = $row;
			}
			else {
				$output[$row[$key]] = $row;
			}
		}
	}
	
	mysql_free_result($result);
	return $output;
}

function GetSonyData($string) {
	$json = file_get_contents($string);
	$data = json_decode($json, true);
	return $data;
}

function SearchSonyForToons($name, $server) {
	$output = array();
	$querystring = 
		"http://data.soe.com/json/get/eq2/character/?name.first=^" . 
		str_replace(' ', '%20', ucwords($name)) . 
		"&locationdata.world=/" . 
		$server . 
		"/&c:limit=20&c:show=id,name.first,guild.name,type,tradeskills,locationdata.world";

	$toondata = GetSonyData($querystring);
	
	if ($toondata['returned'] > 0) {
		PrintToons($toondata['character_list'], "Y");
	}
}

function GetMyToonsFromSony($list, $group) {
	$output = array();
	$querystring = "http://data.soe.com/json/get/eq2/character/?c:limit=200&c:show=id,name.first,guild.name,type,tradeskills,locationdata.world";

	$mungedlist = array();
	foreach($list as $character) {
		$querystring .= "&id[]=" . $character['sonytoonid'];
		$mungedlist[$character['sonytoonid']] = array(
			'mytoonid' => $character['toonid'],
			'shortcode' => (isset($character['shortcode'])) ? $character['shortcode'] : '',
			'groups' => (isset($character['groups'])) ? $character['groups'] : array()
		);
	}
	
	$toondata = GetSonyData($querystring);

	if ($toondata['returned'] > 0) {
		foreach ($toondata['character_list'] as $key => $toon) {
			$toondata['character_list'][$key]['mytoonid'] = $mungedlist[$toon['id']]['mytoonid'];
			$toondata['character_list'][$key]['shortcode'] = $mungedlist[$toon['id']]['shortcode'];
			$toondata['character_list'][$key]['groups'] = $mungedlist[$toon['id']]['groups'];
		}

		PrintToons($toondata['character_list'], "N", $group);
	}
}

function PrintToons($list, $search, $groups=array()) {
	$idlist = array();
	
	foreach ($list as $key => $toon) {
		if (!isset($toon['guild'])) {
			$list[$key]['guild']['name'] = '';
		}
		
		foreach ($toon['tradeskills'] as $class => $level) {
			$list[$key]['tradeskills']['class'] = $class;
			$list[$key]['tradeskills']['level'] = $level['level'];
		}
		$idlist[] = $toon['id'];
	}
		
	$outputstring = '';
	if (is_array($list)) {
		foreach ($list as $toon) {
			$outputstring .= '<tr>';
			if ($search == "Y") {
				$outputstring .= '<td><input name="toonstoadd[]" type="checkbox" value="' . $toon['id'] . '" /></td>';
			}
			else {
				$outputstring .= '<td><a href="#" onclick="removetoon(this, \'' . $toon['mytoonid'] . '\');return false;">X</a></td>';
			}
			
			$outputstring .= '<td><a href="./character.php?toon=' . $toon['id'] . '">' . $toon['name']['first'] . '</a></td><td>' . $toon['type']['class'] . ' (' . $toon['type']['level'] . ')' .
			'</td><td>' . ucwords($toon['tradeskills']['class']) . ' (' . $toon['tradeskills']['level'] . ')</td><td>' . $toon['guild']['name'] . '</td>';
			
			if ($search == "N") {
				$outputstring .= '<td>' . $toon['locationdata']['world'] . '</td><td>';
				$outputstring .= '<select class="groupselect" name="group_' . $toon['mytoonid'] . '[]" multiple="multiple"';
				
				if (count($groups) < 1) {
					$outputstring .= ' style="display: none;">';
				}
				else {
					$outputstring .= '>';
					
					foreach ($groups as $value) {
						$outputstring .= '<option value="' . $value['toongroupid'] . '"';
						
						if (isset($toon['groups']) && in_array($value['toongroupid'], $toon['groups'])) {
							$outputstring .= ' selected';
						}
						
						$outputstring .= '>' . $value['name'] . '</option>';
					}
				}
					$outputstring .= '</select></td><td>';
				if (isset($toon['shortcode']) && $toon['shortcode'] != '') {
					$outputstring .= '<a href="http://rldn.us/' . $toon['shortcode'] . '">http://rldn.us/' . $toon['shortcode'] . '</a>';
				}
				else {
					$outputstring .= '<button type="button" onclick="generatetranslation(this, \'' . $toon['id'] . '\');">Generate Anonymizer</button>';
				}
				
				$outputstring .= '</td>';
			}
			$outputstring .= '</tr>';
		}
		print $outputstring;
	}
}

function GetCharacter($sonytoonid) {
	$characterquery = "http://data.soe.com/json/get/eq2/character/" . $sonytoonid;
		
	$characterdata = GetSonyData($characterquery);
	
	$itemquery = "http://data.soe.com/json/get/eq2/item/?c:limit=50&c:show=id,displayname";
	
	foreach ($characterdata['character_list'][0]['equipmentslot_list'] as $key => $slot) {
		$itemquery .= "&id[]=" . $slot['item']['id'];
		$characterdata['character_list'][0]['equipmentslot_list'][$slot['item']['id']] = $slot;
		unset($characterdata['character_list'][0]['equipmentslot_list'][$key]);
	}
	
	
	
	$itemdata = GetSonyData($itemquery);
	
	foreach ($itemdata['item_list'] as $item) {
		$characterdata['character_list'][0]['equipmentslot_list'][$item['id']]['item']['displayname'] = $item['displayname'];
	}
	
	return $characterdata['character_list'][0];
}

function SearchSonyForLoot($name) {
	$output = array();
	
	$querystring = 
		"http://data.soe.com/json/get/eq2/item/?displayname_lower=/" . 
		str_replace(' ', '%20', strtolower($name)) . 
		"/&c:show=id,displayname,itemlevel";
	
	if ($_SESSION['user']['adminyn'] == 'Y') {
		$querystring .= '&c:limit=400';
	}
	else {
		$querystring .= '&c:limit=20';
	}

	$lootdata = GetSonyData($querystring);
	
	if ($lootdata['returned'] > 0) {
		PrintLoot($lootdata['item_list'], "Y");
	}
}

function GetLootFromSony($list) {
	$output = array();
	$querystring = "http://data.soe.com/json/get/eq2/item/?c:limit=200&c:show=id,displayname,itemlevel";

	$mungedlist = array();
	foreach($list as $loot) {
		$querystring .= "&id[]=" . $loot['sonylootid'];
		$mungedlist[$loot['sonylootid']] = array(
			'mylootid' => $loot['lootid'],
		);
	}
	
	$lootdata = GetSonyData($querystring);
	$coloridlist = array();

	if ($lootdata['returned'] > 0) {
		foreach ($lootdata['item_list'] as $key => $loot) {
			$lootdata['item_list'][$key]['mylootid'] = $mungedlist[$loot['id']]['mylootid'];
			$coloridlist[] = $loot['id'];
		}
		
		$itemcolors = array();
		$itemcolors = GetItemColors($coloridlist);
		
		// I hate to loop through this again, but I don't see any other way...
		foreach ($lootdata['item_list'] as $key => $loot) {
			if (isset($itemcolors[$loot['id']]['difficultygroupid']))
			$lootdata['item_list'][$key]['difficultygroupid'] = $itemcolors[$loot['id']]['difficultygroupid'];
		}

		PrintLoot($lootdata['item_list'], "N");
	}
}

function PrintLoot($list, $search) {
	
	$difficultysql = 'select * from difficultygroup';
	
	$difficultygroups = RunQuery($difficultysql);
	
	$outputstring = '';
	
	foreach ($list as $item) {
		$outputstring .= '<tr>';
		
		if ($search == "N") {
			$outputstring .= '<td><a href="#" onclick="removeloot(this, \'' . $item['mylootid'] . '\');return false;">X</a></td>';
		}
		
		$outputstring .= '<td><a href="http://eq2.zam.com/wiki/EQ2_Item:' . str_replace(' ', '_', $item['displayname']) . '">' . $item['displayname'] . '</a></td><td>' . $item['itemlevel'] . '</td>';
		
		$outputstring .='<td><select id="sony_' . $item['id'] . '" name="' . $item['id'] . '" onchange="updateitemzone(\'' . $item['id'] . '\')">';
		
		$outputstring .= '<option value="">Select</option>';
		
		foreach ($difficultygroups as $group) {
			$outputstring .= '<option value="' . $group['difficultygroupid'] . '"';
			
			if (isset($item['difficultygroupid']) && $item['difficultygroupid'] == $group['difficultygroupid']) {
				$outputstring .= ' selected';
			}
			
			$outputstring .= '>' . $group['name'] . '</option>';
		}
		
		$outputstring .= '</select>';
		
		if ($search == "N") {
			$outputstring .= '<td><button type="button" onclick="comparegear(\'' . $item['id'] . '\')">Check Upgrades</button></td>';
		}
		else {
			$outputstring .= '<td><button type="button" onclick="additem(this, \'' . $item['id'] . '\')">Add</button></td>';
		}
		$outputstring .= '</tr>';
	}
	print $outputstring;
}

function CreateLootDiv($inputarray, $hover=false) {
	$itemdivs = array();
	$inky = 0;
	
	if ($hover) {
		$lootarray = $inputarray;	
	}
	else {
		$lootarray = $inputarray['item_list'];
	} 
	
	foreach ($lootarray as $item) {
		$itemdivs[$inky] = '<div id="item_' . $item['id'] . '" class="itemd_surround itemd_hoverdiv"';
		
		if (!$hover) {
			$itemdivs[$inky] .= ' style="left: 0px; top: 35px; display: block;"';
		}
		
		$itemdivs[$inky] .= '><div class="itemd_name">' . $item['displayname'] . '</div>';
		$itemdivs[$inky] .= '<div class="itemd_icon"><img src="http://data.soe.com/img/eq2/icons/' . $item['iconid'] . '/item/"></div>';
		$itemdivs[$inky] .= '<div style="color: #ff939d;" class="itemd_tier">' . $item['tier'] . '</div>';
		$itemdivs[$inky] .= '<div class="itemd_flags">';
		
		foreach ($item['flags'] as $name => $value) {
			if ($value['value'] == 1) {
				$itemdivs[$inky] .= $name . '&nbsp; ';
			}
		}
		
		$itemdivs[$inky] .= '</div><div class="itemd_green">';
		
		$modlist = array();
		
		foreach ($item['modifiers'] as $modifier) {
			switch ($modifier['type']) {
				case 'ac':
				case 'attribute':
				case 'skill':
					$modlist[$modifier['type']] .= '+' . $modifier['value'] . '&nbsp;' . $modifier['displayname'] . '&nbsp; ';
					break;
				case 'modifyproperty':
					$modlist[$modifier['type']] .= round($modifier['value'], 1) . '%&nbsp;' . $modifier['displayname'] . '<br>';
					break;
					case 'normalizedmod':
						$modlist[$modifier['normalizedmod']] .= '+' . $modifier['value'] . '&nbsp;Ability Mod<br>';
					break;
				default:
					print "REPORT THIS ITEM";
					break;
			}
		}
		
		if (isset($modlist['attribute'])) {
			$itemdivs[$inky] .= $modlist['attribute'];
		}
		
		$itemdivs[$inky] .= '</div><div class="itemd_green">';
		
		if (isset($modlist['ac'])) {
			$itemdivs[$inky] .= $modlist['ac'];
		}
		
		$itemdivs[$inky] .= '</div><div class="itemd_green">';
		
		if (isset($modlist['skill'])) {
			$itemdivs[$inky] .= $modlist['skill'];
		}
		
		$itemdivs[$inky] .= '</div><div class="itemd_blue">';
		
		if (isset($modlist['modifyproperty'])) {
			$itemdivs[$inky] .= $modlist['modifyproperty'];
		}
		
		$itemdivs[$inky] .= '</div><div class="itemd_blue"></div><div class="itemd_blue">';
		
		if (isset($modlist['normalizedmod'])) {
			$itemdivs[$inky] .= $modlist['normalizedmod'];
		}
		
		$itemdivs[$inky] .= '</div><div class="itemd_blue">';
		
		if (isset($item['adornment_list'])) {
			foreach ($item['adornment_list'] as $adornlist) {
				$itemdivs[$inky] .= $adornlist['name'] . '<br>';
			}
		}
		
		$itemdivs[$inky] .= '</div><br>';
		
		if ($item['type'] == 'Armor' && $item['slot_list']['name'] != 'Charm') {
			$itemdivs[$inky] .= '<div style="width: 150px; float: left; color: white;">' . $item['typeinfo']['knowledgedesc']  . ' (' . $item['slot_list'][0]['name'] . ')</div>';
			$itemdivs[$inky] .= '<div class="ui-helper-clearfix"></div>';
			$itemdivs[$inky] .= '<div style="width: 80px; float: left;">Mitigation</div>';
			$itemdivs[$inky] .= '<div style="width: 100px; float: left; color: white;">' . $item['typeinfo']['maxarmorclass'] . '</div>';
			$itemdivs[$inky] .= '<div class="ui-helper-clearfix"></div>';
		}
		else {
			if ($item['type'] == 'Weapon') {
				$itemdivs[$inky] .= '<div style="width: 150px; float: left; color: white;">' . $item['typeinfo']['knowledgedesc'] . '</div>';
				$itemdivs[$inky] .= '<div class="ui-helper-clearfix"></div>';
			}
			
			$itemdivs[$inky] .= '<div style="width: 80px; float: left;">Slots</div>	<div style="width: 100px; float: left; color: white;">';
			
			$slots = array();
			
			foreach ($item['slot_list'] as $slot) {
				$slots[] = $slot['name'];
			}
			
			$itemdivs[$inky] .= implode(', ', $slots);
			
			$itemdivs[$inky] .= '</div><div class="ui-helper-clearfix"></div>';
			
			if ($item['type'] == 'Weapon') {
				
				$itemdivs[$inky] .= '<div style="width: 80px; float: left;">Damage</div>';
				$itemdivs[$inky] .= '<div style="width: 80px; float: left; color: white;">' . $item['typeinfo']['minbasedamage'] . ' - ' . $item['typeinfo']['maxbasedamage'] . '</div>';
				$itemdivs[$inky] .= '<div style="width: 100px; float: left; color: white;">(' . round($item['typeinfo']['damagerating'], 2) . ' Rating)</div>';
				$itemdivs[$inky] .= '<div class="ui-helper-clearfix"></div>';
				
				$itemdivs[$inky] .= '<div style="width: 80px; float: left;">Delay</div>';
				$itemdivs[$inky] .= '<div style="width: 100px; float: left; color: white;">' . round($item['typeinfo']['delay'], 1) . ' Seconds</div>';
				$itemdivs[$inky] .= '<div class="ui-helper-clearfix"></div>';
			}
		}
		
		$itemdivs[$inky] .= '<div style="width: 80px; float: left;">Level</div>';
		$itemdivs[$inky] .= '<div style="width: 150px; float: left;" class="itemd_green">' . $item['leveltouse'] . '</div>';
		$itemdivs[$inky] .= '<div class="ui-helper-clearfix"></div><div class="itemd_green">';
		
		$classes = array();
			
		foreach ($item['typeinfo']['classes'] as $class) {
			$slots[] = $slot['displayname'];
		}
			
		$itemdivs[$inky] .= implode(', ', $classes);
		
		$itemdivs[$inky] .= '</div><br>';
		
		if (isset($item['effect_list'])) {
			$itemdivs[$inky] .= '<div class="itemd_effects">Effects:</div><div style="font-weight: normal;">';
			
			foreach ($item['effect_list'] as $effect) {
				$deeky = $effect['indentation'];
				while ($deeky > 0) {
					if ($deeky == 1) {
						$itemdivs[$inky] .= '•&nbsp;';
					}
					else {
						$itemdivs[$inky] .= '&nbsp;&nbsp;';
					}
					
					$deeky--;
				}
				
				if (substr($effect['description'], 0, 1) == '\\') {
					$itemdivs[$inky] .= '<span style="color: ' . substr($effect['description'], 1, 7) . '">' . substr($effect['description'], 8, -3) . '</span>';
				}
				else {
					$itemdivs[$inky] .= $effect['description'];
				}
				
				$itemdivs[$inky] .= '<br>';
			}
			$itemdivs[$inky] .= '</div>';
		}

		if (isset($item['adornmentslot_list'])) {
			$itemdivs[$inky] .= '<div class="itemd_adornslots">Adornment Slots:</div><div style="font-weight: normal;">';
			
			$adornslotlist = array();
			
			foreach ($item['adornmentslot_list'] as $slot) {
				$adornslotlist[] = '<span style="color: ' . $slot['color'] . '">' . $slot['color'] . '</span>';
			}
			
			$itemdivs[$inky] .= implode(', ', $adornslotlist) . '</div>';
		}
		
		$itemdivs[$inky] .= '</div>';
		
		$inky++;
	}
	//print_r($itemdivs);
	return $itemdivs;
}

function PrintGroupGrid($toongroupid) {

	$toonquery = "select sonytoonid from toon where toonid in (select toonid "
		. "from grouplink  "
		. 'where toongroupid = "' . $toongroupid . '" '
		. "and userid = " . $_SESSION['user']['userid'] . ")";
		
	$toonlist = array();
	$result = mysql_query($toonquery) or die(mysql_error());
	
	if (mysql_num_rows($result) > 0) {
		while($row = mysql_fetch_assoc($result)) {
			$toonlist[] = $row['sonytoonid'];
		}
	}
	
	mysql_free_result($result);
	
	if (count($toonlist)) {
		$toonstring = "http://data.soe.com/json/get/eq2/character/?c:limit=200&c:show=id,name.first,equipmentslot_list,stats.ability,stats.combat,stats.defense,stats.weapon";
		$itemstring = "http://data.soe.com/json/get/eq2/item/?c:limit=400&id[]=";
	
		foreach($toonlist as $character) {
			$toonstring .= "&id[]=" . $character;
		}
		
		$toondata = GetSonyData($toonstring);

		
		if ($toondata['returned'] > 0) {
			$sonyarray = array();
			$inky = 0;	
			
			foreach ($toondata['character_list'] as $toonkey => $toon) {
				foreach ($toon['equipmentslot_list'] as $slotkey => $slot) {
					switch ($slot['name']) {
						case 'ammo':
						case 'food':
						case 'drink':
							break;
						default:
							//$sonyarray[$toonkey] = $sonyarray[$toonkey] . '&id[]=' . $slot['item']['id'];
							if (count($sonyarray[$inky]) >= 400) {
								$inky++;
							} 
							
							if (!in_array_m($slot['item']['id'], $sonyarray)) {
								$sonyarray[$inky][] = $slot['item']['id'];
							}
							
							$toondata['character_list'][$toonkey]['equipmentslot_list'][$slot['name']] = $slot;
							break;
					}
						
					unset($toondata['character_list'][$toonkey]['equipmentslot_list'][$slotkey]);
				}
			}
				
			$itemlistforcolor = array();
			$itemlist = array();
			
			
			foreach ($sonyarray as $itemarray) {
				$tempitem = GetSonyData($itemstring . implode('&id[]=', $itemarray));
				if ($tempitem['returned'] > 0) {
					foreach ($tempitem['item_list'] as $key => $item) {
						$itemlist[$item['id']] = $item;
						$itemlistforcolor[] = $item['id'];
					}
				}
			}
			
			$colorlist = array();
			$colorlist = GetItemColors($itemlistforcolor);
			
			foreach($toondata['character_list'] as $toon) {
				print '<tr><td>' . $toon['name']['first'] . '</td><td></td>';
				
				$slotlist = array(
					'head',
					'shoulders',
					'chest',
					'forearms',
					'hands',
					'legs',
					'feet',
					'primary',
					'secondary',
					'ranged',
					'cloak',
					'activate1',
					'activate2',
					'ears',
					'ears2',
					'neck',
					'left_ring',
					'right_ring',
					'left_wrist',
					'right_wrist',
					'waist',
				);
				
				foreach ($slotlist as $slot) {
					
					$itemid = $toon['equipmentslot_list'][$slot]['item']['id'];

					print '<td';
					
					if (isset($colorlist[$itemid]['color'])) {
						print ' style="background-color: #' . $colorlist[$itemid]['color'] . ';"';
					}
					
					print '>';
					
					if (isset($itemlist[$itemid]['displayname'])) {
						print '<a href="./item.php?loot=' . $itemid . '" onmouseover="ShowContent(\'item_' . $itemid . '\');return true;" onmouseout="HideContent(\'item_' . $itemid . '\');return true;">' . $itemlist[$itemid]['displayname'] . '</a>';
					}
					
					print '</td>';
					
				}
				
				print '</tr>';
			}
			
			global $itemholder;
			
			$itemholder = CreateLootDiv($itemlist, true);
		}

	}
}

/*
 * Takes an array of sony item IDs
 */

function GetItemColors($sonylootid) {
		
	$colorlist = array();
	$colorquery = "select lootdifficulty.sonylootid, difficultygroup.color, difficultygroup.name, difficultygroup.difficultygroupid "
	. "from lootdifficulty left join difficultygroup "
	. "on lootdifficulty.difficultygroupid = difficultygroup.difficultygroupid "
	. "where lootdifficulty.sonylootid in (" . implode(',', $sonylootid) . ")";
	
	$result = mysql_query($colorquery) or die(mysql_error());
		
	if (mysql_num_rows($result) > 0) {
		while($row = mysql_fetch_assoc($result)) {
			$colorlist[$row['sonylootid']] = $row;
		}
	}
		
	mysql_free_result($result);
	
	return $colorlist;
}

function GetZoneColors() {
	$selectsql = 'select * from difficultygroup';
	
	$difficultygroups = RunQuery($selectsql);
	
	$outputstring = '';
	
	foreach ($difficultygroups as $group) {
		$outputstring .= '<tr id="zone_' . $group['difficultygroupid'] . '"><td><a href="#" onclick="deletezone(' . $group['difficultygroupid'] . '); return false;">X</a></td>';
		$outputstring .= '<td>' . $group['name'] . '</td>';
		$outputstring .= '<td><input name="' . $group['difficultygroupid'] . '" value="' . $group['color'] . '"></td>';
	}
	
	print $outputstring;
}

function SaveDifficultyGroupPost() {
	$_POST = si($_POST);
	
	if (isset($_POST['zonename']) && is_array($_POST['zonecolor'])) {
		$sql = "insert into difficultygroup (name, color) values ";
		foreach ($_POST['zonename'] as $key => $value) {
			if (substr($_POST['zonecolor'][$key], 0, 1) == '#') {
				$_POST['zonecolor'][$key] = substr($_POST['zonecolor'][$key], 0);
			}
			
			$sql .= "('" . $value . "', '" . $_POST['zonecolor'][$key] . "'),";
		}
		$sql = substr_replace($sql ,"",-1);
		$result = mysql_query($sql);
	}
	
	foreach ($_POST as $key => $value) {
		if ($key != 'zonename' || $key != 'zonecolor') {
			
			if (substr($value, 0, 1) == '#') {
				$value = substr($value, 1);
			}
			
			mysql_query('update difficultygroup set color="' . $value . '" where difficultygroupid = ' . $key);
		}
	}
}

function in_array_m($needle, $haystack) {
	foreach ($haystack as $value) {
		if (in_array($needle, $value)) {
			return true;
		}
	}	
	return false;
}
?>