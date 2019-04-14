<?php
$servername = "localhost";
$username = "root";
$password = "root";
$dbname = "tt1Pruebas";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

//$sql = "SELECT * FROM MyGuests Orders LIMIT 15, 10";

$sql = "SELECT * FROM  posicion_servo";


$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
        echo "<div>id: " . $row["id"]. "&#09- Name: " . $row["firstname"] . $row["lastname"]. "-Email :".$row["email"]."Fecha :".$row["reg_date"]."</div><hr><br>";
    }
} else {
    echo "0 results";
}
$conn->close();
?>
