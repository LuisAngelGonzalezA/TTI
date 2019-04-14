<?php

include("conexion.php");

$sql = "select*from sensadoP";


$result = $conn->query($sql);
$datos=array();
if ($result->num_rows >= 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
       $datos[]=$row;

    }
    echo json_encode($datos);
} else {
    echo "0 results";
}

$conn->close();

?> 
