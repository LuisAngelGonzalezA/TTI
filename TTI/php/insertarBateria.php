<?php

error_reporting(E_ALL);
ini_set('display_errors', '1');
include("conexion.php");


$operacion="1";
$nombre=$_GET["nombre"];
$voltajeMax=$_GET["voltajeMax"];
$voltajeMin=$_GET["voltajeMin"];
$corriente=$_GET["corriente"];
$numeroCeldas=$_GET["numeroCeldas"];
$temperatura=$_GET["temperatura"];
$memoria=$_GET["memoria"];
$isEliminado="0";
$json = array();

$sql = "INSERT INTO bateria(id_mecanismo,nombre,voltaje_max, 	voltaje_min,corriente,nu_celdas,temperatura_max,hasMemoria,isEliminado)
	 values(".$operacion.",'".$nombre."',".$voltajeMax.",".$voltajeMin.",".$corriente.","	.$numeroCeldas.",".$temperatura.",".$memoria.",".$isEliminado.")";	
	
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
