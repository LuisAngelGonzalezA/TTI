
<?php
$servername = "localhost";
$username = "root2";
$password = "1234";
$dbname = "tornasol";
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
?>
