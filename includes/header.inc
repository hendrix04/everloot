<?
	require('includes/functions.inc');
	require('includes/loginstuff.inc');
?>
<html>
	<head>
		<title>Everloot</title>
		<link rel="stylesheet" media="screen" type="text/css" href="./style/style.css" />
		<script type="text/javascript" src="./js/jquery.js"></script>
		<script type="text/javascript" src="./js/javascript.js"></script>
		<script type="text/javascript" src="./js/jquery.validation.js"></script>
		<script type="text/javascript" src="./js/jquery.tablesorter.js"></script>
		<script type="text/javascript" src="./js/popup.js"></script>
	</head>
	<body>
	<?php 
		if (isset($_SESSION['user']) && trim($_SERVER['PHP_SELF']) != '/index.php') {
			$menu = '<a href="./home.php">Home</a> | <a href="./findtoon.php">Add Toon</a> | <a href="./loot.php">Loot</a> ';
			
			if ($_SESSION['user']['adminyn'] == 'Y') {
				$menu .= '| <a href="./zones.php">Zones</a> '; 
			}
			
			$menu .= '| <a href="./">Logout</a>';
			print $menu;
		}
		else {
			print '<a href="#" onclick="alert(\'Not yet, sorry\'); return false;">Register</a>';
		}
	?>
		<br />