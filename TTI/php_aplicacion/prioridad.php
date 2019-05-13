<?php

error_reporting(E_ALL);
ini_set('display_errors', '1');
include("conexion.php");

$idBateria=$_GET["id_bateria"];
$activo="1";
$json = array();

$sql = "INSERT INTO historial_bateria_panel (id_bateria,fecha,activo,id_panel)
	 values(".$idBateria.",NOW(),".$activo.",13)";

$sqlUpdate="UPDATE historial_bateria_panel SET activo = 0 WHERE id_bateria !='{$idBateria}'";	
	

	$operacion["operacion"] = '7';
	$json['datos'][] = $operacion;

	if ($conn->query($sql) === TRUE) {
		$conn->query($sqlUpdate);
	    echo json_encode($json);
	} else {
		$result["nombre"] = '';
		$json['datos'][] = $result;
		echo $sql;
	    echo json_encode($json);
	}	

mysqli_close($conn);

?>
