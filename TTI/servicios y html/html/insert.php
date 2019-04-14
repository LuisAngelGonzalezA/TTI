<?php
$servername = "localhost";
$username = "TT";
$password = "TT";
$dbname = "tt1Pruebas";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "INSERT INTO posicion_servo values(1,1,1)";

if ($conn->query($sql) === TRUE) {
    $last_id = $conn->insert_id;
    echo "New record created successfully. Last inserted ID is: " . $last_id."<br>".$conn->insert_firstname;
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>
