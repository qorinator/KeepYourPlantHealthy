<?php
	// Setting header to JSon
	header('Content-type: application/json');

	// Database
	$servername = "localhost";
	$username = "kyph";
	$password = "kyph";
	$database = "SensorsValueDatabase";

	// Get Connection
	try {
		$conn = new PDO("mysql:host=$servername;dbname=$database", $username, $password);
		$conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	}
	catch(PDOException $e) {
		echo "Connection failed: " . $e->getMessage();
	}

	// Query to get data from the table
	$query="SELECT * FROM temperature";

	// Execute querry
	$result=$conn->query($query);	
	
	// Convert the results into an associative array
	$jsonarray = array();
	$i=0;
	foreach ($conn->query($query) as $row) {
		$sqlarray = array();
		$sqlarray["Date"] = $row['date'];
		$sqlarray["Average"] = $row['average'];
		$sqlarray["Minimum"] = $row['minimum'];
		$sqlarray["Maximum"] = $row['maximum'];		
		
		$jsonarray[$i] = $sqlarray;
		$i++;
	}

	// Free resources
	$result->closeCursor();
	$conn = null;

	// Output the return value of JSon encode using 
	// the echo function
	echo json_encode($jsonarray);
?>