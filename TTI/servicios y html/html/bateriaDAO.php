<?php

include("conexion.php");

$operacion=$_POST["sql"];
/*$nombre=$_POST["nombre"];
$voltajeMax=$_POST["voltajeMax"]
$voltajeMin="2.1";//$_POST["voltajeMin"]
$numeroCeldas="1";//$_POST["numeroCeldas"]
$temperatura="10";//$_POST["temperatura"]
$memoria="1";//$_POST["memoria"]

$sql = "INSERT INTO bateria(id_mecanismo,nombre,voltaje_max, voltaje_min,corriente,nu_celdas,temperatura_max,hasMemoria)
 values(".$operacion.",'".$nombre."',".$voltajeMax.",".$voltajeMin.",0.0,".$numeroCeldas.",".$temperatura.",".$memoria.")";
*/ 
if ($conn->query($operacion) === TRUE) {
    echo "New record created successfully.";
} else {
    echo "Error updating record: $sql" . $conn->error;
}


$conn->close();
?>
