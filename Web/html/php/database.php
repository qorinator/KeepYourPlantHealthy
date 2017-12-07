<?php

$servername = "localhost";
$username = "webuser";
$password = "raspberry";
$database = "example";

try
{
	$conn = new PDO("mysql:host=$servername;dbname=example", $username, $password);
	$conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
}
catch(PDOException $e)
{
	echo "Connection failed: " . $e->getMessage();
}

$query="SELECT * FROM example";
$result = $conn->query($query);

$foodList = array();
$i = 0;
foreach ($conn->query($query) as $row)
{
	$idAndData = array();
	$idAndData["ID"] = $row['id'];
	$idAndData["Data"] = $row['data'];
	$foodList[$i] = $idAndData;
	$i++;
}
$row = $result->rowCount();
$conn = null;
echo json_encode($foodList);
?>
