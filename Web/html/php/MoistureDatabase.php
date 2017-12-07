<?php
	// Setting header to JSon
	header('Content-type: application/json');

	// Database
	$servername = "localhost";
	$username = "kyph";
	$password = "kyph";
	$database = "SensorsValueDatabase";
	$table = "DailyMeasurement";

	// Get Connection
	try {
		$conn = new PDO("mysql:host=$servername;dbname=$database", $username, $password);
		$conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	}
	catch(PDOException $e) {
		echo "Connection failed: " . $e->getMessage();
	}

	// Query to get data from the table
	$query="SELECT * FROM  MoistureMeasurement";

	// Execute querry
	$result=$conn->query($query);	
	
	// Convert the results into an associative array
	$jsonarray = array();
	$i=0;
	foreach ($conn->query($query) as $row) {
		$sqlarray = array();
		$sqlarray["Time"] = $row['date'];
		$sqlarray["Moisture"] = $row['value'];
		
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