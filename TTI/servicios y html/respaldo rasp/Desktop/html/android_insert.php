<?php
$servername = "localhost";
$username = "root";
$password = "root";
$dbname = "tt1Pruebas";

$posicion_x=$_POST["x"];
$posicion_y=$_POST["y"];



// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "update posicion_servo set posicion_x = $posicion_x, posicion_y = $posicion_y where unico = 1";


if ($conn->query($sql) === TRUE) {
    echo "New record created successfully. x : ".$posicion_x."  , y :  ".$posicion_y;
} else {
    echo "Error updating record: $sql" . $conn->error;
}


$conn->close();
?>