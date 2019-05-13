<?php

include("conexion.php");

$id=$_GET["id_bateria"];
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

$sql = "UPDATE bateria SET id_mecanismo='{$operacion}', nombre='{$nombre}', voltaje_max='{$voltajeMax}', voltaje_min='{$voltajeMin}', corriente='{$corriente}', nu_celdas='{$numeroCeldas}', temperatura_max='{$temperatura}', hasMemoria='{$memoria}', isEliminado='{$isEliminado}' WHERE id_bateria='{$id}'";

	
	if (mysqli_query($conn,$sql) === TRUE) {
		$result["operacion"] = '2';
		$json['datos'][] = $result;
	    echo json_encode($json);
	} else {
		echo $conn->error;
	}	

mysqli_close($conn);

?>
