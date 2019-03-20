<?php
$servername = "localhost";
$username = "TT";
$password = "TT";
$dbname = "tt1Pruebas";

$posicion_x=$_POST["x"];
$posicion_y=$_POST["y"];



// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "insert into posicion_panel(posicion_x,posicion_y) values(".$posicion_x.",".$posicion_y")";


if ($conn->query($sql) === TRUE) {
    echo "New record created successfully. x : ".$posicion_x."  , y :  ".$posicion_y;
} else {
    echo "Error updating record: $sql" . $conn->error;
}


$conn->close();
?>
