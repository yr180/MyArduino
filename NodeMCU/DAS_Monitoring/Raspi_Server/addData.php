<?php
   	include("connectDB.php");

   	$link=Connection();

	$temp1=$_GET["temp1"];

	$query = "INSERT INTO `templog` (`temperature`) VALUES ($temp1)";

   	mysql_query($query,$link);
	mysql_close($link);

   	header("Location: index.php");
?>

