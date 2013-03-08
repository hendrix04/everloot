<?
	include('includes/header.inc');
	
	if ($_SERVER['REQUEST_METHOD'] == 'POST') {
		RegisterUser();
	}
?>
<h1>Coming Soon!!!</h1>
<br />
<form action="register.php" method="post">
	Name:
	<br />
	<input type="text" name="username" class="required" />
	<br />
	Password:
	<br />
	<input type="password" name="password" class="required" />
	<br />
	<br />
	Email:
	<br />
	<input type="text" name="email" class="required" />
	<br />
	one + 2 as text
	<br />
	<input type="text" name="botcheck" class="required" />
	<br />
	Secret Key:
	<br />
	<input type="text" name="secret" class="required" />
	<br />
	<input type="submit" value="Submit" />
</form>

<?
	include('includes/footer.inc');
?>