function findtoon() {
	$("#findtoon").validate();
}

function searchtoons() {
	if ($('#findtoon').valid()) {
		$.post('./ws.php?call=searchtoons', $('#findtoon').serialize(), function(data) {
			$('#toondata').html(data);
			$("#toonsection").show();
			$(".tablesorter").trigger("update");
		}, "html");
	}
}

function addtoons() {
	$.post('./ws.php?call=addtoons', $('#addtoons').serialize(), function(data) {
		//alert("inserted " + data['inserted'] + " characters");
		
		alert ("inserted selected");
	}, "json");
}

function removetoon(element, toon) {
	$.post('./ws.php?call=removetoon', { toonid: toon}, function(data) {
		$(element).closest('tr').remove();
	}, "html");
}

function generatetranslation(element, toon) {
	$.post('./ws.php?call=generatekey', { sonytoonid: toon}, function(data) {
		$(element).closest('td').html('<a href="http://rldn.us/' + data['shortcode'] + '">http://rldn.us/' + data['shortcode'] + '</a>');
	}, "json");
}

function loot() {
	$("#findsonyloot").validate();
}

function searchsonyloot() {
	if ($('#findsonyloot').valid()) {
		$.post('./ws.php?call=searchsonyloot', $('#findsonyloot').serialize(), function(data) {
			$('#lootdata').html(data);
			$("#lootsection").show();
			$(".tablesorter").trigger("update");
		}, "html");
	}
}

function additem(element, sonyitemid) {
	$.post('./ws.php?call=addloot', {sonylootid: sonyitemid}, function(data) {

		$('#lootlist').append($(element).closest('tr').remove());
		$(element).closest('tr').prepend('<td><a href="#" onclick="removeloot(this, \'' + data['inserted'] + '\');return false;">X</a></td>');
		$(element).closest('td').html('<button type="button" onclick="comparegear(\'' + sonyitemid + '\')">Check Upgrades</button>');
		
		$('#listdiv').show();
	}, "json");
}

function comparegear(item) {
	alert("not yet");
}

function removeloot(element, loot) {
	$.post('./ws.php?call=removeloot', { loot: loot}, function(data) {
		$(element).closest('tr').remove();
	}, "json");
}

function addgroup() {
	$.post('./ws.php?call=addgroup', $('#addgroupform').serialize(), function(data) {
		$('#addgroupform > input').val('');
		if (data['value'] == -1) {
			alert('You already have a group called ' + data['name']);
		}
		else {
			$('.groupselect').append($("<option/>", {
		        value: data['value'],
		        text: data['name']
		    }));
			
			$appendstr = '<tr><td><a href="#" onclick="removeloot(this, \'' + data['value'] + '\');return false;">X</a></td><td>' + data['name'] + '</td>';
			$appendstr += '<td><a href="./grid.php?group=' + data['value'] + '">View Grid</a></td></tr>';
			
			$('#grouplist').append($appendstr);
		}

		/*$('#lootlist').append($(element).closest('tr').remove());
		$(element).closest('tr').prepend('<td><a href="#" onclick="removeloot(this, \'' + data['inserted'] + '\');return false;">X</a></td>');
		$(element).closest('td').html('<button type="button" onclick="comparegear(\'' + sonyitemid + '\')">Check Upgrades</button>');*/
		
		$('.groupselect').show();
	}, "json");
}

function removegroup(element, group) {
	$.post('./ws.php?call=removegroup', { group: group}, function(data) {
		$(element).closest('tr').remove();
		$(".groupselect option[value=" + group + "]").remove();
	}, "json");
}

function updatetoongroups() {
	$.post('./ws.php?call=updategroup', $('#updategroupform').serialize(), function(data) {
		alert('Groups Updated');
	}, "json");
}

function addzonerow() {
	$('#zonelist').append('<tr><td>&nbsp;</td><td><input type="text" name="zonename[]"></td><td><input type="text" name="zonecolor[]"></td></tr>');
}

function deletezone(zone) {
	$.post('./ws.php?call=deletezone', { zone: zone }, function() {
		$('#zone_' + zone).remove();
	});
}

function updateitemzone(item) {
	$.post('./ws.php?call=updateitemzone', { sonylootid: item, zone: $('#sony_' + item).val() });
}

$(document).ready(function() {
	var currentpage = document.location.href.substring(document.location.href.lastIndexOf("/")+1);
	
	$(".tablesorter").tablesorter();
	
	switch (currentpage) {
		case "findtoon.php":
			findtoon();
			break;
		case "loot.php":
			loot();
			break;
		default:
			break;
	}
	
	/*if (currentpage == 'checkin.php') {
		//poll server to update Selected every minute
		setInterval(function() {
			$.get('ws.php?call=selectedpoll', function(data) {
				$('#selected').html(data);
			});
		}, 60000);
	}
	
	if (currentpage == 'commander.php') {
		$("#registeredtable").tablesorter();
		$("#unregisteredtable").tablesorter();
		//poll server to update checked in users every minute
		setInterval(function() {
			$.get('ws.php?call=getregistered', function(data) {
				$('#registereddata').html(data);
				$("#registeredtable").trigger("update");
			});
			
			$.get('ws.php?call=getunregistered', function(data) {
				$('#unregistereddata').html(data);
				$("#unregisteredtable").trigger("update");
			});
		}, 60000);
	}*/
	
	/*$.get('./ws.php?call=getloot&item=3290075689', function(data) {

		$('#item1').append('')
		alert(data.item_list[0].displayname);
	}, 'json');*/
	
});