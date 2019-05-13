
<?php
$servername = "localhost";
$username = "TT";
$password = "TT";
$dbname = "tornasol";
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
?>
