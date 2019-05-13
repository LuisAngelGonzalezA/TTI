<?php

error_reporting(E_ALL);
ini_set('display_errors', '1');
include("conexion.php");


$operacion="1";
$nombre=$_GET["nombre"];
$voltajeMax=$_GET["voltajeMax"];
$corriente=$_GET["corriente"];
$isEliminado="0";
$json = array();

$sql = "INSERT INTO panel_solar(id_mecanismo,nombre,voltaje_max, 	corriente_max,isEliminado)
	 values(".$operacion.",'".$nombre."',".$voltajeMax.",".$corriente.",".$isEliminado.")";	
	
	if ($conn->query($sql) === TRUE) {
		$result["nombre"] = '';
		$json['datos'][] = $result;
	    echo json_encode($json);
	} else {
		$result["nombre"] = '';
		$json['datos'][] = $result;
	    echo json_encode($json);
	}	

mysqli_close($conn);

?>
